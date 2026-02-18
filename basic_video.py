#!/usr/bin/env python3
#
# EPITECH PROJECT, 2026
# ecran_hub
# File description:
# basic_video.py
#

import socket
import time

HOST = "127.0.0.1"
PORT = 6767
DEFAULT_VIDEO = "https://www.youtube.com/shorts/QUoTSm0_nT0"

def send_video(url):
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.settimeout(5)
            s.connect((HOST, PORT))
            payload = f"{url}\r\n".encode()
            s.sendall(payload)
            time.sleep(0.1) 
    except Exception as e:
        print(f"Connection Error: {e}")

if __name__ == "__main__":
    send_video(DEFAULT_VIDEO)
