#python
from robots_flexcell import robots
import csv
import numpy as np


basepath = '/home/santiago/York/flex-cell/'
filename = 'test.csv'
positions = {}
discrete_positions = {}
step_size = 0.5
current_time = 0.0


ur_robot_model = robots.UR5e_RoboSim_Simulation(mqtt_enabled=False,zmq_enabled=False)
ur_robot_model.set_motion_time(2.0)## Definition of the trajectory time


def sysCall_init():
    # do some initialization here
    #sim = require('sim')
    global j0
    global j1
    global j2
    global j3
    global j4
    global j5
    global l_fg
    global r_fg
    global end_effector
    global ur5e_sim
    global ref_cuboid

    simBase = sim.getObject('.')
    #simTip = sim.getObject('./tip')
    #simTarget = sim.getObject('./target')

    #sim.pauseSimulation()
    base_name = "/1_base_link_collision/"
    base_name_alt = "/1_base_link_collision/"
    j0 = sim.getObject(base_name + "17_shoulder_pan_joint") # J0
    j1 = sim.getObject(base_name + "11_shoulder_lift_joint") # J1
    j2 = sim.getObject(base_name +"16_elbow_joint") # J2
    j3 = sim.getObject(base_name + "15_wrist_1_joint") # J3
    j4 = sim.getObject(base_name + "18_wrist_2_joint") # J4
    j5 = sim.getObject(base_name + "14_wrist_3_joint") # J5

    #j0_alt = sim.getObject(base_name_alt + "17_shoulder_pan_joint") # J0
    #j1_alt = sim.getObject(base_name_alt + "15_shoulder_lift_joint") # J1
    #j2_alt = sim.getObject(base_name_alt +"14_elbow_joint") # J2
    #j3_alt = sim.getObject(base_name_alt + "12_wrist_1_joint") # J3
    #j4_alt = sim.getObject(base_name_alt + "11_wrist_2_joint") # J4
    #j5_alt = sim.getObject(base_name_alt + "18_wrist_3_joint") # J5
    r_fg = sim.getObject(base_name + "13_rightFingerGripper") # Right finger gripper (OnRobot 2FG7)
    l_fg = sim.getObject(base_name + "12_leftFingerGripper") # Left finger gripper (OnRobot 2FG7)


    #l_fg_alt = sim.getObject(base_name_alt + "11_leftFingerGripper") # Left finger gripper (OnRobot 2FG7)
    #r_fg_alt = sim.getObject(base_name_alt + "15_rightFingerGripper") # Right finger gripper (OnRobot 2FG7)



    ur5e_sim = sim.getObject("/1_base_link_collision")
    ref_cuboid = sim.getObject("/Cuboid")
    print("Sim objects correctly loaded")








    simRemoteApi.start(8888)
    print("Start client as 'simple_bullet_remoteApi 8888 "+ str(j0)+" "+str(j1)+" "+str(j2)+" "+str(j3)+" "+str(j4)+" "+str(j5)+" "+str(l_fg)+" "+str(r_fg)+"'")


    n_iterations = 0
    MAX_ITERATIONS = 1
    idx = 0
    path = basepath+'tests/'+filename
    with open(path,'r') as file:
        reader = csv.reader(file, delimiter=",")
        for row in reader:
            if n_iterations == MAX_ITERATIONS:
                continue
            n_iterations = n_iterations + 1
            X = row[0]
            Y = row[1]
            Z = row[2]
            n_X = int(X)
            n_Y = int(Y)
            n_Z = int(Z)
            discrete_positions[idx] = [n_X,n_Y,n_Z]
            print(str(X)+","+str(Y)+","+str(Z))
            # Transformations
            #n_X -> n_Z
            #n_Y -> -n_Y
            #n_Z -> n_X


            x,yc,zc = ur_robot_model.compute_xyz_flexcell(n_X,n_Y,Z=n_Z)
            yj,zj = ur_robot_model.compute_yz_joint(yc,zc)
            # Perform the transformations with existing models
            target_position = ur_robot_model.compute_q(x,yj,zj)[0]
            q_traj = ur_robot_model.compute_trajectory(ur_robot_model.get_previous_position(),target_position,plot=False)
            q_traj = q_traj
            ur_robot_model.transmit_robot_motion(q_traj)

            n_entry = round((step_size+current_time)/0.05)
            motion_done = False
            if n_entry>len(q_traj):
                n_entry = len(q_traj)
                motion_done = True
            n_entry = len(q_traj)
            actual_traj_array = q_traj[n_entry-1]
            actual_q0 = actual_traj_array[0]
            actual_q1 = actual_traj_array[1]
            actual_q2 = actual_traj_array[2]
            actual_q3 = actual_traj_array[3]
            actual_q4 = actual_traj_array[4]
            actual_q5 = actual_traj_array[5]
            print("moving to [" + str(actual_traj_array) + "]")


            sim.setJointTargetPosition(j0,actual_q0)
            sim.setJointTargetPosition(j1,actual_q1)
            sim.setJointTargetPosition(j2,actual_q2)
            sim.setJointTargetPosition(j3,actual_q3)
            sim.setJointTargetPosition(j4,actual_q4)
            sim.setJointTargetPosition(j5,actual_q5)

            #sim.setJointTargetPosition(j1_alt,np.pi/2)
            #sim.setJointTargetPosition(j2_alt,np.pi/2)
            #sim.setJointTargetPosition(j0_alt,actual_q0)
            #sim.setJointTargetPosition(j1_alt,actual_q1)
            #sim.setJointTargetPosition(j2_alt,actual_q2)
            #sim.setJointTargetPosition(j3_alt,actual_q3)
            #sim.setJointTargetPosition(j4_alt,actual_q4)
            #sim.setJointTargetPosition(j5_alt,actual_q5)
            #sim.setObjectPose(end_effector,ref_cuboid,[x,yj,zc,-5*np.pi/4,0,0,0])

            #time.sleep(step_size)
            #current_time = current_time + step_size
            if motion_done:
                previous_array = np.array([actual_q0,actual_q1,actual_q2,actual_q3,actual_q4,actual_q5])
                ur_robot_model.set_previous_position(previous_array)
                #continue
            idx = idx + 1
            positions[idx] = [x, yj, zj]



