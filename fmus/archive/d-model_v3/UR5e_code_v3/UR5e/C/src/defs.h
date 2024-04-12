/*
	This file contains type definitions derived from the RoboSim model.
	These include both recurrent definitions such as STATUS_Enum and application specific definition such as TRANSITIONS_sm_Type.
*/

#ifndef DEFS
#define DEFS

#include "string.h"
#include <stdio.h>
#include <stdbool.h>

FILE* log_file;

/* Representation of enum STATUS */

typedef enum {
	STATUS_ENTER_STATE,
	STATUS_ENTER_CHILDREN,
	STATUS_EXECUTE_STATE,
	STATUS_EXIT_CHILDREN,
	STATUS_EXIT_STATE,
	STATUS_INACTIVE,
} STATUS_Type;

typedef union {
} STATUS_Data;

typedef struct {
	STATUS_Type type;
	STATUS_Data data;
} STATUS_Enum;

STATUS_Enum create_STATUS_ENTER_STATE() {
	STATUS_Data data;

	STATUS_Type type = STATUS_ENTER_STATE;

	STATUS_Enum aux = (STATUS_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
STATUS_Enum create_STATUS_ENTER_CHILDREN() {
	STATUS_Data data;

	STATUS_Type type = STATUS_ENTER_CHILDREN;

	STATUS_Enum aux = (STATUS_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
STATUS_Enum create_STATUS_EXECUTE_STATE() {
	STATUS_Data data;

	STATUS_Type type = STATUS_EXECUTE_STATE;

	STATUS_Enum aux = (STATUS_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
STATUS_Enum create_STATUS_EXIT_CHILDREN() {
	STATUS_Data data;

	STATUS_Type type = STATUS_EXIT_CHILDREN;

	STATUS_Enum aux = (STATUS_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
STATUS_Enum create_STATUS_EXIT_STATE() {
	STATUS_Data data;

	STATUS_Type type = STATUS_EXIT_STATE;

	STATUS_Enum aux = (STATUS_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
STATUS_Enum create_STATUS_INACTIVE() {
	STATUS_Data data;

	STATUS_Type type = STATUS_INACTIVE;

	STATUS_Enum aux = (STATUS_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
/* Representation of enum RESULT */

typedef enum {
	RESULT_WAIT,
	RESULT_CONT,
} RESULT_Type;

typedef union {
} RESULT_Data;

typedef struct {
	RESULT_Type type;
	RESULT_Data data;
} RESULT_Enum;

RESULT_Enum create_RESULT_WAIT() {
	RESULT_Data data;

	RESULT_Type type = RESULT_WAIT;

	RESULT_Enum aux = (RESULT_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
RESULT_Enum create_RESULT_CONT() {
	RESULT_Data data;

	RESULT_Type type = RESULT_CONT;

	RESULT_Enum aux = (RESULT_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
/* Representation of enum STATES_sm */

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

STATES_sm_Enum create_STATES_sm_NONE() {
	STATES_sm_Data data;

	STATES_sm_Type type = STATES_sm_NONE;

	STATES_sm_Enum aux = (STATES_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
STATES_sm_Enum create_STATES_sm_Idle() {
	STATES_sm_Data data;

	STATES_sm_Type type = STATES_sm_Idle;

	STATES_sm_Enum aux = (STATES_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
STATES_sm_Enum create_STATES_sm_ArmMove() {
	STATES_sm_Data data;

	STATES_sm_Type type = STATES_sm_ArmMove;

	STATES_sm_Enum aux = (STATES_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
STATES_sm_Enum create_STATES_sm_ArmStop() {
	STATES_sm_Data data;

	STATES_sm_Type type = STATES_sm_ArmStop;

	STATES_sm_Enum aux = (STATES_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
STATES_sm_Enum create_STATES_sm_GripperClose() {
	STATES_sm_Data data;

	STATES_sm_Type type = STATES_sm_GripperClose;

	STATES_sm_Enum aux = (STATES_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
STATES_sm_Enum create_STATES_sm_GripperOpen() {
	STATES_sm_Data data;

	STATES_sm_Type type = STATES_sm_GripperOpen;

	STATES_sm_Enum aux = (STATES_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
STATES_sm_Enum create_STATES_sm_ArmMoving() {
	STATES_sm_Data data;

	STATES_sm_Type type = STATES_sm_ArmMoving;

	STATES_sm_Enum aux = (STATES_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
STATES_sm_Enum create_STATES_sm_ArmStopping() {
	STATES_sm_Data data;

	STATES_sm_Type type = STATES_sm_ArmStopping;

	STATES_sm_Enum aux = (STATES_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
STATES_sm_Enum create_STATES_sm_GripperClosing() {
	STATES_sm_Data data;

	STATES_sm_Type type = STATES_sm_GripperClosing;

	STATES_sm_Enum aux = (STATES_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
STATES_sm_Enum create_STATES_sm_GripperOpening() {
	STATES_sm_Data data;

	STATES_sm_Type type = STATES_sm_GripperOpening;

	STATES_sm_Enum aux = (STATES_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
/* Representation of enum TRANSITIONS_sm */

typedef enum {
	TRANSITIONS_sm_NONE,
	TRANSITIONS_sm_sm_t5_2,
	TRANSITIONS_sm_sm_t5_4,
	TRANSITIONS_sm_sm_t5_3,
	TRANSITIONS_sm_sm_t3,
	TRANSITIONS_sm_sm_t1_1,
	TRANSITIONS_sm_sm_t3_2,
	TRANSITIONS_sm_sm_t5_1,
	TRANSITIONS_sm_sm_t3_3,
	TRANSITIONS_sm_sm_t2_3,
	TRANSITIONS_sm_sm_t4_4,
	TRANSITIONS_sm_sm_t5,
	TRANSITIONS_sm_sm_t2,
	TRANSITIONS_sm_sm_t3_1,
	TRANSITIONS_sm_sm_t4_2,
	TRANSITIONS_sm_sm_t2_nonfeasible,
	TRANSITIONS_sm_sm_t4_1,
	TRANSITIONS_sm_sm_t2_1,
	TRANSITIONS_sm_sm_t2_2,
	TRANSITIONS_sm_sm_t2_4,
	TRANSITIONS_sm_sm_t4,
	TRANSITIONS_sm_sm_t4_3,
	TRANSITIONS_sm_sm_t1,
} TRANSITIONS_sm_Type;

typedef union {
} TRANSITIONS_sm_Data;

typedef struct {
	TRANSITIONS_sm_Type type;
	TRANSITIONS_sm_Data data;
} TRANSITIONS_sm_Enum;

TRANSITIONS_sm_Enum create_TRANSITIONS_sm_NONE() {
	TRANSITIONS_sm_Data data;

	TRANSITIONS_sm_Type type = TRANSITIONS_sm_NONE;

	TRANSITIONS_sm_Enum aux = (TRANSITIONS_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
TRANSITIONS_sm_Enum create_TRANSITIONS_sm_sm_t5_2() {
	TRANSITIONS_sm_Data data;

	TRANSITIONS_sm_Type type = TRANSITIONS_sm_sm_t5_2;

	TRANSITIONS_sm_Enum aux = (TRANSITIONS_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
TRANSITIONS_sm_Enum create_TRANSITIONS_sm_sm_t5_4() {
	TRANSITIONS_sm_Data data;

	TRANSITIONS_sm_Type type = TRANSITIONS_sm_sm_t5_4;

	TRANSITIONS_sm_Enum aux = (TRANSITIONS_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
TRANSITIONS_sm_Enum create_TRANSITIONS_sm_sm_t5_3() {
	TRANSITIONS_sm_Data data;

	TRANSITIONS_sm_Type type = TRANSITIONS_sm_sm_t5_3;

	TRANSITIONS_sm_Enum aux = (TRANSITIONS_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
TRANSITIONS_sm_Enum create_TRANSITIONS_sm_sm_t3() {
	TRANSITIONS_sm_Data data;

	TRANSITIONS_sm_Type type = TRANSITIONS_sm_sm_t3;

	TRANSITIONS_sm_Enum aux = (TRANSITIONS_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
TRANSITIONS_sm_Enum create_TRANSITIONS_sm_sm_t1_1() {
	TRANSITIONS_sm_Data data;

	TRANSITIONS_sm_Type type = TRANSITIONS_sm_sm_t1_1;

	TRANSITIONS_sm_Enum aux = (TRANSITIONS_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
TRANSITIONS_sm_Enum create_TRANSITIONS_sm_sm_t3_2() {
	TRANSITIONS_sm_Data data;

	TRANSITIONS_sm_Type type = TRANSITIONS_sm_sm_t3_2;

	TRANSITIONS_sm_Enum aux = (TRANSITIONS_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
TRANSITIONS_sm_Enum create_TRANSITIONS_sm_sm_t5_1() {
	TRANSITIONS_sm_Data data;

	TRANSITIONS_sm_Type type = TRANSITIONS_sm_sm_t5_1;

	TRANSITIONS_sm_Enum aux = (TRANSITIONS_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
TRANSITIONS_sm_Enum create_TRANSITIONS_sm_sm_t3_3() {
	TRANSITIONS_sm_Data data;

	TRANSITIONS_sm_Type type = TRANSITIONS_sm_sm_t3_3;

	TRANSITIONS_sm_Enum aux = (TRANSITIONS_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
TRANSITIONS_sm_Enum create_TRANSITIONS_sm_sm_t2_3() {
	TRANSITIONS_sm_Data data;

	TRANSITIONS_sm_Type type = TRANSITIONS_sm_sm_t2_3;

	TRANSITIONS_sm_Enum aux = (TRANSITIONS_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
TRANSITIONS_sm_Enum create_TRANSITIONS_sm_sm_t4_4() {
	TRANSITIONS_sm_Data data;

	TRANSITIONS_sm_Type type = TRANSITIONS_sm_sm_t4_4;

	TRANSITIONS_sm_Enum aux = (TRANSITIONS_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
TRANSITIONS_sm_Enum create_TRANSITIONS_sm_sm_t5() {
	TRANSITIONS_sm_Data data;

	TRANSITIONS_sm_Type type = TRANSITIONS_sm_sm_t5;

	TRANSITIONS_sm_Enum aux = (TRANSITIONS_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
TRANSITIONS_sm_Enum create_TRANSITIONS_sm_sm_t2() {
	TRANSITIONS_sm_Data data;

	TRANSITIONS_sm_Type type = TRANSITIONS_sm_sm_t2;

	TRANSITIONS_sm_Enum aux = (TRANSITIONS_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
TRANSITIONS_sm_Enum create_TRANSITIONS_sm_sm_t3_1() {
	TRANSITIONS_sm_Data data;

	TRANSITIONS_sm_Type type = TRANSITIONS_sm_sm_t3_1;

	TRANSITIONS_sm_Enum aux = (TRANSITIONS_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
TRANSITIONS_sm_Enum create_TRANSITIONS_sm_sm_t4_2() {
	TRANSITIONS_sm_Data data;

	TRANSITIONS_sm_Type type = TRANSITIONS_sm_sm_t4_2;

	TRANSITIONS_sm_Enum aux = (TRANSITIONS_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
TRANSITIONS_sm_Enum create_TRANSITIONS_sm_sm_t2_nonfeasible() {
	TRANSITIONS_sm_Data data;

	TRANSITIONS_sm_Type type = TRANSITIONS_sm_sm_t2_nonfeasible;

	TRANSITIONS_sm_Enum aux = (TRANSITIONS_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
TRANSITIONS_sm_Enum create_TRANSITIONS_sm_sm_t4_1() {
	TRANSITIONS_sm_Data data;

	TRANSITIONS_sm_Type type = TRANSITIONS_sm_sm_t4_1;

	TRANSITIONS_sm_Enum aux = (TRANSITIONS_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
TRANSITIONS_sm_Enum create_TRANSITIONS_sm_sm_t2_1() {
	TRANSITIONS_sm_Data data;

	TRANSITIONS_sm_Type type = TRANSITIONS_sm_sm_t2_1;

	TRANSITIONS_sm_Enum aux = (TRANSITIONS_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
TRANSITIONS_sm_Enum create_TRANSITIONS_sm_sm_t2_2() {
	TRANSITIONS_sm_Data data;

	TRANSITIONS_sm_Type type = TRANSITIONS_sm_sm_t2_2;

	TRANSITIONS_sm_Enum aux = (TRANSITIONS_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
TRANSITIONS_sm_Enum create_TRANSITIONS_sm_sm_t2_4() {
	TRANSITIONS_sm_Data data;

	TRANSITIONS_sm_Type type = TRANSITIONS_sm_sm_t2_4;

	TRANSITIONS_sm_Enum aux = (TRANSITIONS_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
TRANSITIONS_sm_Enum create_TRANSITIONS_sm_sm_t4() {
	TRANSITIONS_sm_Data data;

	TRANSITIONS_sm_Type type = TRANSITIONS_sm_sm_t4;

	TRANSITIONS_sm_Enum aux = (TRANSITIONS_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
TRANSITIONS_sm_Enum create_TRANSITIONS_sm_sm_t4_3() {
	TRANSITIONS_sm_Data data;

	TRANSITIONS_sm_Type type = TRANSITIONS_sm_sm_t4_3;

	TRANSITIONS_sm_Enum aux = (TRANSITIONS_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
TRANSITIONS_sm_Enum create_TRANSITIONS_sm_sm_t1() {
	TRANSITIONS_sm_Data data;

	TRANSITIONS_sm_Type type = TRANSITIONS_sm_sm_t1;

	TRANSITIONS_sm_Enum aux = (TRANSITIONS_sm_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}

/* Representation of record MovementArgs */
typedef struct {
	int targety;
	int targetz;
	int targetx;
} MovementArgs;

/* Representation of enum M_DiscreteGrippingArm_input */

typedef enum {
	M_DiscreteGrippingArm_input_collision,
	M_DiscreteGrippingArm_input_gripperClosed,
	M_DiscreteGrippingArm_input_nonfeasibleMoveDiscreteCommand,
	M_DiscreteGrippingArm_input_openGripperCommand,
	M_DiscreteGrippingArm_input_closeGripperCommand,
	M_DiscreteGrippingArm_input_moveCompleted,
	M_DiscreteGrippingArm_input_robotStopped,
	M_DiscreteGrippingArm_input_moveDiscreteCommand,
	M_DiscreteGrippingArm_input_feasibleMoveDiscreteCommand,
	M_DiscreteGrippingArm_input_gripperOpened,
	M_DiscreteGrippingArm_input__done_,
	M_DiscreteGrippingArm_input__terminate_,
	M_DiscreteGrippingArm_input__unknown_,
} M_DiscreteGrippingArm_input_Type;

typedef struct {
	MovementArgs v1;
} M_DiscreteGrippingArm_input_moveDiscreteCommand_Data;

typedef union {
	M_DiscreteGrippingArm_input_moveDiscreteCommand_Data moveDiscreteCommand;
} M_DiscreteGrippingArm_input_Data;

/* Representation of enum M_DiscreteGrippingArm_output */

typedef enum {
	M_DiscreteGrippingArm_output_stop,
	M_DiscreteGrippingArm_output_movejoint,
	M_DiscreteGrippingArm_output_setvelocity,
	M_DiscreteGrippingArm_output_movecartesian,
	M_DiscreteGrippingArm_output_movediscrete,
	M_DiscreteGrippingArm_output_place,
	M_DiscreteGrippingArm_output_reset,
	M_DiscreteGrippingArm_output_pick,
	M_DiscreteGrippingArm_output__done_,
} M_DiscreteGrippingArm_output_Type;

typedef struct {
	float v1;
} M_DiscreteGrippingArm_output_movejoint_Data;

typedef struct {
	float v1;
} M_DiscreteGrippingArm_output_setvelocity_Data;

typedef struct {
	float v1;
	float v2;
	float v3;
	float v4;
} M_DiscreteGrippingArm_output_movecartesian_Data;

typedef struct {
	int v1;
	int v2;
	int v3;
	float v4;
} M_DiscreteGrippingArm_output_movediscrete_Data;

typedef struct {
	float v1;
	float v2;
	float v3;
} M_DiscreteGrippingArm_output_place_Data;

typedef struct {
	float v1;
	float v2;
	float v3;
} M_DiscreteGrippingArm_output_pick_Data;

typedef union {
	M_DiscreteGrippingArm_output_movejoint_Data movejoint;
	M_DiscreteGrippingArm_output_setvelocity_Data setvelocity;
	M_DiscreteGrippingArm_output_movecartesian_Data movecartesian;
	M_DiscreteGrippingArm_output_movediscrete_Data movediscrete;
	M_DiscreteGrippingArm_output_place_Data place;
	M_DiscreteGrippingArm_output_pick_Data pick;
} M_DiscreteGrippingArm_output_Data;

typedef struct {
	M_DiscreteGrippingArm_output_Type type;
	M_DiscreteGrippingArm_output_Data data;
} M_DiscreteGrippingArm_output_Enum;

typedef struct {
	M_DiscreteGrippingArm_input_Type type;
	M_DiscreteGrippingArm_input_Data data;
} M_DiscreteGrippingArm_input_Enum;

/* Representation of enum C_cm_input */

typedef enum {
	C_cm_input_moveCompleted,
	C_cm_input_closeGripperCommand,
	C_cm_input_openGripperCommand,
	C_cm_input_nonfeasibleMoveDiscreteCommand,
	C_cm_input_robotStopped,
	C_cm_input_gripperOpened,
	C_cm_input_feasibleMoveDiscreteCommand,
	C_cm_input_collision,
	C_cm_input_gripperClosed,
	C_cm_input_moveDiscreteCommand,
	C_cm_input__done_,
	C_cm_input__terminate_,
} C_cm_input_Type;

typedef struct {
	MovementArgs v1;
} C_cm_input_moveDiscreteCommand_Data;

typedef union {
	C_cm_input_moveDiscreteCommand_Data moveDiscreteCommand;
} C_cm_input_Data;

typedef struct {
	C_cm_input_Type type;
	C_cm_input_Data data;
} C_cm_input_Enum;

/* Representation of enum sm_input */

typedef enum {
	sm_input_nonfeasibleMoveDiscreteCommand,
	sm_input_openGripperCommand,
	sm_input_closeGripperCommand,
	sm_input_collision,
	sm_input_gripperClosed,
	sm_input_moveCompleted,
	sm_input_robotStopped,
	sm_input_feasibleMoveDiscreteCommand,
	sm_input_gripperOpened,
	sm_input_moveDiscreteCommand,
	sm_input__done_,
	sm_input__terminate_,
} sm_input_Type;

typedef struct {
	MovementArgs v1;
} sm_input_moveDiscreteCommand_Data;

typedef union {
	sm_input_moveDiscreteCommand_Data moveDiscreteCommand;
} sm_input_Data;

typedef struct {
	sm_input_Type type;
	sm_input_Data data;
} sm_input_Enum;

/* Representation of enum sm_output */

typedef enum {
	sm_output_movejoint,
	sm_output_movecartesian,
	sm_output_movediscrete,
	sm_output_reset,
	sm_output_pick,
	sm_output_stop,
	sm_output_place,
	sm_output_setvelocity,
	sm_output__done_,
} sm_output_Type;

typedef struct {
	float v1;
} sm_output_movejoint_Data;

typedef struct {
	float v1;
	float v2;
	float v3;
	float v4;
} sm_output_movecartesian_Data;

typedef struct {
	int v1;
	int v2;
	int v3;
	float v4;
} sm_output_movediscrete_Data;

typedef struct {
	float v1;
	float v2;
	float v3;
} sm_output_pick_Data;

typedef struct {
	float v1;
	float v2;
	float v3;
} sm_output_place_Data;

typedef struct {
	float v1;
} sm_output_setvelocity_Data;

typedef union {
	sm_output_movejoint_Data movejoint;
	sm_output_movecartesian_Data movecartesian;
	sm_output_movediscrete_Data movediscrete;
	sm_output_pick_Data pick;
	sm_output_place_Data place;
	sm_output_setvelocity_Data setvelocity;
} sm_output_Data;

typedef struct {
	sm_output_Type type;
	sm_output_Data data;
} sm_output_Enum;

/* Representation of enum C_cm_output */

typedef enum {
	C_cm_output_pick,
	C_cm_output_movecartesian,
	C_cm_output_place,
	C_cm_output_reset,
	C_cm_output_movediscrete,
	C_cm_output_movejoint,
	C_cm_output_setvelocity,
	C_cm_output_stop,
	C_cm_output__done_,
} C_cm_output_Type;

typedef struct {
	float v1;
	float v2;
	float v3;
} C_cm_output_pick_Data;

typedef struct {
	float v1;
	float v2;
	float v3;
	float v4;
} C_cm_output_movecartesian_Data;

typedef struct {
	float v1;
	float v2;
	float v3;
} C_cm_output_place_Data;

typedef struct {
	int v1;
	int v2;
	int v3;
	float v4;
} C_cm_output_movediscrete_Data;

typedef struct {
	float v1;
} C_cm_output_movejoint_Data;

typedef struct {
	float v1;
} C_cm_output_setvelocity_Data;

typedef union {
	C_cm_output_pick_Data pick;
	C_cm_output_movecartesian_Data movecartesian;
	C_cm_output_place_Data place;
	C_cm_output_movediscrete_Data movediscrete;
	C_cm_output_movejoint_Data movejoint;
	C_cm_output_setvelocity_Data setvelocity;
} C_cm_output_Data;

typedef struct {
	C_cm_output_Type type;
	C_cm_output_Data data;
} C_cm_output_Enum;

// Temporary solution to trim strings taken from http://www.martinbroadhurst.com/trim-a-string-in-c.html

char *ltrim(char *str, const char *seps)
{
    size_t totrim;
    if (seps == NULL) {
        seps = "\t\n\v\f\r ";
    }
    totrim = strspn(str, seps);
    if (totrim > 0) {
        size_t len = strlen(str);
        if (totrim == len) {
            str[0] = '\0';
        }
        else {
            memmove(str, str + totrim, len + 1 - totrim);
        }
    }
    return str;
}

char *rtrim(char *str, const char *seps)
{
    int i;
    if (seps == NULL) {
        seps = "\t\n\v\f\r ";
    }
    i = strlen(str) - 1;
    while (i >= 0 && strchr(seps, str[i]) != NULL) {
        str[i] = '\0';
        i--;
    }
    return str;
}

char *trim(char *str, const char *seps)
{
    return ltrim(rtrim(str, seps), seps);
}

M_DiscreteGrippingArm_input_Enum create_M_DiscreteGrippingArm_input_collision() {
	M_DiscreteGrippingArm_input_Data data;

	M_DiscreteGrippingArm_input_Type type = M_DiscreteGrippingArm_input_collision;

	M_DiscreteGrippingArm_input_Enum aux = (M_DiscreteGrippingArm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
M_DiscreteGrippingArm_input_Enum create_M_DiscreteGrippingArm_input_gripperClosed() {
	M_DiscreteGrippingArm_input_Data data;

	M_DiscreteGrippingArm_input_Type type = M_DiscreteGrippingArm_input_gripperClosed;

	M_DiscreteGrippingArm_input_Enum aux = (M_DiscreteGrippingArm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
M_DiscreteGrippingArm_input_Enum create_M_DiscreteGrippingArm_input_nonfeasibleMoveDiscreteCommand() {
	M_DiscreteGrippingArm_input_Data data;

	M_DiscreteGrippingArm_input_Type type = M_DiscreteGrippingArm_input_nonfeasibleMoveDiscreteCommand;

	M_DiscreteGrippingArm_input_Enum aux = (M_DiscreteGrippingArm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
M_DiscreteGrippingArm_input_Enum create_M_DiscreteGrippingArm_input_openGripperCommand() {
	M_DiscreteGrippingArm_input_Data data;

	M_DiscreteGrippingArm_input_Type type = M_DiscreteGrippingArm_input_openGripperCommand;

	M_DiscreteGrippingArm_input_Enum aux = (M_DiscreteGrippingArm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
M_DiscreteGrippingArm_input_Enum create_M_DiscreteGrippingArm_input_closeGripperCommand() {
	M_DiscreteGrippingArm_input_Data data;

	M_DiscreteGrippingArm_input_Type type = M_DiscreteGrippingArm_input_closeGripperCommand;

	M_DiscreteGrippingArm_input_Enum aux = (M_DiscreteGrippingArm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
M_DiscreteGrippingArm_input_Enum create_M_DiscreteGrippingArm_input_moveCompleted() {
	M_DiscreteGrippingArm_input_Data data;

	M_DiscreteGrippingArm_input_Type type = M_DiscreteGrippingArm_input_moveCompleted;

	M_DiscreteGrippingArm_input_Enum aux = (M_DiscreteGrippingArm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
M_DiscreteGrippingArm_input_Enum create_M_DiscreteGrippingArm_input_robotStopped() {
	M_DiscreteGrippingArm_input_Data data;

	M_DiscreteGrippingArm_input_Type type = M_DiscreteGrippingArm_input_robotStopped;

	M_DiscreteGrippingArm_input_Enum aux = (M_DiscreteGrippingArm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
M_DiscreteGrippingArm_input_Enum create_M_DiscreteGrippingArm_input_moveDiscreteCommand(MovementArgs v1) {
	M_DiscreteGrippingArm_input_Data data;
	data.moveDiscreteCommand.v1 = v1;

	M_DiscreteGrippingArm_input_Type type = M_DiscreteGrippingArm_input_moveDiscreteCommand;

	M_DiscreteGrippingArm_input_Enum aux = (M_DiscreteGrippingArm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
M_DiscreteGrippingArm_input_Enum create_M_DiscreteGrippingArm_input_feasibleMoveDiscreteCommand() {
	M_DiscreteGrippingArm_input_Data data;

	M_DiscreteGrippingArm_input_Type type = M_DiscreteGrippingArm_input_feasibleMoveDiscreteCommand;

	M_DiscreteGrippingArm_input_Enum aux = (M_DiscreteGrippingArm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
M_DiscreteGrippingArm_input_Enum create_M_DiscreteGrippingArm_input_gripperOpened() {
	M_DiscreteGrippingArm_input_Data data;

	M_DiscreteGrippingArm_input_Type type = M_DiscreteGrippingArm_input_gripperOpened;

	M_DiscreteGrippingArm_input_Enum aux = (M_DiscreteGrippingArm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
M_DiscreteGrippingArm_input_Enum create_M_DiscreteGrippingArm_input__done_() {
	M_DiscreteGrippingArm_input_Data data;

	M_DiscreteGrippingArm_input_Type type = M_DiscreteGrippingArm_input__done_;

	M_DiscreteGrippingArm_input_Enum aux = (M_DiscreteGrippingArm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
M_DiscreteGrippingArm_input_Enum create_M_DiscreteGrippingArm_input__terminate_() {
	M_DiscreteGrippingArm_input_Data data;

	M_DiscreteGrippingArm_input_Type type = M_DiscreteGrippingArm_input__terminate_;

	M_DiscreteGrippingArm_input_Enum aux = (M_DiscreteGrippingArm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}

M_DiscreteGrippingArm_input_Enum create_M_DiscreteGrippingArm_input__unknown_() {
	M_DiscreteGrippingArm_input_Data data;

	M_DiscreteGrippingArm_input_Type type = M_DiscreteGrippingArm_input__unknown_;

	M_DiscreteGrippingArm_input_Enum aux = (M_DiscreteGrippingArm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}

M_DiscreteGrippingArm_output_Enum create_M_DiscreteGrippingArm_output_stop() {
	M_DiscreteGrippingArm_output_Data data;

	M_DiscreteGrippingArm_output_Type type = M_DiscreteGrippingArm_output_stop;

	M_DiscreteGrippingArm_output_Enum aux = (M_DiscreteGrippingArm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
M_DiscreteGrippingArm_output_Enum create_M_DiscreteGrippingArm_output_movejoint(float v1) {
	M_DiscreteGrippingArm_output_Data data;
	data.movejoint.v1 = v1;

	M_DiscreteGrippingArm_output_Type type = M_DiscreteGrippingArm_output_movejoint;

	M_DiscreteGrippingArm_output_Enum aux = (M_DiscreteGrippingArm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
M_DiscreteGrippingArm_output_Enum create_M_DiscreteGrippingArm_output_setvelocity(float v1) {
	M_DiscreteGrippingArm_output_Data data;
	data.setvelocity.v1 = v1;

	M_DiscreteGrippingArm_output_Type type = M_DiscreteGrippingArm_output_setvelocity;

	M_DiscreteGrippingArm_output_Enum aux = (M_DiscreteGrippingArm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
M_DiscreteGrippingArm_output_Enum create_M_DiscreteGrippingArm_output_movecartesian(float v1,float v2,float v3,float v4) {
	M_DiscreteGrippingArm_output_Data data;
	data.movecartesian.v1 = v1;
	data.movecartesian.v2 = v2;
	data.movecartesian.v3 = v3;
	data.movecartesian.v4 = v4;

	M_DiscreteGrippingArm_output_Type type = M_DiscreteGrippingArm_output_movecartesian;

	M_DiscreteGrippingArm_output_Enum aux = (M_DiscreteGrippingArm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
M_DiscreteGrippingArm_output_Enum create_M_DiscreteGrippingArm_output_movediscrete(int v1,int v2,int v3,float v4) {
	M_DiscreteGrippingArm_output_Data data;
	data.movediscrete.v1 = v1;
	data.movediscrete.v2 = v2;
	data.movediscrete.v3 = v3;
	data.movediscrete.v4 = v4;

	M_DiscreteGrippingArm_output_Type type = M_DiscreteGrippingArm_output_movediscrete;

	M_DiscreteGrippingArm_output_Enum aux = (M_DiscreteGrippingArm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
M_DiscreteGrippingArm_output_Enum create_M_DiscreteGrippingArm_output_place(float v1,float v2,float v3) {
	M_DiscreteGrippingArm_output_Data data;
	data.place.v1 = v1;
	data.place.v2 = v2;
	data.place.v3 = v3;

	M_DiscreteGrippingArm_output_Type type = M_DiscreteGrippingArm_output_place;

	M_DiscreteGrippingArm_output_Enum aux = (M_DiscreteGrippingArm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
M_DiscreteGrippingArm_output_Enum create_M_DiscreteGrippingArm_output_reset() {
	M_DiscreteGrippingArm_output_Data data;

	M_DiscreteGrippingArm_output_Type type = M_DiscreteGrippingArm_output_reset;

	M_DiscreteGrippingArm_output_Enum aux = (M_DiscreteGrippingArm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
M_DiscreteGrippingArm_output_Enum create_M_DiscreteGrippingArm_output_pick(float v1,float v2,float v3) {
	M_DiscreteGrippingArm_output_Data data;
	data.pick.v1 = v1;
	data.pick.v2 = v2;
	data.pick.v3 = v3;

	M_DiscreteGrippingArm_output_Type type = M_DiscreteGrippingArm_output_pick;

	M_DiscreteGrippingArm_output_Enum aux = (M_DiscreteGrippingArm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
M_DiscreteGrippingArm_output_Enum create_M_DiscreteGrippingArm_output__done_() {
	M_DiscreteGrippingArm_output_Data data;

	M_DiscreteGrippingArm_output_Type type = M_DiscreteGrippingArm_output__done_;

	M_DiscreteGrippingArm_output_Enum aux = (M_DiscreteGrippingArm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}


C_cm_input_Enum create_C_cm_input_moveCompleted() {
	C_cm_input_Data data;

	C_cm_input_Type type = C_cm_input_moveCompleted;

	C_cm_input_Enum aux = (C_cm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
C_cm_input_Enum create_C_cm_input_closeGripperCommand() {
	C_cm_input_Data data;

	C_cm_input_Type type = C_cm_input_closeGripperCommand;

	C_cm_input_Enum aux = (C_cm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
C_cm_input_Enum create_C_cm_input_openGripperCommand() {
	C_cm_input_Data data;

	C_cm_input_Type type = C_cm_input_openGripperCommand;

	C_cm_input_Enum aux = (C_cm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
C_cm_input_Enum create_C_cm_input_nonfeasibleMoveDiscreteCommand() {
	C_cm_input_Data data;

	C_cm_input_Type type = C_cm_input_nonfeasibleMoveDiscreteCommand;

	C_cm_input_Enum aux = (C_cm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
C_cm_input_Enum create_C_cm_input_robotStopped() {
	C_cm_input_Data data;

	C_cm_input_Type type = C_cm_input_robotStopped;

	C_cm_input_Enum aux = (C_cm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
C_cm_input_Enum create_C_cm_input_gripperOpened() {
	C_cm_input_Data data;

	C_cm_input_Type type = C_cm_input_gripperOpened;

	C_cm_input_Enum aux = (C_cm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
C_cm_input_Enum create_C_cm_input_feasibleMoveDiscreteCommand() {
	C_cm_input_Data data;

	C_cm_input_Type type = C_cm_input_feasibleMoveDiscreteCommand;

	C_cm_input_Enum aux = (C_cm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
C_cm_input_Enum create_C_cm_input_collision() {
	C_cm_input_Data data;

	C_cm_input_Type type = C_cm_input_collision;

	C_cm_input_Enum aux = (C_cm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
C_cm_input_Enum create_C_cm_input_gripperClosed() {
	C_cm_input_Data data;

	C_cm_input_Type type = C_cm_input_gripperClosed;

	C_cm_input_Enum aux = (C_cm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
C_cm_input_Enum create_C_cm_input_moveDiscreteCommand(MovementArgs v1) {
	C_cm_input_Data data;
	data.moveDiscreteCommand.v1 = v1;

	C_cm_input_Type type = C_cm_input_moveDiscreteCommand;

	C_cm_input_Enum aux = (C_cm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
C_cm_input_Enum create_C_cm_input__done_() {
	C_cm_input_Data data;

	C_cm_input_Type type = C_cm_input__done_;

	C_cm_input_Enum aux = (C_cm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
C_cm_input_Enum create_C_cm_input__terminate_() {
	C_cm_input_Data data;

	C_cm_input_Type type = C_cm_input__terminate_;

	C_cm_input_Enum aux = (C_cm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}

sm_input_Enum create_sm_input_nonfeasibleMoveDiscreteCommand() {
	sm_input_Data data;

	sm_input_Type type = sm_input_nonfeasibleMoveDiscreteCommand;

	sm_input_Enum aux = (sm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
sm_input_Enum create_sm_input_openGripperCommand() {
	sm_input_Data data;

	sm_input_Type type = sm_input_openGripperCommand;

	sm_input_Enum aux = (sm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
sm_input_Enum create_sm_input_closeGripperCommand() {
	sm_input_Data data;

	sm_input_Type type = sm_input_closeGripperCommand;

	sm_input_Enum aux = (sm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
sm_input_Enum create_sm_input_collision() {
	sm_input_Data data;

	sm_input_Type type = sm_input_collision;

	sm_input_Enum aux = (sm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
sm_input_Enum create_sm_input_gripperClosed() {
	sm_input_Data data;

	sm_input_Type type = sm_input_gripperClosed;

	sm_input_Enum aux = (sm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
sm_input_Enum create_sm_input_moveCompleted() {
	sm_input_Data data;

	sm_input_Type type = sm_input_moveCompleted;

	sm_input_Enum aux = (sm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
sm_input_Enum create_sm_input_robotStopped() {
	sm_input_Data data;

	sm_input_Type type = sm_input_robotStopped;

	sm_input_Enum aux = (sm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
sm_input_Enum create_sm_input_feasibleMoveDiscreteCommand() {
	sm_input_Data data;

	sm_input_Type type = sm_input_feasibleMoveDiscreteCommand;

	sm_input_Enum aux = (sm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
sm_input_Enum create_sm_input_gripperOpened() {
	sm_input_Data data;

	sm_input_Type type = sm_input_gripperOpened;

	sm_input_Enum aux = (sm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
sm_input_Enum create_sm_input_moveDiscreteCommand(MovementArgs v1) {
	sm_input_Data data;
	data.moveDiscreteCommand.v1 = v1;

	sm_input_Type type = sm_input_moveDiscreteCommand;

	sm_input_Enum aux = (sm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
sm_input_Enum create_sm_input__done_() {
	sm_input_Data data;

	sm_input_Type type = sm_input__done_;

	sm_input_Enum aux = (sm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
sm_input_Enum create_sm_input__terminate_() {
	sm_input_Data data;

	sm_input_Type type = sm_input__terminate_;

	sm_input_Enum aux = (sm_input_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}

sm_output_Enum create_sm_output_movejoint(float v1) {
	sm_output_Data data;
	data.movejoint.v1 = v1;

	sm_output_Type type = sm_output_movejoint;

	sm_output_Enum aux = (sm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
sm_output_Enum create_sm_output_movecartesian(float v1,float v2,float v3,float v4) {
	sm_output_Data data;
	data.movecartesian.v1 = v1;
	data.movecartesian.v2 = v2;
	data.movecartesian.v3 = v3;
	data.movecartesian.v4 = v4;

	sm_output_Type type = sm_output_movecartesian;

	sm_output_Enum aux = (sm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
sm_output_Enum create_sm_output_movediscrete(int v1,int v2,int v3,float v4) {
	sm_output_Data data;
	data.movediscrete.v1 = v1;
	data.movediscrete.v2 = v2;
	data.movediscrete.v3 = v3;
	data.movediscrete.v4 = v4;

	sm_output_Type type = sm_output_movediscrete;

	sm_output_Enum aux = (sm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
sm_output_Enum create_sm_output_reset() {
	sm_output_Data data;

	sm_output_Type type = sm_output_reset;

	sm_output_Enum aux = (sm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
sm_output_Enum create_sm_output_pick(float v1,float v2,float v3) {
	sm_output_Data data;
	data.pick.v1 = v1;
	data.pick.v2 = v2;
	data.pick.v3 = v3;

	sm_output_Type type = sm_output_pick;

	sm_output_Enum aux = (sm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
sm_output_Enum create_sm_output_stop() {
	sm_output_Data data;

	sm_output_Type type = sm_output_stop;

	sm_output_Enum aux = (sm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
sm_output_Enum create_sm_output_place(float v1,float v2,float v3) {
	sm_output_Data data;
	data.place.v1 = v1;
	data.place.v2 = v2;
	data.place.v3 = v3;

	sm_output_Type type = sm_output_place;

	sm_output_Enum aux = (sm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
sm_output_Enum create_sm_output_setvelocity(float v1) {
	sm_output_Data data;
	data.setvelocity.v1 = v1;

	sm_output_Type type = sm_output_setvelocity;

	sm_output_Enum aux = (sm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
sm_output_Enum create_sm_output__done_() {
	sm_output_Data data;

	sm_output_Type type = sm_output__done_;

	sm_output_Enum aux = (sm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}

C_cm_output_Enum create_C_cm_output_pick(float v1,float v2,float v3) {
	C_cm_output_Data data;
	data.pick.v1 = v1;
	data.pick.v2 = v2;
	data.pick.v3 = v3;

	C_cm_output_Type type = C_cm_output_pick;

	C_cm_output_Enum aux = (C_cm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
C_cm_output_Enum create_C_cm_output_movecartesian(float v1,float v2,float v3,float v4) {
	C_cm_output_Data data;
	data.movecartesian.v1 = v1;
	data.movecartesian.v2 = v2;
	data.movecartesian.v3 = v3;
	data.movecartesian.v4 = v4;

	C_cm_output_Type type = C_cm_output_movecartesian;

	C_cm_output_Enum aux = (C_cm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
C_cm_output_Enum create_C_cm_output_place(float v1,float v2,float v3) {
	C_cm_output_Data data;
	data.place.v1 = v1;
	data.place.v2 = v2;
	data.place.v3 = v3;

	C_cm_output_Type type = C_cm_output_place;

	C_cm_output_Enum aux = (C_cm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
C_cm_output_Enum create_C_cm_output_reset() {
	C_cm_output_Data data;

	C_cm_output_Type type = C_cm_output_reset;

	C_cm_output_Enum aux = (C_cm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
C_cm_output_Enum create_C_cm_output_movediscrete(int v1,int v2,int v3,float v4) {
	C_cm_output_Data data;
	data.movediscrete.v1 = v1;
	data.movediscrete.v2 = v2;
	data.movediscrete.v3 = v3;
	data.movediscrete.v4 = v4;

	C_cm_output_Type type = C_cm_output_movediscrete;

	C_cm_output_Enum aux = (C_cm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
C_cm_output_Enum create_C_cm_output_movejoint(float v1) {
	C_cm_output_Data data;
	data.movejoint.v1 = v1;

	C_cm_output_Type type = C_cm_output_movejoint;

	C_cm_output_Enum aux = (C_cm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
C_cm_output_Enum create_C_cm_output_setvelocity(float v1) {
	C_cm_output_Data data;
	data.setvelocity.v1 = v1;

	C_cm_output_Type type = C_cm_output_setvelocity;

	C_cm_output_Enum aux = (C_cm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
C_cm_output_Enum create_C_cm_output_stop() {
	C_cm_output_Data data;

	C_cm_output_Type type = C_cm_output_stop;

	C_cm_output_Enum aux = (C_cm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}
C_cm_output_Enum create_C_cm_output__done_() {
	C_cm_output_Data data;

	C_cm_output_Type type = C_cm_output__done_;

	C_cm_output_Enum aux = (C_cm_output_Enum) {
		.type = type,
		.data = data
	};

	return aux;
}

/* Representation of record sm_state */
typedef struct {
	bool done;
	STATES_sm_Enum state;
	STATES_sm_Enum target_state;
	STATUS_Enum status;
	bool en_SimDiscreteGrippingArmMovement_ArmStop_1_done;
	int en_SimDiscreteGrippingArmMovement_ArmStop_1_counter;
	bool en_SimDiscreteGrippingArmMovement_GripperClose_1_done;
	int en_SimDiscreteGrippingArmMovement_GripperClose_1_counter;
	bool en_SimDiscreteGrippingArmMovement_ArmMove_1_done;
	int en_SimDiscreteGrippingArmMovement_ArmMove_1_counter;
	bool en_SimDiscreteGrippingArmMovement_GripperOpen_1_done;
	int en_SimDiscreteGrippingArmMovement_GripperOpen_1_counter;
} sm_state;
/* Representation of record sm_memory */
typedef struct {
	int TARGET_Z;
	float opening_force;
	int TARGET_X;
	MovementArgs margs;
	float MOTION_VEL;
	float PI;
	float opening_speed;
	float closing_speed;
	float closing_force;
	float closing_diameter;
	int TARGET_Y;
	float lv;
	float opening_diameter;
	float av;
} sm_memory;
/* Representation of record sm_inputstate */
typedef struct {
	bool nonfeasibleMoveDiscreteCommand;
	bool openGripperCommand;
	bool closeGripperCommand;
	bool collision;
	bool gripperClosed;
	bool moveCompleted;
	bool robotStopped;
	bool feasibleMoveDiscreteCommand;
	bool gripperOpened;
	bool moveDiscreteCommand;
	MovementArgs moveDiscreteCommand_value;
	TRANSITIONS_sm_Enum _transition_;
} sm_inputstate;

typedef struct {
	pthread_barrier_t can_write, can_read;
	M_DiscreteGrippingArm_output_Enum value;
} M_DiscreteGrippingArm_output_Enum_Channel;

typedef struct {
	pthread_barrier_t can_write, can_read;
	M_DiscreteGrippingArm_input_Enum value;
} M_DiscreteGrippingArm_input_Enum_Channel;

typedef struct {
	pthread_barrier_t can_write, can_read;
	C_cm_input_Enum value;
} C_cm_input_Enum_Channel;
typedef struct {
	pthread_barrier_t can_write, can_read;
	sm_input_Enum value;
} sm_input_Enum_Channel;
typedef struct {
	pthread_barrier_t can_write, can_read;
	sm_output_Enum value;
} sm_output_Enum_Channel;
typedef struct {
	pthread_barrier_t can_write, can_read;
	C_cm_output_Enum value;
} C_cm_output_Enum_Channel;

typedef struct {
	C_cm_input_Enum_Channel* start_cm;
	sm_output_Enum_Channel* end_sm;
	C_cm_output_Enum_Channel* end_cm;
	sm_input_Enum_Channel* start_sm;
} ctrl_cm_thread_Channels;

typedef struct {
	M_DiscreteGrippingArm_output_Enum_Channel* end_DiscreteGrippingArm;
	M_DiscreteGrippingArm_input_Enum_Channel* start_DiscreteGrippingArm;
} control_Channels;

typedef struct {
	sm_input_Enum_Channel* start_sm;
	sm_output_Enum_Channel* end_sm;
} stm_sm_Channels;

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

	//Terminate simulation
	bool terminateSimulation;

} ModelData;

//#define M(v) (comp->v)

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
/**** ****/

#endif
