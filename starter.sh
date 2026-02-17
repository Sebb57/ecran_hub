#!/usr/bin/env sh

cd ecran_hub || exit
git pull

if [ -f "./my_venv/bin/activate" ]; then
    source ./my_venv/bin/activate
else
    echo "Error: my_venv not found in $(pwd)"
    exit 1
fi
streamlit run dashboard.py &

./ecran_hub 6767 . &

sleep 5

python3 basic_video.py

wait
