#!/usr/bin/env python3
"""Build the web/debug target and serve it locally."""
import http.server
import os
import socketserver
import subprocess
import sys

ROOT    = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PROJECT = "Harpia.SampleGame"
PORT    = int(sys.argv[1]) if len(sys.argv) > 1 else 8080
BIN_DIR = os.path.join(ROOT, "build", "web", "bin")
URL     = f"http://localhost:{PORT}/{PROJECT}.html"

os.chdir(ROOT)
subprocess.run(["cmake", "--workflow", "--preset", "web"], check=True)

print(f"\n  Open: {URL}\n")

os.chdir(BIN_DIR)
with socketserver.TCPServer(("", PORT), http.server.SimpleHTTPRequestHandler) as httpd:
    httpd.serve_forever()
