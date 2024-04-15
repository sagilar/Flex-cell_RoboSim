from mapping import mapping as mpp
import time
from robots_flexcell import robots
from threading import Timer

ur_robot_model = robots.UR5e_RoboSim_Simulation()
mapping = mpp.Mapping()



def check_for_events():
    args = {
        "equation_0": ["flexcellAngularPosition[completed]"]
    }
    result = mapping.get_event("moveCompleted",args=None)
    print("moveCompleted platform event (timer): " + str(result))
    checking_timer.run()

checking_timer = Timer(0.5, check_for_events)
checking_timer.daemon = True

if __name__ == "__main__":
    try:
        mapping.start_simulation()
        ## The args should come from the c++ code
        # The args could also come as a dict of dicts (with the variable names)

        checking_timer.start()

        args = {
            "action_0":[3.1415/4,-3.1415/2,-3.1415/2,0,0,0]
        }

        mapping.execute_operation("movejoint",args=args)
        time.sleep(5.0)

        ''' Inputs from the platform (checked on a periodic basis based on the steps) '''
        args = {
            "equation_0": ["flexcellAngularPosition[completed]"]
        }
        result = mapping.get_event("moveCompleted",args=None)
        print("moveCompleted platform event: " + str(result))

        args = {
            "equation_0": ["flexcellAngularPosition[completed]"],
        }
        result = mapping.get_event("robotStopped",args=None)
        print("robotStopped platform event: " + str(result))

        args = {
            "equation_0": [0.05,0.083],
            "equation_1": [0.05,0.083],
        }
        result = mapping.get_event("gripperOpened",args=args)
        print("gripperOpened platform event: " + str(result))

        args = {
            "equation_0": [0.05,0.083],
            "equation_1": [0.05,0.083],
        }
        result = mapping.get_event("gripperClosed",args=args)
        print("gripperClosed platform event: " + str(result))



        # Updating the values based on the platform
        j0 = mapping.get_joint_position("j0")
        j1 = mapping.get_joint_position("j1")
        j2 = mapping.get_joint_position("j2")
        j3 = mapping.get_joint_position("j3")
        j4 = mapping.get_joint_position("j4")
        j5 = mapping.get_joint_position("j5")
        qd0 = mapping.get_joint_velocity("j0")
        qd1 = mapping.get_joint_velocity("j1")
        qd2 = mapping.get_joint_velocity("j2")
        qd3 = mapping.get_joint_velocity("j3")
        qd4 = mapping.get_joint_velocity("j4")
        qd5 = mapping.get_joint_velocity("j5")
        ''' not available in CoppeliaSim
        qdd0 = 0.0
        qdd1 = 0.0
        qdd2 = 0.0
        qdd3 = 0.0
        qdd4 = 0.0
        qdd5 = 0.0
        '''
        t0 = mapping.get_joint_force("j0")
        t1 = mapping.get_joint_force("j1")
        t2 = mapping.get_joint_force("j2")
        t3 = mapping.get_joint_force("j3")
        t4 = mapping.get_joint_force("j4")
        t5 = mapping.get_joint_force("j5")

        fk_matrix = ur_robot_model.compute_fk(j0,j1,j2,j3,j4,j5)
        pose = fk_matrix[:,3]
        x = fk_matrix[:,3][0]
        y = fk_matrix[:,3][1]
        z = fk_matrix[:,3][2]
        rx = fk_matrix[0,0]
        ry = fk_matrix[1,1]
        rz = fk_matrix[2,2]

        # To be characterized first
        args = {
            "equation_0": [qd0,t0,0.05,50],
            "equation_1": [qd1,t1,0.05,50],
            "equation_2": [qd2,t2,0.05,50],
            "equation_3": [qd3,t3,0.05,50],
            "equation_4": [qd4,t4,0.05,50],
            "equation_5": [qd5,t5,0.05,50]
        }
        result = mapping.get_event("collision",args=args)
        print("collision platform event: " + str(result))

        args = {
            "action_0":[2,2,2]
        }

        '''mapping.execute_operation("movediscrete",args=args)
        time.sleep(5.0)

        args = {
            "action_0":[0.2,0.2,0.5] #,0,0,3.1415/4] only x, y, z
        }

        mapping.execute_operation("movecartesian",args=args)
        time.sleep(5.0)'''

        mapping.execute_operation("stop",args=None)

        mapping.execute_operation("pick",args=None)

        mapping.execute_operation("place",args=None)


    finally:
        mapping.stop_simulation()
        checking_timer.cancel()
        print("Application stopped")
