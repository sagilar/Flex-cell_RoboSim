#ifndef INTERFACE
#define INTERFACE

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "defs.h"
#include "aux.h"

M_DiscreteGrippingArm_input_Enum read_input() {
    {
        char _s0[256];
        sprintf(_s0, "%s", "Enter an event:");
        printf("%s", _s0);
    }
    char* _event_;
    char _temp_0[256];
    if (fgets(_temp_0, sizeof(_temp_0), stdin) == NULL) exit (0);
    _event_ = trim(_temp_0,NULL);
    if (strcmp(_event_, "nonfeasibleMoveDiscreteCommand") == 0) {
        {
            char _s0[256];
            sprintf(_s0, "%s", "Found event nonfeasibleMoveDiscreteCommand");
            printf("%s\n", _s0);}
        {
            return create_M_DiscreteGrippingArm_input_nonfeasibleMoveDiscreteCommand();
        }
    }
    else if (strcmp(_event_, "closeGripperCommand") == 0) {
            {
                char _s0[256];
                sprintf(_s0, "%s", "Found event closeGripperCommand");
                printf("%s\n", _s0);}
            {
                return create_M_DiscreteGrippingArm_input_closeGripperCommand();
            }
            }
    else if (strcmp(_event_, "") == 0) {
            {
                return create_M_DiscreteGrippingArm_input__done_();
            }
    }
    else if (strcmp(_event_, "collision") == 0) {
            {
                char _s0[256];
                sprintf(_s0, "%s", "Found event collision");
                printf("%s\n", _s0);}
            {
                return create_M_DiscreteGrippingArm_input_collision();
            }
            }
    else if (strcmp(_event_, "gripperOpened") == 0) {
            {
                char _s0[256];
                sprintf(_s0, "%s", "Found event gripperOpened");
                printf("%s\n", _s0);}
            {
                return create_M_DiscreteGrippingArm_input_gripperOpened();
            }
            }
    else if (strcmp(_event_, "feasibleMoveDiscreteCommand") == 0) {
            {
                char _s0[256];
                sprintf(_s0, "%s", "Found event feasibleMoveDiscreteCommand");
                printf("%s\n", _s0);}
            {
                return create_M_DiscreteGrippingArm_input_feasibleMoveDiscreteCommand();
            }
            }
    else if (strcmp(_event_, "openGripperCommand") == 0) {
            {
                char _s0[256];
                sprintf(_s0, "%s", "Found event openGripperCommand");
                printf("%s\n", _s0);}
            {
                return create_M_DiscreteGrippingArm_input_openGripperCommand();
            }
            }
    else if (strcmp(_event_, "robotStopped") == 0) {
            {
                char _s0[256];
                sprintf(_s0, "%s", "Found event robotStopped");
                printf("%s\n", _s0);}
            {
                return create_M_DiscreteGrippingArm_input_robotStopped();
            }
            }
    else if (strcmp(_event_, "moveCompleted") == 0) {
            {
                char _s0[256];
                sprintf(_s0, "%s", "Found event moveCompleted");
                printf("%s\n", _s0);}
            {
                return create_M_DiscreteGrippingArm_input_moveCompleted();
            }
            }
    else if (strcmp(_event_, "gripperClosed") == 0) {
            {
                char _s0[256];
                sprintf(_s0, "%s", "Found event gripperClosed");
                printf("%s\n", _s0);}
            {
                return create_M_DiscreteGrippingArm_input_gripperClosed();
            }
            }
    else if (strcmp(_event_, "moveDiscreteCommand") == 0) {
        {
            char _s0[256];
            sprintf(_s0, "%s", "Found event moveDiscreteCommand");
            printf("%s\n", _s0);}
        {
            char _s0[256];
            sprintf(_s0, "%s", "Enter value for event moveDiscreteCommand of type MovementArgs. Each attribute will be requested one at a time. ");
            printf("%s\n", _s0);}
        {
                MovementArgs _value_ = (MovementArgs) {
                                        .target_X = 0
                                        ,
                                        .target_Y = 0
                                        ,
                                        .target_Z = 0
                                        };
                {
                    {
                        char _s0[256];
                        sprintf(_s0, "%s", "Enter value for attribute target_X of type integer: ");
                        printf("%s", _s0);
                    }
                    {
                        char* _svalue_;
                        char _temp_0[256];
                        if (fgets(_temp_0, sizeof(_temp_0), stdin) == NULL) exit (0);
                        _svalue_ = trim(_temp_0,NULL);
                        int _target_X_value_ = 0;
                        _target_X_value_ = atoi(_svalue_);
                        (_value_).target_X = _target_X_value_;
                    }
                }
                {
                    {
                        char _s0[256];
                        sprintf(_s0, "%s", "Enter value for attribute target_Y of type integer: ");
                        printf("%s", _s0);
                    }
                    {
                        char* _svalue_;
                        char _temp_0[256];
                        if (fgets(_temp_0, sizeof(_temp_0), stdin) == NULL) exit (0);
                        _svalue_ = trim(_temp_0,NULL);
                        int _target_Y_value_ = 0;
                        _target_Y_value_ = atoi(_svalue_);
                        (_value_).target_Y = _target_Y_value_;
                    }
                }
                {
                    {
                        char _s0[256];
                        sprintf(_s0, "%s", "Enter value for attribute target_Z of type integer: ");
                        printf("%s", _s0);
                    }
                    {
                        char* _svalue_;
                        char _temp_0[256];
                        if (fgets(_temp_0, sizeof(_temp_0), stdin) == NULL) exit (0);
                        _svalue_ = trim(_temp_0,NULL);
                        int _target_Z_value_ = 0;
                        _target_Z_value_ = atoi(_svalue_);
                        (_value_).target_Z = _target_Z_value_;
                    }
                }
                {
                    return create_M_DiscreteGrippingArm_input_moveDiscreteCommand(_value_);
                }
            }
    }
    else if (strcmp(_event_, "$end") == 0) {
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
            sprintf(_s0, "%s%s", "Unknown event: ", _event_);
            printf("%s\n", _s0);
        }
        {
            return create_M_DiscreteGrippingArm_input__unknown_();
        }
    }
}

