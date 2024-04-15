/*! \file skeleton.c
 * In this file there are the implementations
 * of the fuctions declared in fmu.h
 * along with the data needed.
 */
#include "fmu.h"
#include <stdio.h>

/* d-model


// States
(inputstate).collision = false;
(inputstate).gripperOpened = false;
(inputstate).closeGripperCommand = false;
(inputstate).robotStopped = false;
(inputstate).moveCompleted = false;
(inputstate).gripperClosed = false;
(inputstate).feasibleMoveDiscreteCommand = false;
(inputstate).openGripperCommand = false;
(inputstate).moveDiscreteCommand = false;
(inputstate).nonfeasibleMoveDiscreteCommand = false;

// Inputs
comp->fmiBuffer.realBuffer[1] = comp->sm_inputstate.collision;
comp->fmiBuffer.realBuffer[2] = comp->sm_inputstate.gripperOpened;
comp->fmiBuffer.realBuffer[3] = comp->sm_inputstate.closeGripperCommand;
comp->fmiBuffer.realBuffer[4] = comp->sm_inputstate.robotStopped;
comp->fmiBuffer.realBuffer[5] = comp->sm_inputstate.moveCompleted;
comp->fmiBuffer.realBuffer[6] = comp->sm_inputstate.gripperClosed;
comp->fmiBuffer.realBuffer[7] = comp->sm_inputstate.feasibleMoveDiscreteCommand;
comp->fmiBuffer.realBuffer[8] = comp->sm_inputstate.openGripperCommand;
comp->fmiBuffer.realBuffer[9] = comp->sm_inputstate.moveDiscreteCommand;
comp->fmiBuffer.realBuffer[10] = comp->sm_inputstate.nonfeasibleMoveDiscreteCommand;
comp->fmiBuffer.realBuffer[11] = comp->sm_inputstate.moveDiscreteCommand_value;
comp->fmiBuffer.realBuffer[12] = comp->sm_inputstate.moveDiscreteCommand_value.target_X;
comp->fmiBuffer.realBuffer[13] = comp->sm_inputstate.moveDiscreteCommand_value.target_Y;
comp->fmiBuffer.realBuffer[14] = comp->sm_inputstate.moveDiscreteCommand_value.target_Z;

// Outputs
comp->fmiBuffer.realBuffer[20] = comp->sm_state.done;
comp->fmiBuffer.realBuffer[21] = comp->sm_state.state;
comp->fmiBuffer.realBuffer[22] = comp->sm_state.target_state;
comp->fmiBuffer.realBuffer[23] = comp->sm_state.status;

// Memory
comp->fmiBuffer.realBuffer[30] = comp->sm_memory.MOTION_VEL;
comp->fmiBuffer.realBuffer[31] = comp->sm_memory.opening_diameter;
comp->fmiBuffer.realBuffer[32] = comp->sm_memory.PI;
comp->fmiBuffer.realBuffer[33] = comp->sm_memory.av;
comp->fmiBuffer.realBuffer[34] = comp->sm_memory.TARGET_X;
comp->fmiBuffer.realBuffer[35] = comp->sm_memory.TARGET_Y;
comp->fmiBuffer.realBuffer[36] = comp->sm_memory.TARGET_Z;
comp->fmiBuffer.realBuffer[37] = comp->sm_memory.closing_speed;
comp->fmiBuffer.realBuffer[38] = comp->sm_memory.closing_force;
comp->fmiBuffer.realBuffer[39] = comp->sm_memory.closing_diameter;
comp->fmiBuffer.realBuffer[40] = comp->sm_memory.lv;
comp->fmiBuffer.realBuffer[41] = comp->sm_memory.opening_speed;
comp->fmiBuffer.realBuffer[42] = comp->sm_memory.opening_force;
comp->fmiBuffer.realBuffer[43] = comp->sm_memory.margs;
comp->fmiBuffer.realBuffer[44] = comp->sm_memory.margs.target_X;
comp->fmiBuffer.realBuffer[45] = comp->sm_memory.margs.target_Y;
comp->fmiBuffer.realBuffer[46] = comp->sm_memory.margs.target_Z;

*/


 /**
 * Function for the initialization of the model.
 * It calls the init function of the model and sets the output.
 * It initializes the semaphore and creates the websocket thread.
 * @param location is the directory where the fmu has been unzipped. Might be used in future version
 *
 */
