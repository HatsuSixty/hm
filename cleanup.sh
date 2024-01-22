#!/bin/sh

find . -iname "*~" -exec rm -vf {} +
find . -iname "*.o" -exec rm -vf {} +
rm -vf hm
rm -vf hasm
rm -vf foo*
