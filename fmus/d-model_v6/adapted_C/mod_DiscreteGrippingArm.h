/*
	This file contains function definitions derived from the module DiscreteGrippingArm.
*/

#ifndef MOD_DISCRETEGRIPPINGARM__H
#define MOD_DISCRETEGRIPPINGARM__H
#define _POSIX_C_SOURCE 200112L

#include "defs.h"
#include <threads.h>
#include <stdio.h>

void mod_DiscreteGrippingArm_step(C_cm_input_Enum_Channel* start_cm
									, C_cm_output_Enum_Channel* end_cm) {
	{
		char _s0[256];
		sprintf(_s0, "%s", "Started step of module DiscreteGrippingArm");
		fprintf(log_file, "DEBUG: %s\n", _s0);
	}
	{
		char _s0[256];
		sprintf(_s0, "%s", "Finished step of module DiscreteGrippingArm");
		fprintf(log_file, "DEBUG: %s\n", _s0);
	}
}

void *mod_DiscreteGrippingArm_thread(void *arg) {
	mod_DiscreteGrippingArm_thread_Channels* channels = (mod_DiscreteGrippingArm_thread_Channels*) arg;
	M_DiscreteGrippingArm_input_Enum_Channel* start_DiscreteGrippingArm = channels->start_DiscreteGrippingArm;
	C_cm_output_Enum_Channel* end_cm = channels->end_cm;
	M_DiscreteGrippingArm_output_Enum_Channel* end_DiscreteGrippingArm = channels->end_DiscreteGrippingArm;
	C_cm_input_Enum_Channel* start_cm = channels->start_cm;
{
	bool terminate__ = false;
	while (!terminate__) {
		{
			bool inputDone = false;
			while (!inputDone) {
				{
					char _s0[256];
					sprintf(_s0, "%s", "- Waiting for input on channel start_DiscreteGrippingArm");
					fprintf(log_file, "DEBUG: %s\n", _s0);
				}
				M_DiscreteGrippingArm_input_Enum _input_;
				{	
					pthread_barrier_wait(&start_DiscreteGrippingArm->can_write);
					pthread_barrier_wait(&start_DiscreteGrippingArm->can_read);
					_input_ = start_DiscreteGrippingArm->value;	
				}
				{
					char _s0[256];
					sprintf(_s0, "%s", "- Read input on channel start_DiscreteGrippingArm");
					fprintf(log_file, "DEBUG: %s\n", _s0);
				}
				if (_input_.type == M_DiscreteGrippingArm_input_moveCompleted) {
					{
						pthread_barrier_wait(&start_cm->can_write);
						start_cm->value = create_C_cm_input_moveCompleted();
						pthread_barrier_wait(&start_cm->can_read);
					}
				}
				else if (_input_.type == M_DiscreteGrippingArm_input_moveDiscreteCommand) {
				     	MovementArgs _aux1_ = _input_.data.moveDiscreteCommand.v1;
				     	{
				     		pthread_barrier_wait(&start_cm->can_write);
				     		start_cm->value = create_C_cm_input_moveDiscreteCommand(_aux1_);
				     		pthread_barrier_wait(&start_cm->can_read);
				     	}
				     }
				else if (_input_.type == M_DiscreteGrippingArm_input_openGripperCommand) {
				     	{
				     		pthread_barrier_wait(&start_cm->can_write);
				     		start_cm->value = create_C_cm_input_openGripperCommand();
				     		pthread_barrier_wait(&start_cm->can_read);
				     	}
				     }
				else if (_input_.type == M_DiscreteGrippingArm_input_nonfeasibleMoveDiscreteCommand) {
				     	{
				     		pthread_barrier_wait(&start_cm->can_write);
				     		start_cm->value = create_C_cm_input_nonfeasibleMoveDiscreteCommand();
				     		pthread_barrier_wait(&start_cm->can_read);
				     	}
				     }
				else if (_input_.type == M_DiscreteGrippingArm_input_gripperOpened) {
				     	{
				     		pthread_barrier_wait(&start_cm->can_write);
				     		start_cm->value = create_C_cm_input_gripperOpened();
				     		pthread_barrier_wait(&start_cm->can_read);
				     	}
				     }
				else if (_input_.type == M_DiscreteGrippingArm_input_feasibleMoveDiscreteCommand) {
				     	{
				     		pthread_barrier_wait(&start_cm->can_write);
				     		start_cm->value = create_C_cm_input_feasibleMoveDiscreteCommand();
				     		pthread_barrier_wait(&start_cm->can_read);
				     	}
				     }
				else if (_input_.type == M_DiscreteGrippingArm_input_collision) {
				     	{
				     		pthread_barrier_wait(&start_cm->can_write);
				     		start_cm->value = create_C_cm_input_collision();
				     		pthread_barrier_wait(&start_cm->can_read);
				     	}
				     }
				else if (_input_.type == M_DiscreteGrippingArm_input_robotStopped) {
				     	{
				     		pthread_barrier_wait(&start_cm->can_write);
				     		start_cm->value = create_C_cm_input_robotStopped();
				     		pthread_barrier_wait(&start_cm->can_read);
				     	}
				     }
				else if (_input_.type == M_DiscreteGrippingArm_input_gripperClosed) {
				     	{
				     		pthread_barrier_wait(&start_cm->can_write);
				     		start_cm->value = create_C_cm_input_gripperClosed();
				     		pthread_barrier_wait(&start_cm->can_read);
				     	}
				     }
				else if (_input_.type == M_DiscreteGrippingArm_input_closeGripperCommand) {
				     	{
				     		pthread_barrier_wait(&start_cm->can_write);
				     		start_cm->value = create_C_cm_input_closeGripperCommand();
				     		pthread_barrier_wait(&start_cm->can_read);
				     	}
				     }
				else if (_input_.type == M_DiscreteGrippingArm_input__done_) {
				     	{
				     		pthread_barrier_wait(&start_cm->can_write);
				     		start_cm->value = create_C_cm_input__done_();
				     		pthread_barrier_wait(&start_cm->can_read);
				     	}
				     	inputDone = true;
				     }
				else if (_input_.type == M_DiscreteGrippingArm_input__terminate_) {
				     	{
				     		pthread_barrier_wait(&start_cm->can_write);
				     		start_cm->value = create_C_cm_input__terminate_();
				     		pthread_barrier_wait(&start_cm->can_read);
				     	}
				     	terminate__ = true;
				     }
			}
			
		}
		{
			char _s0[256];
			sprintf(_s0, "%s", "Finished reading inputs of module DiscreteGrippingArm");
			fprintf(log_file, "DEBUG: %s\n", _s0);
		}
		mod_DiscreteGrippingArm_step(start_cm
		                             , end_cm);
		{
			bool outputDone = false;
			while (!outputDone) {
				C_cm_output_Enum _output_;
				{	
					pthread_barrier_wait(&end_cm->can_write);
					pthread_barrier_wait(&end_cm->can_read);
					_output_ = end_cm->value;	
				}
				if (_output_.type == C_cm_output_stop) {
					{
						pthread_barrier_wait(&end_DiscreteGrippingArm->can_write);
						end_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_output_stop();
						pthread_barrier_wait(&end_DiscreteGrippingArm->can_read);
					}
				}
				else if (_output_.type == C_cm_output_movejoint) {
				     	float _aux1_ = _output_.data.movejoint.v1;
				     	float _aux2_ = _output_.data.movejoint.v2;
				     	float _aux3_ = _output_.data.movejoint.v3;
				     	float _aux4_ = _output_.data.movejoint.v4;
				     	float _aux5_ = _output_.data.movejoint.v5;
				     	float _aux6_ = _output_.data.movejoint.v6;
				     	{
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_write);
				     		end_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_output_movejoint(_aux1_
				     		                                                                               ,_aux2_
				     		                                                                               ,_aux3_
				     		                                                                               ,_aux4_
				     		                                                                               ,_aux5_
				     		                                                                               ,_aux6_);
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_read);
				     	}
				     }
				else if (_output_.type == C_cm_output_pick) {
				     	float _aux1_ = _output_.data.pick.v1;
				     	float _aux2_ = _output_.data.pick.v2;
				     	float _aux3_ = _output_.data.pick.v3;
				     	{
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_write);
				     		end_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_output_pick(_aux1_
				     		                                                                          ,_aux2_
				     		                                                                          ,_aux3_);
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_read);
				     	}
				     }
				else if (_output_.type == C_cm_output_place) {
				     	float _aux1_ = _output_.data.place.v1;
				     	float _aux2_ = _output_.data.place.v2;
				     	float _aux3_ = _output_.data.place.v3;
				     	{
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_write);
				     		end_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_output_place(_aux1_
				     		                                                                           ,_aux2_
				     		                                                                           ,_aux3_);
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_read);
				     	}
				     }
				else if (_output_.type == C_cm_output_movecartesian) {
				     	float _aux1_ = _output_.data.movecartesian.v1;
				     	float _aux2_ = _output_.data.movecartesian.v2;
				     	float _aux3_ = _output_.data.movecartesian.v3;
				     	float _aux4_ = _output_.data.movecartesian.v4;
				     	float _aux5_ = _output_.data.movecartesian.v5;
				     	float _aux6_ = _output_.data.movecartesian.v6;
				     	{
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_write);
				     		end_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_output_movecartesian(_aux1_
				     		                                                                                   ,_aux2_
				     		                                                                                   ,_aux3_
				     		                                                                                   ,_aux4_
				     		                                                                                   ,_aux5_
				     		                                                                                   ,_aux6_);
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_read);
				     	}
				     }
				else if (_output_.type == C_cm_output_setvelocity) {
				     	float _aux1_ = _output_.data.setvelocity.v1;
				     	{
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_write);
				     		end_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_output_setvelocity(_aux1_);
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_read);
				     	}
				     }
				else if (_output_.type == C_cm_output_movediscrete) {
				     	int _aux1_ = _output_.data.movediscrete.v1;
				     	int _aux2_ = _output_.data.movediscrete.v2;
				     	int _aux3_ = _output_.data.movediscrete.v3;
				     	{
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_write);
				     		end_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_output_movediscrete(_aux1_
				     		                                                                                  ,_aux2_
				     		                                                                                  ,_aux3_);
				     		pthread_barrier_wait(&end_DiscreteGrippingArm->can_read);
				     	}
				     }
				else if (_output_.type == C_cm_output__done_) {
				     	outputDone = true;
				     }
			}
			
		}
		{
			pthread_barrier_wait(&end_DiscreteGrippingArm->can_write);
			end_DiscreteGrippingArm->value = create_M_DiscreteGrippingArm_output__done_();
			pthread_barrier_wait(&end_DiscreteGrippingArm->can_read);
		}
	}
}
}

#endif