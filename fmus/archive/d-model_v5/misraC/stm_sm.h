/*
	This file contains function definitions derived from the state machine sm.
*/

#ifndef STM_SM__H
#define STM_SM__H
#define _POSIX_C_SOURCE 200112L

#include "defs.h"
#include "aux.h"
#include <threads.h>
#include <stdio.h>

/* Declaration of function signatures */
char* print_STATUS(STATUS_Enum* value);
void mod_DiscreteGrippingArm_step(C_cm_input_Enum_Channel* start_cm
									, C_cm_output_Enum_Channel* end_cm);
RESULT_Enum SimDiscreteGrippingArmMovement_J2(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);
RESULT_Enum en_SimDiscreteGrippingArmMovement_ArmStop_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output);
RESULT_Enum SimDiscreteGrippingArmMovement_j0(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);
RESULT_Enum en_SimDiscreteGrippingArmMovement_GripperClose_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output);
void ctrl_cm_step(sm_input_Enum_Channel* start_sm
					, sm_output_Enum_Channel* end_sm);
char* print_STATES_sm(STATES_sm_Enum* value);
RESULT_Enum en_SimDiscreteGrippingArmMovement_ArmMove_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output);
RESULT_Enum stm_sm_step(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);
char* print_sm_state(sm_state* state);
RESULT_Enum SimDiscreteGrippingArmMovement_J4(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);
RESULT_Enum en_SimDiscreteGrippingArmMovement_GripperOpen_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output);
RESULT_Enum SimDiscreteGrippingArmMovement_J5(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);
RESULT_Enum SimDiscreteGrippingArmMovement_J3(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output);

void *stm_sm(void *arg) {
	stm_sm_Channels* channels = (stm_sm_Channels*) arg;
	sm_input_Enum_Channel* start_sm = channels->start_sm;
	sm_output_Enum_Channel* end_sm = channels->end_sm;
{
	// state machine variable declarations;
	sm_inputstate inputstate = (sm_inputstate) {
	                           	.robotStopped = false,
	                           	.moveCompleted = false,
	                           	.moveDiscreteCommand = false,
	                           	.moveDiscreteCommand_value = (MovementArgs) {
	                           		.target_X = 0
	                           		,
	                           		.target_Y = 0
	                           		,
	                           		.target_Z = 0
	                           	},
	                           	.gripperOpened = false,
	                           	.feasibleMoveDiscreteCommand = false,
	                           	.collision = false,
	                           	.nonfeasibleMoveDiscreteCommand = false,
	                           	.gripperClosed = false,
	                           	.closeGripperCommand = false,
	                           	.openGripperCommand = false,
	                           	._transition_ = create_TRANSITIONS_sm_NONE()
	                           };
	sm_state state = (sm_state) {
	                 	.done = false,
	                 	.state = create_STATES_sm_NONE(),
	                 	.target_state = create_STATES_sm_NONE(),
	                 	.status = create_STATUS_ENTER_STATE(),
	                 	.en_SimDiscreteGrippingArmMovement_ArmMove_1_done = false,
	                 	.en_SimDiscreteGrippingArmMovement_ArmMove_1_counter = 0
	                 	,
	                 	.en_SimDiscreteGrippingArmMovement_ArmStop_1_done = false,
	                 	.en_SimDiscreteGrippingArmMovement_ArmStop_1_counter = 0
	                 	,
	                 	.en_SimDiscreteGrippingArmMovement_GripperOpen_1_done = false,
	                 	.en_SimDiscreteGrippingArmMovement_GripperOpen_1_counter = 0
	                 	,
	                 	.en_SimDiscreteGrippingArmMovement_GripperClose_1_done = false,
	                 	.en_SimDiscreteGrippingArmMovement_GripperClose_1_counter = 0
	                 };
	sm_memory memorystate = (sm_memory) {
	                        	.closing_force = 0.0
	                        	,
	                        	.closing_diameter = 0.0
	                        	,
	                        	.opening_diameter = 0.0
	                        	,
	                        	.closing_speed = 0.0
	                        	,
	                        	.margs = (MovementArgs) {
	                        		.target_X = 0
	                        		,
	                        		.target_Y = 0
	                        		,
	                        		.target_Z = 0
	                        	},
	                        	.TARGET_Y = 0
	                        	,
	                        	.PI = 0.0
	                        	,
	                        	.opening_speed = 0.0
	                        	,
	                        	.opening_force = 0.0
	                        	,
	                        	.av = 0.0
	                        	,
	                        	.MOTION_VEL = 0.0
	                        	,
	                        	.lv = 0.0
	                        	,
	                        	.TARGET_Z = 0
	                        	,
	                        	.TARGET_X = 0
	                        };
	// state machine loop;
	while (!(state).done) {
		{
			{
				char _s0[256];
				sprintf(_s0, "%s", "- Waiting for input on channel start_sm");
				fprintf(log_file, "DEBUG: %s\n", _s0);
			}
			bool inputDone = false;
			while (!inputDone) {
				sm_input_Enum _input_;
				{	
					pthread_barrier_wait(&start_sm->can_write);
					pthread_barrier_wait(&start_sm->can_read);
					_input_ = start_sm->value;	
				}
				{
					char _s0[256];
					sprintf(_s0, "%s", "- Read input on channel start_sm");
					fprintf(log_file, "DEBUG: %s\n", _s0);
				}
				if (_input_.type == sm_input_robotStopped) {
					(inputstate).robotStopped = true;
				}
				else if (_input_.type == sm_input_moveCompleted) {
				     	(inputstate).moveCompleted = true;
				     }
				else if (_input_.type == sm_input_moveDiscreteCommand) {
				     	MovementArgs _aux_ = _input_.data.moveDiscreteCommand.v1;
				     	(inputstate).moveDiscreteCommand = true;
				     	(inputstate).moveDiscreteCommand_value = _aux_;
				     }
				else if (_input_.type == sm_input_gripperOpened) {
				     	(inputstate).gripperOpened = true;
				     }
				else if (_input_.type == sm_input_feasibleMoveDiscreteCommand) {
				     	(inputstate).feasibleMoveDiscreteCommand = true;
				     }
				else if (_input_.type == sm_input_collision) {
				     	(inputstate).collision = true;
				     }
				else if (_input_.type == sm_input_nonfeasibleMoveDiscreteCommand) {
				     	(inputstate).nonfeasibleMoveDiscreteCommand = true;
				     }
				else if (_input_.type == sm_input_gripperClosed) {
				     	(inputstate).gripperClosed = true;
				     }
				else if (_input_.type == sm_input_closeGripperCommand) {
				     	(inputstate).closeGripperCommand = true;
				     }
				else if (_input_.type == sm_input_openGripperCommand) {
				     	(inputstate).openGripperCommand = true;
				     }
				else if (_input_.type == sm_input__done_) {
				     	inputDone = true;
				     }
				else if (_input_.type == sm_input__terminate_) {
				     	inputDone = true;
				     }
			}
		}
		RESULT_Enum ret = create_RESULT_CONT();
		while (	ret.type == create_RESULT_CONT().type
		        ) {
			char* temp_;
			temp_ = print_sm_state(&state);
			{
				char _s0[256];
				sprintf(_s0, "%s", temp_);
				fprintf(log_file, "DEBUG: %s\n", _s0);
			}
            free(temp_);
			ret = stm_sm_step(&state, &inputstate, &memorystate, end_sm);
		}
		{
			pthread_barrier_wait(&end_sm->can_write);
			end_sm->value = create_sm_output__done_();
			pthread_barrier_wait(&end_sm->can_read);
		}
		// update clocks;
		// reset input events;
		(inputstate).closeGripperCommand = false;
		(inputstate).collision = false;
		(inputstate).gripperOpened = false;
		(inputstate).feasibleMoveDiscreteCommand = false;
		(inputstate).openGripperCommand = false;
		(inputstate).nonfeasibleMoveDiscreteCommand = false;
		(inputstate).moveCompleted = false;
		(inputstate).robotStopped = false;
		(inputstate).moveDiscreteCommand = false;
		(inputstate).gripperClosed = false;
		{
			char _s0[256];
			sprintf(_s0, "%s", "		Sent output _done_ on channel end_sm");
			fprintf(log_file, "DEBUG: %s\n", _s0);
		}
		
	}
}
}

