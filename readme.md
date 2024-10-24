# Digital Twin implementations of robotic platforms with Co-simulation and RoboStar

This repository contains the [templates](#templates) for the technique to create Digital Twin implementations of robotic platforms using co-simulation and [RoboStar](https://github.com/UoY-RoboStar) technologies associated to [this publication](#cite-this-work).

We also provide [examples](#implementation-for-the-ur5eur3e) for the instantiation of the [templates](#templates) for the Universal Robots UR5e (see [here](UR5e/)) and the UR3e (see [here](UR3e/)). The UR5e belongs to a manufacturing cell, the [Flex-cell](https://github.com/INTO-CPS-Association/DTaaS-examples/tree/main/digital_twins/flex-cell), which has been used as a case study for Digital Twins in robotics. For these examples, we provide the implementations for simulation using [CoppeliaSim](https://github.com/CoppeliaRobotics) and for real robots using the [URInterface](https://gitlab.au.dk/clagms/urinterface), which is based on the [Universal Robots RTDE](https://github.com/UniversalRobots/RTDE_Python_Client_Library).



## Installation
0. Java and Python must be installed.
1. Clone this repository.
<pre>
git clone https://github.com/INTO-CPS-Association/DigitalTwins_RoboSim.git
</pre>
2. Install CoppeliaSim:
  https://www.coppeliarobotics.com/
3. Install ZeroMQ to communicate remotely with CoppeliaSim and the URInterface to communicate with the UR5e/UR3e:
<pre>
  python3 -m pip install coppeliasim-zmqremoteapi-client zmq urinterface
</pre>
4. Install the additional dependencies for running and testing the examples and components - [Robotics Toolbox Python](https://github.com/petercorke/robotics-toolbox-python), pickle, [FMPy](https://github.com/CATIA-Systems/FMPy), mqtt, and pika (AMQP):
<pre>
  python3 -m pip install roboticstoolbox-python pickle fmpy paho-mqtt pika
</pre>

## External resources
Some of the tools this approach relies on include:
1. [UniFMU](https://github.com/INTO-CPS-Association/unifmu).
2. [RoboTool](https://robostar.cs.york.ac.uk/robotool/).
3. [RabbitMQFMU](https://github.com/INTO-CPS-Association/fmu-rabbitmq).
4. [Maestro](https://github.com/INTO-CPS-Association/maestro).
5. [FMI Standard and headers](https://github.com/modelica/fmi-standard).



## Implementation for the UR5e/UR3e
### Model artefacts
The RoboSim models are available in the folders ```URxe/robosim_models```. More precisely, the ```p-model``` is contained in the file ```urxe_gripper.pm```, the ```d-model``` in the file ```urxe_gripper.rst```, and the ```platform mapping model``` in the file ```mapping.pm```. **Note:** Both UR5e and UR3e use the same platform mapping and d-model (stored in the `UR5e` folder). [RoboTool](https://robostar.cs.york.ac.uk/robotool/) is required to access the models using the Eclipse Modeling Framework.

### Implementation and co-simulation artifacts

#### d-model C and d-model FMU
The implementation for the d-model C code is in the folder ```dmodelFMU```, which is adapted with the headers and interfaces of the [FMI Standard](https://github.com/modelica/fmi-standard) in folder ```dmodelFMU/adapted_C``` (the original source code generated with RoboSim is in `dmodelFMU/UR5e_code_v6`).  
The generation of the FMU for a different robot (or different data scope) needs to modify the data pointer between the FMI interface and the C application. The data structure is defined in the ```adapted_C/defs_fmi.h``` file under the struct ```ModelData```.
The ```skeleton.c``` file provides the interaction between the FMI data and the C application data using the data pointer, and taking over the ```adapted_C/DiscreteGrippingArm.c``` main C file through the ```init``` and ```tick``` methods, where the data pointer is passed and updated between the two data scopes. Be aware that the array indexes to access the data pointer in the FMI side are dependent on the indexes in the ```modelDescription.xml``` file.  
To generate the d-model FMU, use the ```makefile``` script through ```make all```. This will generate the ```dmodelFMU.fmu``` file, which is then used for the co-simulation.
The script ```dmodelFMU/test_fmu.py``` can be used to test the d-model FMU at the unit level.

#### Simulation based on the p-model
The implementation for the p-model SDF file is in the folder ```URxe/Scenes_CoppeliaSim```, which includes the ```urxe_gripper_pmodel.sdf``` generated from the p-models and the ```ur3e-DTLab.ttt``` and ```flex-cell-simple.ttt``` CoppeliaSim scenes accordingly, which are reduced versions of the original setup.
**Note:** Be sure your CoppeliaSim installation has the plugin that enables the Remote API via ZeroMQ.

#### Platform Mapping Interface and Platform Mapping FMU
The instantiation of the platform mapping is particular for each robotic platform. In the folder ```URxe/mapping```, we provide the prototypical implementation of the Platform Mapping Interface enabled with the interfaces for CoppeliaSim and for the URInterface.
This implementation is then used in the platform mapping FMU in the folder ```URxe/mappingFMU``` as part of the resources of the FMU, which has been created with [UniFMU](https://github.com/INTO-CPS-Association/unifmu).
Changes in the logic of the platform mapping FMU are to be made in the ```model.py``` file in the resources folder of the FMU, which are to be consistent with the ```ModelDescription.xml```.
The script ```URxe/mappingFMU/wrap_fmu.sh``` copies and pastes the previously created mapping interface into the FMU resources folder, and wraps the files with ```.fmu``` extension.
The script ```URxe/mappingFMU/test_fmu.py``` can be used to test the platform mapping FMU at the unit level.
**Note:** In case stand-alone libraries are to be used within the FMU, these should be copied and pasted in the FMU resources folder (if not installed system-wide).

#### Controller FMU
The controllerFMU or is alternative [RabbitMQFMU](https://github.com/INTO-CPS-Association/fmu-rabbitmq) are stored in the folder ```URxe/controller/```. The controllerFMU follows the [UniFMU](https://github.com/INTO-CPS-Association/unifmu) structure, and therefore, changes in the logic of the controller FMU are to be made in the ```model.py``` file in the resources folder of the FMU, which are to be consistent with the ```ModelDescription.xml```.
For RabbitMQFMU, the logic is to be updated in the publisher file ```URxe/controller/publisher_rmq.py```, which needs to be consistent with the ```ModelDescription.xml``` provided with RabbitMQFMU in the folders ```URxe/controller/rmqfmu``` and ```URxe/controller/rmqfmu/resources```.
The script ```URxe/controller/wrap_fmu.sh``` wraps the controllerFMU and RabbitMQFMU recently updated with ```.fmu``` extension.
The script ```URxe/controller/test_fmu.py``` can be used to test the controllerFMU at the unit level.


#### Co-simulation
The implementation for the co-simulation is in folder ```URxe/co-simulation```. Here, the FMUs previously created FMUs are orchestrated by the co-simulation engine [Maestro](https://github.com/INTO-CPS-Association/maestro) through the definition of the co-simulation configuration file ```multimodel_"".json```. There are 4 co-simulation files per robot, including combinations with RabbitMQFMU/ControllerFMU and CoppeliaSim/URInterface (**Note:** using RabbitMQFMU requires an active RabbitMQ broker to connect to, using CoppeliaSim requires that CoppeliaSim is up and running with the respective scene, and using the actual UR5e/UR3e robot requires that the robot is connected to the same network as the computer where you are running the co-simulation, with the right IP address provided in the platform mapping interface, and with remote control enabled on the teach pendant).

To execute the co-simulation, the JAR file for Maestro is required ([download it here](https://github.com/INTO-CPS-Association/maestro/releases/latest)), and execute the script ```URxe/co-simulation/cosimulation_execution.sh``` to run the co-simulation.
In this script, you can update the value of the variables ```using_rmqfmu=false``` and ```using_simulation=false``` to `true` or `false` depending on the scenario you want to run.
To stop the co-simulation and background services, use the script ```terminate.sh```.

The output of experiments is generated to the folder ```URxe/co-simulation/results``` by default (this path can be updated in the ```URxe/co-simulation/cosimulation_execution.sh``` file).

## Templates
We provide templates based on the provided methodology in our paper (see [Cite this work](#cite-this-work)) in the [templates folder](templates/).

The script ```templates/helper.py``` provides a set of miscellaneous functions that help with automatically printing some portions of code to set up the templates based on the particular RoboSim models and variables names. These portions of code are printed to the terminal and must be copied and pasted to the corresponding files.

To use this script, update the RoboSim module name in `robosim_module_name = "name"`; update the dictionary `vars` with your Input Events, Operations, and Arguments for Input Events and Operations accordingly; define which of the Input Events are to be provided by the controller FMU in `vars_controller`; and define which variables of the robotic platform you want to log in `vars_log_pmFMU` (these are not necessarily part of the RoboSim module but observations you can get from the robotic platform - either real or simulated).

The script provides 11 functions that provide some portions of code for the following files or sections in the templates:
1. `connections` field in the `step5_co-simulation/multimodel.json` file used by Maestro to set up the co-simulation given the FMUs and connections (see [here](templates/step5_co-simulation/multimodel.json)). (**Step 5 in the methodology**)
2. `ModelDescription.xml` of the platform mapping FMU (see [here](templates/steps6-7_MappingFMU/mappingFMU/modelDescription.xml)). (**Step 6 in the methodology**)
3. `model.py` of the platform mapping FMU (see [here](templates/steps6-7_MappingFMU/mappingFMU/resources/model.py)). (**Steps 6 and 7 in the methodology**)
4. `ModelDescription.xml` of the d-model FMU (see [here](templates/steps8-11_dmodelFMU/modelDescription.xml)). (**Step 8 in the methodology**)
5. `ModelData struct` in `steps8-11_dmodelFMU/adapted_C/defs_fmi.h` of the d-model FMU (see [here](templates/steps8-11_dmodelFMU/adapted_C/defs_fmi.h)). (**Step 9 in the methodology**)
6. `read_input` function in the `steps8-11_dmodelFMU/adapted_C/interface.h` file of the d-model FMU (see [here](templates/steps8-11_dmodelFMU/adapted_C/interface.h)). (**Step 10 in the methodology**)
7. `write_output` function in the `steps8-11_dmodelFMU/adapted_C/interface.h` file of the d-model FMU (see [here](templates/steps8-11_dmodelFMU/adapted_C/interface.h)). (**Step 10 in the methodology**)
8. `skeleton.c` of the d-model FMU (see [here](templates/steps8-11_dmodelFMU/skeleton.c)). (**Step 11 in the methodology**)
9. `setStartValues` function in the `steps8-11_dmodelFMU/adapted_C/main.c` file of the d-model FMU (see [here](templates/steps8-11_dmodelFMU/adapted_C/main.c)). (**Step 11 in the methodology**)
10. `model.py` of the controller FMU (see [here](templates/steps12-13_controller/controllerFMU/resources/model.py)). (**Steps 12 and 13 in the methodology**)
11. `ModelDescription.xml` of the controller FMU (also works for the outputs of the RabbitMQ FMU) (see [here](templates/steps12-13_controller/controllerFMU/modelDescription.xml) for the controllerFMU; RabbitMQ FMU requires the same `ModelDescription.xml` in two places, [here](templates/steps12-13_controller/rmqfmu/modelDescription.xml) and [here](templates/steps12-13_controller/rmqfmu/resources/modelDescription.xml)). (**Step 13 in the methodology**)



### Steps
- **Steps 1 and 2** are case-specific. Refer to the examples provided in [UR5e/UR3e Models](#models) for further guidance.
- **Step 3** refers to the platform mapping interface, whose template is provided in [mapping template](templates/step3_mapping/). Here, the user is expected create the mapping given the robotic platform and the communication interface and libraries required. For exemplification, refer to [mapping UR5e](UR5e/mapping/) to see the instantiation of the mapping template for the UR5e with two different interfaces, the CoppeliaSim Remote API and the URInterface.
- **Step 4** is case-specific; be sure the simulation or real robotic platform is running and enabled for remote connection based on the communication interface provided in Step 3. Refer to the examples provided in [UR5e/UR3e Models](#p-model) for further guidance.
- **Step 5** is defined in the `co-simulation/multimodel.json` file ([co-simulation template](templates/step5_co-simulation/)) for the co-simulation and the distinct `ModelDescription.xml` files for each FMU. Use the feature **1** of `templates/helper.py` to get the connections between FMUs. The features **2, 4, and 11** also help to set up the `ModelDescription.xml` files that are used for the FMUs used in the co-simulation. For exemplification, refer to [co-simulation UR5e](UR5e/co-simulation/) to see the implementation of the co-simulation for the UR5e.
- **Steps 6 and 7** are provided in the [mapping FMU template](templates/steps6-7_mappingFMU/). Use the features **2 and 3** of the `templates/helper.py` to set up the platform mapping FMU. When everything is done, use the provided script `templates/steps6-7_mappingFMU/wrap_fmu.sh` to wrap the platform mapping FMU with extension `.fmu`, including the worked-out **Step 3**. For exemplification, refer to [mapping FMU UR5e](UR5e/mapping/) to see the instantiation of the mapping FMU template for the UR5e.
- **Step 8** is provided in the [d-model FMU template](templates/steps8-11_dmodelFMU/). Adapt the automatically generated C code in the `templates/steps8-11_dmodelFMU/adapted_C` folder using the guidance provided to adapt the `main.c` file. Update the `ModelDescription.xml` file using the feature **4** of the `templates/helper.py`.
For exemplification, refer to [d-model FMU](d-model/) to see the instantiation of the d-model FMU template for the UR5e.
- **Step 9** is provided in the [defs_fmi.h template](templates/steps8-11_dmodelFMU/adapted_C/defs_fmi.h). Use the feature **5** of the `templates/helper.py` to update the data struct.
- **Step 10** is provided in the [interface.h template](templates/steps8-11_dmodelFMU/adapted_C/interface.h). Use the features **6 and 7** of the `templates/helper.py` to update the behavior of the `interface.h` based on your data.
- **Step 11** is provided in the [d-model FMU template](templates/steps8-11_dmodelFMU/). Adapt the `skeleton.c` using the feature **8** of the `templates/helper.py` and the `main.c` using the feature **9** of the `templates/helper.py`. Be sure to have the modified structure in your `main.c` so the program is started using the `init` and called using the `tick` function.
- **Steps 12 and 13** are provided in the [templates for the controller and RabbitMQ FMU](templates/steps12-13_controller). The logic is to be stored in the `templates/steps12-13_controller/controllerFMU/resources/model.py` (see [here](templates/steps12-13_controller/controllerFMU/resources/model.py)) for the controller FMU (use the feature **10** of the `templates/helper.py` to set up the `model.py` of the controller FMU) and in the `templates/steps12-13_controller/publisher_rmq.py` (see [here](templates/steps12-13_controller/publisher_rmq.py)) for the RabbitMQ FMU. Use the feature **11** of the `templates/helper.py` to set up the `ModelDescription.xml` files of the controller FMU and the RabbitMQ FMU (**Note:** RabbitMQ FMU requires that the `ModelDescription.xml` file is also stored in its resources folder `rmqfmu/resources/`). For exemplification, refer to [controller UR5e](UR5e/controller) to see the instantiation of the controller FMU and RabbitMQ FMU templates for the UR5e.

### Execution

After these steps have been worked out, the co-simulation can be executed using the script `templates/step5_co-simulation/cosimulation_execution.sh`. For exemplification, refer to [co-simulation UR5e](UR5e/co-simulation/) to see the implementation of the co-simulation for the UR5e.

## Cite this work
TBD