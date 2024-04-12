# Author: Santiago Gil
# modeldescription.xml helper
events = ["collision","gripperOpened","closeGripperCommand","robotStopped","moveCompleted","gripperClosed","feasibleMoveDiscreteCommand",
          "openGripperCommand","moveDiscreteCommand","nonfeasibleMoveDiscreteCommand"]

int_input = ["target_X","target_Y","target_Z"]

parameters_real = ["MOTION_VEL","opening_diameter","PI","av","closing_speed","closing_force",
                   "closing_diameter","lv","opening_speed","opening_force"]

outputs_string = ["state","target_state","status","output_command"]




""""""
text_input = '''<ScalarVariable name="{}" valueReference="{}" variability="discrete" causality="input">
      <String start="" />
    </ScalarVariable>'''

text_output = '''<ScalarVariable name="{}" valueReference="{}" variability="discrete" causality="output">
      <String />
    </ScalarVariable>'''

text_real_input = '''<ScalarVariable name="{}" valueReference="{}" causality="input" variability="continuous">
      <Real start="0.0" />
    </ScalarVariable>'''

text_int_input = '''<ScalarVariable name="{}" valueReference="{}" causality="input" variability="discrete">
      <Integer start="0" />
    </ScalarVariable>'''

text_real_output = '''<ScalarVariable name="{}" valueReference="{}" causality="output" variability="continuous">
      <Real />
    </ScalarVariable>'''

text_boolean_input = '''<ScalarVariable name="{}" valueReference="{}" causality="input" variability="discrete">
      <Boolean start="false"/>
    </ScalarVariable>'''

text_boolean_output = '''<ScalarVariable name="{}" valueReference="{}" causality="output" variability="discrete">
      <Boolean />
    </ScalarVariable>'''

text_real_parameter = '''<ScalarVariable name="{}" valueReference="{}" causality="parameter" variability="fixed">
      <Real start="0.0" />
    </ScalarVariable>'''

structure_output = '''<Unknown index="{}" />'''

result_output_structure = ""

for i in range(len(events)):
    k = i
    print(text_boolean_input.format(events[i],str(k)))

for i in range(len(int_input)):
    k = i+len(events)
    print(text_int_input.format(int_input[i],str(k)))

for i in range(len(parameters_real)):
    k = i+len(events)+len(int_input)
    print(text_real_parameter.format(parameters_real[i],str(k)))

print(text_boolean_output.format("done",str(len(events)+len(int_input)+len(parameters_real))))
k = len(events)+len(int_input)+len(parameters_real)+1
result_output_structure = result_output_structure + structure_output.format(k) + "\n"

for i in range(len(outputs_string)):
    k = i+len(events)+len(int_input)+len(parameters_real)+1
    print(text_output.format(outputs_string[i],str(k)))
    result_output_structure = result_output_structure + structure_output.format(k+1) + "\n"

print(result_output_structure)


'''
# Structure of skeleton - initialization
structure_buffer_real = "comp->fmiBuffer.realBuffer[{}] = comp->modelData.{};"
structure_buffer_int = "comp->fmiBuffer.intBuffer[{}] = comp->modelData.{};"
structure_buffer_bool = "comp->fmiBuffer.booleanBuffer[{}] = comp->modelData.{};"
structure_buffer_string = "comp->fmiBuffer.stringBuffer[{}] = comp->modelData.{};"

for i in range(len(events)):
    k = i
    print(structure_buffer_bool.format(str(k),events[i]))

for i in range(len(int_input)):
    k = i+len(events)
    print(structure_buffer_int.format(str(k),int_input[i]))

for i in range(len(parameters_real)):
    k = i+len(events)+len(int_input)
    print(structure_buffer_real.format(str(k),parameters_real[i]))

print(structure_buffer_bool.format(str(len(events)+len(int_input)+len(parameters_real)),"done"))


for i in range(len(outputs_string)):
    k = i+len(events)+len(int_input)+len(parameters_real)+1
    print(structure_buffer_string.format(str(k),outputs_string[i]))
'''

'''
# Structure of skeleton - update before doStep (for inputs)
print("inputs")
structure_buffer_real = "comp->modelData.{} = comp->fmiBuffer.realBuffer[{}];"
structure_buffer_int = "comp->modelData.{} = comp->fmiBuffer.intBuffer[{}];"
structure_buffer_bool = "comp->modelData.{} = comp->fmiBuffer.booleanBuffer[{}];"
structure_buffer_string = "comp->modelData.{} = comp->fmiBuffer.stringBuffer[{}];"

for i in range(len(events)):
    k = i
    print(structure_buffer_bool.format(events[i],str(k)))

for i in range(len(int_input)):
    k = i+len(events)
    print(structure_buffer_int.format(int_input[i],str(k)))

for i in range(len(parameters_real)):
    k = i+len(events)+len(int_input)
    print(structure_buffer_real.format(parameters_real[i],str(k)))
'''
'''
# Structure of skeleton - update after doStep (for outputs)
print("outputs")
structure_buffer_real = "comp->fmiBuffer.realBuffer[{}] = comp->modelData.{};"
structure_buffer_int = "comp->fmiBuffer.intBuffer[{}] = comp->modelData.{};"
structure_buffer_bool = "comp->fmiBuffer.booleanBuffer[{}] = comp->modelData.{};"
structure_buffer_string = "comp->fmiBuffer.stringBuffer[{}] = comp->modelData.{};"

print(structure_buffer_bool.format(str(len(events)+len(int_input)+len(parameters_real)),"done"))
for i in range(len(outputs_string)):
    k = i+len(events)+len(int_input)+len(parameters_real)+1
    print(structure_buffer_string.format(str(k),outputs_string[i]))
'''

##### d-model FMU #####
'''
for i in range(10):
    print(text_real_output.format("d_model_event_args_" + str(i),str(i+28)))
for i in range(15):
    print(structure_output.format(str(i+24)))
'''

##### RMQFMU #####
print(text_output.format("controller_event",21))
for i in range(10):
    print(text_real_output.format("controller_event_args_" + str(i),str(i+22)))
for i in range(11):
    print(structure_output.format(str(i+1)))
