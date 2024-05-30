# UR5e Digital Twin with RoboSim

This repository contains the source code to create a model-based Digital Twin implementation for the Universal Robots UR5e robotic arm in a co-simulation setting using [RoboStar](https://github.com/UoY-RoboStar) technology and [CoppeliaSim](https://github.com/CoppeliaRobotics).

## Models
The RoboSim models are available in the folder ```robosim_models/UR5e```. More precisely, the ```p-model``` is contained in the file ```ur5e_gripper.pm```, the ```d-model``` in the file ```ur5e_gripper.rst```, and the ```platform mapping model``` in the file ```mapping.pm```. [RoboTool](https://robostar.cs.york.ac.uk/robotool/) is required to access the models using the Eclipse Modeling Framework.

## Implementations

### d-model
The implementation for the d-model C code is in the folder ```fmus/d-model_v6/UR5e_code_v6/UR5e```, which is adapted with the headers and interfaces of the [FMI Standard](https://github.com/modelica/fmi-standard) in folder ```fmus/d-model_v6/adapted_C```.  
To generate the FMU, use the ```makefile``` script through ```make all```. This will generate the ```dmodelFMU.fmu``` file, which is then used for the co-simulation setting.

### p-model
The implementation for the p-model SDF file is in the folder ```Scenes_CoppeliaSim```, which includes the ```ur5e_gripper_pmodel.sdf``` generated from the p-model and the ```flex-cell-simple.ttt``` CoppeliaSim scene, which is a reduced version of the original (without including the Flex-cell infrastructure due to exceding GitHub's maximum storage capacity) that contains the scripts with the enabled [CoppeliaSim Remote API](https://manual.coppeliarobotics.com/en/remoteApiOverview.htm) to be integrated with the Platform Mapping Interface.
This implementation requires CoppeliaSim with the plugin that enables the Remote API.

### Platform Mapping Interface
The implementation for the platform mapping model is in the folder ```mapping```, where the Python prototypical implementation of the Platform Mapping Interface is given (in the ```mapping/mapping/mapping.py``` file) and its integration with the FMI Standard is achieved using [UniFMU](https://github.com/INTO-CPS-Association/unifmu) in the folder ```mapping/mappingFMU``` (more precisely in the ```resources/model.py``` file).
This generates the ```mappingFMU.fmu``` file, which is then used for the co-simulation setting.

## Co-simulation
The implementation for the co-simulation is in folder ```co-simulation```. Here, the FMUs previously created and the ControllerFMU (in the folder ```co-simulation/controllerFMU/controllerFMU```) or the [RabbitMQFMU](https://github.com/INTO-CPS-Association/fmu-rabbitmq) (in the folder ```co-simulation/rmqfmu```) are orchestrated by the co-simulation engine [Maestro](https://github.com/INTO-CPS-Association/maestro) through the definition of the co-simulation configuration file ```multimodel.json``` (with RabbitMQFMU -- this setting requires an active RabbitMQ broker to connect to) or ```multimodel_normq.json``` (with the ControllerFMU).
To execute the co-simulation, the JAR file for Maestro is required ([download it here](https://github.com/INTO-CPS-Association/maestro/releases/latest)), and use the script ```cosimulation_execution.sh``` to run the co-simulation.
To stop the co-simulation and background services, use the script ```terminate.sh```.

The output of experiments is generated to the folder ```co-simulation/results``` and the ```tests``` folder provides the ```plot.py``` script to generate some plots using the generated CSV file.
