#!/bin/bash
echo "Terminating background services..."
pkill -9 java
pkill -9 -f controller_UR5e_flexcell.py
pkill -9 -f controller_UR3e_DTLab.py

