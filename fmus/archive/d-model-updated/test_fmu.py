# Santiago
from fmpy import read_model_description, extract
from fmpy.fmi2 import FMU2Slave
from fmpy.util import plot_result, download_test_file
import numpy as np
import shutil

fmu_filename = 'DiscreteGrippingArm.fmu'
start_time = 0.0
threshold = 2.0
stop_time = 2.0
step_size = 0.5

# read the model description
model_description = read_model_description(fmu_filename)

#download_test_file('2.0', 'CoSimulation', 'MapleSim', '2016.2', 'CoupledClutches', "CoupledClutches.fmu")


'''model_description_2 = read_model_description("CoupledClutches.fmu")

vrs2 = {}
for variable in model_description_2.modelVariables:
    print(type(variable))
    print(type(variable.valueReference))
    vrs2[variable.name] = variable.valueReference
print(vrs2)
vr_inputs   = vrs2['inputs']
print(vr_inputs)
print(type(vr_inputs))'''

# collect the value references
vrs = {}
for variable in model_description.modelVariables:
    #print(type(variable))
    #print(type(variable.valueReference))
    vrs[variable.name] = variable.valueReference
#print(vrs)

# get the value references for the variables we want to get/set
#vr_inputs   = vrs['inputs']      # normalized force on the 3rd clutch
#vr_outputs4 = vrs['outputs[4]']  # angular velocity of the 4th inertia

# extract the FMU
unzipdir = extract(fmu_filename)
#unzipdir = extract("CoupledClutches.fmu")

fmu = FMU2Slave(guid=model_description.guid,
                unzipDirectory=unzipdir,
                modelIdentifier=model_description.coSimulation.modelIdentifier,
                instanceName='instance1')
'''
fmu = FMU2Slave(guid=model_description_2.guid,
                unzipDirectory=unzipdir,
                modelIdentifier=model_description_2.coSimulation.modelIdentifier,
                instanceName='instance1')
'''
#print(fmu.getInteger(12))
# initialize
print("Initializing FMI Simulation")
fmu.instantiate()
fmu.setupExperiment(startTime=start_time)
fmu.enterInitializationMode()
fmu.exitInitializationMode()

li = [v for k,v in vrs.items()]
#for k,v in vrs.items():

print(fmu.getReal(li))
print(fmu.getReal(li))
print(fmu.getBoolean(li))
print(fmu.getInteger(li))
#print(fmu.getInteger(target_X_var))
#print(fmu.getReal(vrs['moveDiscreteCommand']))
#print(fmu.getInteger(34))
#print(fmu.getString(23))

time = start_time

rows = []  # list to record the results

# simulation loop
while time < stop_time:

    # NOTE: the FMU.get*() and FMU.set*() functions take lists of
    # value references as arguments and return lists of values

    # set the input
    #fmu.setReal([vr_inputs], [0.0 if time < 0.9 else 1.0])

    # perform one step
    print("Before FMI DoStep")
    fmu.doStep(currentCommunicationPoint=time, communicationStepSize=step_size)
    print("After FMI DoStep")

    # advance the time
    time += step_size

    # get the values for 'inputs' and 'outputs[4]'
    #print(fmu.getInteger(12))



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
