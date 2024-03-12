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
    //init(comp->modelData);
    init(&comp->modelData);


    // parameters (i.e. memory)
    comp->fmiBuffer.realBuffer[30] = comp->modelData.MOTION_VEL;
    comp->fmiBuffer.realBuffer[31] = comp->modelData.opening_diameter;
    comp->fmiBuffer.realBuffer[32] = comp->modelData.PI;
    comp->fmiBuffer.realBuffer[33] = comp->modelData.av;
    comp->fmiBuffer.intBuffer[34] = comp->modelData.TARGET_X;
    comp->fmiBuffer.intBuffer[35] = comp->modelData.TARGET_Y;
    comp->fmiBuffer.intBuffer[36] = comp->modelData.TARGET_Z;
    comp->fmiBuffer.realBuffer[37] = comp->modelData.closing_speed;
    comp->fmiBuffer.realBuffer[38] = comp->modelData.closing_force;
    comp->fmiBuffer.realBuffer[39] = comp->modelData.closing_diameter;
    comp->fmiBuffer.realBuffer[40] = comp->modelData.lv;
    comp->fmiBuffer.realBuffer[41] = comp->modelData.opening_speed;
    comp->fmiBuffer.realBuffer[42] = comp->modelData.opening_force;
    //comp->fmiBuffer.realBuffer[43] = comp->modelData.margs;
    comp->fmiBuffer.intBuffer[12] = comp->modelData.target_X;
    comp->fmiBuffer.intBuffer[13] = comp->modelData.target_Y;
    comp->fmiBuffer.intBuffer[14] = comp->modelData.target_Z;

    // comp->fmiBuffer.realBuffer[30] = comp->MOTION_VEL;
    // comp->fmiBuffer.realBuffer[31] = comp->opening_diameter;
    // comp->fmiBuffer.realBuffer[32] = comp->PI;
    // comp->fmiBuffer.realBuffer[33] = comp->av;
    // comp->fmiBuffer.realBuffer[34] = comp->TARGET_X;
    // comp->fmiBuffer.realBuffer[35] = comp->TARGET_Y;
    // comp->fmiBuffer.realBuffer[36] = comp->TARGET_Z;
    // comp->fmiBuffer.realBuffer[37] = comp->closing_speed;
    // comp->fmiBuffer.realBuffer[38] = comp->closing_force;
    // comp->fmiBuffer.realBuffer[39] = comp->closing_diameter;
    // comp->fmiBuffer.realBuffer[40] = comp->lv;
    // comp->fmiBuffer.realBuffer[41] = comp->opening_speed;
    // comp->fmiBuffer.realBuffer[42] = comp->opening_force;
    // //comp->fmiBuffer.realBuffer[43] = comp->margs;
    // comp->fmiBuffer.intBuffer[44] = comp->margs.target_X;
    // comp->fmiBuffer.intBuffer[45] = comp->margs.target_Y;
    // comp->fmiBuffer.intBuffer[46] = comp->margs.target_Z;

    comp->fmiBuffer.booleanBuffer[1] = comp->modelData.collision;
    comp->fmiBuffer.booleanBuffer[2] = comp->modelData.gripperOpened;
    comp->fmiBuffer.booleanBuffer[3] = comp->modelData.closeGripperCommand;
    comp->fmiBuffer.booleanBuffer[4] = comp->modelData.robotStopped;
    comp->fmiBuffer.booleanBuffer[5] = comp->modelData.moveCompleted;
    comp->fmiBuffer.booleanBuffer[6] = comp->modelData.gripperClosed;
    comp->fmiBuffer.booleanBuffer[7] = comp->modelData.feasibleMoveDiscreteCommand;
    comp->fmiBuffer.booleanBuffer[8] = comp->modelData.openGripperCommand;
    comp->fmiBuffer.booleanBuffer[9] = comp->modelData.moveDiscreteCommand;
    comp->fmiBuffer.booleanBuffer[10] = comp->modelData.nonfeasibleMoveDiscreteCommand;




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
      comp->modelData.MOTION_VEL = comp->fmiBuffer.realBuffer[30];
      comp->modelData.opening_diameter = comp->fmiBuffer.realBuffer[31];
      comp->modelData.PI = comp->fmiBuffer.realBuffer[32];
      comp->modelData.av = comp->fmiBuffer.realBuffer[33];
      comp->modelData.TARGET_X = comp->fmiBuffer.intBuffer[34];
      comp->modelData.TARGET_Y = comp->fmiBuffer.intBuffer[35];
      comp->modelData.TARGET_Z = comp->fmiBuffer.intBuffer[36];
      comp->modelData.closing_speed = comp->fmiBuffer.realBuffer[37];
      comp->modelData.closing_force = comp->fmiBuffer.realBuffer[38];
      comp->modelData.closing_diameter = comp->fmiBuffer.realBuffer[39];
      comp->modelData.lv = comp->fmiBuffer.realBuffer[40];
      comp->modelData.opening_speed = comp->fmiBuffer.realBuffer[41];
      comp->modelData.opening_force = comp->fmiBuffer.realBuffer[42];

      comp->first = 1;
  	}
    //parameters

    /*comp->modelData.MOTION_VEL = comp->fmiBuffer.realBuffer[30];
    comp->modelData.opening_diameter = comp->fmiBuffer.realBuffer[31];
    comp->modelData.PI = comp->fmiBuffer.realBuffer[32];
    comp->modelData.av = comp->fmiBuffer.realBuffer[33];
    comp->modelData.TARGET_X = comp->fmiBuffer.intBuffer[34];
    comp->modelData.TARGET_Y = comp->fmiBuffer.intBuffer[35];
    comp->modelData.TARGET_Z = comp->fmiBuffer.intBuffer[36];
    comp->modelData.closing_speed = comp->fmiBuffer.realBuffer[37];
    comp->modelData.closing_force = comp->fmiBuffer.realBuffer[38];
    comp->modelData.closing_diameter = comp->fmiBuffer.realBuffer[39];
    comp->modelData.lv = comp->fmiBuffer.realBuffer[40];
    comp->modelData.opening_speed = comp->fmiBuffer.realBuffer[41];
    comp->modelData.opening_force = comp->fmiBuffer.realBuffer[42];*/
    //comp->modelData.margs = comp->fmiBuffer.realBuffer[43];
    comp->modelData.target_X = comp->fmiBuffer.intBuffer[12];
    comp->modelData.target_Y = comp->fmiBuffer.intBuffer[13];
    comp->modelData.target_Z = comp->fmiBuffer.intBuffer[14];


    // inputs
    comp->modelData.collision = comp->fmiBuffer.booleanBuffer[1];
    comp->modelData.gripperOpened = comp->fmiBuffer.booleanBuffer[2];
    comp->modelData.closeGripperCommand = comp->fmiBuffer.booleanBuffer[3];
    comp->modelData.robotStopped = comp->fmiBuffer.booleanBuffer[4];
    comp->modelData.moveCompleted = comp->fmiBuffer.booleanBuffer[5];
    comp->modelData.gripperClosed = comp->fmiBuffer.booleanBuffer[6];
    comp->modelData.feasibleMoveDiscreteCommand = comp->fmiBuffer.booleanBuffer[7];
    comp->modelData.openGripperCommand = comp->fmiBuffer.booleanBuffer[8];
    comp->modelData.moveDiscreteCommand = comp->fmiBuffer.booleanBuffer[9];
    comp->modelData.nonfeasibleMoveDiscreteCommand = comp->fmiBuffer.booleanBuffer[10];
    //comp->modelData.moveDiscreteCommand_value = comp->fmiBuffer.realBuffer[11];
    //comp->modelData.moveDiscreteCommand_value.target_X = comp->fmiBuffer.intBuffer[12];
    //comp->modelData.moveDiscreteCommand_value.target_Y = comp->fmiBuffer.intBuffer[13];
    //comp->modelData.moveDiscreteCommand_value.target_Z = comp->fmiBuffer.intBuffer[14];
    //tick(comp->modelData);
    tick(&comp->modelData);

    //outputs TO UPDATE
    comp->fmiBuffer.stringBuffer[24] = comp->modelData.output_command;
    comp->fmiBuffer.stringBuffer[21] = comp->modelData.state;
    /*comp->fmiBuffer.stringBuffer[20] = comp->modelData.done;
    comp->fmiBuffer.stringBuffer[21] = comp->modelData.state;
    comp->fmiBuffer.stringBuffer[22] = comp->modelData.target_state;
    comp->fmiBuffer.stringBuffer[23] = comp->modelData.status;*/


}

void terminate(ModelInstance* comp) {
    comp->terminateSimulation = true;
    comp->modelData.terminateSimulation = true;
    release();
}
