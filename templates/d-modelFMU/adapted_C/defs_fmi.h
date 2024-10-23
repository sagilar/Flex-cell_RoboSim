#ifndef DEFSFMI
#define DEFSFMI
#include <stdio.h>
#include <stdbool.h>


typedef struct {
  /***** Update these data accordingly based on your RoboSim module variables *****/ 
  float var0_float;
	bool var1_boolean;
	char *var2_string;
	int var3_int;
	bool var4_boolean;
	bool var5_boolean;

  /***** End *****/	

  // d-model-specific outputs
  char *d_model_event;
  char *state;
  char *target_state;
  char *status;
  bool done;


	//Terminate simulation flag
	bool terminateSimulation;
} ModelData;

void setStartValues(ModelData* comp); // Optional

//#define M(v) (comp->v)
#define M(v) (comp->v)

/**
 * init function
 */
void init(ModelData* comp);

/**
 * trigger
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
