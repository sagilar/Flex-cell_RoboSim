#!/bin/bash
#Author: Santiago Gil
rm mappingFMU.fmu
# Creating the fmu
cp -r -T ../mapping mappingFMU/resources/mapping # Notice that the mapping interface is copied and pasted into the platform mapping FMU's resources folder
(cd mappingFMU && zip -r mappingFMU.fmu .)
cp mappingFMU/mappingFMU.fmu .
rm mappingFMU/mappingFMU.fmu


