#pragma once
#define FMI_VERSION 2

#ifndef FMU_H
#define FMU_H
#endif

#if FMI_VERSION != 1 && FMI_VERSION != 2 && FMI_VERSION != 3
#error FMI_VERSION must be one of 1, 2 or 3
#endif

#define UNUSED(x) (void)(x)

#include <stddef.h>  // for size_t
#include <stdbool.h> // for bool
#include <stdint.h>



#include "./fmi/fmi2Functions.h"
#include "FmuGUID.h"
//#include "model.h"
//#include "misraC/DiscreteGrippingArm.h"


#define BOOL_COUNT 13
#define INT_COUNT 13
#define REAL_COUNT 13
#define STRING_COUNT 13
#define FMI_COSIMULATION

//#include "config.h"

#if FMI_VERSION == 1

#define not_modelError (Instantiated| Initialized | Terminated)

typedef enum {
    Instantiated = 1<<0,
    Initialized  = 1<<1,
    Terminated   = 1<<2,
    modelError   = 1<<3
} ModelState;

#elif FMI_VERSION == 2

typedef enum {
    StartAndEnd        = 1<<0,
    Instantiated       = 1<<1,
    InitializationMode = 1<<2,

    // ME states
    EventMode          = 1<<3,
    ContinuousTimeMode = 1<<4,

    // CS states
    StepComplete       = 1<<5,
    StepInProgress     = 1<<6,
    StepFailed         = 1<<7,
    StepCanceled       = 1<<8,

    Terminated         = 1<<9,
} ModelState;

#else

typedef enum {
    StartAndEnd            = 1 << 0,
    ConfigurationMode      = 1 << 1,
    Instantiated           = 1 << 2,
    InitializationMode     = 1 << 3,
    EventMode              = 1 << 4,
    ContinuousTimeMode     = 1 << 5,
    StepMode               = 1 << 6,
    ClockActivationMode    = 1 << 7,
    StepDiscarded          = 1 << 8,
    ReconfigurationMode    = 1 << 9,
    IntermediateUpdateMode = 1 << 10,
    Terminated             = 1 << 11,
} ModelState;

#endif

typedef enum {
    ModelExchange,
    CoSimulation,
    ScheduledExecution,
} InterfaceType;

typedef enum {
    OK,
    Warning,
    Discard,
    Error,
    Fatal,
    Pending
} Status;

#if FMI_VERSION < 3
typedef void (*loggerType) (void *componentEnvironment, const char *instanceName, int status, const char *category, const char *message, ...);
#else
typedef void (*loggerType) (void *componentEnvironment, int status, const char *category, const char *message);
#endif

typedef void (*lockPreemptionType)   (void);
typedef void (*unlockPreemptionType) (void);


typedef void (*intermediateUpdateType) (void *instanceEnvironment,
                                        double intermediateUpdateTime,
                                        bool intermediateVariableSetRequested,
                                        bool intermediateVariableGetAllowed,
                                        bool intermediateStepFinished,
                                        bool canReturnEarly,
                                        bool *earlyReturnRequested,
                                        double *earlyReturnTime);

typedef void(*clockUpdateType) (void *instanceEnvironment);

typedef enum {
    vr_time,
    vr_sm_memory,
    vr_sm_input_state,
    vr_sm_state,
    vr_en_SimDiscreteGrippingArmMovement_ArmStop_1_done,
    vr_en_SimDiscreteGrippingArmMovement_ArmStop_1_counter,
    vr_en_SimDiscreteGrippingArmMovement_GripperOpen_1_done,
    vr_en_SimDiscreteGrippingArmMovement_GripperOpen_1_counter,
    vr_en_SimDiscreteGrippingArmMovement_GripperClose_1_done,
  	vr_en_SimDiscreteGrippingArmMovement_GripperClose_1_counter,
  	vr_en_SimDiscreteGrippingArmMovement_ArmMove_1_done,
  	vr_en_SimDiscreteGrippingArmMovement_ArmMove_1_counter,
    vr_MOTION_VEL,
  	vr_opening_diameter,
  	vr_PI,
  	vr_av,
  	vr_TARGET_Y,
  	vr_closing_speed,
  	vr_closing_force,
  	vr_closing_diameter,
  	vr_lv,
  	vr_opening_speed,
  	vr_opening_force,
  	vr_TARGET_X,
  	vr_TARGET_Z,
    vr_target_X,
  	vr_target_Y,
    vr_target_Z,
    vr_gripperOpened,
  	vr_robotStopped,
  	vr_closeGripperCommand,
  	vr_collision,
  	vr_feasibleMoveDiscreteCommand,
  	vr_gripperClosed,
  	vr_nonfeasibleMoveDiscreteCommand,
  	vr_moveCompleted,
  	vr_openGripperCommand,
  	vr_moveDiscreteCommand,

} ValueReference;

