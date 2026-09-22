#!/usr/bin/env python3
"""Single entry point for the ROM-to-project pipeline.

This is a dispatch layer over the existing tools, not a reimplementation. Each
stage is independently runnable; the CLI just names the sequence and keeps the
vocabulary consistent.

    decomp setup <rom>       install the ROM and bootstrap the toolchain
    decomp analyze           rebuild analysis/*.json (functions, xrefs, structs, systems)
    decomp decompile         deterministic match pass + one AI packet
    decomp rename            symbol layer: list, set, apply, generate
    decomp document          regenerate docs/systems/ and docs/functions/
    decomp verify            match_function + make compare
    decomp status            lifecycle tier table

Run via `./decomp <stage>` at the repo root, or `make analyze` etc.
"""

from __future__ import annotations

import argparse
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TOOLS = ROOT / "tools" / "decomp"


def _run(tool: str, *args: str) -> int:
    """Run a sibling tool as a subprocess so its own CLI stays authoritative."""
    cmd = [sys.executable, str(TOOLS / tool), *args]
    print(f"$ {' '.join(cmd[1:])}", flush=True)
    return subprocess.call(cmd, cwd=ROOT)


def _make(*targets: str) -> int:
    cmd = ["make", *targets]
    print(f"$ {' '.join(cmd)}", flush=True)
    return subprocess.call(cmd, cwd=ROOT)


def cmd_setup(args: argparse.Namespace) -> int:
    rom = Path(args.rom)
    target = ROOT / "baserom.gba"
    if rom.resolve() != target.resolve():
        if not rom.is_file():
            print(f"ROM not found: {rom}", file=sys.stderr)
            return 2
        print(f"copying {rom} -> {target.name}")
        target.write_bytes(rom.read_bytes())
    code = _make("compare")
    if code != 0:
        return code
    return _run("generate_asm.py", "--force") if not (ROOT / "asm" / "nonmatchings").is_dir() else 0


def cmd_analyze(_: argparse.Namespace) -> int:
    return _run("analyze.py")


def cmd_decompile(args: argparse.Namespace) -> int:
    code = _run("script_first.py")
    if code != 0:
        return code
    if args.no_packet:
        return 0
    return _run("agent_packet.py", "--next")


def cmd_rename(args: argparse.Namespace) -> int:
    passthrough = list(args.rename_args or [])
    if not passthrough:
        passthrough = ["list"]
    return _run("symbols.py", *passthrough)


def cmd_document(_: argparse.Namespace) -> int:
    return _run("document.py")


def cmd_verify(args: argparse.Namespace) -> int:
    if args.function:
        code = _run("match_function.py", *args.function)
        if code != 0:
            return code
    return _make("compare")


def cmd_status(_: argparse.Namespace) -> int:
    code = _run("tier.py")
    if code != 0:
        return code
    return _run("progress.py")


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="stage")

    p_setup = sub.add_parser("setup", help="install the ROM and bootstrap")
    p_setup.add_argument("rom", help="path to the retail ROM")

    sub.add_parser("analyze", help="rebuild analysis/*.json")
    p_dec = sub.add_parser("decompile", help="deterministic pass + one packet")
    p_dec.add_argument("--no-packet", action="store_true")

    p_ren = sub.add_parser("rename", help="symbol layer")
    p_ren.add_argument(
        "rename_args",
        nargs="*",
        help="passed to symbols.py, e.g. `set sub_0802B8BC --symbol Name`",
    )

    sub.add_parser("document", help="regenerate docs/systems and docs/functions")
    p_ver = sub.add_parser("verify", help="match_function + make compare")
    p_ver.add_argument("function", nargs="*", help="optional function and path")
    sub.add_parser("status", help="lifecycle tier table")

    args = ap.parse_args()
    if not args.stage:
        ap.print_help()
        return 0
    return {
        "setup": cmd_setup,
        "analyze": cmd_analyze,
        "decompile": cmd_decompile,
        "rename": cmd_rename,
        "document": cmd_document,
        "verify": cmd_verify,
        "status": cmd_status,
    }[args.stage](args)


if __name__ == "__main__":
    raise SystemExit(main())
