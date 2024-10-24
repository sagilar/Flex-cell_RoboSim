# Author: Santiago

vars = {}
vars = {}

## RoboSim Module Name
robosim_module_name = "DiscreteGrippingArm"

### Fill in your var names and types e.g. vars["position"]="Boolean"

# inputs
vars["feasibleMoveDiscreteCommand"]=["Boolean","InputEvent"]
vars["robotStopped"]=["Boolean","InputEvent"]
vars["gripperOpened"]=["Boolean","InputEvent"]
vars["collision"]=["Boolean","InputEvent"]
vars["closeGripperCommand"]=["Boolean","InputEvent"]
vars["gripperClosed"]=["Boolean","InputEvent"]
vars["nonfeasibleMoveDiscreteCommand"]=["Boolean","InputEvent"]
vars["moveCompleted"]=["Boolean","InputEvent"]
vars["openGripperCommand"]=["Boolean","InputEvent"]
vars["moveDiscreteCommand"]=["Boolean","InputEvent"]
vars["feasibleMoveDiscreteCommand"]=["Boolean","InputEvent"]
vars["MovementArgs_target_X"]=["Integer","InputEventArgument"]
vars["MovementArgs_target_Y"]=["Integer","InputEventArgument"]
vars["MovementArgs_target_Z"]=["Integer","InputEventArgument"]


# Outputs
vars["movediscrete"]=["Boolean","Operation"]
vars["pick"]=["Boolean","Operation"]
vars["place"]=["Boolean","Operation"]
vars["target_X"]=["Integer","OperationArgument"]
vars["target_Y"]=["Integer","OperationArgument"]
vars["target_Z"]=["Integer","OperationArgument"]
vars["closing_diameter"]=["Real","OperationArgument"]
vars["closing_speed"]=["Real","OperationArgument"]
vars["closing_force"]=["Real","OperationArgument"]
vars["opening_diameter"]=["Real","OperationArgument"]
vars["opening_speed"]=["Real","OperationArgument"]
vars["opening_force"]=["Real","OperationArgument"]
vars["stop"]=["Boolean","Operation"]
vars["movejoint"]=["Boolean","Operation"]
vars["target_q0"]=["Real","OperationArgument"]
vars["target_q1"]=["Real","OperationArgument"]
vars["target_q2"]=["Real","OperationArgument"]
vars["target_q3"]=["Real","OperationArgument"]
vars["target_q4"]=["Real","OperationArgument"]
vars["target_q5"]=["Real","OperationArgument"]
vars["movecartesian"]=["Boolean","Operation"]
vars["target_x"]=["Real","OperationArgument"]
vars["target_y"]=["Real","OperationArgument"]
vars["target_z"]=["Real","OperationArgument"]
vars["target_rx"]=["Real","OperationArgument"]
vars["target_ry"]=["Real","OperationArgument"]
vars["target_rz"]=["Real","OperationArgument"]
vars["setvelocity"]=["Boolean","Operation"]
vars["target_v"]=["Real","OperationArgument"]

vars_list = list(vars)

# Define which variables are provided by the controller FMU
vars_controller = ["moveDiscreteCommand",
                   "MovementArgs_target_X",
                   "MovementArgs_target_Y",
                   "MovementArgs_target_Z",
                   "closeGripperCommand",
                   "openGripperCommand"]


# For mapping FMU: write down which variables are to be logged from the platform mapping FMU
vars_log_pmFMU = {}
vars_log_pmFMU["q0"] = "Real"
vars_log_pmFMU["q1"] = "Real"
vars_log_pmFMU["q2"] = "Real"
vars_log_pmFMU["q3"] = "Real"
vars_log_pmFMU["q4"] = "Real"
vars_log_pmFMU["q5"] = "Real"
vars_log_pmFMU["qd0"] = "Real"
vars_log_pmFMU["qd1"] = "Real"
vars_log_pmFMU["qd2"] = "Real"
vars_log_pmFMU["qd3"] = "Real"
vars_log_pmFMU["qd4"] = "Real"
vars_log_pmFMU["qd5"] = "Real"
vars_log_pmFMU["qdd0"] = "Real"
vars_log_pmFMU["qdd1"] = "Real"
vars_log_pmFMU["qdd2"] = "Real"
vars_log_pmFMU["qdd3"] = "Real"
vars_log_pmFMU["qdd4"] = "Real"
vars_log_pmFMU["qdd5"] = "Real"
vars_log_pmFMU["t0"] = "Real"
vars_log_pmFMU["t1"] = "Real"
vars_log_pmFMU["t2"] = "Real"
vars_log_pmFMU["t3"] = "Real"
vars_log_pmFMU["t4"] = "Real"
vars_log_pmFMU["t5"] = "Real"
vars_log_pmFMU["x"] = "Real"
vars_log_pmFMU["y"] = "Real"
vars_log_pmFMU["z"] = "Real"
vars_log_pmFMU["rx"] = "Real"
vars_log_pmFMU["ry"] = "Real"
vars_log_pmFMU["rz"] = "Real"

