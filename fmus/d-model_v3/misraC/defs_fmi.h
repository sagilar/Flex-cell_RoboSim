#ifndef DEFSFMI
#define DEFSFMI
#include <stdio.h>
#include <stdbool.h>
/**** Update Santiago ****/
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

  // Outputs
  char *output_command;
  char *state;

	//Terminate simulation
	bool terminateSimulation;

} ModelData;

void setStartValues(ModelData* comp);

//#define M(v) (comp->v)
#define M(v) (comp->v)

/**
 * init function
 */
void init(ModelData* comp);

/**
 * triggers
 */
/*bool per_tick(ModelData* comp);*/
ModelData* tick(ModelData* comp);




/**
 * leave/enter functions (Unused)
 */
void enter(ModelData* comp);
void leave(ModelData* comp);


/*
* Function to free memory when terminating
*/
void release();
/**** ****/



#endif
