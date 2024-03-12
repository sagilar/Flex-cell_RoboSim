#ifndef FMU_H
#define FMU_H


#include "fmi/fmi2Functions.h"
#include "FmuGUID.h"
#include "misraC/defs_fmi.h"
#include <stdbool.h> // for bool


#define BOOL_COUNT 20
#define INT_COUNT 20
#define REAL_COUNT 20
#define STRING_COUNT 20
#define FMI_COSIMULATION

typedef struct {
     fmi2Boolean booleanBuffer[BOOL_COUNT];
     fmi2Integer intBuffer[INT_COUNT];
     fmi2Real realBuffer[REAL_COUNT];
     fmi2String stringBuffer[STRING_COUNT];
} FmiBuffer;

/*typedef struct {

    FmiBuffer fmiBuffer;
  	//State st; 		// Structure containing the state of the model
  	int first;

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

} ModelInstance;*/

/*typedef struct {
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

	//Terminate simulation
	bool terminateSimulation;

} ModelData;*/

typedef struct {
    /* Specific to the framework*/
    FmiBuffer fmiBuffer;
  	int first;
    bool terminateSimulation;
    ModelData modelData;
} ModelInstance;

//void setStartValues(ModelInstance* comp);

// shorthand to access the variables
//#define M(v) (comp->modelData.v)

// "stringification" macros
//#define xstr(s) str(s)
//#define str(s) #s

void initialize(ModelInstance*, fmi2String);
void doStep(ModelInstance*, const char*);
void terminate(ModelInstance*);

#endif
