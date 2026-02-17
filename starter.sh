#!/usr/bin/env sh

cd ecran_hub || exit
git pull

source my_venv/bin/activate
streamlit run dashboard.py &

./ecran_hub 6767 . &
sleep 2

python3 basic_video.py

wait
