/*
	This file contains function definitions derived from the controller cm.
*/

#ifndef CTRL_CM__H
#define CTRL_CM__H
#define _POSIX_C_SOURCE 200112L

#include "defs.h"
#include <threads.h>
#include <stdio.h>

void ctrl_cm_step(sm_input_Enum_Channel* start_sm
                    , sm_output_Enum_Channel* end_sm) {
    {
        char _s0[256];
        sprintf(_s0, "%s", "	Started step of controller cm");
        fprintf(log_file, "DEBUG: %s\n", _s0);
    }
}
	

void *ctrl_cm_thread(void *arg) {
	ctrl_cm_thread_Channels* channels = (ctrl_cm_thread_Channels*) arg;
	C_cm_input_Enum_Channel* start_cm = channels->start_cm;
	sm_output_Enum_Channel* end_sm = channels->end_sm;
	C_cm_output_Enum_Channel* end_cm = channels->end_cm;
	sm_input_Enum_Channel* start_sm = channels->start_sm;
    {
        bool terminate__ = false;
        while (!terminate__) {
            {
                bool inputDone = false;
                while (!inputDone) {
                    {
                        char _s0[256];
                        sprintf(_s0, "%s", "- Waiting for input on channel start_cm");
                        fprintf(log_file, "DEBUG: %s\n", _s0);
                    }
                    C_cm_input_Enum _input_;
                    {	
                        pthread_barrier_wait(&start_cm->can_write);
                        pthread_barrier_wait(&start_cm->can_read);
                        _input_ = start_cm->value;	
                    }
                    {
                        char _s0[256];
                        sprintf(_s0, "%s", "- Read input on channel start_cm");
                        fprintf(log_file, "DEBUG: %s\n", _s0);
                    }
                    if (_input_.type == C_cm_input_moveCompleted) {
                        {
                            pthread_barrier_wait(&start_sm->can_write);
                            start_sm->value = create_sm_input_moveCompleted();
                            pthread_barrier_wait(&start_sm->can_read);
                        }
                    }
                    else if (_input_.type == C_cm_input_closeGripperCommand) {
                            {
                                pthread_barrier_wait(&start_sm->can_write);
                                start_sm->value = create_sm_input_closeGripperCommand();
                                pthread_barrier_wait(&start_sm->can_read);
                            }
                        }
                    else if (_input_.type == C_cm_input_openGripperCommand) {
                            {
                                pthread_barrier_wait(&start_sm->can_write);
                                start_sm->value = create_sm_input_openGripperCommand();
                                pthread_barrier_wait(&start_sm->can_read);
                            }
                        }
                    else if (_input_.type == C_cm_input_nonfeasibleMoveDiscreteCommand) {
                            {
                                pthread_barrier_wait(&start_sm->can_write);
                                start_sm->value = create_sm_input_nonfeasibleMoveDiscreteCommand();
                                pthread_barrier_wait(&start_sm->can_read);
                            }
                        }
                    else if (_input_.type == C_cm_input_robotStopped) {
                            {
                                pthread_barrier_wait(&start_sm->can_write);
                                start_sm->value = create_sm_input_robotStopped();
                                pthread_barrier_wait(&start_sm->can_read);
                            }
                        }
                    else if (_input_.type == C_cm_input_gripperOpened) {
                            {
                                pthread_barrier_wait(&start_sm->can_write);
                                start_sm->value = create_sm_input_gripperOpened();
                                pthread_barrier_wait(&start_sm->can_read);
                            }
                        }
                    else if (_input_.type == C_cm_input_feasibleMoveDiscreteCommand) {
                            {
                                pthread_barrier_wait(&start_sm->can_write);
                                start_sm->value = create_sm_input_feasibleMoveDiscreteCommand();
                                pthread_barrier_wait(&start_sm->can_read);
                            }
                        }
                    else if (_input_.type == C_cm_input_collision) {
                            {
                                pthread_barrier_wait(&start_sm->can_write);
                                start_sm->value = create_sm_input_collision();
                                pthread_barrier_wait(&start_sm->can_read);
                            }
                        }
                    else if (_input_.type == C_cm_input_gripperClosed) {
                            {
                                pthread_barrier_wait(&start_sm->can_write);
                                start_sm->value = create_sm_input_gripperClosed();
                                pthread_barrier_wait(&start_sm->can_read);
                            }
                        }
                    else if (_input_.type == C_cm_input_moveDiscreteCommand) {
                            MovementArgs _aux1_ = _input_.data.moveDiscreteCommand.v1;
                            {
                                pthread_barrier_wait(&start_sm->can_write);
                                start_sm->value = create_sm_input_moveDiscreteCommand(_aux1_);
                                pthread_barrier_wait(&start_sm->can_read);
                            }
                        }
                    else if (_input_.type == C_cm_input__done_) {
                            {
                                pthread_barrier_wait(&start_sm->can_write);
                                start_sm->value = create_sm_input__done_();
                                pthread_barrier_wait(&start_sm->can_read);
                            }
                            inputDone = true;
                        }
                    else if (_input_.type == C_cm_input__terminate_) {
                            {
                                pthread_barrier_wait(&start_sm->can_write);
                                start_sm->value = create_sm_input__terminate_();
                                pthread_barrier_wait(&start_sm->can_read);
                            }
                            terminate__ = true;
                        }
                }
                
            }
            {
                char _s0[256];
                sprintf(_s0, "%s", "	Finished reading inputs of controller cm");
                fprintf(log_file, "DEBUG: %s\n", _s0);
            }
            ctrl_cm_step(start_sm
                        , end_sm);
            {
                bool outputDone = false;
                while (!outputDone) {
                    sm_output_Enum _output_;
                    {	
                        pthread_barrier_wait(&end_sm->can_write);
                        pthread_barrier_wait(&end_sm->can_read);
                        _output_ = end_sm->value;	
                    }
                    if (_output_.type == sm_output_movejoint) {
                        float _aux1_ = _output_.data.movejoint.v1;
                        {
                            pthread_barrier_wait(&end_cm->can_write);
                            end_cm->value = create_C_cm_output_movejoint(_aux1_);
                            pthread_barrier_wait(&end_cm->can_read);
                        }
                    }
                    else if (_output_.type == sm_output_movecartesian) {
                            float _aux1_ = _output_.data.movecartesian.v1;
                            float _aux2_ = _output_.data.movecartesian.v2;
                            float _aux3_ = _output_.data.movecartesian.v3;
                            float _aux4_ = _output_.data.movecartesian.v4;
                            {
                                pthread_barrier_wait(&end_cm->can_write);
                                end_cm->value = create_C_cm_output_movecartesian(_aux1_
                                                                                ,_aux2_
                                                                                ,_aux3_
                                                                                ,_aux4_);
                                pthread_barrier_wait(&end_cm->can_read);
                            }
                        }
                    else if (_output_.type == sm_output_movediscrete) {
                            int _aux1_ = _output_.data.movediscrete.v1;
                            int _aux2_ = _output_.data.movediscrete.v2;
                            int _aux3_ = _output_.data.movediscrete.v3;
                            float _aux4_ = _output_.data.movediscrete.v4;
                            {
                                pthread_barrier_wait(&end_cm->can_write);
                                end_cm->value = create_C_cm_output_movediscrete(_aux1_
                                                                                ,_aux2_
                                                                                ,_aux3_
                                                                                ,_aux4_);
                                pthread_barrier_wait(&end_cm->can_read);
                            }
                        }
                    else if (_output_.type == sm_output_setvelocity) {
                            float _aux1_ = _output_.data.setvelocity.v1;
                            {
                                pthread_barrier_wait(&end_cm->can_write);
                                end_cm->value = create_C_cm_output_setvelocity(_aux1_);
                                pthread_barrier_wait(&end_cm->can_read);
                            }
                        }
                    else if (_output_.type == sm_output_stop) {
                            {
                                pthread_barrier_wait(&end_cm->can_write);
                                end_cm->value = create_C_cm_output_stop();
                                pthread_barrier_wait(&end_cm->can_read);
                            }
                        }
                    else if (_output_.type == sm_output_reset) {
                            {
                                pthread_barrier_wait(&end_cm->can_write);
                                end_cm->value = create_C_cm_output_reset();
                                pthread_barrier_wait(&end_cm->can_read);
                            }
                        }
                    else if (_output_.type == sm_output_pick) {
                            float _aux1_ = _output_.data.pick.v1;
                            float _aux2_ = _output_.data.pick.v2;
                            float _aux3_ = _output_.data.pick.v3;
                            {
                                pthread_barrier_wait(&end_cm->can_write);
                                end_cm->value = create_C_cm_output_pick(_aux1_
                                                                        ,_aux2_
                                                                        ,_aux3_);
                                pthread_barrier_wait(&end_cm->can_read);
                            }
                        }
                    else if (_output_.type == sm_output_place) {
                            float _aux1_ = _output_.data.place.v1;
                            float _aux2_ = _output_.data.place.v2;
                            float _aux3_ = _output_.data.place.v3;
                            {
                                pthread_barrier_wait(&end_cm->can_write);
                                end_cm->value = create_C_cm_output_place(_aux1_
                                                                        ,_aux2_
                                                                        ,_aux3_);
                                pthread_barrier_wait(&end_cm->can_read);
                            }
                        }
                    else if (_output_.type == sm_output__done_) {
                            {
                                pthread_barrier_wait(&end_cm->can_write);
                                end_cm->value = create_C_cm_output__done_();
                                pthread_barrier_wait(&end_cm->can_read);
                            }
                            outputDone = true;
                        }
                }
                
            }
        }
    }
}

#endif