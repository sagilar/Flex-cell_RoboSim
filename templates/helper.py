# Author: Santiago

vars = {}
vars = {}

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
vars["MovementArgs.target_X"]=["Integer","InputEventArgument"]
vars["MovementArgs.target_Y"]=["Integer","InputEventArgument"]
vars["MovementArgs.target_Z"]=["Integer","InputEventArgument"]


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

vars_list = list(vars)

# Define which variables are provided by the controller FMU
vars_controller = ["moveDiscreteCommand","MovementArgs.target_X","MovementArgs.target_Y","MovementArgs.target_Z","closeGripperCommand","openGripperCommand"]


def create_mappingfmu_skeleton():

    print("*** (MappingFMU) For def __init__***")
    for k,v in vars.items():
        if v[0] == "Boolean":
            print("self." + k + " = False")
        elif v[0] == "Real":
            print("self." + k + " = 0.0")
        elif v[0] == "Integer":
            print("self." + k + " = 0")
        elif v[0] == "String":
            print('self.' + k + ' = ""')

    print("*** (MappingFMU) For self.reference_to_attribute***")
    for k,v in vars.items():
        print(str(vars_list.index(k)) + ': ' + k + ',')



    print("*** For def fmi2ExtSerialize***")
    for k,v in vars.items():
        print('self.' + k + ',')

    print("*** For def fmi2ExtDeserialize (1st part)***")
    for k,v in vars.items():
        print(k + ',')

    print("*** For def fmi2ExtDeserialize (2nd part)***")
    for k,v in vars.items():
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

text_integer_input = '''<ScalarVariable name="{}" valueReference="{}" causality="input" variability="continuous">
      <Integer start="0" />
    </ScalarVariable>'''

text_integer_output = '''<ScalarVariable name="{}" valueReference="{}" causality="output" variability="continuous">
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
            if v[0] == "Boolean":
                print(text_boolean_output.format(k,str(vars_list.index(k))))
            elif v[0] == "Real":
                print(text_real_output.format(k,str(vars_list.index(k))))
            elif v[0] == "Integer":
                print(text_integer_output.format(k,str(vars_list.index(k))))
            elif v[0] == "String":
                print(text_output.format(k,str(vars_vars_listlist.index(k))))
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

def create_controllerfmu_mdxml():
    print("*** For modeldescription.xml in controllerFMU ***")
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


def create_connections():
    print("*** For connections in Multimodel.json ***")
    struct_connections = ''
    controller_connections = ''
    for k,v in vars.items():
        if "InputEvent" in v[1]:
            if k in vars_controller:
                controller_connections += '"{{controller}}.controller.{}" : ["{{mapping}}.mapping.{}"],\n'.format(k,k)
            struct_connections += '"{{mapping}}.mapping.{}" : ["{{dmodel}}.dmodel.{}"],\n'.format(k,k)
        elif "Operation" in v[1]:
            struct_connections += '"{{dmodel}}.dmodel.{}" : ["{{mapping}}.mapping.{}"],\n'.format(k,k)
    print(controller_connections[:-1])
    print(struct_connections[:-2])

if __name__=='__main__':
    create_mappingfmu_skeleton()
    create_mappingfmu_mdxml()
    create_dmodelfmu_data_struct()
    create_dmodelfmu_mdxml()
    create_controllerfmu_mdxml()
    create_connections()