def sysCall_actuation():
    # put your actuation code here
    '''
    global j0
    global j1
    global j2
    global j3
    global j4
    global j5
    global l_fg
    global r_fg
    global end_effector
    global ur5e_sim
    global ref_cuboid

    #for i,pos in discrete_positions.items():
    #n_X = pos[0]
    #n_Y = pos[1]
    #n_Z = pos[2]
    n_X = discrete_positions[1][0]
    n_Y = discrete_positions[1][1]
    n_Z = discrete_positions[1][2]
    x,yc,zc = ur_robot_model.compute_xyz_flexcell(n_X,n_Y,Z=n_Z)
    yj,zj = ur_robot_model.compute_yz_joint(yc,zc)
    # Perform the transformations with existing models
    target_position = ur_robot_model.compute_q(x,yj,zj)[0]
    q_traj = ur_robot_model.compute_trajectory(ur_robot_model.get_previous_position(),target_position,plot=False)
    q_traj = q_traj
    ur_robot_model.transmit_robot_motion(q_traj)

    n_entry = round((step_size+current_time)/0.05)
    motion_done = False
    if n_entry>len(q_traj):
        n_entry = len(q_traj)
        motion_done = True
    actual_traj_array = q_traj[n_entry-1]
    actual_q0 = actual_traj_array[0]
    actual_q1 = actual_traj_array[1]
    actual_q2 = actual_traj_array[2]
    actual_q3 = actual_traj_array[3]
    actual_q4 = actual_traj_array[4]
    actual_q5 = actual_traj_array[5]

    sim.setJointTargetPosition(j0,actual_q0)
    sim.setJointTargetPosition(j1,actual_q1)
    sim.setJointTargetPosition(j2,actual_q2)
    sim.setJointTargetPosition(j3,actual_q3)
    sim.setJointTargetPosition(j4,actual_q4)
    sim.setJointTargetPosition(j5,actual_q5)
    print("Moving joints to: [" + str(actual_q0) + "," + str(actual_q1) + "," +str(actual_q2) + "," + str(actual_q3) + "," + str(actual_q4) + "," + str(actual_q5) + "]")
    #sim.setObjectPose(end_effector,ref_cuboid,[x,yj,zc,-5*np.pi/4,0,0,0])

    #time.sleep(step_size)
    #current_time = current_time + step_size
    if motion_done:
        previous_array = np.array([actual_q0,actual_q1,actual_q2,actual_q3,actual_q4,actual_q5])
        ur_robot_model.set_previous_position(previous_array)
    positions[1] = [x, yj, zj]
    #time.sleep(5.0)'''
    pass

def sysCall_sensing():
    # put your sensing code here
    pass

def sysCall_cleanup():
    # do some clean-up here
    global j0
    global j1
    global j2
    global j3
    global j4
    global j5
    global l_fg
    global r_fg
    global end_effector
    global ur5e_sim
    global ref_cuboid


    output_file = basepath+'results/'+filename
    with open(output_file, "w") as output:
        for i,o in positions.items():
            print(str(o[0]) + ", " + str(o[1]) + ","  + str(o[2]))
            output.write(str(o[0])+","+str(o[1])+","+str(o[2])+"\n")
        output.close()


    simRemoteApi.stop(8888)
    print("Stopped remote api")

# See the user manual or the available code snippets for additional callback functions and details
