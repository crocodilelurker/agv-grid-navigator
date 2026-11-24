#!/usr/bin/env python3
"""
Packs web/index.html into index_html.h so the ESP32 sketch can serve it.

Run this every time index.html changes, then upload the sketch again.

Usage (from the solutions/ folder):
    python3 web/make_header.py codes/v06_wifi_web_control

It writes  codes/v06_wifi_web_control/index_html.h
"""
import pathlib
import sys

DELIM = "AGVHTML"  # raw-string marker; must not appear in the page

here = pathlib.Path(__file__).resolve().parent
html = (here / "index.html").read_text(encoding="utf-8")

if f"){DELIM}\"" in html:
    sys.exit(f"Error: the text '){DELIM}\"' appears in index.html - change DELIM.")

if len(sys.argv) < 2:
    sys.exit("Usage: python3 web/make_header.py <sketch folder>")

out_dir = pathlib.Path(sys.argv[1])
if not out_dir.is_dir():
    sys.exit(f"Error: folder not found: {out_dir}")

out = out_dir / "index_html.h"
out.write_text(
    "// AUTO-GENERATED from web/index.html by web/make_header.py\n"
    "// Do not edit by hand - edit web/index.html and run the script again.\n"
    "#pragma once\n\n"
    f'const char INDEX_HTML[] PROGMEM = R"{DELIM}(\n{html}\n){DELIM}";\n',
    encoding="utf-8",
)
print(f"Wrote {out} ({len(html.encode('utf-8'))} bytes of HTML)")