vars_log_pmFMU_list = list(vars_log_pmFMU)

def create_mappingfmu_skeleton():

    print("*** (MappingFMU - model.py) For def __init__***")
    for k,v in vars.items():
        if v[0] == "Boolean":
            print("self." + k + " = False")
        elif v[0] == "Real":
            print("self." + k + " = 0.0")
        elif v[0] == "Integer":
            print("self." + k + " = 0")
        elif v[0] == "String":
            print('self.' + k + ' = ""')
    
    if len(vars_log_pmFMU)>0:
        for k,v in vars_log_pmFMU.items():
            if v == "Boolean":
                print("self." + k + " = False")
            elif v == "Real":
                print("self." + k + " = 0.0")
            elif v == "Integer":
                print("self." + k + " = 0")
            elif v == "String":
                print('self.' + k + ' = ""')
        

    print("*** (MappingFMU - model.py) For self.reference_to_attribute***")
    for k,v in vars.items():
        print(str(vars_list.index(k)) + ': "' + k + '",')
    
    if len(vars_log_pmFMU)>0:
        for k,v in vars_log_pmFMU.items():
            print(str(vars_log_pmFMU_list.index(k) + len(vars_list)) + ': "' + k + '",')



    print("*** (MappingFMU - model.py) For def fmi2ExtSerialize***")
    for k,v in vars.items():
        print('self.' + k + ',')
    
    if len(vars_log_pmFMU)>0:
        for k,v in vars_log_pmFMU.items():
            print('self.' + k + ',')

    print("*** (MappingFMU - model.py) For def fmi2ExtDeserialize (1st part)***")
    for k,v in vars.items():
        print(k + ',')

    if len(vars_log_pmFMU)>0:
        for k,v in vars_log_pmFMU.items():
            print(k + ',')

    print("*** (MappingFMU - model.py) For def fmi2ExtDeserialize (2nd part)***")
    for k,v in vars.items():
        print('self.' + k + ' = ' + k)
    
    if len(vars_log_pmFMU)>0:
        for k,v in vars_log_pmFMU.items():
            print('self.' + k + ' = ' + k)


variables_init = '<ModelVariables>'
variables_end = '</ModelVariables>'
text_input = '''<ScalarVariable name="{}" valueReference="{}" variability="discrete" causality="input">
      <String start="" />
    </ScalarVariable>'''

text_output = '''<ScalarVariable name="{}" valueReference="{}" variability="discrete" causality="output">
      <String />
    </ScalarVariable>'''

text_real_input = '''<ScalarVariable name="{}" valueReference="{}" causality="input" variability="continuous">
      <Real start="0.0" />
    </ScalarVariable>'''

text_real_output = '''<ScalarVariable name="{}" valueReference="{}" causality="output" variability="continuous">
      <Real />
    </ScalarVariable>'''

text_integer_input = '''<ScalarVariable name="{}" valueReference="{}" causality="input" variability="discrete">
      <Integer start="0" />
    </ScalarVariable>'''

text_integer_output = '''<ScalarVariable name="{}" valueReference="{}" causality="output" variability="discrete">
      <Integer />
    </ScalarVariable>'''

text_boolean_input = '''<ScalarVariable name="{}" valueReference="{}" causality="input" variability="discrete">
      <Boolean start="false"/>
    </ScalarVariable>'''

text_boolean_output = '''<ScalarVariable name="{}" valueReference="{}" causality="output" variability="discrete">
      <Boolean />
    </ScalarVariable>'''

ms_init = '<ModelStructure>'
ms_end = '</ModelStructure>'
output_init = '<Outputs>'
output_end = '</Outputs>'
unknowns_init = '<InitialUnknowns>'
unknowns_end = '</InitialUnknowns>'

structure_output = '''<Unknown index="{}" />'''