void initialize(ModelInstance* comp, const char* location) {
    init(&comp->modelData);


    // input events from platform mapping
    comp->fmiBuffer.booleanBuffer[0] = comp->modelData.collision;
    comp->fmiBuffer.booleanBuffer[1] = comp->modelData.gripperOpened;
    comp->fmiBuffer.booleanBuffer[2] = comp->modelData.closeGripperCommand;
    comp->fmiBuffer.booleanBuffer[3] = comp->modelData.robotStopped;
    comp->fmiBuffer.booleanBuffer[4] = comp->modelData.moveCompleted;
    comp->fmiBuffer.booleanBuffer[5] = comp->modelData.gripperClosed;
    comp->fmiBuffer.booleanBuffer[6] = comp->modelData.feasibleMoveDiscreteCommand;
    comp->fmiBuffer.booleanBuffer[7] = comp->modelData.openGripperCommand;
    comp->fmiBuffer.booleanBuffer[8] = comp->modelData.moveDiscreteCommand;
    comp->fmiBuffer.booleanBuffer[9] = comp->modelData.nonfeasibleMoveDiscreteCommand;
    // arguments(inputs)
    //comp->fmiBuffer.intBuffer[10] = comp->modelData.target_X;
    //comp->fmiBuffer.intBuffer[11] = comp->modelData.target_Y;
    //comp->fmiBuffer.intBuffer[12] = comp->modelData.target_Z;
    comp->fmiBuffer.realBuffer[10] = comp->modelData.target_X;
    comp->fmiBuffer.realBuffer[11] = comp->modelData.target_Y;
    comp->fmiBuffer.realBuffer[12] = comp->modelData.target_Z;
    // parameters (i.e. memory)
    comp->fmiBuffer.realBuffer[13] = comp->modelData.MOTION_VEL;
    comp->fmiBuffer.realBuffer[14] = comp->modelData.opening_diameter;
    comp->fmiBuffer.realBuffer[15] = comp->modelData.PI;
    comp->fmiBuffer.realBuffer[16] = comp->modelData.av;
    comp->fmiBuffer.realBuffer[17] = comp->modelData.closing_speed;
    comp->fmiBuffer.realBuffer[18] = comp->modelData.closing_force;
    comp->fmiBuffer.realBuffer[19] = comp->modelData.closing_diameter;
    comp->fmiBuffer.realBuffer[20] = comp->modelData.lv;
    comp->fmiBuffer.realBuffer[21] = comp->modelData.opening_speed;
    comp->fmiBuffer.realBuffer[22] = comp->modelData.opening_force;
    // outputs to platform mapping
    comp->fmiBuffer.booleanBuffer[23] = comp->modelData.done;
    comp->fmiBuffer.stringBuffer[24] = comp->modelData.state;
    comp->fmiBuffer.stringBuffer[25] = comp->modelData.target_state;
    comp->fmiBuffer.stringBuffer[26] = comp->modelData.status;
    comp->fmiBuffer.stringBuffer[27] = comp->modelData.d_model_event;
    comp->fmiBuffer.realBuffer[28] = comp->modelData.d_model_event_args_0;
    comp->fmiBuffer.realBuffer[29] = comp->modelData.d_model_event_args_1;
    comp->fmiBuffer.realBuffer[30] = comp->modelData.d_model_event_args_2;
    comp->fmiBuffer.realBuffer[31] = comp->modelData.d_model_event_args_3;
    comp->fmiBuffer.realBuffer[32] = comp->modelData.d_model_event_args_4;
    comp->fmiBuffer.realBuffer[33] = comp->modelData.d_model_event_args_5;
    comp->fmiBuffer.realBuffer[34] = comp->modelData.d_model_event_args_6;
    comp->fmiBuffer.realBuffer[35] = comp->modelData.d_model_event_args_7;
    comp->fmiBuffer.realBuffer[36] = comp->modelData.d_model_event_args_8;
    comp->fmiBuffer.realBuffer[37] = comp->modelData.d_model_event_args_9;


    comp->first = 0;
    /**/
    printf("Initialization complete\n");
}

