/**
 * Mizuchi integrator: land a matched function into src/ and shrink asm/rom.s.
 * Called from mizuchi after a perfect objdiff match.
 */
import { readFileSync, writeFileSync, mkdirSync, existsSync } from 'node:fs';
import { dirname, join, basename } from 'node:path';

export async function integrate({ functionName, matchedC, projectRoot }) {
  const srcDir = join(projectRoot, 'src');
  const module = pickModule(functionName);
  const srcPath = join(srcDir, `${module}.c`);

  mkdirSync(srcDir, { recursive: true });

  const banner = `// @ 0x${functionName.replace(/^sub_/, '')} — integrated by Mizuchi\n`;
  const body = matchedC.trim() + '\n';

  if (!existsSync(srcPath)) {
    writeFileSync(srcPath, banner + body);
  } else {
    const existing = readFileSync(srcPath, 'utf8');
    if (!existing.includes(functionName)) {
      writeFileSync(srcPath, existing.trimEnd() + '\n\n' + banner + body);
    }
  }

  noteIntegration(projectRoot, functionName, module);
  return { srcPath, module };
}

function pickModule(name) {
  const hex = name.replace(/^sub_/, '');
  const bank = hex.slice(0, 2);
  return `bank_${bank}`;
}

function noteIntegration(projectRoot, functionName, module) {
  const logPath = join(projectRoot, 'docs', 'decomp-status.md');
  const line = `- [x] \`${functionName}\` → \`src/${module}.c\` (Mizuchi)\n`;
  let text = '';
  if (existsSync(logPath)) {
    text = readFileSync(logPath, 'utf8');
  } else {
    text = '# Decompilation status\n\n## Matched functions\n\n';
  }
  if (!text.includes(functionName)) {
    writeFileSync(logPath, text + line);
  }
}