def create_mappingfmu_mdxml():
    print("*** For modeldescription.xml in MappingFMU ***")
    # modeldescription.xml helper

    result_output_structure = ""

    print('***** ModelDescription.xml - ModelVariables *****')
    print(variables_init)
    for k,v in vars.items():
        if "InputEvent" in v[1]:
            if k in vars_controller:
                if v[0] == "Boolean":
                    print(text_boolean_input.format(k,str(vars_list.index(k))))
                elif v[0] == "Real":
                    print(text_real_input.format(k,str(vars_list.index(k))))
                elif v[0] == "Integer":
                    print(text_integer_input.format(k,str(vars_list.index(k))))
                elif v[0] == "String":
                    print(text_input.format(k,str(vars_list.index(k))))
            else:
                if v[0] == "Boolean":
                    print(text_boolean_output.format(k,str(vars_list.index(k))))
                elif v[0] == "Real":
                    print(text_real_output.format(k,str(vars_list.index(k))))
                elif v[0] == "Integer":
                    print(text_integer_output.format(k,str(vars_list.index(k))))
                elif v[0] == "String":
                    print(text_output.format(k,str(vars_list.index(k))))
                result_output_structure = result_output_structure + structure_output.format(vars_list.index(k)+1) + "\n"
        elif "Operation" in v[1]:
            if v[0] == "Boolean":
                print(text_boolean_input.format(k,str(vars_list.index(k))))
            elif v[0] == "Real":
                print(text_real_input.format(k,str(vars_list.index(k))))
            elif v[0] == "Integer":
                print(text_integer_input.format(k,str(vars_list.index(k))))
            elif v[0] == "String":
                print(text_input.format(k,str(vars_list.index(k))))

    if len(vars_log_pmFMU)>0:
        for k,v in vars_log_pmFMU.items():
            if v == "Boolean":
                print(text_boolean_output.format(k,str(vars_log_pmFMU_list.index(k) + len(vars_list))))
            elif v == "Real":
                print(text_real_output.format(k,str(vars_log_pmFMU_list.index(k) + len(vars_list))))
            elif v == "Integer":
                print(text_integer_output.format(k,str(vars_log_pmFMU_list.index(k) + len(vars_list))))
            elif v == "String":
                print(text_output.format(k,str(vars_log_pmFMU_list.index(k) + len(vars_list))))
            result_output_structure = result_output_structure + structure_output.format(vars_log_pmFMU_list.index(k)+1 + len(vars_list)) + "\n"

    print(variables_end)

    print('***** ModelDescription.xml - ModelStructure ******')
    print(ms_init)
    print(output_init)
    print(result_output_structure)
    print(output_end)
    print(unknowns_init)
    print(result_output_structure)
    print(unknowns_end)
    print(ms_end)




def create_dmodelfmu_data_struct():
    print("*** For dmodelFMU data struct (defs_fmi.h) ***")
    print("typedef struct {")
    for k,v in vars.items():
        if v[0] == "Boolean":
            print("\tbool " + k + ";")
        elif v[0] == "Real":
            print("\tfloat " + k + ";")
        elif v[0] == "Integer":
            print("\tint " + k + ";")
        elif v[0] == "String":
            print("\tchar *" + k + ";")

    print("\tchar *state;")
    print("\tchar *target_state;")
    print("\tchar *status;")
    print("\tbool done;")
    print("\tbool terminateSimulation;")
    print("} ModelData;")

