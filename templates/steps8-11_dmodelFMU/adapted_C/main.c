#include "defs_fmi.h"

/***** Initialize the infrastructure pointer for the whole scope *****/
__Infrastructure__* state;

// Additional Functions
/***** Optional: initialize the values of the ModelData struct *****/
void setStartValues(ModelData *comp) {
		comp->terminateSimulation = false;
		// Parameters
		M(var0_float) = 0.0;
		M(var1_boolean) = false;
		M(var2_string) = "";
		M(var3_int) = 0;
		M(var4_boolean) = false;
		M(var5_boolean) = false;
}

/***** Init and tick functions (no need for changes) *****/
void init(ModelData* comp) { //Replace for the main function
		setStartValues(comp); // Optional
		printf("Initializing the RoboSim ... module\n");
		update_fmi_data(comp);
		state = (__Infrastructure__*)malloc(sizeof(__Infrastructure__));

		__initialiseProgrammingEnvironment__();
		__initialiseConcurrencyInfrastructure__(state);

}

ModelData* tick(ModelData* comp){
	update_fmi_data(comp);
	{
		bool terminate__ = false;
		if ((!comp->terminateSimulation) || (!terminate__)) {
			terminate__ = __step__(state);
		}
	}
	return comp;
}

void release(){
	printf("Terminating modules\n");
	__clean__(state);
	exit(0);
}
