#ifndef INTERFACE
#define INTERFACE

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "defs.h"
#include "aux.h"
#include "defs_fmi.h"

ModelData* fmi_data_interface;
void update_fmi_data(ModelData* comp){
  fmi_data_interface = comp;
}

M_DiscreteGrippingArm_input_Enum read_input() {
    if (fmi_data_interface->nonfeasibleMoveDiscreteCommand) {
        {
            char _s0[256];
            //sprintf(_s0, "%s", "Found event nonfeasibleMoveDiscreteCommand");
            //printf("%s\n", _s0);
            }
        {
            fmi_data_interface->nonfeasibleMoveDiscreteCommand = false;
            return create_M_DiscreteGrippingArm_input_nonfeasibleMoveDiscreteCommand();
        }
    }
    if (fmi_data_interface->closeGripperCommand) {
        {
            char _s0[256];
            //sprintf(_s0, "%s", "Found event closeGripperCommand");
            //printf("%s\n", _s0);
            }
        {
            fmi_data_interface->closeGripperCommand = false;
            return create_M_DiscreteGrippingArm_input_closeGripperCommand();
        }
    }
    else if (fmi_data_interface->collision) {
        {
            char _s0[256];
            //sprintf(_s0, "%s", "Found event collision");
            //printf("%s\n", _s0);
            }
        {
            fmi_data_interface->collision = false;
            return create_M_DiscreteGrippingArm_input_collision();
        }
    }
    else if (fmi_data_interface->gripperOpened) {
        {
            char _s0[256];
            //sprintf(_s0, "%s", "Found event gripperOpened");
            //printf("%s\n", _s0);
            }
        {
            fmi_data_interface->gripperOpened = false;
            return create_M_DiscreteGrippingArm_input_gripperOpened();
        }
    }
    else if (fmi_data_interface->feasibleMoveDiscreteCommand) {
        {
            char _s0[256];
            //sprintf(_s0, "%s", "Found event feasibleMoveDiscreteCommand");
            //printf("%s\n", _s0);
            }
        {
            fmi_data_interface->feasibleMoveDiscreteCommand = false;
            return create_M_DiscreteGrippingArm_input_feasibleMoveDiscreteCommand();
        }
    }
    else if (fmi_data_interface->openGripperCommand) {
        {
            char _s0[256];
            //sprintf(_s0, "%s", "Found event openGripperCommand");
            //printf("%s\n", _s0);
            }
        {
            fmi_data_interface->openGripperCommand = false;
            return create_M_DiscreteGrippingArm_input_openGripperCommand();
        }
    }
    else if (fmi_data_interface->robotStopped) {
        {
            char _s0[256];
            //sprintf(_s0, "%s", "Found event robotStopped");
            //printf("%s\n", _s0);
            }
        {
            fmi_data_interface->robotStopped = false;
            return create_M_DiscreteGrippingArm_input_robotStopped();
        }
    }
    else if (fmi_data_interface->gripperClosed) {
        {
            char _s0[256];
            //sprintf(_s0, "%s", "Found event gripperClosed");
            //printf("%s\n", _s0);
            }
        {
            fmi_data_interface->gripperClosed = false;
            return create_M_DiscreteGrippingArm_input_gripperClosed();
        }
    }
    else if (fmi_data_interface->moveCompleted) {
        {
            char _s0[256];
            //sprintf(_s0, "%s", "Found event moveCompleted");
            //printf("%s\n", _s0);
            }
        {
            fmi_data_interface->moveCompleted = false;
            return create_M_DiscreteGrippingArm_input_moveCompleted();
        }
    }
    else if (fmi_data_interface->moveDiscreteCommand) {
        {
            char _s0[256];
            //sprintf(_s0, "%s", "Found event moveDiscreteCommand");
            //printf("%s\n", _s0);
            }
        {
            MovementArgs _value_ = (MovementArgs) {
                                    .target_Y = 0
                                    ,
                                    .target_Z = 0
                                    ,
                                    .target_X = 0
                                    };
            {
                {
                    (_value_).target_Y = fmi_data_interface->MovementArgs_target_Y;
                }
            }
            {
                {
                    (_value_).target_Z = fmi_data_interface->MovementArgs_target_Z;
                }
            }
            {
                {
                    (_value_).target_X = fmi_data_interface->MovementArgs_target_X;
                }
            }
            {
                fmi_data_interface->moveDiscreteCommand = false; // to shutdown memory
                return create_M_DiscreteGrippingArm_input_moveDiscreteCommand(_value_);
            }
        }
    }
    else if (fmi_data_interface->terminateSimulation) {
        {
            char _s0[256];
            sprintf(_s0, "%s", "Terminating system. One more cycle will run before this program ends.");
            printf("%s\n", _s0);
        }
        {
            return create_M_DiscreteGrippingArm_input__terminate_();
        }
    }
    else {
        return create_M_DiscreteGrippingArm_input__done_();
    }

}