typedef struct {
  //sm_memory sm_memory; // Variable containing the memories of the model
  //sm_inputstate sm_inputstate; // Variable containing the input states
  //sm_state sm_state; // Variable containing the state of the model

  // SM_STATE
  bool en_SimDiscreteGrippingArmMovement_ArmStop_1_done;
	int en_SimDiscreteGrippingArmMovement_ArmStop_1_counter;
	bool en_SimDiscreteGrippingArmMovement_GripperOpen_1_done;
	int en_SimDiscreteGrippingArmMovement_GripperOpen_1_counter;
	bool en_SimDiscreteGrippingArmMovement_GripperClose_1_done;
	int en_SimDiscreteGrippingArmMovement_GripperClose_1_counter;
	bool en_SimDiscreteGrippingArmMovement_ArmMove_1_done;
	int en_SimDiscreteGrippingArmMovement_ArmMove_1_counter;

  // SM_MEMORY
  float MOTION_VEL;
	float opening_diameter;
	float PI;
	float av;
	int TARGET_Y;
	float closing_speed;
	float closing_force;
	float closing_diameter;
	float lv;
	float opening_speed;
	//MovementArgs margs;
	float opening_force;
	int TARGET_X;
	int TARGET_Z;
  int target_X;
  int target_Y;
	int target_Z;

  //SM_INPUTSTATE
  bool gripperOpened;
	bool robotStopped;
	bool closeGripperCommand;
	bool collision;
	bool feasibleMoveDiscreteCommand;
	bool gripperClosed;
	bool nonfeasibleMoveDiscreteCommand;
	bool moveCompleted;
	bool openGripperCommand;
	bool moveDiscreteCommand;

} ModelData;

typedef struct {
     fmi2Boolean booleanBuffer[BOOL_COUNT];
     fmi2Integer intBuffer[INT_COUNT];
     fmi2Real realBuffer[REAL_COUNT];
     fmi2String stringBuffer[STRING_COUNT];
} FmiBuffer;

typedef struct {

    /* Specific to the framework*/
    FmiBuffer fmiBuffer;
  	//State st; 		// Structure containing the state of the model
  	int first;
    /* */

    double startTime;
    double stopTime;
    double time;
    const char *instanceName;
    InterfaceType type;
    const char *resourceLocation;

    Status status;

    // callback functions
    loggerType logger;
    intermediateUpdateType intermediateUpdate;
    clockUpdateType clockUpdate;

    lockPreemptionType lockPreemtion;
    unlockPreemptionType unlockPreemtion;

    bool logEvents;
    bool logErrors;

    void *componentEnvironment;
    ModelState state;

    // event info
    bool newDiscreteStatesNeeded;
    bool terminateSimulation;
    bool nominalsOfContinuousStatesChanged;
    bool valuesOfContinuousStatesChanged;
    bool nextEventTimeDefined;
    double nextEventTime;
    bool clocksTicked;

    bool isDirtyValues;

    ModelData modelData;

    // internal solver steps
    uint64_t nSteps;

    // Co-Simulation
    bool earlyReturnAllowed;
    bool eventModeUsed;

    // solver
    size_t nz;
    double* z;
    double* prez;

    size_t nx;
    double* x;
    double* dx;

} ModelInstance;

ModelInstance *createModelInstance(
    loggerType logger,
    intermediateUpdateType intermediateUpdate,
    void *componentEnvironment,
    const char *instanceName,
    const char *instantiationToken,
    const char *resourceLocation,
    bool loggingOn,
    InterfaceType interfaceType);

void freeModelInstance(ModelInstance *comp);

Status configurate(ModelInstance* comp);

Status reset(ModelInstance* comp);

void setStartValues(ModelInstance* comp);

Status calculateValues(ModelInstance *comp);

Status getFloat (ModelInstance* comp, ValueReference vr, float       values[], size_t nValues, size_t *index);
Status getInteger    (ModelInstance* comp, ValueReference vr, int      values[], size_t nValues, size_t *index);
/*Status getFloat32 (ModelInstance* comp, ValueReference vr, float       values[], size_t nValues, size_t *index);
Status getFloat64 (ModelInstance* comp, ValueReference vr, double      values[], size_t nValues, size_t *index);
Status getInt8    (ModelInstance* comp, ValueReference vr, int8_t      values[], size_t nValues, size_t *index);
Status getUInt8   (ModelInstance* comp, ValueReference vr, uint8_t     values[], size_t nValues, size_t *index);
Status getInt16   (ModelInstance* comp, ValueReference vr, int16_t     values[], size_t nValues, size_t *index);
Status getUInt16  (ModelInstance* comp, ValueReference vr, uint16_t    values[], size_t nValues, size_t *index);
Status getInt32   (ModelInstance* comp, ValueReference vr, int32_t     values[], size_t nValues, size_t *index);
Status getUInt32  (ModelInstance* comp, ValueReference vr, uint32_t    values[], size_t nValues, size_t *index);
Status getInt64   (ModelInstance* comp, ValueReference vr, int64_t     values[], size_t nValues, size_t *index);
Status getUInt64  (ModelInstance* comp, ValueReference vr, uint64_t    values[], size_t nValues, size_t *index);*/
Status getBoolean (ModelInstance* comp, ValueReference vr, bool        values[], size_t nValues, size_t *index);
Status getString  (ModelInstance* comp, ValueReference vr, const char* values[], size_t nValues, size_t *index);
Status getBinary  (ModelInstance* comp, ValueReference vr, size_t sizes[], const char* values[], size_t nValues, size_t *index);

