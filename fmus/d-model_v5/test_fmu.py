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

fmu_filename = 'DiscreteGrippingArm.fmu'
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
    # NOTE: the FMU.get*() and FMU.set*() functions take lists of
    # value references as arguments and return lists of values
    print("Before FMI DoStep idx " + str(idx))
    if idx == 2:
        fmu.setInteger([vrs["target_X"],vrs["target_Y"],vrs["target_Z"]],[4,18,4]) #Update of target_x y and z
        fmu.setBoolean([vrs["moveDiscreteCommand"]],[True]) # moveDiscreteCommand event
    if idx == 3:
        fmu.setBoolean([vrs["moveDiscreteCommand"]],[False]) # moveDiscreteCommand event
        fmu.setBoolean([vrs["feasibleMoveDiscreteCommand"]],[True]) # feasibleMoveDiscreteCommand event

    if idx == 4:
        fmu.setBoolean([vrs["feasibleMoveDiscreteCommand"]],[False]) # feasibleMoveDiscreteCommand event
        fmu.setBoolean([vrs["moveCompleted"]],[True]) # moveCompleted event

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
    print("Output command (from d-model): " + str(fmu.getString([vrs["output_command"]])))
    print("State (from d-model): " + str(fmu.getString([vrs["state"]])))
    #print("Output arguments (sim): " + str(fmu.getString([28,29,30,31])))

    #print("Output command (sim): " + str(fmu.getString([vrs["output_command"]])))
    #print("current State (sim): " + str(fmu.getString([vrs["state"]])))

    '''print("Values in simulation:")
    for k,v in vrs.items():
        print(str(k) + " : " + str(fmu.getInteger([v])))
        print(str(k) + " : " + str(fmu.getString([v])))
        print(str(k) + " : " + str(fmu.getReal([v])))
        print(str(k) + " : " + str(fmu.getBoolean([v])))
        print("------------------------------")
    '''
    # advance the time
    time += step_size
    idx = idx + 1



fmu.terminate()
fmu.freeInstance()
print("Terminating FMI Simulation")
# clean up
shutil.rmtree(unzipdir, ignore_errors=True)

# convert the results to a structured NumPy array
#result = np.array(rows, dtype=np.dtype([('time', np.float64), ('inputs', np.float64), ('outputs[4]', np.float64)]))

# plot the results
#if show_plot:
#    plot_result(result)
