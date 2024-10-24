import pickle
from mapping import mapping as mpp # **Note**: it uses the mapping module previously created

class Model:
    def __init__(self) -> None:
        
        self.mapping = mpp.Mapping()
        self.mapping.start_mapping()

        self.var0_float = 0.0
        self.var1_boolean = False # To d-model FMU
        self.var2_string = ""
        self.var3_int = 0
        self.var4_boolean = False # From controller FMU
        self.var5_boolean = False # From d-model FMU 


        self.reference_to_attribute = {
            0: "var0_float",
            1: "var1_boolean",
            2: "var2_string",
            3: "var3_int",
            4: "var4_boolean",
            5: "var5_boolean",
        }


    def fmi2DoStep(self, current_time, step_size, no_step_prior):
        '''Resetting outputs'''
        self.var1_boolean = False
        self.var2_string = ""

        ''' Input coming from the controller'''

        # Here, you should process the inputs from the controller FMU according to your case study
        # if self.var4_boolean:
        #     # Do something

        ''' Forward commands to the d-model FMU '''
        # Here, you should forward the commands coming from the controller FMU to the d-model FMU

        ''' Inputs from the d-model software '''
        # Here, you should receive the operations from the d-model and the execute them on the robotic platform using the platform mapping interface
        # d-model operation call --> self.mapping.execute_operation("operation",args=operation_args)


        ''' Inputs from the platform (checked on a periodic basis based on the steps) '''
        # Updating the values based on the platform
        # self.var0_float = self.mapping.get_data("var0_data")
        # self.var3_int = self.mapping.get_data("var0_data")

        ''' Computation of events and forwarding them to the d-model '''
        # input_event_args = {
        #     "equation_0" : [self.var0_float],
        #     "equation_1" : [self.var3_int],
        #     ...
        # }
        # result = self.mapping.get_event("some_input_event",args=input_event_args)
        # self.var5_boolean = all(it == True for it in result)
        # print("var5_boolean platform event: " + str(self.var5_boolean))

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
                self.var0_float,
                self.var1_boolean,
                self.var2_string,
                self.var3_int,
                self.var4_boolean,
                self.var5_boolean,
            )
        )
        return Fmi2Status.ok, bytes

    def fmi2ExtDeserialize(self, bytes) -> int:
        (
            var0_float,
            var1_boolean,
            var2_string,
            var3_int,
            var4_boolean,
            var5_boolean,
        ) = pickle.loads(bytes)
        self.var0_float = var0_float
        self.var1_boolean = var1_boolean
        self.var2_string = var2_string
        self.var3_int = var3_int
        self.var4_boolean = var4_boolean
        self.var5_boolean = var5_boolean

        return Fmi2Status.ok

    def fmi2Terminate(self):
        self.mapping.stop_mapping()
        return Fmi2Status.ok

    def fmi2FreeInstance(self):
        self.mapping.stop_mapping()
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