# UR5e/UR3e Digital Twin with RoboSim

This repository contains the source code to create a model-based Digital Twin implementation for the Universal Robots UR3e and UR5e robotic arm in a co-simulation setting using [RoboStar](https://github.com/UoY-RoboStar) technology and [CoppeliaSim](https://github.com/CoppeliaRobotics). This case study has been used in another setup, the [Flex-cell](https://github.com/INTO-CPS-Association/DTaaS-examples/tree/main/digital_twins/flex-cell), this time only including the UR5e and not the Kuka LBR iiwa 7.

## Installation
1. Clone this repository.
<pre>
git clone git@github.com:sagilar/Flex-cell_RoboSim.git
</pre>
2. Install CoppeillaSim (Ubuntu 22.04):
  https://www.coppeliarobotics.com/


## Models
The RoboSim models are available in the folders ```robosim_models/UR3e``` and ```robosim_models/UR5e```. More precisely, the ```p-model``` is contained in the file ```ur5e_gripper.pm```, the ```d-model``` in the file ```ur5e_gripper.rst```, and the ```platform mapping model``` in the file ```mapping.pm```. [RoboTool](https://robostar.cs.york.ac.uk/robotool/) is required to access the models using the Eclipse Modeling Framework.

## Implementations

### d-model
The implementation for the d-model C code is in the folder ```dmodelFMU/d-model_v6/UR5e_code_v6/UR5e```, which is adapted with the headers and interfaces of the [FMI Standard](https://github.com/modelica/fmi-standard) in folder ```dmodelFMU/d-model_v6/adapted_C```.  
The generation of the FMU for a different robot (or different data scope) needs to modify the data pointer between the FMI interface and the C application. The data pointer is defined in the ```adapted_C/defs_fmi.h``` file under the struct ```ModelData```.
The ```skeleton.c``` file provides the interaction between the FMI data and the C application data using the data pointer, and taking over the ```adapted_C/DiscreteGrippingArm.c``` main C file through the ```init``` and ```tick``` methods, where the data pointer is passed and updated between the two data scopes. Be aware that the array indexes to access the data pointer in the FMI side are dependent on the indexes in the ```modelDescription.xml``` file.  
To generate the d-model FMU, use the ```makefile``` script through ```make all```. This will generate the ```dmodelFMU.fmu``` file, which is then used for the co-simulation setting.

### p-model
The implementation for the p-model SDF file is in the folder ```Scenes_CoppeliaSim```, which includes the ```ur3e_gripper_pmodel.sdf``` and ```ur5e_gripper_pmodel.sdf``` generated from the p-models and the ```ur3e-DTLab.ttt``` and ```flex-cell-simple.ttt``` CoppeliaSim scenes, which are reduced versions of the original setup (without including the Flex-cell infrastructure due to exceding GitHub's maximum storage capacity) that are enabled with the [CoppeliaSim Remote API](https://manual.coppeliarobotics.com/en/remoteApiOverview.htm) to be integrated with the Platform Mapping Interface.
This implementation requires CoppeliaSim with the plugin that enables the Remote API.

### Platform Mapping Interface
The implementation for the platform mapping model is in the folder ```mapping```, where the Python prototypical implementation of the Platform Mapping Interface is given (in the ```mapping/mapping/mapping.py``` file) and its integration with the FMI Standard is achieved using [UniFMU](https://github.com/INTO-CPS-Association/unifmu) in the folder ```mapping/mappingFMU``` (more precisely in the ```resources/model.py``` file).  There is one implementation of CoppeliaSim and one for the URInterface for each robot, i.e., two for the UR3e and two for the UR5e.
This generates the ```mappingFMU.fmu``` file, which is then used for the co-simulation setting.  
To adapt the business logic of the Platform Mapping FMU, instantiate the Platform Mapping Interface to the corresponding endpoint interfaces (and copy it to ```mapping/mappingFMU/resources``` folder with folder name ```mapping```) and update the _fmi2DoStep_ method in the ```model.py``` file. Ensure the variables in ```model.py``` correspond to the ```modelDescription.xml``` and to the platform mapping model data.
**Note:** The user is to update the corresponding folder version inside the ```mapping/mappingFMU/resources``` folder according to the desired interface to be used.  
Use the ```wrap_fmu.sh``` script to wrap the content inside the MappingFMU folder into the ```mappingFMU.fmu```

## Co-simulation
The implementation for the co-simulation is in folder ```co-simulation```. Here, the FMUs previously created (which are to be stored in ```co-simulation/models```) and the ControllerFMU (in the folder ```controllerFMU```) or the [RabbitMQFMU](https://github.com/INTO-CPS-Association/fmu-rabbitmq) (in the folder ```co-simulation/rmqfmu```) are orchestrated by the co-simulation engine [Maestro](https://github.com/INTO-CPS-Association/maestro) through the definition of the co-simulation configuration file ```multimodel_"".json```. There are 4 co-simulation files per robot, including combinations with RabbitMQFMU/ControllerFMU and CoppeliaSim/URInterface (**Note:** using RabbitMQFMU requires an active RabbitMQ broker to connect to).
To execute the co-simulation, the JAR file for Maestro is required ([download it here](https://github.com/INTO-CPS-Association/maestro/releases/latest)), and update the corresponding script ```cosimulation_execution_URxe_"".sh``` to run the co-simulation.
To stop the co-simulation and background services, use the script ```terminate.sh```.

The output of experiments is generated to the folder ```co-simulation/results``` and the ```tests``` folder provides the ```plot.py``` script to generate some plots using the generated CSV files.
