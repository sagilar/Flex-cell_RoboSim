/*! \file fmu.h
 * This file contains the definitions of the functions used by myfmu.cpp:
 * 		initialize(fmi2String );
 * 			this one needs the string as parameter to forward the path where the resources folder is unzipped
 *		void doStep(const char*);
 * 			this is the function called every time the fmi2DoStep is invoked
 *		void terminate();
 * 			this is the function called when the co-simulation terminates
 * 		FmiBuffer
 * 			This structure maintains all the variables that are accessed by means of fmi2GetXXX and fmi2SetXXX
 *
 **/
#ifndef FMU_H
#define FMU_H

#include "./fmi/fmi2Functions.h"
#include "FmuGUID.h"
//#include "DiscreteGrippingArm.h"


#define BOOL_COUNT 13
#define INT_COUNT 13
#define REAL_COUNT 13
#define STRING_COUNT 13
#define FMI_COSIMULATION

typedef struct {
     fmi2Boolean booleanBuffer[BOOL_COUNT];
     fmi2Integer intBuffer[INT_COUNT];
     fmi2Real realBuffer[REAL_COUNT];
     fmi2String stringBuffer[STRING_COUNT];
} FmiBuffer;;

typedef struct {
	FmiBuffer fmiBuffer;
	//State st; 		// Structure containing the state of the model
	int first;	 	// Variable for execution of setup option during first step only
  sm_memory sm_memory; // Variable containing the memories of the model
  sm_inputstate sm_inputstate; // Variable containing the input states
  sm_state sm_state; // Variable containing the state of the model

} ModelInstance;

void initialize(ModelInstance*, fmi2String);
void doStep(ModelInstance*, const char*);
void terminate(ModelInstance*);


#endif // FMU_H
