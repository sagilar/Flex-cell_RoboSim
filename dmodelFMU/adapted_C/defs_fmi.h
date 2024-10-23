#ifndef DEFSFMI
#define DEFSFMI
#include <stdio.h>
#include <stdbool.h>

/**** Update ****/
typedef struct {
	bool feasibleMoveDiscreteCommand;
	bool robotStopped;
	bool gripperOpened;
	bool collision;
	bool closeGripperCommand;
	bool gripperClosed;
	bool nonfeasibleMoveDiscreteCommand;
	bool moveCompleted;
	bool openGripperCommand;
	bool moveDiscreteCommand;
	int MovementArgs_target_X;
	int MovementArgs_target_Y;
	int MovementArgs_target_Z;
	bool movediscrete;
	bool pick;
	bool place;
	int target_X;
	int target_Y;
	int target_Z;
	float closing_diameter;
	float closing_speed;
	float closing_force;
	float opening_diameter;
	float opening_speed;
	float opening_force;
	bool stop;
	bool movejoint;
	float target_q0;
	float target_q1;
	float target_q2;
	float target_q3;
	float target_q4;
	float target_q5;
	bool movecartesian;
	float target_x;
	float target_y;
	float target_z;
	float target_rx;
	float target_ry;
	float target_rz;
	bool setvelocity;
	float target_v;
	char *state;
	char *target_state;
	char *status;
	bool done;
	bool terminateSimulation;
} ModelData;



void setStartValues(ModelData* comp);

#define M(v) (comp->v)

/**
 * init function
 */
void init(ModelData* comp);

/**
 * triggers
 */
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
