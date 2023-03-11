#!/usr/bin/env bash


rsync -arvz --exclude 'venv*' --exclude '.git' --progress --delete $(pwd) pi@10.1.10.20:/home/pi

# rsync -arvz -e 'ssh -p <port-number>' --progress --delete user@remote-server:/path/to/remote/folder /path/to/local/folder
