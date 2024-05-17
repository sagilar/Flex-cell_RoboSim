#
from robots_flexcell import robots
import numpy as np


ur_robot_model = robots.UR5e_RoboSim_Simulation(mqtt_enabled=False,zmq_enabled=False)

xc,yc,zc = ur_robot_model.compute_xyz_flexcell(0,23,Z=0)
#yj,zj = ur_robot_model.compute_yz_joint(yc,zc)
yj,zj = ur_robot_model.compute_yz_joint(yc,zc)
xj = xc
# Perform the transformations with existing models
target_position = ur_robot_model.compute_q(xj,yj,zj)[0]

print("x,y,z: " + str(xc) + "," + str(yc) + "," + str(zc))

print("xj,yj,zj: " + str(xj) + "," + str(yj) + "," + str(zj))


print("Target pos: " + str(target_position))

print("Forward kin: " + str(ur_robot_model.compute_fk(target_position[0],target_position[1],target_position[2],target_position[3],target_position[4],target_position[5])))


ur_robot_model.plot(target_position,block=True, limits = [-0.85,0.6,-0.85,0.5,-0.1,0.8])
#ur_robot_model.plot(np.array([-np.pi,0,0,0,0,0]),block=True, limits = [-0.85,0.85,-0.85,0.85,-0.1,0.8])

#q_traj = ur_robot_model.compute_trajectory(ur_robot_model.get_previous_position(),np.array([0,0,0,0,0,np.pi/2]),plot=False)
#2.35223095 -0.2382306   2.08265249 -1.84442189  0.78143462  1.04718485
q_traj = ur_robot_model.compute_trajectory(ur_robot_model.get_previous_position(),target_position,plot=False)

#ur_robot_model.plot(q_traj,backend='pyplot', movie='ur5e.gif')
