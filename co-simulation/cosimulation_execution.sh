#!/bin/bash
echo "Executing Co-simulation experiment"
echo "-----------------------------"
echo "Specification"
echo "-----------------------------"
maestro_path=/home/santiago/Aarhus/Maestro2 # Change path accordingly
output_path=results # Change accordingly
java -jar $maestro_path/maestro-2.4.1-jar-with-dependencies.jar import sg1 coe.json multimodel.json -output generate 

echo "-----------------------------"
echo "Interpretation"
echo "-----------------------------"
java -jar $maestro_path/maestro-2.4.1-jar-with-dependencies.jar interpret generate/spec.mabl -output $output_path

echo "Co-simulation experiment finished. See output results in folder '$output_path'"
