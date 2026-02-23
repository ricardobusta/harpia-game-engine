#!/usr/bin/env python3
"""Build the web/release target and package it for itch.io."""
import os
import shutil
import subprocess
import zipfile

ROOT     = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PROJECT  = "Harpia.SampleGame"
BIN_DIR  = os.path.join(ROOT, "build", "web-release", "bin")
ITCH_DIR = os.path.join(ROOT, "build", "itch_upload")
ITCH_ZIP = os.path.join(ROOT, "build", "itch_upload.zip")

os.chdir(ROOT)
subprocess.run(["cmake", "--workflow", "--preset", "web-release"], check=True)

if os.path.exists(ITCH_DIR):
    shutil.rmtree(ITCH_DIR)
os.makedirs(ITCH_DIR)

shutil.copy(os.path.join(BIN_DIR, f"{PROJECT}.html"), os.path.join(ITCH_DIR, "index.html"))
for ext in ["js", "wasm", "data"]:
    shutil.copy(os.path.join(BIN_DIR, f"{PROJECT}.{ext}"), ITCH_DIR)

if os.path.exists(ITCH_ZIP):
    os.remove(ITCH_ZIP)
with zipfile.ZipFile(ITCH_ZIP, "w", zipfile.ZIP_DEFLATED) as zf:
    for fname in os.listdir(ITCH_DIR):
        zf.write(os.path.join(ITCH_DIR, fname), fname)

print(f"\n  Packaged → build/itch_upload.zip\n")
