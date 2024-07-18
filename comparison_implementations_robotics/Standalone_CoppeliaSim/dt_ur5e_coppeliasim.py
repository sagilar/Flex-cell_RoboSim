### Author: Santiago Gil
from coppeliasim_zmqremoteapi_client import RemoteAPIClient
import time
import numpy as np

client = RemoteAPIClient(host='localhost', port=23000) ### Client
sim = client.getObject('sim') ### Sim Object: the objects are handled from this object serialization


base_name = "/UR5/"
j0 = sim.getObject(base_name + "joint") # J0
j1 = sim.getObject(base_name + "link/joint") # J1
j2 = sim.getObject(base_name +"link/joint/link/joint") # J2
j3 = sim.getObject(base_name + "link/joint/link/joint/link/joint/") # J3
j4 = sim.getObject(base_name + "link/joint/link/joint/link/joint/link/joint/") # J4
j5 = sim.getObject(base_name + "link/joint/link/joint/link/joint/link/joint/link/joint/") # J5


def sync_in(stream_in):
    # Commands, data from PT, updates, etc.
    try:
        command = stream_in[0]
        idx = 0
        for entry in command:
            set_joint_position("j"+str(idx),entry)
            idx = idx + 1
    except:
        pass



def sync_out():
    # analyses, calculations, computations,etc.
    #
    joint_data = []
    velocity_data = []
    force_data = []
    stream_out = []
    for i in range(6):
        j_pos = get_joint_position("j"+str(i))
        j_vel = get_joint_velocity("j"+str(i))
        j_for = get_joint_force("j"+str(i))
        joint_data.append(j_pos)
        velocity_data.append(j_vel)
        force_data.append(j_for)
    stream_out.append(joint_data)
    stream_out.append(velocity_data)
    stream_out.append(force_data)
    return stream_out



def get_joint_position(joint_name):
    if (joint_name == "j0"):
        return sim.getJointPosition(j0)
    elif (joint_name == "j1"):
        return sim.getJointPosition(j1)
    elif (joint_name == "j2"):
        return sim.getJointPosition(j2)
    elif (joint_name == "j3"):
        return sim.getJointPosition(j3)
    elif (joint_name == "j4"):
        return sim.getJointPosition(j4)
    elif (joint_name == "j5"):
        return sim.getJointPosition(j5)
    else:
        print("Joint name '" + str(joint_name) + "' does not exist" )

def get_joint_velocity(joint_name):
    if (joint_name == "j0"):
        return sim.getJointVelocity(j0)
    elif (joint_name == "j1"):
        return sim.getJointVelocity(j1)
    elif (joint_name == "j2"):
        return sim.getJointVelocity(j2)
    elif (joint_name == "j3"):
        return sim.getJointVelocity(j3)
    elif (joint_name == "j4"):
        return sim.getJointVelocity(j4)
    elif (joint_name == "j5"):
        return sim.getJointVelocity(j5)
    else:
        print("Joint name '" + str(joint_name) + "' does not exist" )

def get_joint_force(joint_name):
    if (joint_name == "j0"):
        return sim.getJointForce(j0)
    elif (joint_name == "j1"):
        return sim.getJointForce(j1)
    elif (joint_name == "j2"):
        return sim.getJointForce(j2)
    elif (joint_name == "j3"):
        return sim.getJointForce(j3)
    elif (joint_name == "j4"):
        return sim.getJointForce(j4)
    elif (joint_name == "j5"):
        return sim.getJointForce(j5)
    else:
        print("Joint name '" + str(joint_name) + "' does not exist" )

def set_joint_position(joint_name,val):
    if (joint_name == "j0"):
        sim.setJointTargetPosition(j0,val)
    elif (joint_name == "j1"):
        sim.setJointTargetPosition(j1,val)
    elif (joint_name == "j2"):
        sim.setJointTargetPosition(j2,val)
    elif (joint_name == "j3"):
        sim.setJointTargetPosition(j3,val)
    elif (joint_name == "j4"):
        sim.setJointTargetPosition(j4,val)
    elif (joint_name == "j5"):
        sim.setJointTargetPosition(j5,val)
    else:
        print("Joint name '" + str(joint_name) + "' does not exist" )

def set_joint_velocity(joint_name,val):
    if (joint_name == "j0"):
        sim.setJointTargetVelocity(j0,val)
    elif (joint_name == "j1"):
        sim.setJointTargetVelocity(j1,val)
    elif (joint_name == "j2"):
        sim.setJointTargetVelocity(j2,val)
    elif (joint_name == "j3"):
        sim.setJointTargetVelocity(j3,val)
    elif (joint_name == "j4"):
        sim.setJointTargetVelocity(j4,val)
    elif (joint_name == "j5"):
        sim.setJointTargetVelocity(j5,val)
    else:
        print("Joint name '" + str(joint_name) + "' does not exist" )

def set_joint_force(joint_name,val):
    if (joint_name == "j0"):
        sim.setJointTargetForce(j0,val)
    elif (joint_name == "j1"):
        sim.setJointTargetForce(j1,val)
    elif (joint_name == "j2"):
        sim.setJointTargetForce(j2,val)
    elif (joint_name == "j3"):
        sim.setJointTargetForce(j3,val)
    elif (joint_name == "j4"):
        sim.setJointTargetForce(j4,val)
    elif (joint_name == "j5"):
        sim.setJointTargetForce(j5,val)
    else:
        print("Joint name '" + str(joint_name) + "' does not exist" )


if __name__ == '__main__':
    n_iterations = 30
    step_size = 0.5
    sim.startSimulation()

    for i in range(n_iterations):
        stream_in = []
        # No model-based approach -> IK needs to be computed externally
        if (i==2):
            command = [0.0,np.pi,np.pi/2,np.pi/2,0.0,0.0]
            stream_in.append(command)

        elif (i==11):
            command = [np.pi/4,np.pi,np.pi/2,np.pi/2,0.0,0.0]
            stream_in.append(command)

        elif (i==16):
            command = [3*np.pi/4,np.pi,np.pi/2,np.pi/2,0.0,0.0]
            stream_in.append(command)

        elif (i==25):
            command = [2*np.pi,np.pi,np.pi/2,np.pi/2,0.0,0.0]
            stream_in.append(command)
        sync_in(stream_in)
        stream_out = sync_out()
        # misses management of events
        print("Stream out : ", stream_out)
        time.sleep(step_size)
    sim.stopSimulation()
