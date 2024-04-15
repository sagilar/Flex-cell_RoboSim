#!/bin/bash
echo "Terminating background services..."
pkill -9 -f controller.py
