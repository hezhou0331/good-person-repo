// build.mjs — Markdown -> HTML(+服务端KaTeX) -> A4横向五列 PDF
import { readFileSync, writeFileSync, mkdirSync } from "node:fs";
import { fileURLToPath, pathToFileURL } from "node:url";
import { dirname, join } from "node:path";
import MarkdownIt from "markdown-it";
import katexPlugin from "@vscode/markdown-it-katex";
import markPlugin from "markdown-it-mark";
import { chromium } from "playwright";

const __dirname = dirname(fileURLToPath(import.meta.url));
const root = __dirname;

// 1) Markdown -> HTML
const md = new MarkdownIt({ html: true, breaks: false, linkify: false });
md.use(katexPlugin.default ?? katexPlugin);
md.use(markPlugin.default ?? markPlugin);

const source = readFileSync(join(root, "CheatSheet.md"), "utf8");
const bodyHtml = md.render(source);

// 2) 注入模板（本地 KaTeX CSS + style.css，离线可用）
const katexCssPath = join(root, "node_modules", "katex", "dist", "katex.min.css");
const katexCssUrl = pathToFileURL(katexCssPath).href;
const styleCss = readFileSync(join(root, "style.css"), "utf8");

const html = `<!DOCTYPE html>
<html lang="zh-CN">
<head>
<meta charset="utf-8">
<link rel="stylesheet" href="${katexCssUrl}">
<style>${styleCss}</style>
</head>
<body>
${bodyHtml}
</body>
</html>`;

mkdirSync(join(root, "tmp"), { recursive: true });
const htmlPath = join(root, "tmp", "cheatsheet.html");
writeFileSync(htmlPath, html, "utf8");
console.log("HTML 写入:", htmlPath);

// 3) Chromium 打印 PDF（先写临时文件，再尝试覆盖正式文件，避免被查看器占用导致 EBUSY）
mkdirSync(join(root, "output", "pdf"), { recursive: true });
const pdfPath = join(root, "output", "pdf", "CheatSheet.pdf");
const tmpPdf = join(root, "tmp", "CheatSheet.pdf");

const browser = await chromium.launch();
const page = await browser.newPage();
await page.goto(pathToFileURL(htmlPath).href, { waitUntil: "networkidle" });
await page.pdf({
  path: tmpPdf,
  format: "A4",
  landscape: true,
  printBackground: true,
  preferCSSPageSize: true,
  margin: { top: "4mm", bottom: "4mm", left: "4mm", right: "4mm" },
});
await browser.close();

import("node:fs").then(({ copyFileSync }) => {
  try {
    copyFileSync(tmpPdf, pdfPath);
    console.log("PDF 生成:", pdfPath);
  } catch (e) {
    const alt = join(root, "output", "pdf", "CheatSheet_new.pdf");
    copyFileSync(tmpPdf, alt);
    console.log("⚠ 正式文件被占用(请关闭已打开的 CheatSheet.pdf)，已输出到:", alt);
    console.log("  源临时文件:", tmpPdf);
  }
});
