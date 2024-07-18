function sysCall_init()
    if simROS then
        sim.addLog(sim.verbosity_msgs,"ROS interface was found.")
        startSub=simROS.subscribe('/startSimulation', 'std_msgs/Bool', 'startSimulation_callback')
        pauseSub=simROS.subscribe('/pauseSimulation', 'std_msgs/Bool', 'pauseSimulation_callback')
        stopSub=simROS.subscribe('/stopSimulation', 'std_msgs/Bool', 'stopSimulation_callback')
        enableSynModeSub=simROS.subscribe('/enableSyncMode', 'std_msgs/Bool', 'enableSyncMode_callback')
        triggerNextStepSub=simROS.subscribe('/triggerNextStep', 'std_msgs/Bool', 'triggerNextStep_callback')

        simStepDonePub=simROS.advertise('/simulationStepDone', 'std_msgs/Bool')
        simStatePub=simROS.advertise('/simulationState','std_msgs/Int32')
        simTimePub=simROS.advertise('/simulationTime','std_msgs/Float32')
        auxPub=simROS.advertise('/privateMsgAux', 'std_msgs/Bool')
        auxSub=simROS.subscribe('/privateMsgAux', 'std_msgs/Bool', 'aux_callback')
        
        rosInterfaceSynModeEnabled=false
        haltMainScript=false
    else
        sim.addLog(sim.verbosity_scripterrors,"ROS interface was not found. Cannot run.")
    end
    base_name = "/UR5/"
    j0 = sim.getObject(base_name .. "joint") 
    j1 = sim.getObject(base_name .. "link/joint") 
    j2 = sim.getObject(base_name .."link/joint/link/joint") 
    j3 = sim.getObject(base_name .. "link/joint/link/joint/link/joint/") 
    j4 = sim.getObject(base_name .. "link/joint/link/joint/link/joint/link/joint/") 
    j5 = sim.getObject(base_name .. "link/joint/link/joint/link/joint/link/joint/link/joint/") 
    
    pub_j0 = simROS.advertise('/pub_j0', 'std_msgs/Float32')
    sub_j0 = simROS.subscribe('/sub_j0', 'std_msgs/Float32', 'j0_callback')
    pub_j1 = simROS.advertise('/pub_j1', 'std_msgs/Float32')
    sub_j1 = simROS.subscribe('/sub_j1', 'std_msgs/Float32', 'j1_callback')
    pub_j2 = simROS.advertise('/pub_j2', 'std_msgs/Float32')
    sub_j2 = simROS.subscribe('/sub_j2', 'std_msgs/Float32', 'j2_callback')
    pub_j3 = simROS.advertise('/pub_j3', 'std_msgs/Float32')
    sub_j3 = simROS.subscribe('/sub_j3', 'std_msgs/Float32', 'j3_callback')
    pub_j4 = simROS.advertise('/pub_j4', 'std_msgs/Float32')
    sub_j4 = simROS.subscribe('/sub_j4', 'std_msgs/Float32', 'j4_callback')
    pub_j5 = simROS.advertise('/pub_j5', 'std_msgs/Float32')
    sub_j5 = simROS.subscribe('/sub_j5', 'std_msgs/Float32', 'j5_callback')
end
function startSimulation_callback(msg)
    sim.startSimulation()
end

function pauseSimulation_callback(msg)
    sim.pauseSimulation()
end

function stopSimulation_callback(msg)
    sim.stopSimulation()
end

function enableSyncMode_callback(msg)
    rosInterfaceSynModeEnabled=msg.data
    haltMainScript=rosInterfaceSynModeEnabled
end

function triggerNextStep_callback(msg)
    haltMainScript=false
end

function aux_callback(msg)
    simROS.publish(simStepDonePub,{data=true})
end

function publishSimState()
    local state=0 -- simulation not running
    local s=sim.getSimulationState()
    if s==sim.simulation_paused then
        state=2 -- simulation paused
    elseif s==sim.simulation_stopped then
        state=0 -- simulation stopped
    else
        state=1 -- simulation running
    end
    simROS.publish(simStatePub,{data=state})
end

function j0_callback(msg)
    
    sim.addLog(sim.verbosity_scriptinfos, "j0 receives the following command: " .. msg.data )
    sim.setJointTargetPosition(j0,msg.data)
end

function j1_callback(msg)

    sim.addLog(sim.verbosity_scriptinfos, "j1 receives the following command: " .. msg.data )
    sim.setJointTargetPosition(j1,msg.data)
end

function j2_callback(msg)

    sim.addLog(sim.verbosity_scriptinfos, "j2 receives the following command: " .. msg.data )
    sim.setJointTargetPosition(j2,msg.data)
end

function j3_callback(msg)

    sim.addLog(sim.verbosity_scriptinfos, "j3 receives the following command: " .. msg.data )
    sim.setJointTargetPosition(j3,msg.data)
end

function j4_callback(msg)

    sim.addLog(sim.verbosity_scriptinfos, "j4 receives the following command: " .. msg.data )
    sim.setJointTargetPosition(j4,msg.data)
end

function j5_callback(msg)

    sim.addLog(sim.verbosity_scriptinfos, "j5 receives the following command: " .. msg.data )
    sim.setJointTargetPosition(j5,msg.data)
end

function sysCall_nonSimulation()
    if simROS then
        publishSimState()
    end
end

function sysCall_beforeMainScript()
    return {doNotRunMainScript=haltMainScript}
end

function sysCall_actuation()
    if simROS then
        simROS.publish(pub_j0, {data= sim.getJointPosition(j0)})
	simROS.publish(pub_j1, {data= sim.getJointPosition(j1)})
	simROS.publish(pub_j2, {data= sim.getJointPosition(j2)})
	simROS.publish(pub_j3, {data= sim.getJointPosition(j3)})
	simROS.publish(pub_j4, {data= sim.getJointPosition(j4)})
	simROS.publish(pub_j5, {data= sim.getJointPosition(j5)})
    end
end

function sysCall_sensing()
    if simROS then
        simROS.publish(auxPub,{data=true})
        haltMainScript=rosInterfaceSynModeEnabled
    end
end

function sysCall_suspended()
    if simROS then
        publishSimState()
    end
end

function sysCall_afterSimulation()
    if simROS then
        publishSimState()
    end
end

function sysCall_cleanup()
    if simROS then
    	simROS.shutdownPublisher(pub_j0)
	simROS.shutdownPublisher(pub_j1)
	simROS.shutdownPublisher(pub_j2)
	simROS.shutdownPublisher(pub_j3)
	simROS.shutdownPublisher(pub_j4)
	simROS.shutdownPublisher(pub_j5)
	simROS.shutdownSubscriber(sub_j0)
	simROS.shutdownSubscriber(sub_j1)
	simROS.shutdownSubscriber(sub_j2)
	simROS.shutdownSubscriber(sub_j3)
	simROS.shutdownSubscriber(sub_j4)
	simROS.shutdownSubscriber(sub_j5)
        simROS.shutdownSubscriber(startSub)
        simROS.shutdownSubscriber(pauseSub)
        simROS.shutdownSubscriber(stopSub)
        simROS.shutdownSubscriber(enableSynModeSub)
        simROS.shutdownSubscriber(triggerNextStepSub)
        simROS.shutdownPublisher(simStepDonePub)
        simROS.shutdownPublisher(simStatePub)
        simROS.shutdownPublisher(simTimePub)
        simROS.shutdownSubscriber(auxSub)
        simROS.shutdownPublisher(auxPub)
    end
end


