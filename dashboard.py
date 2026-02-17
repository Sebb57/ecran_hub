#!/usr/bin/env python3
# https://sebb57.github.io

import streamlit as st
import socket

PI_IP = "127.0.0.1" 
PI_PORT = 6767

st.title("Écran hub")

url = st.text_input("lien vidéo/gif/... à mettre sur l'écran")

if url:
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((PI_IP, PI_PORT))
            s.sendall(f"{url}\n".encode())
            st.success("lien envoyé!")
    except Exception as e:
        st.error(f"Connection failed: {e}")
