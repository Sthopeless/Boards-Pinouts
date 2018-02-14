#!/bin/bash

cd /home/esp-pinout/
git checkout master
git branch -D upload
git fetch origin master
git reset --hard origin/master
