#Author: Santiago Gil

import io
import types
'''***** Robotic platform-specific *****'''
## Be sure the Python package for communicating with the robotic platform is installed and running

'''***** Specific to the case study*****'''
## Add extra libraries if needed for your case study

class Operation():
    ## No need to update
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
    ## No need to update
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

    def __init__(self,host="localhost",port=23000):
        '''Endpoint-specific'''
        # Initialize the connection between endpoint and Python here using the host's IP address and port provided    

        '''Specific to the case study'''
        # Initialize the communication threads, publishers, and subscribers (and callbacks) required for the case study

        # State: Initialize a dict/object based on the variables defined in the RoboSim module to store the state of the variables to be monitored/controlled
        self.data = {} # generic data dict/object
        self.data["var0_float"] = 0.0
        self.data["var1_boolean"] = False
        self.data["var2_string"] = ""
        self.data["var3_int"] = 0
        self.data["var4_boolean"] = False
        self.data["var5_boolean"] = False
        

        '''Actions'''
        # Actions per operation defined in the RoboSim module
        # actions_operation = [
        #     self.operation_callback(arguments),            
        # ]

        '''Equations'''
        # Equations per input event defined in the RoboSim module
        # equations_input_event = [
        #     lambda : self.get_input_event_state() == 0.0,
        # ]

        '''Initialization of services -> Operations and Input Events'''
        # self.operations_list = []
        # self.operations = types.SimpleNamespace() # To be refined with a proper dot notation
        # self.operations.operation = Operation(name="operation",actions=actions_operation)
        # self.operations_list.extend([self.operations.operation,])

        # self.input_events_list = []
        # self.input_events = types.SimpleNamespace()
        # self.input_events.input_event = InputEvent(name="input_event",equations=equations_input_event)
        # self.input_events_list.extend([self.input_events.input_event,])

    def start_mapping(self):
        self._start_mapping()

    def stop_mapping(self):
        self._stop_mapping()

    def execute_operation(self,operation_name,args=None):
        exec_op = None
        #for op in self.operations:
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

    def get_data(self,var_name):
        return self._get_data(var_name)

    def set_data(self,var_name,val):
        self._set_data(var_name,val)

    ### Implementations - Update accordingly (specifically to the API of the robotic platform) ###

    def _start_mapping(self):
        # Initialize with the endpoint-specific components
        pass

    def _stop_mapping(self):
        # Terminate with the endpoint-specific components
        pass

    def _get_data(self,var_name):
        if (var_name == "var0_float"):
            return self.data["var0_float"]
        elif (var_name == "var1_boolean"):
            return self.data["var1_boolean"]
        elif (var_name == "var2_string"):
            return self.data["var2_string"]
        elif (var_name == "var3_int"):
            return self.data["var3_int"]
        elif (var_name == "var4_boolean"):
            return self.data["var4_boolean"]
        elif (var_name == "var5_boolean"):
            return self.data["var5_boolean"]
        else:
            print("Variable '" + str(var_name) + "' does not exist" )

    def _set_data(self,var_name,val):
        if (var_name == "var0_float"):
            self.data["var0_float"] = val
            # Call the endpoint-specific operation to set the data on the robotic platform
        elif (var_name == "var1_boolean"):
            self.data["var1_boolean"] = val
            # Call the endpoint-specific operation to set the data on the robotic platform
        elif (var_name == "var2_string"):
            self.data["var2_string"] = val
            # Call the endpoint-specific operation to set the data on the robotic platform
        elif (var_name == "var3_int"):
            self.data["var3_int"] = val
            # Call the endpoint-specific operation to set the data on the robotic platform
        elif (var_name == "var4_boolean"):
            self.data["var4_boolean"] = val
            # Call the endpoint-specific operation to set the data on the robotic platform
        elif (var_name == "var5_boolean"):
            self.data["var5_boolean"] = val
            # Call the endpoint-specific operation to set the data on the robotic platform
        else:
            print("Variable '" + str(var_name) + "' does not exist" )

    '''Callbacks (if needed) - update according to the subscribers'''
    def input_event_callback(self, msg):
        self.data[msg.var_name] = msg.data

    def operation_callback(self, msg):
        # Do something at the endpoint
        pass

 ## How it works
'''if __name__=='__main__':
    # Instantiate an object of the parameterized platform mapping interface
    mapping = Mapping(host="localhost",port=23000)
    try:
        # Initialize the mapping interface
        mapping.start_mapping()
        # Do something
        ## Example input event
        input_event_args = {
            "equation_0": some_values_in_a_list,
            "equation_1": [0.1,20.0],
            ...
        }
        result = mapping.get_event("some_input_event",args=input_event_args)

        ## Example operation
        operation_args = {
            "action_0":some_values_in_another_list,
            "action_1":[-3.1415/2],
            ...
        }
        mapping.execute_operation("some_operation",args=operation_args)

        ## Optional: loops

    finally:
        # Stop the mapping interface
        mapping.stop_mapping()
        
'''