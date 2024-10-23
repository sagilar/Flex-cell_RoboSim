#ifndef INTERFACE
#define INTERFACE

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "defs_fmi.h"

ModelData* fmi_data_interface;
void update_fmi_data(ModelData* comp){
  fmi_data_interface = comp;
}

M_RoboSimModule_input_Enum read_input() {
    if (fmi_data_interface->var1_boolean) {
        {
            char _s0[256];
            sprintf(_s0, "%s", "Found event var1_boolean");
            printf("%s\n", _s0);}
        {
            char *_args_ = fmi_data_interface->var2_string;
            fmi_data_interface->var1_boolean = false; // Reset memory
            return create_M_RoboSimModule_input_var1_boolean(_args_);
        }
    }
    else {
            return create_M_RoboSimModule_input__done_();
    }

}

void write_output(M_RoboSimModule_output_Enum _output_) {

    if (_output_.type == M_RoboSimModule_output_var4_boolean) {
        int _aux1_ = _output_.data.var4_boolean.v1;
        {
            fmi_data_interface->var4_boolean = true;
            fmi_data_interface->var3_int = _aux1_;

        }
    }
    else if (_output_.type == M_RoboSimModule_output__done_) {
            
    }
}

#endif
