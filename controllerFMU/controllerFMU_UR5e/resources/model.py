import pickle


class Model:
    def __init__(self) -> None:
        self.controller_event = ""
        self.controller_event_args_0 = 0.0
        self.controller_event_args_1 = 0.0
        self.controller_event_args_2 = 0.0


        self.reference_to_attribute = {
            0: "controller_event",
            1: "controller_event_args_0",
            2: "controller_event_args_1",
            3: "controller_event_args_2"
        }


    def fmi2DoStep(self, current_time, step_size, no_step_prior):
        idx = int(current_time/step_size)
        if (idx==2):
            self.controller_event = "moveDiscreteCommand"
            self.controller_event_args_0 = 0.0
            self.controller_event_args_1 = 23.0
            self.controller_event_args_2 = 1.0
        elif (idx==11):
            self.controller_event = "moveDiscreteCommand"
            self.controller_event_args_0 = 3.0
            self.controller_event_args_1 = 20.0
            self.controller_event_args_2 = 2.0

        elif (idx==16):
            self.controller_event = "moveDiscreteCommand"
            self.controller_event_args_0 = 8.0
            self.controller_event_args_1 = 10.0
            self.controller_event_args_2 = 0.0
        elif (idx==30):
            self.controller_event = "moveDiscreteCommand"
            self.controller_event_args_0 = 1.0
            self.controller_event_args_1 = 13.0
            self.controller_event_args_2 = 0.0
        else:
            self.controller_event = ""
            self.controller_event_args_0 = 0.0
            self.controller_event_args_1 = 0.0
            self.controller_event_args_2 = 0.0
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
                self.controller_event_args_2
            )
        )
        return Fmi2Status.ok, bytes

    def fmi2ExtDeserialize(self, bytes) -> int:
        (
            controller_event,
            controller_event_args_0,
            controller_event_args_1,
            controller_event_args_2,
        ) = pickle.loads(bytes)
        self.controller_event = controller_event
        self.controller_event_args_0 = controller_event_args_0
        self.controller_event_args_1 = controller_event_args_1
        self.controller_event_args_2 = controller_event_args_2

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


if __name__ == "__main__":
    m = Model()

    assert m.real_a == 0.0
    assert m.real_b == 0.0
    assert m.real_c == 0.0
    assert m.integer_a == 0
    assert m.integer_b == 0
    assert m.integer_c == 0
    assert m.boolean_a == False
    assert m.boolean_b == False
    assert m.boolean_c == False
    assert m.string_a == ""
    assert m.string_b == ""
    assert m.string_c == ""

    m.real_a = 1.0
    m.real_b = 2.0
    m.integer_a = 1
    m.integer_b = 2
    m.boolean_a = True
    m.boolean_b = False
    m.string_a = "Hello "
    m.string_b = "World!"

    assert m.fmi2DoStep(0.0, 1.0, False) == Fmi2Status.ok

    assert m.real_c == 3.0
    assert m.integer_c == 3
    assert m.boolean_c == True
    assert m.string_c == "Hello World!"
