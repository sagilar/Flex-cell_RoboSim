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
  //printf("Updating fmi data in the interface module\n");
  fmi_data_interface = comp;
}

M_DiscreteGrippingArm_input_Enum read_input() {
    bool gripperOpened = fmi_data_interface->gripperOpened;
  	bool robotStopped = fmi_data_interface->robotStopped;
  	bool closeGripperCommand = fmi_data_interface->closeGripperCommand;
  	bool collision = fmi_data_interface->collision;
  	bool feasibleMoveDiscreteCommand = fmi_data_interface->feasibleMoveDiscreteCommand;
  	bool gripperClosed = fmi_data_interface->gripperClosed;
  	bool nonfeasibleMoveDiscreteCommand = fmi_data_interface->nonfeasibleMoveDiscreteCommand;
  	bool moveCompleted = fmi_data_interface->moveCompleted;
  	bool openGripperCommand = fmi_data_interface->openGripperCommand;
  	bool moveDiscreteCommand = fmi_data_interface->moveDiscreteCommand;
    int target_X = fmi_data_interface->target_X;
    int target_Y = fmi_data_interface->target_Y;
  	int target_Z = fmi_data_interface->target_Z;

    if (nonfeasibleMoveDiscreteCommand) {
        {
            char _s0[256];
            sprintf(_s0, "%s", "Found event nonfeasibleMoveDiscreteCommand");
            printf("%s\n", _s0);}
        {
            fmi_data_interface->nonfeasibleMoveDiscreteCommand = false;
            return create_M_DiscreteGrippingArm_input_nonfeasibleMoveDiscreteCommand();
        }
    }
    else if (closeGripperCommand) {
            {
                char _s0[256];
                sprintf(_s0, "%s", "Found event closeGripperCommand");
                printf("%s\n", _s0);}
            {
                fmi_data_interface->closeGripperCommand = false;
                return create_M_DiscreteGrippingArm_input_closeGripperCommand();
            }
            }
    /*else if (strcmp(_event_, "") == 0) {
            {
                //return create_M_DiscreteGrippingArm_input__done_();
            }
          }*/
    else if (collision) {
            {
                char _s0[256];
                sprintf(_s0, "%s", "Found event collision");
                printf("%s\n", _s0);}
            {
                fmi_data_interface->collision = false;
                return create_M_DiscreteGrippingArm_input_collision();
            }
            }
    else if (gripperOpened) {
            {
                char _s0[256];
                sprintf(_s0, "%s", "Found event gripperOpened");
                printf("%s\n", _s0);}
            {
                fmi_data_interface->gripperOpened = false;
                return create_M_DiscreteGrippingArm_input_gripperOpened();
            }
            }
    else if (feasibleMoveDiscreteCommand) {
            {
                char _s0[256];
                sprintf(_s0, "%s", "Found event feasibleMoveDiscreteCommand");
                printf("%s\n", _s0);}
            {
                fmi_data_interface->feasibleMoveDiscreteCommand = false;
                return create_M_DiscreteGrippingArm_input_feasibleMoveDiscreteCommand();
            }
            }
    else if (openGripperCommand) {
            {
                char _s0[256];
                sprintf(_s0, "%s", "Found event openGripperCommand");
                printf("%s\n", _s0);}
            {
                fmi_data_interface->openGripperCommand = false;
                return create_M_DiscreteGrippingArm_input_openGripperCommand();
            }
            }
    else if (robotStopped) {
            {
                char _s0[256];
                sprintf(_s0, "%s", "Found event robotStopped");
                printf("%s\n", _s0);}
            {
                fmi_data_interface->robotStopped = false;
                return create_M_DiscreteGrippingArm_input_robotStopped();
            }
            }
    else if (gripperClosed) {
            {
                char _s0[256];
                sprintf(_s0, "%s", "Found event gripperClosed");
                printf("%s\n", _s0);}
            {
                fmi_data_interface->gripperClosed = false;
                return create_M_DiscreteGrippingArm_input_gripperClosed();
            }
            }
    else if (moveCompleted) {
            {
                char _s0[256];
                sprintf(_s0, "%s", "Found event moveCompleted");
                printf("%s\n", _s0);}
            {
                fmi_data_interface->moveCompleted = false;
                return create_M_DiscreteGrippingArm_input_moveCompleted();
            }
            }
    else if (moveDiscreteCommand) {
            {
                char _s0[256];
                sprintf(_s0, "%s", "Found event moveDiscreteCommand");
                printf("%s\n", _s0);}
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
                        (_value_).target_Y = target_Y;
                    }
                }
                {
                    {
                        (_value_).target_Z = target_Z;
                    }
                }
                {
                    {
                        (_value_).target_X = target_X;
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
                // terminate__ = true;
                // inputdone = true;
            {
                return create_M_DiscreteGrippingArm_input__terminate_();
            }
    }
    else {
        {
            char _s0[256];
            //sprintf(_s0, "%s%s", "Unknown event: ", _event_);
            //printf("Uknown event\n");
        }
        {
                return create_M_DiscreteGrippingArm_input__done_();
                return create_M_DiscreteGrippingArm_input__unknown_();
        }
    }

}