/**
 * Function that performs a step of the simulation model.
 * At first the inputs of the are updated with the values fom the master algorithm.
 * Then the tick function is called inside the mutex, in order to guarantee mutual exlusion.
 * Finally the outputs of the model are forwarded to the master algorithm
 * @param action is the action to perform. Might be used in future version.
 */
void doStep(ModelInstance* comp, const char* action) {
  	if(comp->first == 0) {
      //parameters
      comp->modelData.MOTION_VEL = comp->fmiBuffer.realBuffer[13];
      comp->modelData.opening_diameter = comp->fmiBuffer.realBuffer[14];
      comp->modelData.PI = comp->fmiBuffer.realBuffer[15];
      comp->modelData.av = comp->fmiBuffer.realBuffer[16];
      comp->modelData.closing_speed = comp->fmiBuffer.realBuffer[17];
      comp->modelData.closing_force = comp->fmiBuffer.realBuffer[18];
      comp->modelData.closing_diameter = comp->fmiBuffer.realBuffer[19];
      comp->modelData.lv = comp->fmiBuffer.realBuffer[20];
      comp->modelData.opening_speed = comp->fmiBuffer.realBuffer[21];
      comp->modelData.opening_force = comp->fmiBuffer.realBuffer[22];

      comp->first = 1;
  	}
    //inputs and arguments
    comp->modelData.collision = comp->fmiBuffer.booleanBuffer[0];
    comp->modelData.gripperOpened = comp->fmiBuffer.booleanBuffer[1];
    comp->modelData.closeGripperCommand = comp->fmiBuffer.booleanBuffer[2];
    comp->modelData.robotStopped = comp->fmiBuffer.booleanBuffer[3];
    comp->modelData.moveCompleted = comp->fmiBuffer.booleanBuffer[4];
    comp->modelData.gripperClosed = comp->fmiBuffer.booleanBuffer[5];
    comp->modelData.feasibleMoveDiscreteCommand = comp->fmiBuffer.booleanBuffer[6];
    comp->modelData.openGripperCommand = comp->fmiBuffer.booleanBuffer[7];
    comp->modelData.moveDiscreteCommand = comp->fmiBuffer.booleanBuffer[8];
    comp->modelData.nonfeasibleMoveDiscreteCommand = comp->fmiBuffer.booleanBuffer[9];
    comp->modelData.target_X = comp->fmiBuffer.realBuffer[10];
    comp->modelData.target_Y = comp->fmiBuffer.realBuffer[11];
    comp->modelData.target_Z = comp->fmiBuffer.realBuffer[12];

    //step in the module
    tick(&comp->modelData);

    //outputs
    comp->fmiBuffer.booleanBuffer[23] = comp->modelData.done;
    comp->fmiBuffer.stringBuffer[24] = comp->modelData.state;
    comp->fmiBuffer.stringBuffer[25] = comp->modelData.target_state;
    comp->fmiBuffer.stringBuffer[26] = comp->modelData.status;
    comp->fmiBuffer.stringBuffer[27] = comp->modelData.d_model_event;
    comp->fmiBuffer.realBuffer[28] = comp->modelData.d_model_event_args_0;
    comp->fmiBuffer.realBuffer[29] = comp->modelData.d_model_event_args_1;
    comp->fmiBuffer.realBuffer[30] = comp->modelData.d_model_event_args_2;
    comp->fmiBuffer.realBuffer[31] = comp->modelData.d_model_event_args_3;
    comp->fmiBuffer.realBuffer[32] = comp->modelData.d_model_event_args_4;
    comp->fmiBuffer.realBuffer[33] = comp->modelData.d_model_event_args_5;
    comp->fmiBuffer.realBuffer[34] = comp->modelData.d_model_event_args_6;
    comp->fmiBuffer.realBuffer[35] = comp->modelData.d_model_event_args_7;
    comp->fmiBuffer.realBuffer[36] = comp->modelData.d_model_event_args_8;
    comp->fmiBuffer.realBuffer[37] = comp->modelData.d_model_event_args_9;

}

void terminate(ModelInstance* comp) {
    comp->terminateSimulation = true;
    comp->modelData.terminateSimulation = true;
    release();
}
