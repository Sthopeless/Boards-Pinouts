cd /home/esp-pinout/
git add .
git checkout -b upload
git commit -m "$1"
git push origin upload
exit