void write_output(M_DiscreteGrippingArm_output_Enum _output_) {
    if (_output_.type == M_DiscreteGrippingArm_output_place) {
        float _aux1_ = _output_.data.place.v1;
        float _aux2_ = _output_.data.place.v2;
        float _aux3_ = _output_.data.place.v3;
        {
            char _s0[256];
            sprintf(_s0, "%s", "output place");
            printf("%s", _s0);
        }
        {
            char _s0[256];
            sprintf(_s0, "%s", "(");
            printf("%s", _s0);
        }
        {
            char _s0[256];
            sprintf(_s0, "%f", _aux1_);
            printf("%s", _s0);
        }
        {
            char _s0[256];
            sprintf(_s0, "%s", ",");
            printf("%s", _s0);
        }
        {
            char _s0[256];
            sprintf(_s0, "%f", _aux2_);
            printf("%s", _s0);
        }
        {
            char _s0[256];
            sprintf(_s0, "%s", ",");
            printf("%s", _s0);
        }
        {
            char _s0[256];
            sprintf(_s0, "%f", _aux3_);
            printf("%s", _s0);
        }
        {
            char _s0[256];
            sprintf(_s0, "%s", ")");
            printf("%s\n", _s0);}
    }
    else if (_output_.type == M_DiscreteGrippingArm_output_movejoint) {
            float _aux1_ = _output_.data.movejoint.v1;
            float _aux2_ = _output_.data.movejoint.v2;
            float _aux3_ = _output_.data.movejoint.v3;
            float _aux4_ = _output_.data.movejoint.v4;
            float _aux5_ = _output_.data.movejoint.v5;
            float _aux6_ = _output_.data.movejoint.v6;
            {
                char _s0[256];
                sprintf(_s0, "%s", "output movejoint");
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", "(");
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%f", _aux1_);
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", ",");
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%f", _aux2_);
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", ",");
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%f", _aux3_);
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", ",");
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%f", _aux4_);
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", ",");
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%f", _aux5_);
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", ",");
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%f", _aux6_);
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", ")");
                printf("%s\n", _s0);}
            }
    else if (_output_.type == M_DiscreteGrippingArm_output_stop) {
            {
                char _s0[256];
                sprintf(_s0, "%s", "output stop");
                printf("%s\n", _s0);}
            }
    else if (_output_.type == M_DiscreteGrippingArm_output_movecartesian) {
            float _aux1_ = _output_.data.movecartesian.v1;
            float _aux2_ = _output_.data.movecartesian.v2;
            float _aux3_ = _output_.data.movecartesian.v3;
            float _aux4_ = _output_.data.movecartesian.v4;
            float _aux5_ = _output_.data.movecartesian.v5;
            float _aux6_ = _output_.data.movecartesian.v6;
            {
                char _s0[256];
                sprintf(_s0, "%s", "output movecartesian");
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", "(");
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%f", _aux1_);
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", ",");
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%f", _aux2_);
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", ",");
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%f", _aux3_);
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", ",");
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%f", _aux4_);
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", ",");
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%f", _aux5_);
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", ",");
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%f", _aux6_);
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", ")");
                printf("%s\n", _s0);}
            }
    else if (_output_.type == M_DiscreteGrippingArm_output_setvelocity) {
            float _aux1_ = _output_.data.setvelocity.v1;
            {
                char _s0[256];
                sprintf(_s0, "%s", "output setvelocity");
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", "(");
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%f", _aux1_);
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", ")");
                printf("%s\n", _s0);}
            }
    else if (_output_.type == M_DiscreteGrippingArm_output_movediscrete) {
            int _aux1_ = _output_.data.movediscrete.v1;
            int _aux2_ = _output_.data.movediscrete.v2;
            int _aux3_ = _output_.data.movediscrete.v3;
            {
                char _s0[256];
                sprintf(_s0, "%s", "output movediscrete");
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", "(");
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%d", _aux1_);
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", ",");
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%d", _aux2_);
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", ",");
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%d", _aux3_);
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", ")");
                printf("%s\n", _s0);}
            }
    else if (_output_.type == M_DiscreteGrippingArm_output_pick) {
            float _aux1_ = _output_.data.pick.v1;
            float _aux2_ = _output_.data.pick.v2;
            float _aux3_ = _output_.data.pick.v3;
            {
                char _s0[256];
                sprintf(_s0, "%s", "output pick");
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", "(");
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%f", _aux1_);
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", ",");
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%f", _aux2_);
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", ",");
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%f", _aux3_);
                printf("%s", _s0);
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", ")");
                printf("%s\n", _s0);}
            }
    else if (_output_.type == M_DiscreteGrippingArm_output__done_) {
        {
            char _s0[256];
            sprintf(_s0, "%s", "---------------------");
            printf("%s\n", _s0);
        }
    }
}

#endif