def create_dmodelfmu_mdxml():
    print("*** For modeldescription.xml in dmodelFMU ***")
    # modeldescription.xml helper

    result_output_structure = ""

    print('***** ModelDescription.xml - ModelVariables *****')
    print(variables_init)
    for k,v in vars.items():
        if "InputEvent" in v[1]:
            if v[0] == "Boolean":
                print(text_boolean_input.format(k,str(vars_list.index(k))))
            elif v[0] == "Real":
                print(text_real_input.format(k,str(vars_list.index(k))))
            elif v[0] == "Integer":
                print(text_integer_input.format(k,str(vars_list.index(k))))
            elif v[0] == "String":
                print(text_input.format(k,str(vars_list.index(k))))
        elif "Operation" in v[1]:
            if v[0] == "Boolean":
                print(text_boolean_output.format(k,str(vars_list.index(k))))
            elif v[0] == "Real":
                print(text_real_output.format(k,str(vars_list.index(k))))
            elif v[0] == "Integer":
                print(text_integer_output.format(k,str(vars_list.index(k))))
            elif v[0] == "String":
                print(text_output.format(k,str(vars_list.index(k))))
            result_output_structure = result_output_structure + structure_output.format(vars_list.index(k)+1) + "\n"


    print(text_output.format("state",len(vars_list)))
    result_output_structure = result_output_structure + structure_output.format(len(vars_list)+1) + "\n"
    print(text_output.format("target_state",len(vars_list)+1))
    result_output_structure = result_output_structure + structure_output.format(len(vars_list)+2) + "\n"
    print(text_output.format("status",len(vars_list)+2))
    result_output_structure = result_output_structure + structure_output.format(len(vars_list)+3) + "\n"
    print(text_boolean_output.format("done",len(vars_list)+3))
    result_output_structure = result_output_structure + structure_output.format(len(vars_list)+4) + "\n"
    print(text_boolean_input.format("terminateSimulation",len(vars_list)+4))
    
    print(variables_end)

    print('***** ModelDescription.xml - ModelStructure ******')
    print(ms_init)
    print(output_init)
    print(result_output_structure)
    print(output_end)
    print(unknowns_init)
    print(result_output_structure)
    print(unknowns_end)
    print(ms_end)

bool_buffer = 'comp->fmiBuffer.booleanBuffer[{}]'
real_buffer = 'comp->fmiBuffer.realBuffer[{}]'
int_buffer = 'comp->fmiBuffer.intBuffer[{}]'
string_buffer = 'comp->fmiBuffer.stringBuffer[{}]'
model_data_buffer = 'comp->modelData.{}'
def create_dmodel_skeleton_c():
    print("*** For skeleton.c in dmodelFMU ***")
    print("void initialize(ModelInstance* comp, const char* location) {")
    print("init(&comp->modelData);")
    for k,v in vars.items():
        if v[0] == "Boolean":
            print(bool_buffer.format(str(vars_list.index(k))) + " = " + model_data_buffer.format(k) + ";")
        elif v[0] == "Real":
            print(real_buffer.format(str(vars_list.index(k))) + " = " + model_data_buffer.format(k) + ";")
        elif v[0] == "Integer":
            print(int_buffer.format(str(vars_list.index(k))) + " = " + model_data_buffer.format(k) + ";")
        elif v[0] == "String":
            print(string_buffer.format(str(vars_list.index(k))) + " = " + model_data_buffer.format(k) + ";")
    # State data
    print(string_buffer.format(len(vars_list)) + " = " + model_data_buffer.format("state") + ";")
    print(string_buffer.format(len(vars_list)+1) + " = " + model_data_buffer.format("target_state") + ";") 
    print(string_buffer.format(len(vars_list)+2) + " = " + model_data_buffer.format("status") + ";") 
    print(bool_buffer.format(len(vars_list)+3) + " = " + model_data_buffer.format("done") + ";") 
    print("comp->first = 0;")
    print("}")

    print("void doStep(ModelInstance* comp, const char* action) {")
    print("if(comp->first == 0) {")
    for k,v in vars.items():
        if "InputEvent" in v[1]:
            if v[0] == "Boolean":
                print(model_data_buffer.format(k) + " = " + bool_buffer.format(str(vars_list.index(k))) + ";")
            elif v[0] == "Real":
                print(model_data_buffer.format(k) + " = " + real_buffer.format(str(vars_list.index(k))) + ";")
            elif v[0] == "Integer":
                print(model_data_buffer.format(k) + " = " + int_buffer.format(str(vars_list.index(k))) + ";")
            elif v[0] == "String":
                print(model_data_buffer.format(k) + " = " + string_buffer.format(str(vars_list.index(k))) + ";")
    print("}")
    print("// Inputs and arguments")
    for k,v in vars.items():
        if "InputEvent" in v[1]:
            if v[0] == "Boolean":
                print(model_data_buffer.format(k) + " = " + bool_buffer.format(str(vars_list.index(k))) + ";")
            elif v[0] == "Real":
                print(model_data_buffer.format(k) + " = " + real_buffer.format(str(vars_list.index(k))) + ";")
            elif v[0] == "Integer":
                print(model_data_buffer.format(k) + " = " + int_buffer.format(str(vars_list.index(k))) + ";")
            elif v[0] == "String":
                print(model_data_buffer.format(k) + " = " + string_buffer.format(str(vars_list.index(k))) + ";")

    print("// step in the module")
    print("tick(&comp->modelData);")
    print("// Outputs")
    for k,v in vars.items():
        if "Operation" in v[1]:
            if v[0] == "Boolean":
                print(bool_buffer.format(str(vars_list.index(k))) + " = " + model_data_buffer.format(k) + ";")
            elif v[0] == "Real":
                print(real_buffer.format(str(vars_list.index(k))) + " = " + model_data_buffer.format(k) + ";")
            elif v[0] == "Integer":
                print(int_buffer.format(str(vars_list.index(k))) + " = " + model_data_buffer.format(k) + ";")
            elif v[0] == "String":
                print(string_buffer.format(str(vars_list.index(k))) + " = " + model_data_buffer.format(k) + ";")
    # State data
    print(string_buffer.format(len(vars_list)) + " = " + model_data_buffer.format("state") + ";")
    print(string_buffer.format(len(vars_list)+1) + " = " + model_data_buffer.format("target_state") + ";") 
    print(string_buffer.format(len(vars_list)+2) + " = " + model_data_buffer.format("status") + ";") 
    print(bool_buffer.format(len(vars_list)+3) + " = " + model_data_buffer.format("done") + ";") 
    print("}")