void write_output(M_DiscreteGrippingArm_output_Enum _output_) {
    // Reset memories when starting the write_output function
    /*fmi_data_interface->movediscrete = false;
    fmi_data_interface->pick = false;
    fmi_data_interface->place = false;
    fmi_data_interface->stop = false;
    fmi_data_interface->movejoint = false;
    fmi_data_interface->movecartesian = false;
    fmi_data_interface->setvelocity = false;*/

    if (_output_.type == M_DiscreteGrippingArm_output_movecartesian) {
        // unused
        float _aux1_ = _output_.data.movecartesian.v1;
        float _aux2_ = _output_.data.movecartesian.v2;
        float _aux3_ = _output_.data.movecartesian.v3;
        float _aux4_ = _output_.data.movecartesian.v4;
        float _aux5_ = _output_.data.movecartesian.v5;
        float _aux6_ = _output_.data.movecartesian.v6;
        {
            fmi_data_interface->movecartesian = true;
            fmi_data_interface->target_x = _aux1_;
            fmi_data_interface->target_y = _aux2_;
            fmi_data_interface->target_z = _aux3_;
            fmi_data_interface->target_rx = _aux4_;
            fmi_data_interface->target_ry = _aux5_;
            fmi_data_interface->target_rz = _aux6_;
        }
    }
    else if (_output_.type == M_DiscreteGrippingArm_output_setvelocity) {
        // unused
        float _aux1_ = _output_.data.setvelocity.v1;
        {
            fmi_data_interface->setvelocity = true;
            fmi_data_interface->target_v = _aux1_;
        }
    }
    else if (_output_.type == M_DiscreteGrippingArm_output_movediscrete) {
            fmi_data_interface->state = "ArmMove";
            int _aux1_ = _output_.data.movediscrete.v1;
            int _aux2_ = _output_.data.movediscrete.v2;
            int _aux3_ = _output_.data.movediscrete.v3;
            {
                fmi_data_interface->movediscrete = true;
                fmi_data_interface->target_X = _aux1_;
                fmi_data_interface->target_Y = _aux2_;
                fmi_data_interface->target_Z = _aux3_;

            }
          }
    else if (_output_.type == M_DiscreteGrippingArm_output_place) {
            fmi_data_interface->state = "GripperOpen";
            float _aux1_ = _output_.data.place.v1;
            float _aux2_ = _output_.data.place.v2;
            float _aux3_ = _output_.data.place.v3;
            {
                fmi_data_interface->place = true;
                fmi_data_interface->opening_diameter = _aux1_;
                fmi_data_interface->opening_speed = _aux2_;
                fmi_data_interface->opening_force = _aux3_;
            }
          }
    else if (_output_.type == M_DiscreteGrippingArm_output_stop) {
            fmi_data_interface->state = "ArmStop";
            {
                fmi_data_interface->stop = true;
            }
          }
    else if (_output_.type == M_DiscreteGrippingArm_output_movejoint) {
        // Unused
        float _aux1_ = _output_.data.movejoint.v1;
        float _aux2_ = _output_.data.movejoint.v2;
        float _aux3_ = _output_.data.movejoint.v3;
        float _aux4_ = _output_.data.movejoint.v4;
        float _aux5_ = _output_.data.movejoint.v5;
        float _aux6_ = _output_.data.movejoint.v6;
        {
            fmi_data_interface->movejoint = true;
            fmi_data_interface->target_q0 = _aux1_;
            fmi_data_interface->target_q1 = _aux2_;
            fmi_data_interface->target_q2 = _aux3_;
            fmi_data_interface->target_q3 = _aux4_;
            fmi_data_interface->target_q4 = _aux5_;
            fmi_data_interface->target_q5 = _aux6_;
        }

    }
    else if (_output_.type == M_DiscreteGrippingArm_output_pick) {
        fmi_data_interface->state = "GripperClose";
        float _aux1_ = _output_.data.pick.v1;
        float _aux2_ = _output_.data.pick.v2;
        float _aux3_ = _output_.data.pick.v3;
        {
            fmi_data_interface->pick = true;
            fmi_data_interface->closing_diameter = _aux1_;
            fmi_data_interface->closing_speed = _aux2_;
            fmi_data_interface->closing_force = _aux3_;
        }
    }
    else if (_output_.type == M_DiscreteGrippingArm_output__done_) {
    }
}

#endif
