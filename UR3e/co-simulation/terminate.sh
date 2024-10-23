#!/bin/bash
echo "Terminating background services..."
rmq_publisher=../controller/publisher_rmq.py
pkill -9 java
pkill -9 -f $rmq_publisher


