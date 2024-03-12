# Author: Santiago
'''
for i in range(10):
    print(str(i) + ': "args_equation_' + str(i) + '",')

for i in range(10):
    print(str(i+10) + ': "args_action_' + str(i) + '",')

for i in range(10):
    print(str(i+21) + ': "args_operation_action_' + str(i) + '",')


for i in range(10):
    print(str(i+32) + ': "controller_event_args_' + str(i) + '",')

for i in range(6):
    print(str(i+42) + ': "j' + str(i) + '",')

for i in range(6):
    print(str(i+48) + ': "qd' + str(i) + '",')

for i in range(6):
    print(str(i+54) + ': "qdd' + str(i) + '",')

for i in range(6):
    print(str(i+60) + ': "t' + str(i) + '",')


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
    print(str(i+73) + ': "d_model_event_args_' + str(i) + '",')

for i in range(10):
    print('self.d_model_event_args_' + str(i) + ',')

for i in range(10):
    print('d_model_event_args_' + str(i) + ',')

for i in range(10):
    print('self.d_model_event_args_' + str(i) + ' = d_model_event_args_' + str(i))


for i in range(10):
    print(str(i+84) + ': "output_event_args_' + str(i) + '",')

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
'''
'''from robots_flexcell import robots
ur_robot_model = robots.UR5e_RoboSim_Simulation()
ur_robot_model.set_motion_time(2.0)
fk = ur_robot_model.compute_fk(0,0,0,0,0,0)
print(fk)
print(fk[:,3])
print(fk[:,3][0])
print(fk[0,0])
print(fk[1,1])
print(fk[2,2])'''

for i in range(10):
    print(str(i+94) + ': "platform_event_' + str(i) + '",')

for i in range(10):
    print('self.platform_event_' + str(i) + ',')

for i in range(10):
    print('platform_event_' + str(i) + ',')

for i in range(10):
    print('self.platform_event_' + str(i) + ' = platform_event_' + str(i))
