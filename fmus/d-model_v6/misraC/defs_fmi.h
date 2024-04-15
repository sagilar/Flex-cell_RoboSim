#ifndef DEFSFMI
#define DEFSFMI
#include <stdio.h>
#include <stdbool.h>
/**** Update Santiago ****/
typedef struct {
  // Parameters
  float MOTION_VEL;
	float opening_diameter;
	float PI;
	float av;
	float closing_speed;
	float closing_force;
	float closing_diameter;
	float lv;
	float opening_speed;
	//MovementArgs margs;
	float opening_force;

  // Arguments (inputs)
  //int target_X;
  //int target_Y;
	//int target_Z;
  float target_X;
  float target_Y;
	float target_Z;

  // Input events
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
  char *d_model_event;
  char *state;
  char *target_state;
  char *status;
  bool done;
  float d_model_event_args_0;
  float d_model_event_args_1;
  float d_model_event_args_2;
  float d_model_event_args_3;
  float d_model_event_args_4;
  float d_model_event_args_5;
  float d_model_event_args_6;
  float d_model_event_args_7;
  float d_model_event_args_8;
  float d_model_event_args_9;

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
