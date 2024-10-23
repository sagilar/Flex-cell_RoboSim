#Author: Santiago Gil

import io
import types
'''***** Robotic platform-specific *****'''
'''***** URInterface *****'''
## Be sure the Python package is installed: https://gitlab.au.dk/clagms/urinterface
from urinterface.robot_connection import RobotConnection
from pathlib import Path
import csv

'''***** Specific to the case study*****'''
from robotDTLab import robotDTLab # Library for UR3e -> based on the Robotics Toolbox
import numpy as np







class Operation():

    def __init__(self,name="",actions=[],**kwargs):
        self.name = name
        self.actions = actions
        self.arguments = kwargs

    def update_args(self,args):
        self.arguments = args

    def update_actions(self,actions):
        self.actions = actions

    def add_arg(self,dict):
        for key,value in dict.items():
            self.arguments[key] = value

    # This method overwrites all the objects of the same class
    def add_action(self,action):
        self.actions.append(action)

    def delete_actions(self):
        self.actions = []

    def delete_args(self):
        self.arguments = {}

    def execute(self,args):
        results_actions = []
        for action in self.actions:
            action_arguments = None
            idx = self.actions.index(action)
            if idx < len(self.arguments):
                action_arguments = tuple(self.arguments["action_" + str(idx)])
            if action_arguments != None:
                result = action(*action_arguments)
            else:
                result = action()
            if result != None:
                results_actions.append(result)
            else:
                results_actions.append("")
        return results_actions



class InputEvent():
    def __init__(self,name="",equations=[],**kwargs):
        self.name = name
        self.equations = equations
        self.arguments = kwargs

    def update_args(self,args):
        self.arguments = args

    def update_equations(self,equations):
        self.equations = equations

    def add_arg(self,dict):
        for key,value in dict.items():
            self.arguments[key] = value

    ## This method overwrites all the objects of the same class
    def add_equation(self,equation):
        self.equations.append(equation)

    def delete_equations(self):
        self.equations = []

    def delete_args(self):
        self.arguments = {}

    def get_event_result(self,args):
        results_equations = []
        for equation in self.equations:
            equation_arguments = None
            idx = self.equations.index(equation)
            if idx < len(self.arguments):
                equation_arguments = tuple(self.arguments["equation_" + str(idx)])
            if equation_arguments != None:
                result = equation(*equation_arguments)
            else:
                result = equation()
            if result != None:
                results_equations.append(result)
            else:
                results_equations.append("")
        return results_equations

