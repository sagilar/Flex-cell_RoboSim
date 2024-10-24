#!/bin/bash
#Author: Santiago Gil
# Controller FMU
rm controllerFMU.fmu
(cd controllerFMU && zip -r controllerFMU.fmu .)
cp controllerFMU/controllerFMU.fmu .
rm controllerFMU/controllerFMU.fmu

# RMQ FMU
rm rmqfmu.fmu
(cd rmqfmu && zip -r rmqfmu.fmu .)
cp rmqfmu/rmqfmu.fmu .
rm rmqfmu/rmqfmu.fmu
