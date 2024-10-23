#!/bin/bash
echo "Executing Co-simulation experiment"
echo "-----------------------------"
echo "Specification"
echo "-----------------------------"
maestro_path=/home/au698550/installs/Maestro # Change path accordingly
output_path=results # Change accordingly
maestro_jar=maestro-2.4.1-jar-with-dependencies.jar # Change path accordingly
rmq_publisher=../controller/publisher_rmq.py
using_rmqfmu=true # Update for using rmqfmu
using_simulation=true # Update for using real robot or simulation

if [ "$using_rmqfmu" = true ] && [ "$using_simulation" = true ]; then
	java -jar $maestro_path/$maestro_jar import sg1 multimodel_simulation.json -output generate
elif [ "$using_rmqfmu" = true ] && [ "$using_simulation" = false ]; then
	java -jar $maestro_path/$maestro_jar import sg1 multimodel.json -output generate
elif [ "$using_rmqfmu" = false ] && [ "$using_simulation" = false ]; then
	java -jar $maestro_path/$maestro_jar import sg1 multimodel_normq.json -output generate
elif [ "$using_rmqfmu" = false ] && [ "$using_simulation" = true ]; then
	java -jar $maestro_path/$maestro_jar import sg1 multimodel_normq_simulation.json -output generate
fi

echo "-----------------------------"
echo "Interpretation"
echo "-----------------------------"
if [ "$using_rmqfmu" = true ]; then
	python3 $rmq_publisher &
fi
java -jar $maestro_path/$maestro_jar interpret generate/spec.mabl -output $output_path

echo "Co-simulation experiment finished. See output results in folder '$output_path'"
pkill -9 java
pkill -9 -f $rmq_publisher