RESULT_Enum stm_sm_step(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output) {
	{
		char _s0[256];
		sprintf(_s0, "%s", "		Running step of state machine SimDiscreteGrippingArmMovement");
		fprintf(log_file, "DEBUG: %s\n", _s0);
	}
	if ((*state).state.type == create_STATES_sm_NONE().type) {
		{
			char _s0[256];
			sprintf(_s0, "%s", "		Executing initial junction of SimDiscreteGrippingArmMovement");
			fprintf(log_file, "DEBUG: %s\n", _s0);
		}
		{
			(*state).state = create_STATES_sm_Idle();
		}
		return create_RESULT_CONT();
	}
	else if ((*state).state.type == create_STATES_sm_Idle().type) {
			if ((*state).status.type == create_STATUS_ENTER_STATE().type) {
				{
					char _s0[256];
					sprintf(_s0, "%s", "		Entering state Idle");
					fprintf(log_file, "DEBUG: %s\n", _s0);
				}
				{
					(*state).status = create_STATUS_ENTER_CHILDREN();
					return create_RESULT_CONT();
				}
			}
			else if ((*state).status.type == create_STATUS_ENTER_CHILDREN().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Entering children of state Idle");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					(*state).status = create_STATUS_EXECUTE_STATE();
					{
						(*inputstate)._transition_ = create_TRANSITIONS_sm_NONE();
					}
					return create_RESULT_CONT();
					}
			else if ((*state).status.type == create_STATUS_EXECUTE_STATE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Executing state Idle");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_NONE().type
							) {
						if (!((inputstate)->moveDiscreteCommand || (inputstate)->openGripperCommand || (inputstate)->closeGripperCommand)) {
							(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t1_1();
							(*state).status = create_STATUS_EXIT_CHILDREN();
							return create_RESULT_WAIT();
						} else if ((inputstate)->closeGripperCommand) {
							(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t4();
							(*state).status = create_STATUS_EXIT_CHILDREN();
							return create_RESULT_CONT();
						} else if ((inputstate)->openGripperCommand) {
							(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t5();
							(*state).status = create_STATUS_EXIT_CHILDREN();
							return create_RESULT_CONT();
						} else if ((inputstate)->moveDiscreteCommand) {
							(*memorystate).margs = (inputstate)->moveDiscreteCommand_value;
							(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t2();
							(*state).status = create_STATUS_EXIT_CHILDREN();
							return create_RESULT_CONT();
						} else {
							return create_RESULT_CONT();
						}
					} else {
						return create_RESULT_CONT();
					}
					}
			else if ((*state).status.type == create_STATUS_EXIT_CHILDREN().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Exiting children of state Idle");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					(*state).status = create_STATUS_EXIT_STATE();
					return create_RESULT_CONT();
					}
			else if ((*state).status.type == create_STATUS_EXIT_STATE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Exiting state Idle");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					{
						if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t1_1().type
								) {
							(*state).state = create_STATES_sm_Idle();
							(*state).status = create_STATUS_ENTER_STATE();
							return create_RESULT_CONT();
						} else if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t4().type
									) {
							(*state).state = create_STATES_sm_GripperClose();
							(*state).status = create_STATUS_ENTER_STATE();
							return create_RESULT_CONT();
						} else if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t5().type
									) {
							(*state).state = create_STATES_sm_GripperOpen();
							(*state).status = create_STATUS_ENTER_STATE();
							return create_RESULT_CONT();
						} else if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t2().type
									) {
							(*state).state = create_STATES_sm_ArmMove();
							(*state).status = create_STATUS_ENTER_STATE();
							return create_RESULT_CONT();
						} else {
							(*state).status = create_STATUS_INACTIVE();
							(*state).state = create_STATES_sm_NONE();
							return create_RESULT_CONT();
						}
					}
					}
			else if ((*state).status.type == create_STATUS_INACTIVE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		State Idle is inactive");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					return create_RESULT_CONT();
					}
			}
	else if ((*state).state.type == create_STATES_sm_ArmMove().type) {
			if ((*state).status.type == create_STATUS_ENTER_STATE().type) {
				{
					char _s0[256];
					sprintf(_s0, "%s", "		Entering state ArmMove");
					fprintf(log_file, "DEBUG: %s\n", _s0);
				}
				if (!(state)->en_SimDiscreteGrippingArmMovement_ArmMove_1_done) {
					RESULT_Enum _ret_;
					_ret_ = en_SimDiscreteGrippingArmMovement_ArmMove_1(state
																		, inputstate
																		, memorystate
																		, output);
					return _ret_;
				} else {
					(*state).status = create_STATUS_ENTER_CHILDREN();
					(*state).en_SimDiscreteGrippingArmMovement_ArmMove_1_done = false;
					(*state).en_SimDiscreteGrippingArmMovement_ArmMove_1_counter = 0;
					return create_RESULT_CONT();
				}
			}
			else if ((*state).status.type == create_STATUS_ENTER_CHILDREN().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Entering children of state ArmMove");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					(*state).status = create_STATUS_EXECUTE_STATE();
					{
						(*inputstate)._transition_ = create_TRANSITIONS_sm_NONE();
					}
					return create_RESULT_CONT();
					}
			else if ((*state).status.type == create_STATUS_EXECUTE_STATE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Executing state ArmMove");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_NONE().type
							) {
						if ((inputstate)->nonfeasibleMoveDiscreteCommand) {
							(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t2_nonfeasible();
							(*state).status = create_STATUS_EXIT_CHILDREN();
							return create_RESULT_CONT();
						} else if ((inputstate)->feasibleMoveDiscreteCommand) {
							(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t2_1();
							(*state).status = create_STATUS_EXIT_CHILDREN();
							return create_RESULT_CONT();
						} else if (true) {
							(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t0();
							(*state).status = create_STATUS_EXIT_CHILDREN();
							return create_RESULT_WAIT();
						} else {
							return create_RESULT_CONT();
						}
					} else {
						return create_RESULT_CONT();
					}
					}
			else if ((*state).status.type == create_STATUS_EXIT_CHILDREN().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Exiting children of state ArmMove");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					(*state).status = create_STATUS_EXIT_STATE();
					return create_RESULT_CONT();
					}
			else if ((*state).status.type == create_STATUS_EXIT_STATE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Exiting state ArmMove");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					{
						if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t2_nonfeasible().type
								) {
							(*state).state = create_STATES_sm_Idle();
							(*state).status = create_STATUS_ENTER_STATE();
							return create_RESULT_CONT();
						} else if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t2_1().type
									) {
							(*state).state = create_STATES_sm_ArmMoving();
							(*state).status = create_STATUS_ENTER_STATE();
							return create_RESULT_CONT();
						} else if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t0().type
									) {
							RESULT_Enum _ret_;
							_ret_ = SimDiscreteGrippingArmMovement_j0(state
																		, inputstate
																		, memorystate
																		, output);
							return _ret_;
						} else {
							(*state).status = create_STATUS_INACTIVE();
							(*state).state = create_STATES_sm_NONE();
							return create_RESULT_CONT();
						}
					}
					}
			else if ((*state).status.type == create_STATUS_INACTIVE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		State ArmMove is inactive");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					return create_RESULT_CONT();
					}
			}
	else if ((*state).state.type == create_STATES_sm_ArmStop().type) {
			if ((*state).status.type == create_STATUS_ENTER_STATE().type) {
				{
					char _s0[256];
					sprintf(_s0, "%s", "		Entering state ArmStop");
					fprintf(log_file, "DEBUG: %s\n", _s0);
				}
				if (!(state)->en_SimDiscreteGrippingArmMovement_ArmStop_1_done) {
					RESULT_Enum _ret_;
					_ret_ = en_SimDiscreteGrippingArmMovement_ArmStop_1(state
																		, inputstate
																		, memorystate
																		, output);
					return _ret_;
				} else {
					(*state).status = create_STATUS_ENTER_CHILDREN();
					(*state).en_SimDiscreteGrippingArmMovement_ArmStop_1_done = false;
					(*state).en_SimDiscreteGrippingArmMovement_ArmStop_1_counter = 0;
					return create_RESULT_CONT();
				}
			}
			else if ((*state).status.type == create_STATUS_ENTER_CHILDREN().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Entering children of state ArmStop");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					(*state).status = create_STATUS_EXECUTE_STATE();
					{
						(*inputstate)._transition_ = create_TRANSITIONS_sm_NONE();
					}
					return create_RESULT_CONT();
					}
			else if ((*state).status.type == create_STATUS_EXECUTE_STATE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Executing state ArmStop");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_NONE().type
							) {
						if (true) {
							(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t3();
							(*state).status = create_STATUS_EXIT_CHILDREN();
							return create_RESULT_CONT();
						} else {
							return create_RESULT_CONT();
						}
					} else {
						return create_RESULT_CONT();
					}
					}
			else if ((*state).status.type == create_STATUS_EXIT_CHILDREN().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Exiting children of state ArmStop");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					(*state).status = create_STATUS_EXIT_STATE();
					return create_RESULT_CONT();
					}
			else if ((*state).status.type == create_STATUS_EXIT_STATE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Exiting state ArmStop");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					{
						if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t3().type
								) {
							(*state).state = create_STATES_sm_ArmStopping();
							(*state).status = create_STATUS_ENTER_STATE();
							return create_RESULT_CONT();
						} else {
							(*state).status = create_STATUS_INACTIVE();
							(*state).state = create_STATES_sm_NONE();
							return create_RESULT_CONT();
						}
					}
					}
			else if ((*state).status.type == create_STATUS_INACTIVE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		State ArmStop is inactive");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					return create_RESULT_CONT();
					}
			}
	else if ((*state).state.type == create_STATES_sm_GripperClose().type) {
			if ((*state).status.type == create_STATUS_ENTER_STATE().type) {
				{
					char _s0[256];
					sprintf(_s0, "%s", "		Entering state GripperClose");
					fprintf(log_file, "DEBUG: %s\n", _s0);
				}
				if (!(state)->en_SimDiscreteGrippingArmMovement_GripperClose_1_done) {
					RESULT_Enum _ret_;
					_ret_ = en_SimDiscreteGrippingArmMovement_GripperClose_1(state
																				, inputstate
																				, memorystate
																				, output);
					return _ret_;
				} else {
					(*state).status = create_STATUS_ENTER_CHILDREN();
					(*state).en_SimDiscreteGrippingArmMovement_GripperClose_1_done = false;
					(*state).en_SimDiscreteGrippingArmMovement_GripperClose_1_counter = 0;
					return create_RESULT_CONT();
				}
			}
			else if ((*state).status.type == create_STATUS_ENTER_CHILDREN().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Entering children of state GripperClose");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					(*state).status = create_STATUS_EXECUTE_STATE();
					{
						(*inputstate)._transition_ = create_TRANSITIONS_sm_NONE();
					}
					return create_RESULT_CONT();
					}
			else if ((*state).status.type == create_STATUS_EXECUTE_STATE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Executing state GripperClose");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_NONE().type
							) {
						if (true) {
							(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t4_1();
							(*state).status = create_STATUS_EXIT_CHILDREN();
							return create_RESULT_CONT();
						} else {
							return create_RESULT_CONT();
						}
					} else {
						return create_RESULT_CONT();
					}
					}
			else if ((*state).status.type == create_STATUS_EXIT_CHILDREN().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Exiting children of state GripperClose");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					(*state).status = create_STATUS_EXIT_STATE();
					return create_RESULT_CONT();
					}
			else if ((*state).status.type == create_STATUS_EXIT_STATE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Exiting state GripperClose");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					{
						if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t4_1().type
								) {
							(*state).state = create_STATES_sm_GripperClosing();
							(*state).status = create_STATUS_ENTER_STATE();
							return create_RESULT_CONT();
						} else {
							(*state).status = create_STATUS_INACTIVE();
							(*state).state = create_STATES_sm_NONE();
							return create_RESULT_CONT();
						}
					}
					}
			else if ((*state).status.type == create_STATUS_INACTIVE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		State GripperClose is inactive");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					return create_RESULT_CONT();
					}
			}
	else if ((*state).state.type == create_STATES_sm_GripperOpen().type) {
			if ((*state).status.type == create_STATUS_ENTER_STATE().type) {
				{
					char _s0[256];
					sprintf(_s0, "%s", "		Entering state GripperOpen");
					fprintf(log_file, "DEBUG: %s\n", _s0);
				}
				if (!(state)->en_SimDiscreteGrippingArmMovement_GripperOpen_1_done) {
					RESULT_Enum _ret_;
					_ret_ = en_SimDiscreteGrippingArmMovement_GripperOpen_1(state
																			, inputstate
																			, memorystate
																			, output);
					return _ret_;
				} else {
					(*state).status = create_STATUS_ENTER_CHILDREN();
					(*state).en_SimDiscreteGrippingArmMovement_GripperOpen_1_done = false;
					(*state).en_SimDiscreteGrippingArmMovement_GripperOpen_1_counter = 0;
					return create_RESULT_CONT();
				}
			}
			else if ((*state).status.type == create_STATUS_ENTER_CHILDREN().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Entering children of state GripperOpen");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					(*state).status = create_STATUS_EXECUTE_STATE();
					{
						(*inputstate)._transition_ = create_TRANSITIONS_sm_NONE();
					}
					return create_RESULT_CONT();
					}
			else if ((*state).status.type == create_STATUS_EXECUTE_STATE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Executing state GripperOpen");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_NONE().type
							) {
						if (true) {
							(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t5_1();
							(*state).status = create_STATUS_EXIT_CHILDREN();
							return create_RESULT_CONT();
						} else {
							return create_RESULT_CONT();
						}
					} else {
						return create_RESULT_CONT();
					}
					}
			else if ((*state).status.type == create_STATUS_EXIT_CHILDREN().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Exiting children of state GripperOpen");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					(*state).status = create_STATUS_EXIT_STATE();
					return create_RESULT_CONT();
					}
			else if ((*state).status.type == create_STATUS_EXIT_STATE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Exiting state GripperOpen");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					{
						if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t5_1().type
								) {
							(*state).state = create_STATES_sm_GripperOpening();
							(*state).status = create_STATUS_ENTER_STATE();
							return create_RESULT_CONT();
						} else {
							(*state).status = create_STATUS_INACTIVE();
							(*state).state = create_STATES_sm_NONE();
							return create_RESULT_CONT();
						}
					}
					}
			else if ((*state).status.type == create_STATUS_INACTIVE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		State GripperOpen is inactive");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					return create_RESULT_CONT();
					}
			}
	else if ((*state).state.type == create_STATES_sm_ArmMoving().type) {
			if ((*state).status.type == create_STATUS_ENTER_STATE().type) {
				{
					char _s0[256];
					sprintf(_s0, "%s", "		Entering state ArmMoving");
					fprintf(log_file, "DEBUG: %s\n", _s0);
				}
				{
					(*state).status = create_STATUS_ENTER_CHILDREN();
					return create_RESULT_CONT();
				}
			}
			else if ((*state).status.type == create_STATUS_ENTER_CHILDREN().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Entering children of state ArmMoving");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					(*state).status = create_STATUS_EXECUTE_STATE();
					{
						(*inputstate)._transition_ = create_TRANSITIONS_sm_NONE();
					}
					return create_RESULT_CONT();
					}
			else if ((*state).status.type == create_STATUS_EXECUTE_STATE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Executing state ArmMoving");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_NONE().type
							) {
						if (true) {
							(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t2_2();
							(*state).status = create_STATUS_EXIT_CHILDREN();
							return create_RESULT_WAIT();
						} else {
							return create_RESULT_CONT();
						}
					} else {
						return create_RESULT_CONT();
					}
					}
			else if ((*state).status.type == create_STATUS_EXIT_CHILDREN().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Exiting children of state ArmMoving");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					(*state).status = create_STATUS_EXIT_STATE();
					return create_RESULT_CONT();
					}
			else if ((*state).status.type == create_STATUS_EXIT_STATE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Exiting state ArmMoving");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					{
						if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t2_2().type
								) {
							RESULT_Enum _ret_;
							_ret_ = SimDiscreteGrippingArmMovement_J2(state
																		, inputstate
																		, memorystate
																		, output);
							return _ret_;
						} else {
							(*state).status = create_STATUS_INACTIVE();
							(*state).state = create_STATES_sm_NONE();
							return create_RESULT_CONT();
						}
					}
					}
			else if ((*state).status.type == create_STATUS_INACTIVE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		State ArmMoving is inactive");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					return create_RESULT_CONT();
					}
			}
	else if ((*state).state.type == create_STATES_sm_ArmStopping().type) {
			if ((*state).status.type == create_STATUS_ENTER_STATE().type) {
				{
					char _s0[256];
					sprintf(_s0, "%s", "		Entering state ArmStopping");
					fprintf(log_file, "DEBUG: %s\n", _s0);
				}
				{
					(*state).status = create_STATUS_ENTER_CHILDREN();
					return create_RESULT_CONT();
				}
			}
			else if ((*state).status.type == create_STATUS_ENTER_CHILDREN().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Entering children of state ArmStopping");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					(*state).status = create_STATUS_EXECUTE_STATE();
					{
						(*inputstate)._transition_ = create_TRANSITIONS_sm_NONE();
					}
					return create_RESULT_CONT();
					}
			else if ((*state).status.type == create_STATUS_EXECUTE_STATE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Executing state ArmStopping");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_NONE().type
							) {
						if (true) {
							(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t3_1();
							(*state).status = create_STATUS_EXIT_CHILDREN();
							return create_RESULT_WAIT();
						} else {
							return create_RESULT_CONT();
						}
					} else {
						return create_RESULT_CONT();
					}
					}
			else if ((*state).status.type == create_STATUS_EXIT_CHILDREN().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Exiting children of state ArmStopping");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					(*state).status = create_STATUS_EXIT_STATE();
					return create_RESULT_CONT();
					}
			else if ((*state).status.type == create_STATUS_EXIT_STATE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Exiting state ArmStopping");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					{
						if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t3_1().type
								) {
							RESULT_Enum _ret_;
							_ret_ = SimDiscreteGrippingArmMovement_J3(state
																		, inputstate
																		, memorystate
																		, output);
							return _ret_;
						} else {
							(*state).status = create_STATUS_INACTIVE();
							(*state).state = create_STATES_sm_NONE();
							return create_RESULT_CONT();
						}
					}
					}
			else if ((*state).status.type == create_STATUS_INACTIVE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		State ArmStopping is inactive");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					return create_RESULT_CONT();
					}
			}
	else if ((*state).state.type == create_STATES_sm_GripperClosing().type) {
			if ((*state).status.type == create_STATUS_ENTER_STATE().type) {
				{
					char _s0[256];
					sprintf(_s0, "%s", "		Entering state GripperClosing");
					fprintf(log_file, "DEBUG: %s\n", _s0);
				}
				{
					(*state).status = create_STATUS_ENTER_CHILDREN();
					return create_RESULT_CONT();
				}
			}
			else if ((*state).status.type == create_STATUS_ENTER_CHILDREN().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Entering children of state GripperClosing");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					(*state).status = create_STATUS_EXECUTE_STATE();
					{
						(*inputstate)._transition_ = create_TRANSITIONS_sm_NONE();
					}
					return create_RESULT_CONT();
					}
			else if ((*state).status.type == create_STATUS_EXECUTE_STATE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Executing state GripperClosing");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_NONE().type
							) {
						if (true) {
							(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t4_2();
							(*state).status = create_STATUS_EXIT_CHILDREN();
							return create_RESULT_WAIT();
						} else {
							return create_RESULT_CONT();
						}
					} else {
						return create_RESULT_CONT();
					}
					}
			else if ((*state).status.type == create_STATUS_EXIT_CHILDREN().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Exiting children of state GripperClosing");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					(*state).status = create_STATUS_EXIT_STATE();
					return create_RESULT_CONT();
					}
			else if ((*state).status.type == create_STATUS_EXIT_STATE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Exiting state GripperClosing");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					{
						if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t4_2().type
								) {
							RESULT_Enum _ret_;
							_ret_ = SimDiscreteGrippingArmMovement_J4(state
																		, inputstate
																		, memorystate
																		, output);
							return _ret_;
						} else {
							(*state).status = create_STATUS_INACTIVE();
							(*state).state = create_STATES_sm_NONE();
							return create_RESULT_CONT();
						}
					}
					}
			else if ((*state).status.type == create_STATUS_INACTIVE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		State GripperClosing is inactive");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					return create_RESULT_CONT();
					}
			}
	else if ((*state).state.type == create_STATES_sm_GripperOpening().type) {
			if ((*state).status.type == create_STATUS_ENTER_STATE().type) {
				{
					char _s0[256];
					sprintf(_s0, "%s", "		Entering state GripperOpening");
					fprintf(log_file, "DEBUG: %s\n", _s0);
				}
				{
					(*state).status = create_STATUS_ENTER_CHILDREN();
					return create_RESULT_CONT();
				}
			}
			else if ((*state).status.type == create_STATUS_ENTER_CHILDREN().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Entering children of state GripperOpening");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					(*state).status = create_STATUS_EXECUTE_STATE();
					{
						(*inputstate)._transition_ = create_TRANSITIONS_sm_NONE();
					}
					return create_RESULT_CONT();
					}
			else if ((*state).status.type == create_STATUS_EXECUTE_STATE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Executing state GripperOpening");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_NONE().type
							) {
						if (true) {
							(*inputstate)._transition_ = create_TRANSITIONS_sm_sm_t5_2();
							(*state).status = create_STATUS_EXIT_CHILDREN();
							return create_RESULT_WAIT();
						} else {
							return create_RESULT_CONT();
						}
					} else {
						return create_RESULT_CONT();
					}
					}
			else if ((*state).status.type == create_STATUS_EXIT_CHILDREN().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Exiting children of state GripperOpening");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					(*state).status = create_STATUS_EXIT_STATE();
					return create_RESULT_CONT();
					}
			else if ((*state).status.type == create_STATUS_EXIT_STATE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		Exiting state GripperOpening");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					{
						if (	(*inputstate)._transition_.type == create_TRANSITIONS_sm_sm_t5_2().type
								) {
							RESULT_Enum _ret_;
							_ret_ = SimDiscreteGrippingArmMovement_J5(state
																		, inputstate
																		, memorystate
																		, output);
							return _ret_;
						} else {
							(*state).status = create_STATUS_INACTIVE();
							(*state).state = create_STATES_sm_NONE();
							return create_RESULT_CONT();
						}
					}
					}
			else if ((*state).status.type == create_STATUS_INACTIVE().type) {
					{
						char _s0[256];
						sprintf(_s0, "%s", "		State GripperOpening is inactive");
						fprintf(log_file, "DEBUG: %s\n", _s0);
					}
					return create_RESULT_CONT();
					}
			}
}

