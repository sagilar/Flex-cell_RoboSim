import pickle
from mapping import mapping as mpp
import time

class Model:
    def __init__(self) -> None:
        self.mapping = mpp.Mapping()
        self.mapping.start_simulation()
        '''equations/actions + arguments'''
        self.args_equation_0 = ""
        self.args_equation_1 = ""
        self.args_equation_2 = ""
        self.args_equation_3 = ""
        self.args_equation_4 = ""
        self.args_equation_5 = ""
        self.args_equation_6 = ""
        self.args_equation_7 = ""
        self.args_equation_8 = ""
        self.args_equation_9 = ""
        self.args_action_0 = ""
        self.args_action_1 = ""
        self.args_action_2 = ""
        self.args_action_3 = ""
        self.args_action_4 = ""
        self.args_action_5 = ""
        self.args_action_6 = ""
        self.args_action_7 = ""
        self.args_action_8 = ""
        self.args_action_9 = ""
        '''operations + arguments'''
        self.operation = ""
        self.args_operation_action_0 = ""
        self.args_operation_action_1 = ""
        self.args_operation_action_2 = ""
        self.args_operation_action_3 = ""
        self.args_operation_action_4 = ""
        self.args_operation_action_5 = ""
        self.args_operation_action_6 = ""
        self.args_operation_action_7 = ""
        self.args_operation_action_8 = ""
        self.args_operation_action_9 = ""
        '''events : prototype for just one event (there may be many concurrent events)'''
        self.controller_event = ""
        self.controller_event_args_0 = ""
        self.controller_event_args_1 = ""
        self.controller_event_args_2 = ""
        self.controller_event_args_3 = ""
        self.controller_event_args_4 = ""
        self.controller_event_args_5 = ""
        self.controller_event_args_6 = ""
        self.controller_event_args_7 = ""
        self.controller_event_args_8 = ""
        self.controller_event_args_9 = ""
        self.d_model_event = ""
        self.d_model_event_args_0 = ""
        self.d_model_event_args_1 = ""
        self.d_model_event_args_2 = ""
        self.d_model_event_args_3 = ""
        self.d_model_event_args_4 = ""
        self.d_model_event_args_5 = ""
        self.d_model_event_args_6 = ""
        self.d_model_event_args_7 = ""
        self.d_model_event_args_8 = ""
        self.d_model_event_args_9 = ""
        ''' Event forwarding -> d-model '''
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

        '''internal variables'''
        self._target_X = 0
        self._target_Y = 0
        self._target_Z = 0
        self._last_event = ""




        self.reference_to_attribute = {
            0: "args_equation_0",
            1: "args_equation_1",
            2: "args_equation_2",
            3: "args_equation_3",
            4: "args_equation_4",
            5: "args_equation_5",
            6: "args_equation_6",
            7: "args_equation_7",
            8: "args_equation_8",
            9: "args_equation_9",
            10: "args_action_0",
            11: "args_action_1",
            12: "args_action_2",
            13: "args_action_3",
            14: "args_action_4",
            15: "args_action_5",
            16: "args_action_6",
            17: "args_action_7",
            18: "args_action_8",
            19: "args_action_9",
            20: "operation",
            21: "args_operation_action_0",
            22: "args_operation_action_1",
            23: "args_operation_action_2",
            24: "args_operation_action_3",
            25: "args_operation_action_4",
            26: "args_operation_action_5",
            27: "args_operation_action_6",
            28: "args_operation_action_7",
            29: "args_operation_action_8",
            30: "args_operation_action_9",
            31: "controller_event",
            32: "controller_event_args_0",
            33: "controller_event_args_1",
            34: "controller_event_args_2",
            35: "controller_event_args_3",
            36: "controller_event_args_4",
            37: "controller_event_args_5",
            38: "controller_event_args_6",
            39: "controller_event_args_7",
            40: "controller_event_args_8",
            41: "controller_event_args_9",
            42: "j0",
            43: "j1",
            44: "j2",
            45: "j3",
            46: "j4",
            47: "j5",
            48: "qd0",
            49: "qd1",
            50: "qd2",
            51: "qd3",
            52: "qd4",
            53: "qd5",
            54: "qdd0",
            55: "qdd1",
            56: "qdd2",
            57: "qdd3",
            58: "qdd4",
            59: "qdd5",
            60: "t0",
            61: "t1",
            62: "t2",
            63: "t3",
            64: "t4",
            65: "t5",
            66: "x",
            67: "y",
            68: "z",
            69: "rx",
            70: "ry",
            71: "rz",
            72: "d_model_event",
            73: "d_model_event_args_0",
            74: "d_model_event_args_1",
            75: "d_model_event_args_2",
            76: "d_model_event_args_3",
            77: "d_model_event_args_4",
            78: "d_model_event_args_5",
            79: "d_model_event_args_6",
            80: "d_model_event_args_7",
            81: "d_model_event_args_8",
            82: "d_model_event_args_9",
            83: "output_event",
            84: "output_event_args_0",
            85: "output_event_args_1",
            86: "output_event_args_2",
            87: "output_event_args_3",
            88: "output_event_args_4",
            89: "output_event_args_5",
            90: "output_event_args_6",
            91: "output_event_args_7",
            92: "output_event_args_8",
            93: "output_event_args_9",

        }


    def fmi2DoStep(self, current_time, step_size, no_step_prior):
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

            self._target_X = self.controller_event_args_0
            self._target_Y = self.controller_event_args_1
            self._target_Z = self.controller_event_args_2

        elif(self.controller_event == "closeGripperCommand"):
            self.output_event = self.controller_event
            self.output_event_args_0 = self.controller_event_args_0
            self.output_event_args_1 = self.controller_event_args_1
            self.output_event_args_2 = self.controller_event_args_2

        elif(self.controller_event == "openGripperCommand"):
            self.output_event = self.controller_event
            self.output_event_args_0 = self.controller_event_args_0
            self.output_event_args_1 = self.controller_event_args_1
            self.output_event_args_2 = self.controller_event_args_2
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
        moveCompleted = all(it == True for it in result)
        print("moveCompleted platform event: " + str(moveCompleted))


        result = self.mapping.get_event("robotStopped",args=None)
        robotStopped = all(it == True for it in result)
        print("robotStopped platform event: " + str(robotStopped))


        args = {
            "equation_0": [0.05,0.083],
            "equation_1": [0.05,0.083],
        }
        result = self.mapping.get_event("gripperOpened",args=args)
        gripperOpened = all(it == True for it in result)
        print("gripperOpened platform event: " + str(gripperOpened))


        args = {
            "equation_0": [0.05,0.083],
            "equation_1": [0.05,0.083],
        }
        result = self.mapping.get_event("gripperClosed",args=args)
        gripperClosed = all(it == True for it in result)
        print("gripperClosed platform event: " + str(gripperClosed))


        if (self._last_event == "moveDiscreteCommand"):
            args = {
                "equation_0": [self._target_X,self.target_Y,self._target_Z],
            }
            result = self.mapping.get_event("feasibleMoveDiscreteCommand",args=args)
            feasibleMoveDiscreteCommand = all(it == True for it in result)
            print("feasibleMoveDiscreteCommand platform event: " + str(feasibleMoveDiscreteCommand))

            args = {
                "equation_0": [self._target_X,self.target_Y,self._target_Z],
            }
            result = self.mapping.get_event("nonfeasibleMoveDiscreteCommand",args=args)
            nonfeasibleMoveDiscreteCommand = all(it == True for it in result)
            print("nonfeasibleMoveDiscreteCommand platform event: " + str(nonfeasibleMoveDiscreteCommand))


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
        collision = all(it == True for it in result)
        print("collision platform event: " + str(collision))




        # Forwarding the events in the platform to the d-model
        self.output_event


        self._last_event = self.output_event

        '''Resetting events'''
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
                self.args_equation_0,
                self.args_equation_1,
                self.args_equation_2,
                self.args_equation_3,
                self.args_equation_4,
                self.args_equation_5,
                self.args_equation_6,
                self.args_equation_7,
                self.args_equation_8,
                self.args_equation_9,
                self.args_action_0,
                self.args_action_1,
                self.args_action_2,
                self.args_action_3,
                self.args_action_4,
                self.args_action_5,
                self.args_action_6,
                self.args_action_7,
                self.args_action_8,
                self.args_action_9,
                self.operation,
                self.args_operation_action_0,
                self.args_operation_action_1,
                self.args_operation_action_2,
                self.args_operation_action_3,
                self.args_operation_action_4,
                self.args_operation_action_5,
                self.args_operation_action_6,
                self.args_operation_action_7,
                self.args_operation_action_8,
                self.args_operation_action_9,
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

            )
        )
        return Fmi2Status.ok, bytes

    def fmi2ExtDeserialize(self, bytes) -> int:
        (
            args_equation_0,
            args_equation_1,
            args_equation_2,
            args_equation_3,
            args_equation_4,
            args_equation_5,
            args_equation_6,
            args_equation_7,
            args_equation_8,
            args_equation_9,
            args_action_0,
            args_action_1,
            args_action_2,
            args_action_3,
            args_action_4,
            args_action_5,
            args_action_6,
            args_action_7,
            args_action_8,
            args_action_9,
            operation,
            args_operation_action_0,
            args_operation_action_1,
            args_operation_action_2,
            args_operation_action_3,
            args_operation_action_4,
            args_operation_action_5,
            args_operation_action_6,
            args_operation_action_7,
            args_operation_action_8,
            args_operation_action_9,
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

        ) = pickle.loads(bytes)
        self.args_equation_0 = args_equation_0
        self.args_equation_1 = args_equation_1
        self.args_equation_2 = args_equation_2
        self.args_equation_3 = args_equation_3
        self.args_equation_4 = args_equation_4
        self.args_equation_5 = args_equation_5
        self.args_equation_6 = args_equation_6
        self.args_equation_7 = args_equation_7
        self.args_equation_8 = args_equation_8
        self.args_equation_9 = args_equation_9
        self.args_action_0 = args_action_0
        self.args_action_1 = args_action_1
        self.args_action_2 = args_action_2
        self.args_action_3 = args_action_3
        self.args_action_4 = args_action_4
        self.args_action_5 = args_action_5
        self.args_action_6 = args_action_6
        self.args_action_7 = args_action_7
        self.args_action_8 = args_action_8
        self.args_action_9 = args_action_9
        self.operation = operation
        self.args_operation_action_0 = args_operation_action_0
        self.args_operation_action_1 = args_operation_action_1
        self.args_operation_action_2 = args_operation_action_2
        self.args_operation_action_3 = args_operation_action_3
        self.args_operation_action_4 = args_operation_action_4
        self.args_operation_action_5 = args_operation_action_5
        self.args_operation_action_6 = args_operation_action_6
        self.args_operation_action_7 = args_operation_action_7
        self.args_operation_action_8 = args_operation_action_8
        self.args_operation_action_9 = args_operation_action_9
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


        return Fmi2Status.ok

    def fmi2Terminate(self):
        self.mapping.stop_simulation()

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


if __name__ == "__main__":
    m = Model()
    assert m.fmi2DoStep(0.0, 1.0, False) == Fmi2Status.ok
    time.sleep(1.0)
    m.fmi2DoStep(1.0, 1.0, False)
    time.sleep(1.0)
    m.fmi2Terminate()