void write_output(M_DiscreteGrippingArm_output_Enum _output_) {
    //fmi_data_interface->d_model_event = "test command";
    //fmi_data_interface->done = false;
    //fmi_data_interface->status = "ok";
    if (_output_.type == M_DiscreteGrippingArm_output_movecartesian) {
        float _aux1_ = _output_.data.movecartesian.v1;
        float _aux2_ = _output_.data.movecartesian.v2;
        float _aux3_ = _output_.data.movecartesian.v3;
        float _aux4_ = _output_.data.movecartesian.v4;
        {
            fmi_data_interface->d_model_event = "movecartesian";
            fmi_data_interface->d_model_event_args_0 = _aux1_;
            fmi_data_interface->d_model_event_args_1 = _aux2_;
            fmi_data_interface->d_model_event_args_2 = _aux3_;
            fmi_data_interface->d_model_event_args_3 = _aux4_;
        }
    }
    else if (_output_.type == M_DiscreteGrippingArm_output_setvelocity) {

            float _aux1_ = _output_.data.setvelocity.v1;
            {
                fmi_data_interface->d_model_event = "setvelocity";
                fmi_data_interface->d_model_event_args_0 = _aux1_;
            }
          }
    else if (_output_.type == M_DiscreteGrippingArm_output_movediscrete) {
            fmi_data_interface->state = "ArmMove";
            int _aux1_ = _output_.data.movediscrete.v1;
            int _aux2_ = _output_.data.movediscrete.v2;
            int _aux3_ = _output_.data.movediscrete.v3;
            {
                fmi_data_interface->d_model_event = "movediscrete";
                fmi_data_interface->d_model_event_args_0 = _aux1_;
                fmi_data_interface->d_model_event_args_1 = _aux2_;
                fmi_data_interface->d_model_event_args_2 = _aux3_;
            }
          }
    else if (_output_.type == M_DiscreteGrippingArm_output_place) {
            fmi_data_interface->state = "GripperOpen";
            float _aux1_ = _output_.data.place.v1;
            float _aux2_ = _output_.data.place.v2;
            float _aux3_ = _output_.data.place.v3;
            {
                fmi_data_interface->d_model_event = "place";
                fmi_data_interface->d_model_event_args_0 = _aux1_;
                fmi_data_interface->d_model_event_args_1 = _aux2_;
                fmi_data_interface->d_model_event_args_2 = _aux3_;
            }
          }
    else if (_output_.type == M_DiscreteGrippingArm_output_stop) {
            fmi_data_interface->state = "ArmStop";
            {
                fmi_data_interface->d_model_event = "stop";
            }
          }
    else if (_output_.type == M_DiscreteGrippingArm_output_movejoint) {

            float _aux1_ = _output_.data.movejoint.v1;
            {
                fmi_data_interface->d_model_event = "movejoint";
                fmi_data_interface->d_model_event_args_0 = _aux1_;
            }

          }
    else if (_output_.type == M_DiscreteGrippingArm_output_pick) {
            fmi_data_interface->state = "GripperClose";
            float _aux1_ = _output_.data.pick.v1;
            float _aux2_ = _output_.data.pick.v2;
            float _aux3_ = _output_.data.pick.v3;
            {
                fmi_data_interface->d_model_event = "pick";
                fmi_data_interface->d_model_event_args_0 = _aux1_;
            }
          }
    else if (_output_.type == M_DiscreteGrippingArm_output__done_) {
            //fmi_data_interface->state = "Idle";
            //fmi_data_interface->done = true;
            }
}

#endif