char* print_STATUS(STATUS_Enum* value) {
    if (value->type == STATUS_ENTER_STATE) {
        return "ENTER_STATE";
    }
    else if (value->type == STATUS_ENTER_CHILDREN) {
        return "ENTER_CHILDREN";
    }
    else if (value->type == STATUS_EXECUTE_STATE) {
        return "EXECUTE_STATE";
    }
    else if (value->type == STATUS_EXIT_CHILDREN) {
        return "EXIT_CHILDREN";
    }
    else if (value->type == STATUS_EXIT_STATE) {
        return "EXIT_STATE";
    }
    else if (value->type == STATUS_INACTIVE) {
        return "INACTIVE";
    }
}

char* print_STATES_sm(STATES_sm_Enum* value) {
	if (value->type == STATES_sm_NONE) {
		return "NONE";
	}
	else if (value->type == STATES_sm_Idle) {
			return "Idle";
			}
	else if (value->type == STATES_sm_ArmMove) {
			return "ArmMove";
			}
	else if (value->type == STATES_sm_ArmStop) {
			return "ArmStop";
			}
	else if (value->type == STATES_sm_GripperClose) {
			return "GripperClose";
			}
	else if (value->type == STATES_sm_GripperOpen) {
			return "GripperOpen";
			}
	else if (value->type == STATES_sm_ArmMoving) {
			return "ArmMoving";
			}
	else if (value->type == STATES_sm_ArmStopping) {
			return "ArmStopping";
			}
	else if (value->type == STATES_sm_GripperClosing) {
			return "GripperClosing";
			}
	else if (value->type == STATES_sm_GripperOpening) {
			return "GripperOpening";
			}
}

