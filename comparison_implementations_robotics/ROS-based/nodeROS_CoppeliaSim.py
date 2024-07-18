# Author: Santiago Gil
import rospy
import numpy as np
from std_msgs.msg import Float32, Bool

def j0_callback(msg):
    print('j0: ' + str(msg.data))

def j1_callback(msg):
    print('j1: ' + str(msg.data))

def j2_callback(msg):
    print('j2: ' + str(msg.data))

def j3_callback(msg):
    print('j3: ' + str(msg.data))

def j4_callback(msg):
    print('j4: ' + str(msg.data))

def j5_callback(msg):
    print('j5: ' + str(msg.data))

def streat_in_out():
   pub_j0 = rospy.Publisher('sub_j0', Float32, queue_size=10)
   pub_j1 = rospy.Publisher('sub_j1', Float32, queue_size=10)
   pub_j2 = rospy.Publisher('sub_j2', Float32, queue_size=10)
   pub_j3 = rospy.Publisher('sub_j3', Float32, queue_size=10)
   pub_j4 = rospy.Publisher('sub_j4', Float32, queue_size=10)
   pub_j5 = rospy.Publisher('sub_j5', Float32, queue_size=10)
   pub_sim_stop = rospy.Publisher('stopSimulation', Bool, queue_size=10)
   rospy.Subscriber("pub_j0", Float32, j0_callback)
   rospy.Subscriber("pub_j1", Float32, j1_callback)
   rospy.Subscriber("pub_j2", Float32, j2_callback)
   rospy.Subscriber("pub_j3", Float32, j3_callback)
   rospy.Subscriber("pub_j4", Float32, j4_callback)
   rospy.Subscriber("pub_j5", Float32, j5_callback)
   rospy.init_node('external_node', anonymous=True)
   step_size = 0.5
   rate = rospy.Rate(1.0/step_size) # 2hz
   n_iterations = 30

   for i in range(n_iterations):
       # No model-based approach -> IK needs to be computed externally
       if (i==2):
           #command = [0.0,np.pi,np.pi/2,np.pi/2,0.0,0.0]
           pub_j0.publish(0.0)
           pub_j1.publish(np.pi)
           pub_j2.publish(np.pi/2)
           pub_j3.publish(np.pi/2)
           pub_j4.publish(0.0)
           pub_j5.publish(0.0)

       elif (i==11):
           #command = [np.pi/4,np.pi,np.pi/2,np.pi/2,0.0,0.0]
           pub_j0.publish(np.pi/4)
           pub_j1.publish(np.pi)
           pub_j2.publish(np.pi/2)
           pub_j3.publish(np.pi/2)
           pub_j4.publish(0.0)
           pub_j5.publish(0.0)

       elif (i==16):
           #command = [3*np.pi/4,np.pi,np.pi/2,np.pi/2,0.0,0.0]
           pub_j0.publish(3*np.pi/4)
           pub_j1.publish(np.pi)
           pub_j2.publish(np.pi/2)
           pub_j3.publish(np.pi/2)
           pub_j4.publish(0.0)
           pub_j5.publish(0.0)

       elif (i==25):
           #command = [2*np.pi,np.pi,np.pi/2,np.pi/2,0.0,0.0]
           pub_j0.publish(2*np.pi)
           pub_j1.publish(np.pi)
           pub_j2.publish(np.pi/2)
           pub_j3.publish(np.pi/2)
           pub_j4.publish(0.0)
           pub_j5.publish(0.0)

       # events are covered
       rate.sleep()
   pub_sim_stop.publish(True)

if __name__ == '__main__':
  try:
      streat_in_out()
  except rospy.ROSInterruptException:
      pass
