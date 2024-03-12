


fmi2DoStep(current_time, step_size, no_step_prior);

fmi2EnterInitializationMode();

fmi2ExitInitializationMode();

fmi2SetupExperiment(start_time, stop_time, tolerance);

fmi2SetReal(self, references, values);

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
               self.real_a,
               self.real_b,
               self.integer_a,
               self.integer_b,
               self.boolean_a,
               self.boolean_b,
               self.string_a,
               self.string_b,
           )
       )
       return Fmi2Status.ok, bytes

   def fmi2ExtDeserialize(self, bytes) -> int:
       (
           real_a,
           real_b,
           integer_a,
           integer_b,
           boolean_a,
           boolean_b,
           string_a,
           string_b,
       ) = pickle.loads(bytes)
       self.real_a = real_a
       self.real_b = real_b
       self.integer_a = integer_a
       self.integer_b = integer_b
       self.boolean_a = boolean_a
       self.boolean_b = boolean_b
       self.string_a = string_a
       self.string_b = string_b
       self._update_outputs()

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

   def _update_outputs(self):
       self.real_c = self.real_a + self.real_b
       self.integer_c = self.integer_a + self.integer_b
       self.boolean_c = self.boolean_a or self.boolean_b
       self.string_c = self.string_a + self.string_b

typedef enum {
  ok = 0;
  warning = 1;
  discard = 2;
  error = 3;
  fatal = 4;
  pending = 5;
} Fmi2Status;

class Fmi2Status:
           /*Represents the status of the FMU or the results of function calls.

           Values:
               * ok: all well
               * warning: an issue has arisen, but the computation can continue.
               * discard: an operation has resulted in invalid output, which must be discarded
               * error: an error has ocurred for this specific FMU instance.
               * fatal: an fatal error has ocurred which has corrupted ALL FMU instances.
               * pending: indicates that the FMu is doing work asynchronously, which can be retrived later.

           Notes:
               FMI section 2.1.3

           */

           ok = 0
           warning = 1
           discard = 2
           error = 3
           fatal = 4
           pending = 5
