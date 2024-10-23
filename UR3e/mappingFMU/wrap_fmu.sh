#!/bin/bash
#Author: Santiago Gil
rm mappingFMU_CoppeliaSim.fmu
rm mappingFMU_URInterface.fmu
# Creating the fmu for CoppeliaSim
cp -r -T ../mapping/mapping_CoppeliaSim mappingFMU/resources/mapping
(cd mappingFMU && zip -r mappingFMU_CoppeliaSim.fmu .)
cp mappingFMU/mappingFMU_CoppeliaSim.fmu .
rm mappingFMU/mappingFMU_CoppeliaSim.fmu

# Creating the fmu for the URInterface
cp -r -T ../mapping/mapping_URInterface mappingFMU/resources/mapping
(cd mappingFMU && zip -r mappingFMU_URInterface.fmu .)
cp mappingFMU/mappingFMU_URInterface.fmu .
rm mappingFMU/mappingFMU_URInterface.fmu