RESULT_Enum SimDiscreteGrippingArmMovement_J2(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output) {
	if (!((inputstate)->collision || (inputstate)->moveCompleted)) {
		(*state).state = create_STATES_sm_ArmMoving();
		(*state).status = create_STATUS_ENTER_STATE();
		return create_RESULT_CONT();
	} else if ((inputstate)->collision || (inputstate)->moveCompleted) {
		(*state).state = create_STATES_sm_ArmStop();
		(*state).status = create_STATUS_ENTER_STATE();
		return create_RESULT_CONT();
	} else {
		return create_RESULT_CONT();
	}
}
RESULT_Enum en_SimDiscreteGrippingArmMovement_ArmStop_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output) {
	{
		char _s0[256];
		sprintf(_s0, "%s", "Running entry action 1 of state SimDiscreteGrippingArmMovement_ArmStop.");
		fprintf(log_file, "DEBUG: %s\n", _s0);
	}
	if (	(state)->en_SimDiscreteGrippingArmMovement_ArmStop_1_counter == 0 ) {
		{
			pthread_barrier_wait(&output->can_write);
			output->value = create_sm_output_stop();
			pthread_barrier_wait(&output->can_read);
		}
		(*state).en_SimDiscreteGrippingArmMovement_ArmStop_1_counter = 1;
		return create_RESULT_CONT();
	} else {
		(state)->en_SimDiscreteGrippingArmMovement_ArmStop_1_done = true;
		return create_RESULT_CONT();
	}
}
RESULT_Enum SimDiscreteGrippingArmMovement_j0(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output) {
	if (!(inputstate)->feasibleMoveDiscreteCommand && !(inputstate)->nonfeasibleMoveDiscreteCommand) {
		(*state).state = create_STATES_sm_ArmMove();
		(*state).status = create_STATUS_ENTER_STATE();
		return create_RESULT_CONT();
	} else {
		return create_RESULT_CONT();
	}
}
RESULT_Enum en_SimDiscreteGrippingArmMovement_GripperClose_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output) {
	{
		char _s0[256];
		sprintf(_s0, "%s", "Running entry action 1 of state SimDiscreteGrippingArmMovement_GripperClose.");
		fprintf(log_file, "DEBUG: %s\n", _s0);
	}
	if (	(state)->en_SimDiscreteGrippingArmMovement_GripperClose_1_counter == 0 ) {
		{
			pthread_barrier_wait(&output->can_write);
			output->value = create_sm_output_pick((memory)->closing_diameter
													,(memory)->closing_speed
													,(memory)->closing_force);
			pthread_barrier_wait(&output->can_read);
		}
		(*state).en_SimDiscreteGrippingArmMovement_GripperClose_1_counter = 1;
		return create_RESULT_CONT();
	} else {
		(state)->en_SimDiscreteGrippingArmMovement_GripperClose_1_done = true;
		return create_RESULT_CONT();
	}
}


