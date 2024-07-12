from fmpy import read_model_description, extract
from fmpy.fmi2 import FMU2Slave
import numpy as np
import shutil
import signal
import sys
import logging

logging.disable()

def signal_handler(sig, frame):
    print('Ctrl+C pressed')
    fmu.terminate()
    fmu.freeInstance()
    print("Forcing the termination of the FMI Simulation")
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

fmu_filename = 'mappingFMU_CoppeliaSim_UR3e.fmu' ## Update according to the specific MappingFMU instance in use
start_time = 0.0
threshold = 2.0
stop_time = 20.0
step_size = 0.5
# read the model description
model_description = read_model_description(fmu_filename)

# collect the value references
vrs = {}
for variable in model_description.modelVariables:
    vrs[variable.name] = variable.valueReference

# extract the FMU
unzipdir = extract(fmu_filename)

fmu = FMU2Slave(guid=model_description.guid,
                unzipDirectory=unzipdir,
                modelIdentifier=model_description.coSimulation.modelIdentifier,
                instanceName='instance1')

# initialize
print("Initializing FMI Simulation")
fmu.instantiate()
fmu.setupExperiment(startTime=start_time)
fmu.enterInitializationMode()
fmu.exitInitializationMode()


time = start_time

# simulation loop
idx = 0
while time < stop_time:
    # NOTE: the FMU.get*() and FMU.set*() functions take lists of
    # value references as arguments and return lists of values
    print("Before FMI DoStep idx " + str(idx))
    if idx == 2:
        #fmu.setReal([vrs["controller_event_args_0"],vrs["controller_event_args_1"],vrs["controller_event_args_2"]],[4,18,4]) #Update of target_x y and z
        #fmu.setString([vrs["controller_event"]],["moveDiscreteCommand"]) # moveDiscreteCommand event
        #fmu.setReal([vrs["d_model_event_args_0"],vrs["d_model_event_args_1"],vrs["d_model_event_args_3"]],[4,18,4]) #Update of target_x y and z
        fmu.setReal([vrs["controller_event_args_0"],vrs["controller_event_args_1"],vrs["controller_event_args_2"]],[0,0,2]) #Update of target_x y and z
        fmu.setString([vrs["controller_event"]],["moveDiscreteCommand"]) # moveDiscreteCommand event
        fmu.setReal([vrs["d_model_event_args_0"],vrs["d_model_event_args_1"],vrs["d_model_event_args_3"]],[0,0,2]) #Update of target_x y and z
        fmu.setString([vrs["d_model_event"]],["movediscrete"])



    if idx == 11:
        fmu.setReal([vrs["controller_event_args_0"],vrs["controller_event_args_1"],vrs["controller_event_args_2"]],[11,-5,2]) #Update of target_x y and z
        fmu.setString([vrs["controller_event"]],["moveDiscreteCommand"]) # moveDiscreteCommand event
        fmu.setReal([vrs["d_model_event_args_0"],vrs["d_model_event_args_1"],vrs["d_model_event_args_3"]],[11,-5,2]) #Update of target_x y and z
        fmu.setString([vrs["d_model_event"]],["movediscrete"])
        #fmu.setString([vrs["controller_event"]],["closeGripperCommand"]) # closeGripperCommand event
        #fmu.setString([vrs["d_model_event"]],["pick"])

    if idx == 26:
        fmu.setReal([vrs["controller_event_args_0"],vrs["controller_event_args_1"],vrs["controller_event_args_2"]],[1,2,1]) #Update of target_x y and z
        fmu.setString([vrs["controller_event"]],["moveDiscreteCommand"]) # moveDiscreteCommand event
        fmu.setReal([vrs["d_model_event_args_0"],vrs["d_model_event_args_1"],vrs["d_model_event_args_3"]],[1,2,1]) #Update of target_x y and z
        fmu.setString([vrs["d_model_event"]],["movediscrete"])
        #fmu.setString([vrs["controller_event"]],["openGripperCommand"]) # openGripperCommand event
        #fmu.setString([vrs["d_model_event"]],["place"])


    fmu.doStep(currentCommunicationPoint=time, communicationStepSize=step_size)
    print("Output event (mappingFMU): " + str(fmu.getString([vrs["output_event"]])))
    for i in range(10):
        print("Platform event ({}): ".format(i) + str(fmu.getBoolean([vrs["platform_event_{}".format(i)]])))

    for j in range(6):
        print("j{} (mappingFMU): ".format(j) + str(fmu.getReal([vrs["j{}".format(j)]])))
        print("qd{} (mappingFMU): ".format(j) + str(fmu.getReal([vrs["qd{}".format(j)]])))
        print("t{} (mappingFMU): ".format(j) + str(fmu.getReal([vrs["t{}".format(j)]])))


    # advance the time
    time += step_size
    idx = idx + 1



fmu.terminate()
fmu.freeInstance()
print("Terminating FMI Simulation")
# clean up
shutil.rmtree(unzipdir, ignore_errors=True)
