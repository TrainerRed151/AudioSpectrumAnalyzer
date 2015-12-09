#!/bin/bash

rm display
touch display
./run &
clear
watch --color -n 0.1 cat display
rm display
