# Author: Santiago
'''
# model.py helper
for i in range(10):
    print(str(i) + ': "args_equation_' + str(i) + '",')

for i in range(10):
    print(str(i+10) + ': "args_action_' + str(i) + '",')

for i in range(10):
    print(str(i+21) + ': "args_operation_action_' + str(i) + '",')


for i in range(10):
    print(str(i+1) + ': "controller_event_args_' + str(i) + '",')

for i in range(6):
    print(str(i+11) + ': "j' + str(i) + '",')

for i in range(6):
    print(str(i+17) + ': "qd' + str(i) + '",')

for i in range(6):
    print(str(i+23) + ': "qdd' + str(i) + '",')

for i in range(6):
    print(str(i+29) + ': "t' + str(i) + '",')


for i in range(10):
    print('self.args_equation_' + str(i) + ',')

for i in range(10):
    print('self.args_action_' + str(i) + ',')

for i in range(10):
    print('self.args_operation_action_' + str(i) + ',')


for i in range(10):
    print('self.controller_event_args_' + str(i) + ',')

for i in range(6):
    print('self.j' + str(i) + ',')

for i in range(6):
    print('self.qd' + str(i) + ',')

for i in range(6):
    print('self.qdd' + str(i) + ',')

for i in range(6):
    print('self.t' + str(i) + ',')


for i in range(10):
    print('args_equation_' + str(i) + ',')

for i in range(10):
    print('args_action_' + str(i) + ',')

for i in range(10):
    print('args_operation_action_' + str(i) + ',')


for i in range(10):
    print('controller_event_args_' + str(i) + ',')

for i in range(6):
    print('j' + str(i) + ',')

for i in range(6):
    print('qd' + str(i) + ',')

for i in range(6):
    print('qdd' + str(i) + ',')

for i in range(6):
    print('t' + str(i) + ',')

for i in range(10):
    print('self.args_equation_' + str(i) + ' = args_equation_' + str(i))

for i in range(10):
    print('self.args_action_' + str(i) + ' = args_action_' + str(i))

for i in range(10):
    print('self.args_operation_action_' + str(i) + ' = args_operation_action_' + str(i))


for i in range(10):
    print('self.controller_event_args_' + str(i) + ' = controller_event_args_' + str(i))

for i in range(6):
    print('self.j' + str(i) + ' = j' + str(i))

for i in range(6):
    print('self.qd' + str(i) + ' = qd' + str(i))

for i in range(6):
    print('self.qdd' + str(i) + ' = qdd' + str(i))

for i in range(6):
    print('self.t' + str(i) + ' = t' + str(i))


for i in range(10):
    print(str(i+36) + ': "d_model_event_args_' + str(i) + '",')

for i in range(10):
    print('self.d_model_event_args_' + str(i) + ',')

for i in range(10):
    print('d_model_event_args_' + str(i) + ',')

for i in range(10):
    print('self.d_model_event_args_' + str(i) + ' = d_model_event_args_' + str(i))


for i in range(10):
    print(str(i+47) + ': "output_event_args_' + str(i) + '",')


for i in range(10):
    print('self.output_event_args_' + str(i) + ',')

for i in range(10):
    print('output_event_args_' + str(i) + ',')

for i in range(10):
    print('self.output_event_args_' + str(i) + ' = output_event_args_' + str(i))

for i in range(6):
    print('self.j' + str(i) + ' = self.mapping.get_joint_position("j' + str(i) + '")')

for i in range(6):
    print('self.qd' + str(i) + ' = self.mapping.get_joint_velocity("j' + str(i) + '")')

for i in range(6):
    print('self.t' + str(i) + ' = self.mapping.get_joint_force("j' + str(i) + '")')

for i in range(10):
    print(str(i+57) + ': "platform_event_' + str(i) + '",')

for i in range(10):
    print('self.platform_event_' + str(i) + ',')

for i in range(10):
    print('platform_event_' + str(i) + ',')

for i in range(10):
    print('self.platform_event_' + str(i) + ' = platform_event_' + str(i))
'''


'''
# model.py execution
from robots_flexcell import robots
ur_robot_model = robots.UR5e_RoboSim_Simulation()
ur_robot_model.set_motion_time(2.0)
fk = ur_robot_model.compute_fk(0,0,0,0,0,0)
print(fk)
print(fk[:,3])
print(fk[:,3][0])
print(fk[0,0])
print(fk[1,1])
print(fk[2,2])'''

""""""
# modeldescription.xml helper
text_input = '''<ScalarVariable name="{}" valueReference="{}" variability="discrete" causality="input">
      <String start="" />
    </ScalarVariable>'''

text_output = '''<ScalarVariable name="{}" valueReference="{}" variability="discrete" causality="output">
      <String />
    </ScalarVariable>'''

text_real_input = '''<ScalarVariable name="{}" valueReference="{}" causality="input" variability="continuous">
      <Real start="0.0" />
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

structure_output = '''<Unknown index="{}" />'''

result_output_structure = ""

#print(str(0) + ': "controller_event,')
print(text_input.format("controller_event","0"))

for i in range(10):
    k = i+1
    #print(str(i+1) + ': "controller_event_args_' + str(i) + '",')
    print(text_real_input.format("controller_event_args_"+str(i),str(k)))

for i in range(6):
    k = i+11
    #print(str(i+11) + ': "j' + str(k) + '",')
    print(text_real_output.format("j"+str(i),str(k)))
    #print(structure_output.format(k))
    result_output_structure = result_output_structure + structure_output.format(k+1) + "\n"

for i in range(6):
    k = i+17
    #print(str(i+17) + ': "qd' + str(k) + '",')
    print(text_real_output.format("qd"+str(i),str(k)))
    #print(structure_output.format(k))
    result_output_structure = result_output_structure + structure_output.format(k+1) + "\n"

for i in range(6):
    k = i+23
    #print(str(i+23) + ': "qdd' + str(k) + '",')
    print(text_real_output.format("qdd"+str(i),str(k)))
    #print(structure_output.format(k))
    result_output_structure = result_output_structure + structure_output.format(k+1) + "\n"

for i in range(6):
    k = i+29
    #print(str(i+29) + ': "t' + str(k) + '",')
    print(text_real_output.format("t"+str(i),str(k)))
    #print(structure_output.format(k))
    result_output_structure = result_output_structure + structure_output.format(k+1) + "\n"

#print(str(35) + ': "d_model_event,')
print(text_input.format("d_model_event",str(35)))

for i in range(10):
    k = i+36
    #print(str(i+36) + ': "d_model_event_args_' + str(k) + '",')
    print(text_real_input.format("d_model_event_args_"+str(i),str(k)))

#print(str(46) + ': "output_event,')
print(text_output.format("output_event",str(46)))
result_output_structure = result_output_structure + structure_output.format(46+1) + "\n"

for i in range(10):
    k = i+47
    #print(str(i+47) + ': "output_event_args_' + str(k) + '",')
    print(text_real_output.format("output_event_args_"+str(i),str(k)))
    result_output_structure = result_output_structure + structure_output.format(k+1) + "\n"

for i in range(10):
    k = i+57
    #print(str(i+57) + ': "platform_event_' + str(k) + '",')
    print(text_boolean_output.format("platform_event_"+str(i),str(k)))
    result_output_structure = result_output_structure + structure_output.format(k+1) + "\n"

print(result_output_structure)
