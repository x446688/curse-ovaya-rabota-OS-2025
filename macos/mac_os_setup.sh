# This is required to setup XQuartz to allow xserver connections from your machine.

IP=$(ifconfig en1 | grep inet | awk '$1=="inet" {print $2}')
xhost + ${IP}
