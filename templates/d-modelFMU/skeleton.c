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

    /* Update based on the RoboSim module data and the valueReference indexes in the ModelDescription.xml */
    comp->fmiBuffer.realBuffer[0] = comp->modelData.var0_float;
    comp->fmiBuffer.booleanBuffer[1] = comp->modelData.var1_boolean;
    comp->fmiBuffer.stringBuffer[2] = comp->modelData.var2_string;
    comp->fmiBuffer.intBuffer[3] = comp->modelData.var3_int;
    comp->fmiBuffer.booleanBuffer[4] = comp->modelData.var4_boolean;
    comp->fmiBuffer.booleanBuffer[5] = comp->modelData.var5_boolean;

    comp->first = 0;
    /*Initialization complete*/
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
      //inputs
      comp->modelData.var1_boolean = comp->fmiBuffer.booleanBuffer[1];
      comp->modelData.var2_string = comp->fmiBuffer.stringBuffer[2];

      comp->first = 1;
  	}
    //inputs and arguments
    comp->modelData.var1_boolean = comp->fmiBuffer.booleanBuffer[1];
    comp->modelData.var2_string = comp->fmiBuffer.stringBuffer[2];

    //step in the module
    tick(&comp->modelData);

    //outputs
    comp->fmiBuffer.realBuffer[0] = comp->modelData.var0_float;
    comp->fmiBuffer.intBuffer[3] = comp->modelData.var3_int;
    comp->fmiBuffer.booleanBuffer[4] = comp->modelData.var4_boolean;
    comp->fmiBuffer.booleanBuffer[5] = comp->modelData.var5_boolean;

}

void terminate(ModelInstance* comp) {
    comp->terminateSimulation = true;
    comp->modelData.terminateSimulation = true;
    release();
}
