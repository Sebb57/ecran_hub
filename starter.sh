#!/usr/bin/env sh

cd ecran_hub || exit
git pull

./ecran_hub 6767 . &

sleep 5

python3 basic_video.py

wait
