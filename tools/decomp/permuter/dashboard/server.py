"""Local web dashboard for decomp-permuter runs."""

from __future__ import annotations

import json
import mimetypes
import socket
import threading
import webbrowser
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
from typing import Callable

STATIC_DIR = Path(__file__).resolve().parent / "static"
DEFAULT_PORT = 8765


class DashboardServer:
    def __init__(
        self,
        *,
        state_path: Path,
        get_state: Callable[[], dict],
        host: str = "127.0.0.1",
        port: int = DEFAULT_PORT,
    ) -> None:
        self.state_path = state_path
        self.get_state = get_state
        self.host = host
        self.port = port
        self._httpd: ThreadingHTTPServer | None = None
        self._thread: threading.Thread | None = None

    @property
    def url(self) -> str:
        return f"http://{self.host}:{self.port}/"

    def start(self, *, open_browser: bool = False) -> None:
        handler = _make_handler(self.get_state, STATIC_DIR)
        self._httpd = ThreadingHTTPServer((self.host, self.port), handler)
        self._thread = threading.Thread(target=self._httpd.serve_forever, daemon=True)
        self._thread.start()
        if open_browser:
            webbrowser.open(self.url)

    def stop(self) -> None:
        if self._httpd is not None:
            self._httpd.shutdown()
            self._httpd.server_close()
            self._httpd = None


def pick_port(host: str, preferred: int) -> int:
    for port in (preferred, preferred + 1, preferred + 2, 0):
        try:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
                sock.bind((host, port))
                return sock.getsockname()[1]
        except OSError:
            continue
    return preferred


def _make_handler(get_state: Callable[[], dict], static_dir: Path):
    class Handler(BaseHTTPRequestHandler):
        def log_message(self, _format: str, *_args) -> None:
            return

        def _send_json(self, payload: dict, *, status: int = 200) -> None:
            body = json.dumps(payload).encode("utf-8")
            self.send_response(status)
            self.send_header("Content-Type", "application/json")
            self.send_header("Content-Length", str(len(body)))
            self.send_header("Cache-Control", "no-store")
            self.end_headers()
            self.wfile.write(body)

        def _send_file(self, path: Path) -> None:
            if not path.is_file():
                self.send_error(404)
                return
            data = path.read_bytes()
            ctype = mimetypes.guess_type(str(path))[0] or "application/octet-stream"
            self.send_response(200)
            self.send_header("Content-Type", ctype)
            self.send_header("Content-Length", str(len(data)))
            self.end_headers()
            self.wfile.write(data)

        def do_GET(self) -> None:
            if self.path in ("/", "/index.html"):
                self._send_file(static_dir / "index.html")
                return
            if self.path == "/api/state":
                self._send_json(get_state())
                return
            if self.path.startswith("/static/"):
                rel = self.path[len("/static/") :]
                self._send_file(static_dir / rel)
                return
            self.send_error(404)

    return Handler
