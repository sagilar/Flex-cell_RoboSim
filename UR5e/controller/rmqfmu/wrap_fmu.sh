#!/bin/bash
#Author: Santiago Gil
cp modelDescription.xml resources/modelDescription.xml
zip -r rmqfmu.fmu .
cp rmqfmu.fmu ../
rm rmqfmu.fmu
