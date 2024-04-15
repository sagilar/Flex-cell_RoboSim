#!/bin/bash
#Author: Santiago Gil
(cd mappingFMU && zip -r mappingFMU.fmu .)
cp mappingFMU/mappingFMU.fmu .
rm mappingFMU/mappingFMU.fmu