class Mapping():

    def __init__(self,host="192.168.0.11",f_name="mapping_urinterface.csv",config_file="resources_UR/record_configuration.xml"):
        '''Endpoint-specific'''
        self.client = RobotConnection(host) ### Client
        self.data = {}
        self.f_name = f_name
        self.filename = Path(f_name)
        self.config_file =  Path(config_file)
        '''Specific to the case study'''
        self.ur_robot_model = robotDTLab.UR3e_Sim(mqtt_enabled=False,zmq_enabled=False)
        self.ur_robot_model.set_motion_time(2.0)## Definition of the trajectory time

        '''Initialization of data'''
        self.data["actual_q_0"] = 0.0
        self.data["actual_q_1"] = 0.0
        self.data["actual_q_2"] = 0.0
        self.data["actual_q_3"] = 0.0
        self.data["actual_q_4"] = 0.0
        self.data["actual_q_5"] = 0.0
        self.data["actual_qd_0"] = 0.0
        self.data["actual_qd_1"] = 0.0
        self.data["actual_qd_2"] = 0.0
        self.data["actual_qd_3"] = 0.0
        self.data["actual_qd_4"] = 0.0
        self.data["actual_qd_5"] = 0.0
        self.data["actual_TCP_force_0"] = 0.0
        self.data["actual_TCP_force_1"] = 0.0
        self.data["actual_TCP_force_2"] = 0.0
        self.data["actual_TCP_force_3"] = 0.0
        self.data["actual_TCP_force_4"] = 0.0
        self.data["actual_TCP_force_5"] = 0.0
        self.data["target_q_0"] = 0.0
        self.data["target_q_1"] = 0.0
        self.data["target_q_2"] = 0.0
        self.data["target_q_3"] = 0.0
        self.data["target_q_4"] = 0.0
        self.data["target_q_5"] = 0.0
        self.data["target_qd_0"] = 0.0
        self.data["target_qd_1"] = 0.0
        self.data["target_qd_2"] = 0.0
        self.data["target_qd_3"] = 0.0
        self.data["target_qd_4"] = 0.0
        self.data["target_qd_5"] = 0.0

        '''Actions'''
        actions_movejoint = []
        actions_movejoint.append(lambda target_q0: self.set_joint_velocity("j0",target_q0))
        actions_movejoint.append(lambda target_q1: self.set_joint_velocity("j1",target_q1))
        actions_movejoint.append(lambda target_q2: self.set_joint_velocity("j2",target_q2))
        actions_movejoint.append(lambda target_q3: self.set_joint_velocity("j3",target_q3))
        actions_movejoint.append(lambda target_q4: self.set_joint_velocity("j4",target_q4))
        actions_movejoint.append(lambda target_q5: self.set_joint_velocity("j5",target_q5))


        actions_movediscrete = [self._movediscrete] # Condensed action. These perhaps require annotations to generate a function

        actions_movecartesian = [self._movecartesian] # Condensed action. These perhaps require annotations to generate a function

        actions_movejoint = [self._movejoint] # Condensed action. These perhaps require annotations to generate a function

        actions_stop = [self._stop] # Condensed action. These perhaps require annotations to generate a function

        actions_pick = [self._pick] # Condensed action. These perhaps require annotations to generate a function

        actions_place = [self._place] # Condensed action. These perhaps require annotations to generate a function

        actions_setvelocity = []
        actions_setvelocity.append(lambda target_qd0: self.set_joint_velocity("j0",target_qd0))
        actions_setvelocity.append(lambda target_qd1: self.set_joint_velocity("j1",target_qd1))
        actions_setvelocity.append(lambda target_qd2: self.set_joint_velocity("j2",target_qd2))
        actions_setvelocity.append(lambda target_qd3: self.set_joint_velocity("j3",target_qd3))
        actions_setvelocity.append(lambda target_qd4: self.set_joint_velocity("j4",target_qd4))
        actions_setvelocity.append(lambda target_qd5: self.set_joint_velocity("j5",target_qd5))

        '''Equations'''
        equations_nonfeasibleMoveDiscreteCommand = [lambda target_X,target_Y,target_Z: self._calculate_feasibility(target_X,target_Y,target_Z) == False]

        equations_feasibleMoveDiscreteCommand = [lambda target_X,target_Y,target_Z: self._calculate_feasibility(target_X,target_Y,target_Z) == True]

        equations_moveCompleted = []
        equations_moveCompleted.append(lambda : round(self.get_joint_position("j0"),2) == round(self.get_joint_target_position("j0"),2))
        equations_moveCompleted.append(lambda : round(self.get_joint_position("j1"),2) == round(self.get_joint_target_position("j1"),2))
        equations_moveCompleted.append(lambda : round(self.get_joint_position("j2"),2) == round(self.get_joint_target_position("j2"),2))
        equations_moveCompleted.append(lambda : round(self.get_joint_position("j3"),2) == round(self.get_joint_target_position("j3"),2))
        equations_moveCompleted.append(lambda : round(self.get_joint_position("j4"),2) == round(self.get_joint_target_position("j4"),2))
        equations_moveCompleted.append(lambda : round(self.get_joint_position("j5"),2) == round(self.get_joint_target_position("j5"),2))


        equations_robotStopped = []
        equations_robotStopped.append(lambda : round(self.get_joint_velocity("j0"),2)<0.1)
        equations_robotStopped.append(lambda : round(self.get_joint_velocity("j1"),2)<0.1)
        equations_robotStopped.append(lambda : round(self.get_joint_velocity("j2"),2)<0.1)
        equations_robotStopped.append(lambda : round(self.get_joint_velocity("j3"),2)<0.1)
        equations_robotStopped.append(lambda : round(self.get_joint_velocity("j4"),2)<0.1)
        equations_robotStopped.append(lambda : round(self.get_joint_velocity("j5"),2)<0.1)

        equations_gripperClosed = []
        equations_gripperClosed.append(lambda rf,opening: rf<(opening/2 + 0.005))
        equations_gripperClosed.append(lambda lf,opening: lf<(opening/2 + 0.005))

        equations_gripperOpened = []
        equations_gripperOpened.append(lambda rf,opening: rf>(opening/2 - 0.005))
        equations_gripperOpened.append(lambda lf,opening: lf>(opening/2 - 0.005))

        equations_collision = []
        equations_collision.append(lambda qd0,t0,speed_collision,torque_collision: (qd0<speed_collision) and (t0 > torque_collision))
        equations_collision.append(lambda qd1,t1,speed_collision,torque_collision: (qd1<speed_collision) and (t1 > torque_collision))
        equations_collision.append(lambda qd2,t2,speed_collision,torque_collision: (qd2<speed_collision) and (t2 > torque_collision))
        equations_collision.append(lambda qd3,t3,speed_collision,torque_collision: (qd3<speed_collision) and (t3 > torque_collision))
        equations_collision.append(lambda qd4,t4,speed_collision,torque_collision: (qd4<speed_collision) and (t4 > torque_collision))
        equations_collision.append(lambda qd5,t5,speed_collision,torque_collision: (qd5<speed_collision) and (t5 > torque_collision))


        '''Initialization of services -> Operations and Input Events'''
        self.operations_list = []
        self.operations = types.SimpleNamespace() # To be refined with a proper dot notation
        self.operations.movediscrete = Operation(name="movediscrete",actions=actions_movediscrete)
        self.operations.movejoint = Operation(name="movejoint",actions=actions_movejoint)
        self.operations.movecartesian = Operation(name="movecartesian",actions=actions_movecartesian)
        self.operations.setvelocity = Operation(name="setvelocity",actions=actions_setvelocity)
        self.operations.stop = Operation(name="stop",actions=actions_stop)
        self.operations.pick = Operation(name="pick",actions=actions_pick)
        self.operations.place = Operation(name="place",actions=actions_place)
        self.operations_list.extend([self.operations.movediscrete,
                                     self.operations.movejoint,
                                     self.operations.movecartesian,
                                     self.operations.setvelocity,
                                     self.operations.stop,
                                     self.operations.pick,
                                     self.operations.place,])

        self.input_events_list = []
        self.input_events = types.SimpleNamespace()
        self.input_events.nonfeasibleMoveDiscreteCommand = InputEvent(name="nonfeasibleMoveDiscreteCommand",equations=equations_nonfeasibleMoveDiscreteCommand)
        self.input_events.feasibleMoveDiscreteCommand = InputEvent(name="feasibleMoveDiscreteCommand",equations=equations_feasibleMoveDiscreteCommand)
        self.input_events.moveCompleted = InputEvent(name="moveCompleted",equations=equations_moveCompleted)
        self.input_events.robotStopped = InputEvent(name="robotStopped",equations=equations_robotStopped)
        self.input_events.gripperClosed = InputEvent(name="gripperClosed",equations=equations_gripperClosed)
        self.input_events.gripperOpened = InputEvent(name="gripperOpened",equations=equations_gripperOpened)
        self.input_events.collision = InputEvent(name="collision",equations=equations_collision)
        self.input_events_list.extend([self.input_events.nonfeasibleMoveDiscreteCommand,
                                     self.input_events.feasibleMoveDiscreteCommand,
                                     self.input_events.moveCompleted,
                                     self.input_events.robotStopped,
                                     self.input_events.gripperClosed,
                                     self.input_events.gripperOpened,
                                     self.input_events.collision,])

    def start_mapping(self):
        self._start_mapping()

    def stop_mapping(self):
        self._stop_mapping()

    def execute_operation(self,operation_name,args=None):
        exec_op = None
        #for op in self.operations: # Does not work yet
        for op in self.operations_list:
            if op.name == operation_name:
                exec_op = op
        if args != None:
            exec_op.update_args(args)
        #print("Executing operation")
        result = exec_op.execute(exec_op.arguments)
        #print("Operation executed")
        return result

    def get_event(self,input_event_name,args=None):
        event = None
        for ev in self.input_events_list:
            if ev.name == input_event_name:
                event = ev
        if args != None:
            event.update_args(args)
        #print("Reading event")
        result = event.get_event_result(event.arguments)
        #print("Event read")
        return result

    def get_joint_position(self,joint_name):
        return self._get_joint_position(joint_name)

    def get_joint_target_position(self,joint_name):
        return self._get_joint_target_position(joint_name)

    def get_joint_velocity(self,joint_name):
        return self._get_joint_velocity(joint_name)

    def get_joint_target_velocity(self,joint_name):
        return self._get_joint_target_velocity(joint_name)

    def get_joint_force(self,joint_name):
        return self._get_joint_force(joint_name)

    def get_joint_target_force(self,joint_name):
        return self._get_joint_target_force(joint_name)

    def set_joint_position(self,joint_name,val):
        self._set_joint_position(joint_name,val)

    def set_joint_velocity(self,joint_name,val):
        self._set_joint_velocity(joint_name,val)

    def set_joint_force(self,joint_name,val):
        self._set_joint_force(joint_name,val)

    def get_cartesian_positions(self):
        return self._get_cartesian_positions()

    ### Implementations - Update accordingly (specifically to the API of the robotic platform) ###

    '''URInterface Implementations'''
    def _start_mapping(self):
        self.client.start_recording(filename=self.filename, overwrite=True, frequency=10, config_file=self.config_file)

    def _stop_mapping(self):
        self.client.stop_recording()


    def _get_joint_position(self,joint_name):
        self._read_data()
        if (joint_name == "j0"):
            return self.data["actual_q_0"]
        elif (joint_name == "j1"):
            return self.data["actual_q_1"]
        elif (joint_name == "j2"):
            return self.data["actual_q_2"]
        elif (joint_name == "j3"):
            return self.data["actual_q_3"]
        elif (joint_name == "j4"):
            return self.data["actual_q_4"]
        elif (joint_name == "j5"):
            return self.data["actual_q_5"]
        else:
            print("Joint name '" + str(joint_name) + "' does not exist" )

    def _get_joint_velocity(self,joint_name):
        self._read_data()
        if (joint_name == "j0"):
            return self.data["actual_qd_0"]
        elif (joint_name == "j1"):
            return self.data["actual_qd_1"]
        elif (joint_name == "j2"):
            return self.data["actual_qd_2"]
        elif (joint_name == "j3"):
            return self.data["actual_qd_3"]
        elif (joint_name == "j4"):
            return self.data["actual_qd_4"]
        elif (joint_name == "j5"):
            return self.data["actual_qd_5"]
        else:
            print("Joint name '" + str(joint_name) + "' does not exist" )

    def _get_joint_force(self,joint_name):
        self._read_data()
        if (joint_name == "j0"):
            return self.data["actual_TCP_force_0"]
        elif (joint_name == "j1"):
            return self.data["actual_TCP_force_1"]
        elif (joint_name == "j2"):
            return self.data["actual_TCP_force_2"]
        elif (joint_name == "j3"):
            return self.data["actual_TCP_force_3"]
        elif (joint_name == "j4"):
            return self.data["actual_TCP_force_4"]
        elif (joint_name == "j5"):
            return self.data["actual_TCP_force_5"]
        else:
            print("Joint name '" + str(joint_name) + "' does not exist" )

    def _get_joint_target_position(self,joint_name):
        self._read_data()
        if (joint_name == "j0"):
            return self.data["target_q_0"]
        elif (joint_name == "j1"):
            return self.data["target_q_1"]
        elif (joint_name == "j2"):
            return self.data["target_q_2"]
        elif (joint_name == "j3"):
            return self.data["target_q_3"]
        elif (joint_name == "j4"):
            return self.data["target_q_4"]
        elif (joint_name == "j5"):
            return self.data["target_q_5"]
        else:
            print("Joint name '" + str(joint_name) + "' does not exist" )

    def _get_joint_target_velocity(self,joint_name):
        self._read_data()
        if (joint_name == "j0"):
            return self.data["target_qd_0"]
        elif (joint_name == "j1"):
            return self.data["target_qd_1"]
        elif (joint_name == "j2"):
            return self.data["target_qd_2"]
        elif (joint_name == "j3"):
            return self.data["target_qd_3"]
        elif (joint_name == "j4"):
            return self.data["target_qd_4"]
        elif (joint_name == "j5"):
            return self.data["target_qd_5"]
        else:
            print("Joint name '" + str(joint_name) + "' does not exist" )

    def _get_joint_target_force(self,joint_name):
        self._read_data()
        print("Method not available" )

    def _set_joint_position(self,joint_name,val):
        if (joint_name == "j0"):
            self.client.movej(np.array([val,0,0,0,0,0]))
        elif (joint_name == "j1"):
            self.client.movej(np.array([0,val,0,0,0,0]))
        elif (joint_name == "j2"):
            self.client.movej(np.array([0,0,val,0,0,0]))
        elif (joint_name == "j3"):
            self.client.movej(np.array([0,0,0,val,0,0]))
        elif (joint_name == "j4"):
            self.client.movej(np.array([0,0,0,0,val,0]))
        elif (joint_name == "j5"):
            self.client.movej(np.array([0,0,0,0,0,val]))
        else:
            print("Joint name '" + str(joint_name) + "' does not exist" )

    def _set_joint_velocity(self,joint_name,val):
        print("Method not available")

    def _set_joint_force(self,joint_name,val):
        print("Method not available")

    def _get_cartesian_positions(self):
        fk_matrix = self.ur_robot_model.compute_fk(self.data["actual_q_0"],self.data["actual_q_1"],self.data["actual_q_2"],self.data["actual_q_3"],self.data["actual_q_4"],self.data["actual_q_5"])
        pose = fk_matrix[:,3]
        x = fk_matrix[:,3][0]
        y = fk_matrix[:,3][1]
        z = fk_matrix[:,3][2]
        rx = fk_matrix[0,0]
        ry = fk_matrix[1,1]
        rz = fk_matrix[2,2]
        return [x,y,z,rx,ry,rz]

    def _movediscrete(self,target_X,target_Y,target_Z):
        x,yc,zc = self.ur_robot_model.compute_xyz(target_X,target_Y,Z=target_Z)
        target_position = self.ur_robot_model.compute_q(x,yc,zc)[0]
        self.client.movej(target_position)

    def _movecartesian(self, target_x,target_y,target_z): # target_rx,target_ry,target_rz not available for now
        target_position = self.ur_robot_model.compute_q(target_x,target_y,target_z)[0]
        self.client.movej(target_position)

    def _movejoint(self,q0,q1,q2,q3,q4,q5):
        self.client.movej(np.array([q0,q1,q2,q3,q4,q5]))

    def _stop(self):
        self.client.stop_program()

    def _pick(self): # To be implemented with a gripper
        print("Picking method to be implemented")

    def _place(self): # To be implemented with a gripper
        print("Placing method to be implemented")

    def _calculate_feasibility(self,target_X,target_Y,target_Z):
        feasible_motion = self.ur_robot_model.compute_ik_validity(target_X,target_Y,target_Z) # feasibleMoveDiscreteCommand
        return feasible_motion

    # Specific to capture data with the URInterface
    def _read_data(self):
        try:
            with open(self.filename,"r") as csv_file:
                csv_reader = csv.DictReader(csv_file,delimiter=" ")
                dict_data = dict(list(csv_reader)[-1])
                for k,v in dict_data.items():
                    self.data[k] = float(v)
        except Exception as e:
            print("Exception: ", e)

