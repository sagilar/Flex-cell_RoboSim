#ifndef FMU_H
#define FMU_H


#include "fmi/fmi2Functions.h"
#include "FmuGUID.h"
#include "misraC/defs_fmi.h"
#include <stdbool.h> // for bool


#define BOOL_COUNT 40
#define INT_COUNT 40
#define REAL_COUNT 40
#define STRING_COUNT 40
#define FMI_COSIMULATION

typedef struct {
     fmi2Boolean booleanBuffer[BOOL_COUNT];
     fmi2Integer intBuffer[INT_COUNT];
     fmi2Real realBuffer[REAL_COUNT];
     fmi2String stringBuffer[STRING_COUNT];
} FmiBuffer;


typedef struct {
    /* Specific to the framework*/
    FmiBuffer fmiBuffer;
  	int first;
    bool terminateSimulation;
    ModelData modelData;
} ModelInstance;

void initialize(ModelInstance*, fmi2String);
void doStep(ModelInstance*, const char*);
void terminate(ModelInstance*);

#endif