setStartValues_structure = 'M({}) = {};'
def create_setStartValues():
    print("*** For " + robosim_module_name + ".c (name depends on RoboSim module) in dmodelFMU ***")
    print("void setStartValues(ModelData *comp) {")
    print("comp->terminateSimulation = false;")
    for k,v in vars.items():
        if v[0] == "Boolean":
            print(setStartValues_structure.format(k,"false"))
        elif v[0] == "Real":
            print(setStartValues_structure.format(k,"0.0"))
        elif v[0] == "Integer":
            print(setStartValues_structure.format(k,"0"))
        elif v[0] == "String":
            print(setStartValues_structure.format(k,'""'))
    print(setStartValues_structure.format("state",'""'))
    print(setStartValues_structure.format("target_state",'""'))
    print(setStartValues_structure.format("status",'""'))
    print(setStartValues_structure.format("done",'false'))
    print("}")

read_input_structure = '''{2}if (fmi_data_interface->{0}) {{
        {{
            char _s0[256];
            sprintf(_s0, "%%s", "Found event {0}");
            printf("%%s", _s0);}}
        {{
            fmi_data_interface->{0} = false; // reset memory
            return create_M_{1}_input_{0}();
        }}
    }}'''
final_read_input_structure = '''else {{
        return create_M_{}_input__done_();
    }}'''
def set_read_input_interface():
    print("*** For read_input function in interface.h in dmodelFMU - NOTE: Update the arguments ***")
    idx = 0
    s = lambda idx: "else " if idx>0 else ""
    for k,v in vars.items():        
        if "InputEvent" == v[1]:
            print(read_input_structure.format(k,robosim_module_name,s(idx)))
        idx += 1
    print(final_read_input_structure.format(robosim_module_name))

write_output_structure = '''{2}if (_output_.type == M_{0}_output_{1}) {{
        {{
            fmi_data_interface->state = "some_state"; // update accordingly;
            fmi_data_interface->{1} = "some_value" // update accordingly;
        }}
    }}
'''
final_write_output_structure = '''else if (_output_.type == M_{}_output__done_) {{
    }}'''
def set_write_output_interface():
    print("*** For write_output function in interface.h in dmodelFMU - NOTE: Update the arguments ***")
    idx = 0
    s = lambda idx: "else " if idx>0 else ""
    for k,v in vars.items():
        if "Operation" == v[1]:
            print(write_output_structure.format(robosim_module_name,k,s(idx)))
        idx += 1
    print(final_write_output_structure.format(robosim_module_name))


