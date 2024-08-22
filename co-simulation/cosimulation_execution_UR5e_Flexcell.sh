#!/bin/bash
echo "Executing Co-simulation experiment"
echo "-----------------------------"
echo "Specification"
echo "-----------------------------"
maestro_path=/home/santiago/Aarhus/Maestro2 # Change path accordingly
output_path=results # Change accordingly
#java -jar $maestro_path/maestro-2.4.1-jar-with-dependencies.jar import sg1 coe.json multimodel.json -output generate 
java -jar $maestro_path/maestro-2.3.0-jar-with-dependencies.jar import sg1 coe.json multimodel_normq_UR5e_CoppeliaSim.json -output generate ## Update the json specification according to the experiment to run

echo "-----------------------------"
echo "Interpretation"
echo "-----------------------------"
#python3 controller_UR5e_flexcell.py &
#java -jar $maestro_path/maestro-2.4.1-jar-with-dependencies.jar interpret generate/spec.mabl -output $output_path
java -jar $maestro_path/maestro-2.3.0-jar-with-dependencies.jar interpret generate/spec.mabl -output $output_path

echo "Co-simulation experiment finished. See output results in folder '$output_path'"
#pkill -9 java
pkill -9 -f controller_UR5e_flexcell.py