RESULT_Enum en_SimDiscreteGrippingArmMovement_ArmMove_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output) {
	{
		char _s0[256];
		sprintf(_s0, "%s", "Running entry action 1 of state SimDiscreteGrippingArmMovement_ArmMove.");
		fprintf(log_file, "DEBUG: %s\n", _s0);
	}
	if (	(state)->en_SimDiscreteGrippingArmMovement_ArmMove_1_counter == 0 ) {
		{
			pthread_barrier_wait(&output->can_write);
			output->value = create_sm_output_movediscrete(((memory)->margs).target_X,((memory)->margs).target_Y,((memory)->margs).target_Z);
			pthread_barrier_wait(&output->can_read);
		}
		(*state).en_SimDiscreteGrippingArmMovement_ArmMove_1_counter = 1;
		return create_RESULT_CONT();
	} else {
		(state)->en_SimDiscreteGrippingArmMovement_ArmMove_1_done = true;
		return create_RESULT_CONT();
	}
}

char* print_sm_state(sm_state* state) {
    char* temp1_;
    temp1_ = print_STATES_sm(&(state)->state);
    char* temp2_;
    temp2_ = print_STATUS(&(state)->status);
    char* temp3_ = concat(temp1_, " (");
    char* temp4_ = concat(temp3_, temp2_);
    char* temp5_ = concat(temp4_, ")");
    free(temp4_);
    // free(temp3_);
    return temp5_;
}

