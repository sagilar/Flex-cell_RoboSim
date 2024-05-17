import physmod::math::*
import sequence_toolkit::*
import physmod::sensors::*

enumeration flexcellCartesianPosition {
	none
	invalid
	position(MovementArgs)
}

enumeration flexcellAngularPosition {
	none
	completed
	stopped
	position(MovementArgsAngular)
}

enumeration gripperCommand {
	none
	open
	opened
	close
	closed
}

map Mapping_UR5e dmodel DiscreteGrippingArm to pmodel ur5e_gripper {
	var targetCartesianPosition : flexcellCartesianPosition::none
	var targetAngularPosition : flexcellAngularPosition::none
	var gripperPosition : gripperCommand::none
	const Z_table_level:real = 0.020
    const YMIN:int = 0
    const YMAX:int = 23
    const XMIN:int = 0
    const XMAX:int = 15
    const HOLE_DIST:real = 0.05
    const x_min:real = -0.072
    const x_max:real = 1.128
    const y_max:real = 0.731 - 0.020 // compensation
    const y_min:real = -0.369 - 0.020 // compensation
    const T0_COLLISION: real = 1.0
    const T1_COLLISION: real = 1.0
    const T2_COLLISION: real = 1.0
    const T3_COLLISION: real = 1.0
    const T4_COLLISION: real = 1.0
    const T5_COLLISION: real = 1.0
    const SPEED_COLLISION: real = 0.5
    const GRIP_WIDTH_MAX: real = 0.073
	const GRIP_WIDTH_MIN: real = 0.035
    
    var diameter:real, speed:real,force:real
    var q0:real,q1:real,q2:real,q3:real,q4:real,q5:real
    var target_q0:real,target_q1:real,target_q2:real,target_q3:real,target_q4:real,target_q5:real
    var qd0:real,qd1:real,qd2:real,qd3:real,qd4:real,qd5:real
    var target_qd0:real,target_qd1:real,target_qd2:real,target_qd3:real,target_qd4:real,target_qd5:real
    var qdd0:real,qdd1:real,qdd2:real,qdd3:real,qdd4:real,qdd5:real
    var target_x:real,target_y:real,target_z:real,target_rx:real,target_ry:real,target_rz:real
    var target_X:int,target_Y:int,target_Z:int
    var target_velocity: real
    var right_finger_pos:real,left_finger_pos:real
    
    var feasible : boolean
	var completed : boolean
	
	operation movediscrete {
		var target_position_cartesian:flexcellCartesianPosition::position
		//var X: int = target_position_cartesian.targetx
		//var Y: int = target_position_cartesian.targety
		//var Z: int = target_position_cartesian.targetz
		var computed_x:real = x_max - ((target_Y+1)*HOLE_DIST)
        var computed_y:real = (y_max - ((target_X)*HOLE_DIST))
        var computed_z:real = Z_table_level + target_Z * HOLE_DIST
        
        
        
        var target_position_angular:flexcellAngularPosition
        
		//inverse kinematics operation
		var inv_kinematics:vector(real, 6) = inverse_kinematics(computed_x,computed_y,computed_z)
		//target_q0 == inv_kinematics[0]
		//target_q1 == inv_kinematics[1]
		//target_q2 == inv_kinematics[2]
		//target_q3 == inv_kinematics[3]
		//target_q4 == inv_kinematics[4]
		//target_q5 == inv_kinematics[5]
		
		action q0 = target_q0 //ur5e_gripper::base_link::shoulder_pan_joint::M1.dangle == q0
		action q1 = target_q1 //ur5e_gripper::shoulder_link::shoulder_lift_joint::M2.dangle  == q1
		action q2 = target_q2 //ur5e_gripper::upper_arm_link::elbow_joint::M3.dangle == q2
		action q3 = target_q3 //ur5e_gripper::forearm_link::wrist_1_joint::M4.dangle  == q3
		action q4 = target_q4 //ur5e_gripper::wrist_1_link::wrist_2_joint::M5.dangle == q4
		action q5 = target_q5 //ur5e_gripper::wrist_2_link::wrist_3_joint::M6.dangle  == q5
		
	}
	
	operation movejoint {
		action q0 = target_q0 //ur5e_gripper::base_link::shoulder_pan_joint::M1.dangle == q0
		action q1 = target_q1 //ur5e_gripper::shoulder_link::shoulder_lift_joint::M2.dangle  == q1
		action q2 = target_q2 //ur5e_gripper::upper_arm_link::elbow_joint::M3.dangle == q2
		action q3 = target_q3 //ur5e_gripper::forearm_link::wrist_1_joint::M4.dangle  == q3
		action q4 = target_q4 //ur5e_gripper::wrist_1_link::wrist_2_joint::M5.dangle == q4
		action q5 = target_q5 //ur5e_gripper::wrist_2_link::wrist_3_joint::M6.dangle  == q5
	}
	
	operation movecartesian {
		//inverse kinematics first		
		action q0 = target_q0 //ur5e_gripper::base_link::shoulder_pan_joint::M1.dangle == q0
		action q1 = target_q1 //ur5e_gripper::shoulder_link::shoulder_lift_joint::M2.dangle  == q1
		action q2 = target_q2 //ur5e_gripper::upper_arm_link::elbow_joint::M3.dangle == q2
		action q3 = target_q3 //ur5e_gripper::forearm_link::wrist_1_joint::M4.dangle  == q3
		action q4 = target_q4 //ur5e_gripper::wrist_1_link::wrist_2_joint::M5.dangle == q4
		action q5 = target_q5 //ur5e_gripper::wrist_2_link::wrist_3_joint::M6.dangle  == q5
	}
	
	operation setvelocity {
			
		action qd0 = target_velocity //ur5e_gripper::base_link::shoulder_pan_joint::M1.angular_vel == velocity
		action qd1 = target_velocity //ur5e_gripper::shoulder_link::shoulder_lift_joint::M2.angular_vel  == velocity
		action qd2 = target_velocity //ur5e_gripper::upper_arm_link::elbow_joint::M3.angular_vel == velocity
		action qd3 = target_velocity //ur5e_gripper::forearm_link::wrist_1_joint::M4.angular_vel  == velocity
		action qd4 = target_velocity //ur5e_gripper::wrist_1_link::wrist_2_joint::M5.angular_vel == velocity
		action qd5 = target_velocity
	}
	
	operation stop {
		//No low-level control for stopping the robot rather than robot.stop() or joint.stop()
		action qd0 = 0 //ur5e_gripper::base_link::shoulder_pan_joint::M1.angular_vel == 0
		action qd1 = 0 //ur5e_gripper::shoulder_link::shoulder_lift_joint::M2.angular_vel  == 0
		action qd2 = 0 //ur5e_gripper::upper_arm_link::elbow_joint::M3.angular_vel == 0
		action qd3 = 0 //ur5e_gripper::forearm_link::wrist_1_joint::M4.angular_vel  == 0
		action qd4 = 0 //ur5e_gripper::wrist_1_link::wrist_2_joint::M5.angular_vel == 0
		action qd5 = 0 //ur5e_gripper::wrist_2_link::wrist_3_joint::M6.angular_vel  == 0
	}
	
	operation pick {		
		action left_finger_pos = diameter //ur5e_gripper::link_2fg7_base::leftFingerGripper::leftFingerMotor.dangle 
		action right_finger_pos = diameter //ur5e_gripper::link_2fg7_base::rightFingerGripper::rightFingerMotor.dangle
	}
	
	operation place {	
		action left_finger_pos = diameter //ur5e_gripper::link_2fg7_base::leftFingerGripper::leftFingerMotor.dangle
		action right_finger_pos = diameter //ur5e_gripper::link_2fg7_base::rightFingerGripper::rightFingerMotor.dangle == 0.0
	}
	
	input event moveDiscreteCommand {
		equation targetCartesianPosition == flexcellCartesianPosition::position
	}
	
	input event nonfeasibleMoveDiscreteCommand {
		equation targetCartesianPosition == flexcellCartesianPosition::invalid
	}
	
	input event feasibleMoveDiscreteCommand {
		equation targetCartesianPosition != flexcellCartesianPosition::invalid
	}
	
	input event moveCompleted {
		equation targetAngularPosition == flexcellAngularPosition::completed
	}
	
	input event robotStopped {
		equation targetAngularPosition == flexcellAngularPosition::completed \/
				 targetAngularPosition == flexcellAngularPosition::stopped
		equation ur5e_gripper::base_link::VSJ1.output_vel == 0.0
		equation ur5e_gripper::shoulder_link::VSJ2.output_vel  == 0.0
		equation ur5e_gripper::upper_arm_link::VSJ3.output_vel == 0.0
		equation ur5e_gripper::forearm_link::VSJ4.output_vel  == 0.0
		equation ur5e_gripper::wrist_1_link::VSJ5.output_vel == 0.0
		equation ur5e_gripper::wrist_2_link::VSJ6.output_vel  == 0.0
	}
	
	input event gripperClosed {
		equation gripperPosition == gripperCommand::closed
		equation ur5e_gripper::link_2fg7_base::PSLF.output_position < (GRIP_WIDTH_MIN/2 + 0.005)
		equation ur5e_gripper::link_2fg7_base::PSRF.output_position < (GRIP_WIDTH_MIN/2 + 0.005)
	}
	
	input event gripperOpened {
		equation gripperPosition == gripperCommand::opened
		equation ur5e_gripper::link_2fg7_base::PSLF.output_position > (GRIP_WIDTH_MAX/2 - 0.005)
		equation ur5e_gripper::link_2fg7_base::PSRF.output_position > (GRIP_WIDTH_MAX/2 - 0.005)
	}
	
	input event openGripperCommand {
		equation gripperPosition == gripperCommand::open		
	}	
	
	input event closeGripperCommand {
		equation gripperPosition == gripperCommand::close		
	}
	
	input event collision {
		equation ur5e_gripper::base_link::TSJ1.output_torque  > T0_COLLISION /\
				 ur5e_gripper::base_link::VSJ1.output_vel < SPEED_COLLISION
		equation ur5e_gripper::shoulder_link::TSJ2.output_torque   > T1_COLLISION /\
				 ur5e_gripper::shoulder_link::VSJ2.output_vel  < SPEED_COLLISION
		
		equation ur5e_gripper::upper_arm_link::TSJ3.output_torque  > T2_COLLISION /\
				 ur5e_gripper::upper_arm_link::VSJ3.output_vel  < SPEED_COLLISION
		equation ur5e_gripper::forearm_link::TSJ4.output_torque   > T3_COLLISION /\
				 ur5e_gripper::forearm_link::VSJ4.output_vel  < SPEED_COLLISION
		equation ur5e_gripper::wrist_1_link::TSJ5.output_torque  > T4_COLLISION /\
				 ur5e_gripper::wrist_1_link::VSJ5.output_vel  < SPEED_COLLISION
		equation ur5e_gripper::wrist_2_link::TSJ6.output_torque   > T5_COLLISION /\
				 ur5e_gripper::wrist_2_link::VSJ6.output_vel  < SPEED_COLLISION
	}
}

function inverse_kinematics(target_x:real,target_y:real,target_z:real): vector(real,6) {
	//operation -> Robotics Toolbox
	postcondition 
		let target_q0==0.0,target_q1==0.0,target_q2==0.0,target_q3==0.0,target_q4==0.0,target_q5==0.0
	@
	result == [|target_q0,target_q1,target_q2,target_q3,target_q4,target_q5|]
}