def create_controllerfmu_mdxml():
    print("*** For modeldescription.xml in controllerFMU (also valid for RMQFMU) ***")
    # modeldescription.xml helper

    result_output_structure = ""

    print('***** ModelDescription.xml - ModelVariables *****')
    print(variables_init)
    idx = 1
    for k,v in vars.items():
        if k in vars_controller:
            if v[0] == "Boolean":
                print(text_boolean_output.format(k,str(vars_list.index(k))))
            elif v[0] == "Real":
                print(text_real_output.format(k,str(vars_list.index(k))))
            elif v[0] == "Integer":
                print(text_integer_output.format(k,str(vars_list.index(k))))
            elif v[0] == "String":
                print(text_output.format(k,str(vars_list.index(k))))
            result_output_structure = result_output_structure + structure_output.format(idx) + "\n"
            idx += 1

    # for inputs (optional)
    # for k,v in vars.items():
    #     if k in vars_controller_inputs:
    #         if v[0] == "Boolean":
    #             print(text_boolean_input.format(k,str(vars_list.index(k))))
    #         elif v[0] == "Real":
    #             print(text_real_input.format(k,str(vars_list.index(k))))
    #         elif v[0] == "Integer":
    #             print(text_integer_input.format(k,str(vars_list.index(k))))
    #         elif v[0] == "String":
    #             print(text_input.format(k,str(vars_list.index(k))))



    print(variables_end)

    print('***** ModelDescription.xml - ModelStructure ******')
    print(ms_init)
    print(output_init)
    print(result_output_structure)
    print(output_end)
    print(unknowns_init)
    print(result_output_structure)
    print(unknowns_end)
    print(ms_end)

def create_controllerfmu_skeleton():

    print("*** (controllerFMU - model.py) For def __init__***")
    for k,v in vars.items():
        if k in vars_controller:
            if v[0] == "Boolean":
                print("self." + k + " = False")
            elif v[0] == "Real":
                print("self." + k + " = 0.0")
            elif v[0] == "Integer":
                print("self." + k + " = 0")
            elif v[0] == "String":
                print('self.' + k + ' = ""')

    print("*** (controllerFMU - model.py) For self.reference_to_attribute***")
    for k,v in vars.items():
        if k in vars_controller:
            print(str(vars_list.index(k)) + ': "' + k + '",')

    print("*** (controllerFMU - model.py) For def fmi2ExtSerialize***")
    for k,v in vars.items():
        if k in vars_controller:
            print('self.' + k + ',')

    print("*** (controllerFMU - model.py) For def fmi2ExtDeserialize (1st part)***")
    for k,v in vars.items():
        if k in vars_controller:
            print(k + ',')

    print("*** (controllerFMU - model.py) For def fmi2ExtDeserialize (2nd part)***")
    for k,v in vars.items():
        if k in vars_controller:
            print('self.' + k + ' = ' + k)

def create_connections(rmqfmu=False):
    controller_name = "controller"
    if rmqfmu:
        controller_name = "rmqfmu"
    print("*** For connections in Multimodel.json ***")
    struct_connections = ''
    controller_connections = ''
    for k,v in vars.items():
        if "InputEvent" in v[1]:
            if k in vars_controller:
                controller_connections += '"{{{0}}}.{0}.{1}" : ["{{dmodel}}.dmodel.{1}","{{mapping}}.mapping.{1}"],\n'.format(controller_name,k)
            else:
                struct_connections += '"{{mapping}}.mapping.{}" : ["{{dmodel}}.dmodel.{}"],\n'.format(k,k)
        elif "Operation" in v[1]:
            struct_connections += '"{{dmodel}}.dmodel.{}" : ["{{mapping}}.mapping.{}"],\n'.format(k,k)
    print(controller_connections[:-1])
    print(struct_connections[:-2])

if __name__=='__main__':
    print("Miscellaneous 1 - Step 5\n")
    create_connections()
    
    print("\n\n\n\nMiscellaneous 2 - Step 6\n")
    create_mappingfmu_mdxml()
    
    print("\n\n\n\nMiscellaneous 3 - Steps 6 and 7\n")
    create_mappingfmu_skeleton()
    
    print("\n\n\n\nMiscellaneous 4 - Step 8\n")
    create_dmodelfmu_mdxml()
    
    print("\n\n\n\nMiscellaneous 5 - Step 9\n")
    create_dmodelfmu_data_struct()
    
    print("\n\n\n\nMiscellaneous 6 - Step 10\n")
    set_read_input_interface()
    
    print("\n\n\n\nMiscellaneous 7 - Step 10\n")
    set_write_output_interface()
    
    print("\n\n\n\nMiscellaneous 8 - Step 11\n")
    create_dmodel_skeleton_c()
    
    print("\n\n\n\nMiscellaneous 9 - Step 11\n")
    create_setStartValues()
    
    print("\n\n\n\nMiscellaneous 10 - Steps 12 and 13\n")
    create_controllerfmu_skeleton()
    
    print("\n\n\n\nMiscellaneous 11 - Step 13\n")
    create_controllerfmu_mdxml()
    
    
    
