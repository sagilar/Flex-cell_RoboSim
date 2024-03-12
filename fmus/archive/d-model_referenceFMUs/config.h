#ifndef config_h
#define config_h
#include "DiscreteGrippingArm.h"

// define class name and unique id
#define MODEL_IDENTIFIER d_model_UR5e
//#define INSTANTIATION_TOKEN "{1AE5E10D-9521-4DE3-80B9-D0EAAA7D5AF1}"

#define CO_SIMULATION
#define MODEL_EXCHANGE

#define HAS_CONTINUOUS_STATES
#define HAS_EVENT_INDICATORS

#define SET_FLOAT64
#define GET_OUTPUT_DERIVATIVE
#define EVENT_UPDATE

#define FIXED_SOLVER_STEP 1e-3
#define DEFAULT_STOP_TIME 3

/*Specific to the Model*/

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
  sm_memory sm_memory; // Variable containing the memories of the model
  sm_inputstate sm_inputstate; // Variable containing the input states
  sm_state sm_state; // Variable containing the state of the model

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

#endif /* config_h */
