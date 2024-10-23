/*! \file skeleton.c
 * In this file there are the implementations
 * of the fuctions declared in fmu.h
 * along with the data needed.
 */
#include "fmu.h"
#include <stdio.h>

/**
 * Function for the initialization of the model.
 * It calls the init function of the model and sets the output.
 * It initializes the semaphore and creates the websocket thread.
 * @param location is the directory where the fmu has been unzipped. Might be used in future version
 *
 */
void initialize(ModelInstance* comp, const char* location) {
    init(&comp->modelData);
    comp->fmiBuffer.booleanBuffer[0] = comp->modelData.feasibleMoveDiscreteCommand;
    comp->fmiBuffer.booleanBuffer[1] = comp->modelData.robotStopped;
    comp->fmiBuffer.booleanBuffer[2] = comp->modelData.gripperOpened;
    comp->fmiBuffer.booleanBuffer[3] = comp->modelData.collision;
    comp->fmiBuffer.booleanBuffer[4] = comp->modelData.closeGripperCommand;
    comp->fmiBuffer.booleanBuffer[5] = comp->modelData.gripperClosed;
    comp->fmiBuffer.booleanBuffer[6] = comp->modelData.nonfeasibleMoveDiscreteCommand;
    comp->fmiBuffer.booleanBuffer[7] = comp->modelData.moveCompleted;
    comp->fmiBuffer.booleanBuffer[8] = comp->modelData.openGripperCommand;
    comp->fmiBuffer.booleanBuffer[9] = comp->modelData.moveDiscreteCommand;
    comp->fmiBuffer.intBuffer[10] = comp->modelData.MovementArgs_target_X;
    comp->fmiBuffer.intBuffer[11] = comp->modelData.MovementArgs_target_Y;
    comp->fmiBuffer.intBuffer[12] = comp->modelData.MovementArgs_target_Z;
    comp->fmiBuffer.booleanBuffer[13] = comp->modelData.movediscrete;
    comp->fmiBuffer.booleanBuffer[14] = comp->modelData.pick;
    comp->fmiBuffer.booleanBuffer[15] = comp->modelData.place;
    comp->fmiBuffer.intBuffer[16] = comp->modelData.target_X;
    comp->fmiBuffer.intBuffer[17] = comp->modelData.target_Y;
    comp->fmiBuffer.intBuffer[18] = comp->modelData.target_Z;
    comp->fmiBuffer.realBuffer[19] = comp->modelData.closing_diameter;
    comp->fmiBuffer.realBuffer[20] = comp->modelData.closing_speed;
    comp->fmiBuffer.realBuffer[21] = comp->modelData.closing_force;
    comp->fmiBuffer.realBuffer[22] = comp->modelData.opening_diameter;
    comp->fmiBuffer.realBuffer[23] = comp->modelData.opening_speed;
    comp->fmiBuffer.realBuffer[24] = comp->modelData.opening_force;
    comp->fmiBuffer.booleanBuffer[25] = comp->modelData.stop;
    comp->fmiBuffer.booleanBuffer[26] = comp->modelData.movejoint;
    comp->fmiBuffer.realBuffer[27] = comp->modelData.target_q0;
    comp->fmiBuffer.realBuffer[28] = comp->modelData.target_q1;
    comp->fmiBuffer.realBuffer[29] = comp->modelData.target_q2;
    comp->fmiBuffer.realBuffer[30] = comp->modelData.target_q3;
    comp->fmiBuffer.realBuffer[31] = comp->modelData.target_q4;
    comp->fmiBuffer.realBuffer[32] = comp->modelData.target_q5;
    comp->fmiBuffer.booleanBuffer[33] = comp->modelData.movecartesian;
    comp->fmiBuffer.realBuffer[34] = comp->modelData.target_x;
    comp->fmiBuffer.realBuffer[35] = comp->modelData.target_y;
    comp->fmiBuffer.realBuffer[36] = comp->modelData.target_z;
    comp->fmiBuffer.realBuffer[37] = comp->modelData.target_rx;
    comp->fmiBuffer.realBuffer[38] = comp->modelData.target_ry;
    comp->fmiBuffer.realBuffer[39] = comp->modelData.target_rz;
    comp->fmiBuffer.booleanBuffer[40] = comp->modelData.setvelocity;
    comp->fmiBuffer.realBuffer[41] = comp->modelData.target_v;
    comp->fmiBuffer.stringBuffer[42] = comp->modelData.state;
    comp->fmiBuffer.stringBuffer[43] = comp->modelData.target_state;
    comp->fmiBuffer.stringBuffer[44] = comp->modelData.status;
    comp->fmiBuffer.booleanBuffer[45] = comp->modelData.done;
    comp->first = 0;
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
        comp->modelData.feasibleMoveDiscreteCommand = comp->fmiBuffer.booleanBuffer[0];
        comp->modelData.robotStopped = comp->fmiBuffer.booleanBuffer[1];
        comp->modelData.gripperOpened = comp->fmiBuffer.booleanBuffer[2];
        comp->modelData.collision = comp->fmiBuffer.booleanBuffer[3];
        comp->modelData.closeGripperCommand = comp->fmiBuffer.booleanBuffer[4];
        comp->modelData.gripperClosed = comp->fmiBuffer.booleanBuffer[5];
        comp->modelData.nonfeasibleMoveDiscreteCommand = comp->fmiBuffer.booleanBuffer[6];
        comp->modelData.moveCompleted = comp->fmiBuffer.booleanBuffer[7];
        comp->modelData.openGripperCommand = comp->fmiBuffer.booleanBuffer[8];
        comp->modelData.moveDiscreteCommand = comp->fmiBuffer.booleanBuffer[9];
        comp->modelData.MovementArgs_target_X = comp->fmiBuffer.intBuffer[10];
        comp->modelData.MovementArgs_target_Y = comp->fmiBuffer.intBuffer[11];
        comp->modelData.MovementArgs_target_Z = comp->fmiBuffer.intBuffer[12];
    }
    // Inputs and arguments
    comp->modelData.feasibleMoveDiscreteCommand = comp->fmiBuffer.booleanBuffer[0];
    comp->modelData.robotStopped = comp->fmiBuffer.booleanBuffer[1];
    comp->modelData.gripperOpened = comp->fmiBuffer.booleanBuffer[2];
    comp->modelData.collision = comp->fmiBuffer.booleanBuffer[3];
    comp->modelData.closeGripperCommand = comp->fmiBuffer.booleanBuffer[4];
    comp->modelData.gripperClosed = comp->fmiBuffer.booleanBuffer[5];
    comp->modelData.nonfeasibleMoveDiscreteCommand = comp->fmiBuffer.booleanBuffer[6];
    comp->modelData.moveCompleted = comp->fmiBuffer.booleanBuffer[7];
    comp->modelData.openGripperCommand = comp->fmiBuffer.booleanBuffer[8];
    comp->modelData.moveDiscreteCommand = comp->fmiBuffer.booleanBuffer[9];
    comp->modelData.MovementArgs_target_X = comp->fmiBuffer.intBuffer[10];
    comp->modelData.MovementArgs_target_Y = comp->fmiBuffer.intBuffer[11];
    comp->modelData.MovementArgs_target_Z = comp->fmiBuffer.intBuffer[12];
    // step in the module
    tick(&comp->modelData);
    // Outputs
    comp->fmiBuffer.booleanBuffer[13] = comp->modelData.movediscrete;
    comp->fmiBuffer.booleanBuffer[14] = comp->modelData.pick;
    comp->fmiBuffer.booleanBuffer[15] = comp->modelData.place;
    comp->fmiBuffer.intBuffer[16] = comp->modelData.target_X;
    comp->fmiBuffer.intBuffer[17] = comp->modelData.target_Y;
    comp->fmiBuffer.intBuffer[18] = comp->modelData.target_Z;
    comp->fmiBuffer.realBuffer[19] = comp->modelData.closing_diameter;
    comp->fmiBuffer.realBuffer[20] = comp->modelData.closing_speed;
    comp->fmiBuffer.realBuffer[21] = comp->modelData.closing_force;
    comp->fmiBuffer.realBuffer[22] = comp->modelData.opening_diameter;
    comp->fmiBuffer.realBuffer[23] = comp->modelData.opening_speed;
    comp->fmiBuffer.realBuffer[24] = comp->modelData.opening_force;
    comp->fmiBuffer.booleanBuffer[25] = comp->modelData.stop;
    comp->fmiBuffer.booleanBuffer[26] = comp->modelData.movejoint;
    comp->fmiBuffer.realBuffer[27] = comp->modelData.target_q0;
    comp->fmiBuffer.realBuffer[28] = comp->modelData.target_q1;
    comp->fmiBuffer.realBuffer[29] = comp->modelData.target_q2;
    comp->fmiBuffer.realBuffer[30] = comp->modelData.target_q3;
    comp->fmiBuffer.realBuffer[31] = comp->modelData.target_q4;
    comp->fmiBuffer.realBuffer[32] = comp->modelData.target_q5;
    comp->fmiBuffer.booleanBuffer[33] = comp->modelData.movecartesian;
    comp->fmiBuffer.realBuffer[34] = comp->modelData.target_x;
    comp->fmiBuffer.realBuffer[35] = comp->modelData.target_y;
    comp->fmiBuffer.realBuffer[36] = comp->modelData.target_z;
    comp->fmiBuffer.realBuffer[37] = comp->modelData.target_rx;
    comp->fmiBuffer.realBuffer[38] = comp->modelData.target_ry;
    comp->fmiBuffer.realBuffer[39] = comp->modelData.target_rz;
    comp->fmiBuffer.booleanBuffer[40] = comp->modelData.setvelocity;
    comp->fmiBuffer.realBuffer[41] = comp->modelData.target_v;
    comp->fmiBuffer.stringBuffer[42] = comp->modelData.state;
    comp->fmiBuffer.stringBuffer[43] = comp->modelData.target_state;
    comp->fmiBuffer.stringBuffer[44] = comp->modelData.status;
    comp->fmiBuffer.booleanBuffer[45] = comp->modelData.done;
}

void terminate(ModelInstance* comp) {
    comp->terminateSimulation = true;
    comp->modelData.terminateSimulation = true;
    release();
}
