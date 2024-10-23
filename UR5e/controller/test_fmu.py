#
# Santiago
from fmpy import read_model_description, extract
from fmpy.fmi2 import FMU2Slave
from fmpy.util import plot_result, download_test_file
import numpy as np
import shutil
import signal
import sys

def signal_handler(sig, frame):
    print('Ctrl+C pressed')
    fmu.terminate()
    fmu.freeInstance()
    print("Forcing the termination of the FMI Simulation")
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

fmu_filename = 'controllerFMU.fmu'
start_time = 0.0
threshold = 2.0
stop_time = 10.0
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
    print("Before FMI DoStep idx " + str(idx))
    fmu.doStep(currentCommunicationPoint=time, communicationStepSize=step_size)
    print("After FMI DoStep idx " + str(idx))
    print("moveDiscreteCommand command (from controller): " + str(fmu.getBoolean([vrs["moveDiscreteCommand"]])))
    print("moveDiscreteCommand arguments (from controller): " + str(fmu.getInteger([vrs["MovementArgs_target_X"],vrs["MovementArgs_target_Y"],vrs["MovementArgs_target_Z"]])))

    # advance the time
    time += step_size
    idx = idx + 1



fmu.terminate()
fmu.freeInstance()
print("Terminating FMI Simulation")
# clean up
shutil.rmtree(unzipdir, ignore_errors=True)