Status setFloat (ModelInstance* comp, ValueReference vr, const float       values[], size_t nValues, size_t *index);
Status setInteger    (ModelInstance* comp, ValueReference vr, const int      values[], size_t nValues, size_t *index);
/*Status setFloat32 (ModelInstance* comp, ValueReference vr, const float       values[], size_t nValues, size_t *index);
Status setFloat64 (ModelInstance* comp, ValueReference vr, const double      values[], size_t nValues, size_t *index);
Status setInt8    (ModelInstance* comp, ValueReference vr, const int8_t      values[], size_t nValues, size_t *index);
Status setUInt8   (ModelInstance* comp, ValueReference vr, const uint8_t     values[], size_t nValues, size_t *index);
Status setInt16   (ModelInstance* comp, ValueReference vr, const int16_t     values[], size_t nValues, size_t *index);
Status setUInt16  (ModelInstance* comp, ValueReference vr, const uint16_t    values[], size_t nValues, size_t *index);
Status setInt32   (ModelInstance* comp, ValueReference vr, const int32_t     values[], size_t nValues, size_t *index);
Status setUInt32  (ModelInstance* comp, ValueReference vr, const uint32_t    values[], size_t nValues, size_t *index);
Status setInt64   (ModelInstance* comp, ValueReference vr, const int64_t     values[], size_t nValues, size_t *index);
Status setUInt64  (ModelInstance* comp, ValueReference vr, const uint64_t    values[], size_t nValues, size_t *index);*/
Status setBoolean (ModelInstance* comp, ValueReference vr, const bool        values[], size_t nValues, size_t *index);
Status setString  (ModelInstance* comp, ValueReference vr, const char* const values[], size_t nValues, size_t *index);
Status setBinary  (ModelInstance* comp, ValueReference vr, const size_t sizes[], const char* const values[], size_t nValues, size_t *index);

Status activateClock(ModelInstance* comp, ValueReference vr);
Status getClock(ModelInstance* comp, ValueReference vr, bool* value);
Status setClock(ModelInstance* comp, ValueReference vr, const bool* value);

Status getInterval(ModelInstance* comp, ValueReference vr, double* interval, int* qualifier);

Status activateModelPartition(ModelInstance* comp, ValueReference vr, double activationTime);

size_t getNumberOfEventIndicators(ModelInstance* comp);
size_t getNumberOfContinuousStates(ModelInstance* comp);
Status getContinuousStates(ModelInstance *comp, double x[], size_t nx);
Status setContinuousStates(ModelInstance *comp, const double x[], size_t nx);
Status getDerivatives(ModelInstance *comp, double dx[], size_t nx);
Status getOutputDerivative(ModelInstance *comp, ValueReference valueReference, int order, double *value);
Status getPartialDerivative(ModelInstance *comp, ValueReference unknown, ValueReference known, double *partialDerivative);
Status getEventIndicators(ModelInstance *comp, double z[], size_t nz);
Status eventUpdate(ModelInstance *comp);

bool invalidNumber(ModelInstance *comp, const char *f, const char *arg, size_t actual, size_t expected);
bool invalidState(ModelInstance *comp, const char *f, int statesExpected);
bool nullPointer(ModelInstance* comp, const char *f, const char *arg, const void *p);
void logError(ModelInstance *comp, const char *message, ...);
Status setDebugLogging(ModelInstance *comp, bool loggingOn, size_t nCategories, const char * const categories[]);
void logEvent(ModelInstance *comp, const char *message, ...);
void logError(ModelInstance *comp, const char *message, ...);

Status getFMUState(ModelInstance* comp, void** FMUState);
Status setFMUState(ModelInstance* comp, void* FMUState);

// shorthand to access the variables
#define M(v) (comp->modelData.v)

// "stringification" macros
#define xstr(s) str(s)
#define str(s) #s

// assert size of nValues for scalar variables
/*#define ASSERT_NVALUES(N) do { \
    const size_t expected_nValues = *index + (N); \
    if (expected_nValues > nValues) { \
        logError(comp, "Expected nValues >= %zu but was %zu.", expected_nValues, nValues); \
        return Error; \
    } \
} while (0)*/


/**
 * init function
 */
void init(ModelInstance* comp);


void initialize(ModelInstance*, fmi2String);
void doStep(ModelInstance*, const char*);
void terminate(ModelInstance*);

/**
 * triggers
 */
/*bool per_tick(ModelInstance* comp);*/
ModelInstance* tick(ModelInstance* comp);


/**
 * leave/enter functions
 */
/*void enter(Mode m, ModelInstance* comp);
void leave(Mode m, ModelInstance* comp);*/