RESULT_Enum SimDiscreteGrippingArmMovement_J4(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output) {
	if ((inputstate)->gripperClosed) {
		(*state).state = create_STATES_sm_Idle();
		(*state).status = create_STATUS_ENTER_STATE();
		return create_RESULT_CONT();
	} else if (!(inputstate)->gripperClosed) {
		(*state).state = create_STATES_sm_GripperClosing();
		(*state).status = create_STATUS_ENTER_STATE();
		return create_RESULT_CONT();
	} else {
		return create_RESULT_CONT();
	}
}
RESULT_Enum en_SimDiscreteGrippingArmMovement_GripperOpen_1(sm_state* state, sm_inputstate* inputstate, sm_memory* memory, sm_output_Enum_Channel* output) {
	{
		char _s0[256];
		sprintf(_s0, "%s", "Running entry action 1 of state SimDiscreteGrippingArmMovement_GripperOpen.");
		fprintf(log_file, "DEBUG: %s\n", _s0);
	}
	if (	(state)->en_SimDiscreteGrippingArmMovement_GripperOpen_1_counter == 0 ) {
		{
			pthread_barrier_wait(&output->can_write);
			output->value = create_sm_output_place((memory)->opening_diameter
													,(memory)->opening_speed
													,(memory)->opening_force);
			pthread_barrier_wait(&output->can_read);
		}
		(*state).en_SimDiscreteGrippingArmMovement_GripperOpen_1_counter = 1;
		return create_RESULT_CONT();
	} else {
		(state)->en_SimDiscreteGrippingArmMovement_GripperOpen_1_done = true;
		return create_RESULT_CONT();
	}
}
RESULT_Enum SimDiscreteGrippingArmMovement_J5(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output) {
	if ((inputstate)->gripperOpened) {
		(*state).state = create_STATES_sm_Idle();
		(*state).status = create_STATUS_ENTER_STATE();
		return create_RESULT_CONT();
	} else if (!(inputstate)->gripperOpened) {
		(*state).state = create_STATES_sm_GripperOpening();
		(*state).status = create_STATUS_ENTER_STATE();
		return create_RESULT_CONT();
	} else {
		return create_RESULT_CONT();
	}
}
RESULT_Enum SimDiscreteGrippingArmMovement_J3(sm_state* state, sm_inputstate* inputstate, sm_memory* memorystate, sm_output_Enum_Channel* output) {
	if (!(inputstate)->robotStopped) {
		(*state).state = create_STATES_sm_ArmStopping();
		(*state).status = create_STATUS_ENTER_STATE();
		return create_RESULT_CONT();
	} else if ((inputstate)->robotStopped) {
		(*state).state = create_STATES_sm_Idle();
		(*state).status = create_STATUS_ENTER_STATE();
		return create_RESULT_CONT();
	} else {
		return create_RESULT_CONT();
	}
}

#endif


