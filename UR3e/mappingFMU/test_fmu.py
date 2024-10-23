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

fmu_filename = 'mappingFMU_CoppeliaSim.fmu' ## Update according to the specific MappingFMU instance in use
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
        fmu.setInteger([vrs["target_X"],vrs["target_Y"],vrs["target_Z"]],[0,0,2]) #Update of target_x y and z
        fmu.setBoolean([vrs["movediscrete"]],[True])

    if idx == 3:
        fmu.setBoolean([vrs["movediscrete"]],[False])



    if idx == 11:
        fmu.setInteger([vrs["target_X"],vrs["target_Y"],vrs["target_Z"]],[11,-5,2]) #Update of target_x y and z
        fmu.setBoolean([vrs["movediscrete"]],[True])

    if idx == 12:
        fmu.setBoolean([vrs["movediscrete"]],[False])



    fmu.doStep(currentCommunicationPoint=time, communicationStepSize=step_size)
    print("After FMI DoStep idx " + str(idx))
    print("Robot stopped event (mappingFMU): " + str(fmu.getBoolean([vrs["robotStopped"]])))

    for j in range(6):
        print("q{} (mappingFMU): ".format(j) + str(fmu.getReal([vrs["q{}".format(j)]])))
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
