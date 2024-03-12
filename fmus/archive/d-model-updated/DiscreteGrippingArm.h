//Santiago
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <ctype.h>

typedef enum {
	STATES_sm_NONE,
	STATES_sm_Idle,
	STATES_sm_ArmMove,
	STATES_sm_ArmStop,
	STATES_sm_GripperClose,
	STATES_sm_GripperOpen,
	STATES_sm_ArmMoving,
	STATES_sm_ArmStopping,
	STATES_sm_GripperClosing,
	STATES_sm_GripperOpening,
} STATES_sm_Type;

typedef union {
} STATES_sm_Data;

typedef struct {
	STATES_sm_Type type;
	STATES_sm_Data data;
} STATES_sm_Enum;
/* Representation of record MovementArgs */
typedef struct {
	int target_X;
	int target_Y;
	int target_Z;
} MovementArgs;
/* Representation of record MovementArgsAngular */
typedef struct {
	float q5;
	float q1;
	float q2;
	float q4;
	float q0;
	float q3;
} MovementArgsAngular;
/* Representation of record sm_state */
typedef struct {
	bool done;
	STATES_sm_Enum state;
	//STATES_sm_Enum target_state;
	//STATUS_Enum status;
	bool en_SimDiscreteGrippingArmMovement_ArmStop_1_done;
	int en_SimDiscreteGrippingArmMovement_ArmStop_1_counter;
	bool en_SimDiscreteGrippingArmMovement_GripperOpen_1_done;
	int en_SimDiscreteGrippingArmMovement_GripperOpen_1_counter;
	bool en_SimDiscreteGrippingArmMovement_GripperClose_1_done;
	int en_SimDiscreteGrippingArmMovement_GripperClose_1_counter;
	bool en_SimDiscreteGrippingArmMovement_ArmMove_1_done;
	int en_SimDiscreteGrippingArmMovement_ArmMove_1_counter;
} sm_state;
/* Representation of record sm_memory */
typedef struct {
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
	MovementArgs margs;
	float opening_force;
	int TARGET_X;
	int TARGET_Z;
} sm_memory;
/* Representation of record sm_inputstate */
typedef struct {
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
	MovementArgs moveDiscreteCommand_value;
	//TRANSITIONS_sm_Enum _transition_;
} sm_inputstate;

/*
typedef struct {
	MovementArgs v1;
} M_DiscreteGrippingArm_input_moveDiscreteCommand_Data;

typedef union {
	M_DiscreteGrippingArm_input_moveDiscreteCommand_Data moveDiscreteCommand;
} M_DiscreteGrippingArm_input_Data;

typedef struct {
	M_DiscreteGrippingArm_input_Type type;
	M_DiscreteGrippingArm_input_Data data;
} M_DiscreteGrippingArm_input_Enum;

*/
