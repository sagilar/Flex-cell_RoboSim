import pickle
from mapping import mapping as mpp
import time

class Model:
    def __init__(self) -> None:
        self.mapping = mpp.Mapping()
        self.mapping.start_simulation()
        '''events : prototype for just one event (there may be many concurrent events)'''
        self.controller_event = ""
        self.controller_event_args_0 = 0.0
        self.controller_event_args_1 = 0.0
        self.controller_event_args_2 = 0.0
        self.controller_event_args_3 = 0.0
        self.controller_event_args_4 = 0.0
        self.controller_event_args_5 = 0.0
        self.controller_event_args_6 = 0.0
        self.controller_event_args_7 = 0.0
        self.controller_event_args_8 = 0.0
        self.controller_event_args_9 = 0.0
        self.d_model_event = ""
        self.d_model_event_args_0 = 0.0
        self.d_model_event_args_1 = 0.0
        self.d_model_event_args_2 = 0.0
        self.d_model_event_args_3 = 0.0
        self.d_model_event_args_4 = 0.0
        self.d_model_event_args_5 = 0.0
        self.d_model_event_args_6 = 0.0
        self.d_model_event_args_7 = 0.0
        self.d_model_event_args_8 = 0.0
        self.d_model_event_args_9 = 0.0
        ''' Event forwarding controller -> d-model '''
        self.output_event = ""
        self.output_event_args_0 = 0.0
        self.output_event_args_1 = 0.0
        self.output_event_args_2 = 0.0
        self.output_event_args_3 = 0.0
        self.output_event_args_4 = 0.0
        self.output_event_args_5 = 0.0
        self.output_event_args_6 = 0.0
        self.output_event_args_7 = 0.0
        self.output_event_args_8 = 0.0
        self.output_event_args_9 = 0.0
        '''data'''
        self.j0 = 0.0
        self.j1 = 0.0
        self.j2 = 0.0
        self.j3 = 0.0
        self.j4 = 0.0
        self.j5 = 0.0
        self.qd0 = 0.0
        self.qd1 = 0.0
        self.qd2 = 0.0
        self.qd3 = 0.0
        self.qd4 = 0.0
        self.qd5 = 0.0
        self.qdd0 = 0.0
        self.qdd1 = 0.0
        self.qdd2 = 0.0
        self.qdd3 = 0.0
        self.qdd4 = 0.0
        self.qdd5 = 0.0
        self.t0 = 0.0
        self.t1 = 0.0
        self.t2 = 0.0
        self.t3 = 0.0
        self.t4 = 0.0
        self.t5 = 0.0
        self.x = 0.0
        self.y = 0.0
        self.z = 0.0
        self.rx = 0.0
        self.ry = 0.0
        self.rz = 0.0
        ''' Event forwarding platform -> d-model '''
        self.platform_event_0 = False
        self.platform_event_1 = False
        self.platform_event_2 = False
        self.platform_event_3 = False
        self.platform_event_4 = False
        self.platform_event_5 = False
        self.platform_event_6 = False
        self.platform_event_7 = False
        self.platform_event_8 = False
        self.platform_event_9 = False


        '''internal variables'''
        self._target_X = 0
        self._target_Y = 0
        self._target_Z = 0
        self._last_event = ""
        self._moveDiscreteCommand = False
        self._closeGripperCommand = False
        self._openGripperCommand = False
        self._moveCompleted = False
        self._robotStopped = False
        self._gripperOpened = False
        self._gripperClosed = False
        self._feasibleMoveDiscreteCommand = False
        self._nonfeasibleMoveDiscreteCommand = False
        self._collision = False

        self.reference_to_attribute = {
            0: "controller_event",
            1: "controller_event_args_0",
            2: "controller_event_args_1",
            3: "controller_event_args_2",
            4: "controller_event_args_3",
            5: "controller_event_args_4",
            6: "controller_event_args_5",
            7: "controller_event_args_6",
            8: "controller_event_args_7",
            9: "controller_event_args_8",
            10: "controller_event_args_9",
            11: "j0",
            12: "j1",
            13: "j2",
            14: "j3",
            15: "j4",
            16: "j5",
            17: "qd0",
            18: "qd1",
            19: "qd2",
            20: "qd3",
            21: "qd4",
            22: "qd5",
            23: "qdd0",
            24: "qdd1",
            25: "qdd2",
            26: "qdd3",
            27: "qdd4",
            28: "qdd5",
            29: "t0",
            30: "t1",
            31: "t2",
            32: "t3",
            33: "t4",
            34: "t5",
            35: "d_model_event",
            36: "d_model_event_args_0",
            37: "d_model_event_args_1",
            38: "d_model_event_args_2",
            39: "d_model_event_args_3",
            40: "d_model_event_args_4",
            41: "d_model_event_args_5",
            42: "d_model_event_args_6",
            43: "d_model_event_args_7",
            44: "d_model_event_args_8",
            45: "d_model_event_args_9",
            46: "output_event",
            47: "output_event_args_0",
            48: "output_event_args_1",
            49: "output_event_args_2",
            50: "output_event_args_3",
            51: "output_event_args_4",
            52: "output_event_args_5",
            53: "output_event_args_6",
            54: "output_event_args_7",
            55: "output_event_args_8",
            56: "output_event_args_9",
            57: "platform_event_0",
            58: "platform_event_1",
            59: "platform_event_2",
            60: "platform_event_3",
            61: "platform_event_4",
            62: "platform_event_5",
            63: "platform_event_6",
            64: "platform_event_7",
            65: "platform_event_8",
            66: "platform_event_9",

        }


    def fmi2DoStep(self, current_time, step_size, no_step_prior):
        '''Resetting outputs'''
        self._moveDiscreteCommand = False
        self._closeGripperCommand = False
        self._openGripperCommand = False
        self._moveCompleted = False
        self._robotStopped = False
        self._gripperOpened = False
        self._gripperClosed = False
        self._feasibleMoveDiscreteCommand = False
        self._nonfeasibleMoveDiscreteCommand = False
        self._collision = False
        self.output_event = ""
        self.output_event_args_0 = ""
        self.output_event_args_1 = ""
        self.output_event_args_2 = ""
        self.output_event_args_3 = ""
        self.output_event_args_4 = ""
        self.output_event_args_5 = ""
        self.output_event_args_6 = ""
        self.output_event_args_7 = ""
        self.output_event_args_8 = ""
        self.output_event_args_9 = ""

        ''' Input coming from the controller'''

        print("Controller Event: " + self.controller_event)
        print("Arguments: " + str([self.controller_event_args_0,
                                   self.controller_event_args_1,
                                   self.controller_event_args_2,
                                   self.controller_event_args_3,
                                   self.controller_event_args_4,
                                   self.controller_event_args_5,
                                   self.controller_event_args_6,
                                   self.controller_event_args_7,
                                   self.controller_event_args_8,
                                   self.controller_event_args_9,]))

        # Forward to d-model
        if (self.controller_event == "moveDiscreteCommand"):
            self.output_event = self.controller_event
            self.output_event_args_0 = self.controller_event_args_0
            self.output_event_args_1 = self.controller_event_args_1
            self.output_event_args_2 = self.controller_event_args_2


            self._moveDiscreteCommand = True
            self._target_X = self.controller_event_args_0
            self._target_Y = self.controller_event_args_1
            self._target_Z = self.controller_event_args_2

        elif(self.controller_event == "closeGripperCommand"):
            self.output_event = self.controller_event
            self.output_event_args_0 = self.controller_event_args_0
            self.output_event_args_1 = self.controller_event_args_1
            self.output_event_args_2 = self.controller_event_args_2

            self._closeGripperCommand = True

        elif(self.controller_event == "openGripperCommand"):
            self.output_event = self.controller_event
            self.output_event_args_0 = self.controller_event_args_0
            self.output_event_args_1 = self.controller_event_args_1
            self.output_event_args_2 = self.controller_event_args_2
            self._openGripperCommand = True
        else:
            self.output_event = ""
            self.output_event_args_0 = ""
            self.output_event_args_1 = ""
            self.output_event_args_2 = ""

        ''' Inputs from the d-model software '''
        print("d-model Event: " + self.d_model_event)
        print("Arguments: " + str([self.d_model_event_args_0,
                                   self.d_model_event_args_1,
                                   self.d_model_event_args_2,
                                   self.d_model_event_args_3,
                                   self.d_model_event_args_4,
                                   self.d_model_event_args_5,
                                   self.d_model_event_args_6,
                                   self.d_model_event_args_7,
                                   self.d_model_event_args_8,
                                   self.d_model_event_args_9,]))

        # Forwarding the commands to the platform (CoppeliaSim Implementation)
        if (self.d_model_event == "movediscrete"):
            # IK already inside the mapping module
            args = {
                "action_0":[self.d_model_event_args_0, self.d_model_event_args_1, self.d_model_event_args_2]
            }
            self.mapping.execute_operation("movediscrete",args=args)

        elif (self.d_model_event == "movejoint"):
            args = {
                "action_0":[self.d_model_event_args_0,self.d_model_event_args_1,self.d_model_event_args_2,self.d_model_event_args_3,self.d_model_event_args_4,self.d_model_event_args_5]
            }
            self.mapping.execute_operation("movejoint",args=args)

        elif (self.d_model_event == "pick"): # To be implemented. No gripper for now
            self.mapping.execute_operation("pick",args=None) # to be implemented

        elif (self.d_model_event == "place"): # To be implemented. No gripper for now
            self.mapping.execute_operation("place",args=None) # to be implemented

        elif (self.d_model_event == "stop"):
            self.mapping.execute_operation("stop",args=None)


        ''' Inputs from the platform (checked on a periodic basis based on the steps) '''
        # Updating the values based on the platform
        self.j0 = self.mapping.get_joint_position("j0")
        self.j1 = self.mapping.get_joint_position("j1")
        self.j2 = self.mapping.get_joint_position("j2")
        self.j3 = self.mapping.get_joint_position("j3")
        self.j4 = self.mapping.get_joint_position("j4")
        self.j5 = self.mapping.get_joint_position("j5")
        self.qd0 = self.mapping.get_joint_velocity("j0")
        self.qd1 = self.mapping.get_joint_velocity("j1")
        self.qd2 = self.mapping.get_joint_velocity("j2")
        self.qd3 = self.mapping.get_joint_velocity("j3")
        self.qd4 = self.mapping.get_joint_velocity("j4")
        self.qd5 = self.mapping.get_joint_velocity("j5")
        ''' not available in CoppeliaSim
        self.qdd0 = 0.0
        self.qdd1 = 0.0
        self.qdd2 = 0.0
        self.qdd3 = 0.0
        self.qdd4 = 0.0
        self.qdd5 = 0.0
        '''
        self.t0 = self.mapping.get_joint_force("j0")
        self.t1 = self.mapping.get_joint_force("j1")
        self.t2 = self.mapping.get_joint_force("j2")
        self.t3 = self.mapping.get_joint_force("j3")
        self.t4 = self.mapping.get_joint_force("j4")
        self.t5 = self.mapping.get_joint_force("j5")

        self.x = self.mapping.get_cartesian_positions()[0]
        self.y = self.mapping.get_cartesian_positions()[1]
        self.z = self.mapping.get_cartesian_positions()[2]
        self.rx = self.mapping.get_cartesian_positions()[3]
        self.ry = self.mapping.get_cartesian_positions()[4]
        self.rz = self.mapping.get_cartesian_positions()[5]

        # Events
        result = self.mapping.get_event("moveCompleted",args=None)
        self._moveCompleted = all(it == True for it in result)
        print("moveCompleted platform event: " + str(self._moveCompleted))



        result = self.mapping.get_event("robotStopped",args=None)
        self._robotStopped = all(it == True for it in result)
        print("robotStopped platform event: " + str(self._robotStopped))


        args = {
            "equation_0": [0.05,0.083],
            "equation_1": [0.05,0.083],
        }
        result = self.mapping.get_event("gripperOpened",args=args)
        self._gripperOpened = all(it == True for it in result)
        print("gripperOpened platform event: " + str(self._gripperOpened))


        args = {
            "equation_0": [0.05,0.083],
            "equation_1": [0.05,0.083],
        }
        result = self.mapping.get_event("gripperClosed",args=args)
        self._gripperClosed = all(it == True for it in result)
        print("gripperClosed platform event: " + str(self._gripperClosed))


        if (self._last_event == "moveDiscreteCommand"):
            args = {
                "equation_0": [self._target_X,self._target_Y,self._target_Z],
            }
            result = self.mapping.get_event("feasibleMoveDiscreteCommand",args=args)
            self._feasibleMoveDiscreteCommand = all(it == True for it in result)
            print("feasibleMoveDiscreteCommand platform event: " + str(self._feasibleMoveDiscreteCommand))


            args = {
                "equation_0": [self._target_X,self._target_Y,self._target_Z],
            }
            result = self.mapping.get_event("nonfeasibleMoveDiscreteCommand",args=args)
            self._nonfeasibleMoveDiscreteCommand = all(it == True for it in result)
            print("nonfeasibleMoveDiscreteCommand platform event: " + str(self._nonfeasibleMoveDiscreteCommand))

        # To be characterized first
        args = {
            "equation_0": [self.qd0,self.t0,0.05,50],
            "equation_1": [self.qd1,self.t1,0.05,50],
            "equation_2": [self.qd2,self.t2,0.05,50],
            "equation_3": [self.qd3,self.t3,0.05,50],
            "equation_4": [self.qd4,self.t4,0.05,50],
            "equation_5": [self.qd5,self.t5,0.05,50]
        }
        result = self.mapping.get_event("collision",args=args)
        self._collision = all(it == True for it in result)
        print("collision platform event: " + str(self._collision))





        # Forwarding the events in the platform to the d-model
        self.platform_event_0 = self._moveDiscreteCommand
        self.platform_event_1 = self._closeGripperCommand
        self.platform_event_2 = self._openGripperCommand
        self.platform_event_3 = self._moveCompleted
        self.platform_event_4 = self._robotStopped
        self.platform_event_5 = self._gripperOpened
        self.platform_event_6 = self._gripperClosed
        self.platform_event_7 = self._feasibleMoveDiscreteCommand
        self.platform_event_8 = self._nonfeasibleMoveDiscreteCommand
        self.platform_event_9 = self._collision

        # Storing the last event to avoid repetition
        self._last_event = self.output_event

        return Fmi2Status.ok

    def fmi2EnterInitializationMode(self):
        return Fmi2Status.ok

    def fmi2ExitInitializationMode(self):
        return Fmi2Status.ok

    def fmi2SetupExperiment(self, start_time, stop_time, tolerance):
        return Fmi2Status.ok

    def fmi2SetReal(self, references, values):
        return self._set_value(references, values)

    def fmi2SetInteger(self, references, values):
        return self._set_value(references, values)

    def fmi2SetBoolean(self, references, values):
        return self._set_value(references, values)

    def fmi2SetString(self, references, values):
        return self._set_value(references, values)

    def fmi2GetReal(self, references):
        return self._get_value(references)

    def fmi2GetInteger(self, references):
        return self._get_value(references)

    def fmi2GetBoolean(self, references):
        return self._get_value(references)

    def fmi2GetString(self, references):
        return self._get_value(references)

    def fmi2Reset(self):
        return Fmi2Status.ok

    def fmi2Terminate(self):
        return Fmi2Status.ok

    def fmi2ExtSerialize(self):

        bytes = pickle.dumps(
            (
                self.controller_event,
                self.controller_event_args_0,
                self.controller_event_args_1,
                self.controller_event_args_2,
                self.controller_event_args_3,
                self.controller_event_args_4,
                self.controller_event_args_5,
                self.controller_event_args_6,
                self.controller_event_args_7,
                self.controller_event_args_8,
                self.controller_event_args_9,
                self.d_model_event,
                self.d_model_event_args_0,
                self.d_model_event_args_1,
                self.d_model_event_args_2,
                self.d_model_event_args_3,
                self.d_model_event_args_4,
                self.d_model_event_args_5,
                self.d_model_event_args_6,
                self.d_model_event_args_7,
                self.d_model_event_args_8,
                self.d_model_event_args_9,
                self.output_event,
                self.output_event_args_0,
                self.output_event_args_1,
                self.output_event_args_2,
                self.output_event_args_3,
                self.output_event_args_4,
                self.output_event_args_5,
                self.output_event_args_6,
                self.output_event_args_7,
                self.output_event_args_8,
                self.output_event_args_9,
                self.j0,
                self.j1,
                self.j2,
                self.j3,
                self.j4,
                self.j5,
                self.qd0,
                self.qd1,
                self.qd2,
                self.qd3,
                self.qd4,
                self.qd5,
                self.qdd0,
                self.qdd1,
                self.qdd2,
                self.qdd3,
                self.qdd4,
                self.qdd5,
                self.t0,
                self.t1,
                self.t2,
                self.t3,
                self.t4,
                self.t5,
                self.x,
                self.y,
                self.z,
                self.rx,
                self.ry,
                self.rz,
                self.platform_event_0,
                self.platform_event_1,
                self.platform_event_2,
                self.platform_event_3,
                self.platform_event_4,
                self.platform_event_5,
                self.platform_event_6,
                self.platform_event_7,
                self.platform_event_8,
                self.platform_event_9,


            )
        )
        return Fmi2Status.ok, bytes

    def fmi2ExtDeserialize(self, bytes) -> int:
        (
            controller_event,
            controller_event_args_0,
            controller_event_args_1,
            controller_event_args_2,
            controller_event_args_3,
            controller_event_args_4,
            controller_event_args_5,
            controller_event_args_6,
            controller_event_args_7,
            controller_event_args_8,
            controller_event_args_9,
            d_model_event,
            d_model_event_args_0,
            d_model_event_args_1,
            d_model_event_args_2,
            d_model_event_args_3,
            d_model_event_args_4,
            d_model_event_args_5,
            d_model_event_args_6,
            d_model_event_args_7,
            d_model_event_args_8,
            d_model_event_args_9,
            output_event,
            output_event_args_0,
            output_event_args_1,
            output_event_args_2,
            output_event_args_3,
            output_event_args_4,
            output_event_args_5,
            output_event_args_6,
            output_event_args_7,
            output_event_args_8,
            output_event_args_9,
            j0,
            j1,
            j2,
            j3,
            j4,
            j5,
            qd0,
            qd1,
            qd2,
            qd3,
            qd4,
            qd5,
            qdd0,
            qdd1,
            qdd2,
            qdd3,
            qdd4,
            qdd5,
            t0,
            t1,
            t2,
            t3,
            t4,
            t5,
            x,
            y,
            z,
            rx,
            ry,
            rz,
            platform_event_0,
            platform_event_1,
            platform_event_2,
            platform_event_3,
            platform_event_4,
            platform_event_5,
            platform_event_6,
            platform_event_7,
            platform_event_8,
            platform_event_9,

        ) = pickle.loads(bytes)
        self.controller_event = controller_event
        self.controller_event_args_0 = controller_event_args_0
        self.controller_event_args_1 = controller_event_args_1
        self.controller_event_args_2 = controller_event_args_2
        self.controller_event_args_3 = controller_event_args_3
        self.controller_event_args_4 = controller_event_args_4
        self.controller_event_args_5 = controller_event_args_5
        self.controller_event_args_6 = controller_event_args_6
        self.controller_event_args_7 = controller_event_args_7
        self.controller_event_args_8 = controller_event_args_8
        self.controller_event_args_9 = controller_event_args_9
        self.d_model_event = d_model_event
        self.d_model_event_args_0 = d_model_event_args_0
        self.d_model_event_args_1 = d_model_event_args_1
        self.d_model_event_args_2 = d_model_event_args_2
        self.d_model_event_args_3 = d_model_event_args_3
        self.d_model_event_args_4 = d_model_event_args_4
        self.d_model_event_args_5 = d_model_event_args_5
        self.d_model_event_args_6 = d_model_event_args_6
        self.d_model_event_args_7 = d_model_event_args_7
        self.d_model_event_args_8 = d_model_event_args_8
        self.d_model_event_args_9 = d_model_event_args_9
        self.output_event = output_event
        self.output_event_args_0 = output_event_args_0
        self.output_event_args_1 = output_event_args_1
        self.output_event_args_2 = output_event_args_2
        self.output_event_args_3 = output_event_args_3
        self.output_event_args_4 = output_event_args_4
        self.output_event_args_5 = output_event_args_5
        self.output_event_args_6 = output_event_args_6
        self.output_event_args_7 = output_event_args_7
        self.output_event_args_8 = output_event_args_8
        self.output_event_args_9 = output_event_args_9
        self.j0 = j0
        self.j1 = j1
        self.j2 = j2
        self.j3 = j3
        self.j4 = j4
        self.j5 = j5
        self.qd0 = qd0
        self.qd1 = qd1
        self.qd2 = qd2
        self.qd3 = qd3
        self.qd4 = qd4
        self.qd5 = qd5
        self.qdd0 = qdd0
        self.qdd1 = qdd1
        self.qdd2 = qdd2
        self.qdd3 = qdd3
        self.qdd4 = qdd4
        self.qdd5 = qdd5
        self.t0 = t0
        self.t1 = t1
        self.t2 = t2
        self.t3 = t3
        self.t4 = t4
        self.t5 = t5
        self.x = x
        self.y = y
        self.z = z
        self.rx = rx
        self.ry = ry
        self.rz = rz
        self.platform_event_0 = platform_event_0
        self.platform_event_1 = platform_event_1
        self.platform_event_2 = platform_event_2
        self.platform_event_3 = platform_event_3
        self.platform_event_4 = platform_event_4
        self.platform_event_5 = platform_event_5
        self.platform_event_6 = platform_event_6
        self.platform_event_7 = platform_event_7
        self.platform_event_8 = platform_event_8
        self.platform_event_9 = platform_event_9

        return Fmi2Status.ok

    def fmi2Terminate(self):
        self.mapping.stop_simulation()
        return Fmi2Status.ok

    def _set_value(self, references, values):

        for r, v in zip(references, values):
            setattr(self, self.reference_to_attribute[r], v)

        return Fmi2Status.ok

    def _get_value(self, references):

        values = []

        for r in references:
            values.append(getattr(self, self.reference_to_attribute[r]))

        return Fmi2Status.ok, values




class Fmi2Status:
    """Represents the status of the FMU or the results of function calls.

    Values:
        * ok: all well
        * warning: an issue has arisen, but the computation can continue.
        * discard: an operation has resulted in invalid output, which must be discarded
        * error: an error has ocurred for this specific FMU instance.
        * fatal: an fatal error has ocurred which has corrupted ALL FMU instances.
        * pending: indicates that the FMu is doing work asynchronously, which can be retrived later.

    Notes:
        FMI section 2.1.3

    """

    ok = 0
    warning = 1
    discard = 2
    error = 3
    fatal = 4
    pending = 5


'''if __name__ == "__main__":
    m = Model()
    assert m.fmi2DoStep(0.0, 1.0, False) == Fmi2Status.ok
    time.sleep(1.0)
    m.fmi2DoStep(1.0, 1.0, False)
    time.sleep(1.0)
    m.fmi2Terminate()'''
