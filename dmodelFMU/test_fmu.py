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

fmu_filename = 'dmodelFMU.fmu'
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
    fmu.setBoolean([vrs["robotStopped"]],[True]) 
    fmu.setBoolean([vrs["gripperOpened"]],[True]) 
    
    print("Before FMI DoStep idx " + str(idx))
    if idx == 2:
        fmu.setInteger([vrs["MovementArgs_target_X"],vrs["MovementArgs_target_Y"],vrs["MovementArgs_target_Z"]],[4,18,4]) #Update of target_x y and z
        fmu.setBoolean([vrs["moveDiscreteCommand"]],[True]) 
    if idx == 3:
        fmu.setBoolean([vrs["moveDiscreteCommand"]],[False]) 
        fmu.setBoolean([vrs["nonfeasibleMoveDiscreteCommand"]],[True]) 
        #fmu.setBoolean([vrs["feasibleMoveDiscreteCommand"]],[True]) # feasibleMoveDiscreteCommand event

    if idx == 4:
        #fmu.setBoolean([vrs["feasibleMoveDiscreteCommand"]],[False]) # feasibleMoveDiscreteCommand event
        fmu.setBoolean([vrs["moveCompleted"]],[True]) # moveCompleted event
        fmu.setBoolean([vrs["nonfeasibleMoveDiscreteCommand"]],[False]) 

    if idx == 8:
        fmu.setBoolean([vrs["moveCompleted"]],[False]) # moveCompleted event
        fmu.setBoolean([vrs["robotStopped"]],[True]) # robotStopped event

    if idx == 11:
        fmu.setBoolean([vrs["robotStopped"]],[False]) # robotStopped event
        fmu.setBoolean([vrs["closeGripperCommand"]],[True]) # closeGripperCommand event

    if idx == 14:
        fmu.setBoolean([vrs["closeGripperCommand"]],[False]) # closeGripperCommand event
        fmu.setBoolean([vrs["gripperClosed"]],[True]) # gripperClosed event

    if idx == 16:
        fmu.setBoolean([vrs["gripperClosed"]],[False]) # gripperClosed event


    fmu.doStep(currentCommunicationPoint=time, communicationStepSize=step_size)
    print("After FMI DoStep idx " + str(idx))
    print("movediscrete command (from d-model): " + str(fmu.getBoolean([vrs["movediscrete"]])))
    print("movediscrete arguments (from d-model): " + str(fmu.getInteger([vrs["target_X"],vrs["target_Y"],vrs["target_Z"]])))
    print("State (from d-model): " + str(fmu.getString([vrs["state"]])))

    # advance the time
    time += step_size
    idx = idx + 1



fmu.terminate()
fmu.freeInstance()
print("Terminating FMI Simulation")
# clean up
shutil.rmtree(unzipdir, ignore_errors=True)
