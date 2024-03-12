#python

def sysCall_init():
    sim = require('sim')
    simIK = require('simIK')
    
    # Build a kinematic chain and 2 IK groups (undamped and damped) inside of the IK plugin environment,
    # based on the kinematics of the robot in the scene:
    
    simBase = sim.getObject('.')
    simTip = sim.getObject('./redundantRob_tip')
    simTarget = sim.getObject('./redundantRob_target')

    # Simple way:
    self.ikEnv = simIK.createEnvironment()
    self.ikGroup_undamped = simIK.createGroup(self.ikEnv)
    simIK.setGroupCalculation(self.ikEnv, self.ikGroup_undamped, simIK.method_pseudo_inverse, 0, 6)
    simIK.addElementFromScene(self.ikEnv, self.ikGroup_undamped, simBase, simTip, simTarget, simIK.constraint_pose)

    self.ikGroup_damped = simIK.createGroup(self.ikEnv)
    simIK.setGroupCalculation(self.ikEnv, self.ikGroup_damped, simIK.method_damped_least_squares, 1, 99)
    simIK.addElementFromScene(self.ikEnv, self.ikGroup_damped, simBase, simTip, simTarget, simIK.constraint_pose)

    # Elaborate way:
    '''
    simBase = sim.getObject('.')
    simTip = sim.getObject('./redundantRob_tip')
    simTarget = sim.getObject('./redundantRob_target')
    simJoints = [sim.getObject(f'./redundantRob_joint{i}') for i in range(1, 8)]
    ikJoints = []

    self.ikEnv = simIK.createEnvironment()
    ikBase = simIK.createDummy(self.ikEnv)
    simIK.setObjectMatrix(self.ikEnv, ikBase, -1, sim.getObjectMatrix(simBase)) 
    parent = ikBase
    
    for i in range(len(simJoints)):
        ikJoints.append(simIK.createJoint(self.ikEnv, simIK.jointtype_revolute))
        simIK.setJointMode(self.ikEnv, ikJoints[i], simIK.jointmode_ik)
        cyclic, interv = sim.getJointInterval(simJoints[i])
        simIK.setJointInterval(self.ikEnv, ikJoints[i], cyclic, interv)
        simIK.setJointPosition(self.ikEnv, ikJoints[i], sim.getJointPosition(simJoints[i]))
        simIK.setObjectMatrix(self.ikEnv, ikJoints[i], -1, sim.getObjectMatrix(simJoints[i]))
        simIK.setObjectParent(self.ikEnv, ikJoints[i], parent, True) 
        parent = ikJoints[i]
        
    ikTip = simIK.createDummy(self.ikEnv)
    simIK.setObjectMatrix(self.ikEnv, ikTip, -1, sim.getObjectMatrix(simTip))
    simIK.setObjectParent(self.ikEnv, ikTip, parent, True)
    
    ikTarget = simIK.createDummy(self.ikEnv)
    simIK.setObjectMatrix(self.ikEnv, ikTarget, -1, sim.getObjectMatrix(simTarget))
    simIK.setTargetDummy(self.ikEnv, ikTip, ikTarget)

    self.ikGroup_undamped = simIK.createGroup(self.ikEnv)
    simIK.setGroupCalculation(self.ikEnv, self.ikGroup_undamped, simIK.method_pseudo_inverse, 0, 6)
    ikElementHandle = simIK.addElement(self.ikEnv, self.ikGroup_undamped, ikTip)
    simIK.setElementBase(self.ikEnv, self.ikGroup_undamped, ikElementHandle, ikBase)
    simIK.setElementConstraints(self.ikEnv, self.ikGroup_undamped, ikElementHandle, simIK.constraint_pose)
    
    self.ikGroup_damped = simIK.createGroup(self.ikEnv)
    simIK.setGroupCalculation(self.ikEnv, self.ikGroup_damped, simIK.method_damped_least_squares, 1, 99)
    ikElementHandle = simIK.addElement(self.ikEnv, self.ikGroup_damped, ikTip)
    simIK.setElementBase(self.ikEnv, self.ikGroup_damped, ikElementHandle, ikBase)
    simIK.setElementConstraints(self.ikEnv, self.ikGroup_damped, ikElementHandle, simIK.constraint_pose)
    '''

def sysCall_actuation():
    # There is a simple way, and a more elaborate way (but which gives you more options/flexibility):
    
    # Simple way:
    res, *_ = simIK.handleGroup(self.ikEnv, self.ikGroup_undamped, {'syncWorlds': True})
    if res != simIK.result_success:
        simIK.handleGroup(self.ikEnv, self.ikGroup_damped, {'syncWorlds': True})
        sim.addLog(sim.verbosity_scriptwarnings, "IK solver failed.")

    # Elaborate way:
    '''
    simIK.setObjectMatrix(self.ikEnv, ikTarget, ikBase, sim.getObjectMatrix(simTarget, simBase)) 
    res, *_ = simIK.handleGroup(self.ikEnv, self.ikGroup_undamped)
    if res != simIK.result_success:
        simIK.handleGroup(self.ikEnv, self.ikGroup_damped)
        sim.addLog(sim.verbosity_scriptwarnings, "IK solver failed.") 

    for i in range(len(simJoints)):
        sim.setJointPosition(simJoints[i], simIK.getJointPosition(self.ikEnv, ikJoints[i])) 
    '''   

