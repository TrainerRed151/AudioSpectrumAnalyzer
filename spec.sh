#!/bin/bash

parec -d alsa_output.pci-0000_00_1b.0.analog-stereo.monitor --channels=1 --channel-map=mono | ./run
