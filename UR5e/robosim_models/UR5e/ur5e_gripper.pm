import physmod::joints::Revolute
import physmod::joints::Prismatic
import physmod::actuators::*
import physmod::math::*


sensor ForceSensor {
	// Very basic force sensor; needs to be replaced with something more sophisticated
	input input_force: real
	output output_force: real
	equation input_force == output_force
}

sensor TorqueSensor {
	// Very basic force sensor; needs to be replaced with something more sophisticated
	input input_torque: real
	output output_torque: real
	equation input_torque == output_torque
}

sensor VelocitySensor {
	input input_vel: real
	output output_vel: real
	equation input_vel == output_vel
}


sensor PositionSensor {
	input input_position: real
	output output_position: real
	equation input_position == output_position
}

pmodel ur5e_gripper {
	//base: x=0.15, y=0.15, z=0.10 = radio = 0.15
	//shoulder: x=0.12, y=0.14, z=0.14 = radio = 0.14
	//forearm: x=0.55, y=0.14, z=0.12. cylinder radio = 0.085
	//upperarm: x=0.49, y=0.12, z=0.12. cylinder radio = 0.075
	//wrist1: x=0.08, y=0.12, z=0.10. cylinder radio = 0.075
	//wrist2: x=0.08, y=0.10, z=0.9. cylinder radio = 0.075
	//wrist3: x=0.07, y=0.05, z=0.08. cylinder radio = 0.075
	//gripper body: x=90.0, y=71.0, z=117.25. cylinder radio = 71.0 - cube= 60.0x90.0x114.45 lengthxwidthxheight
	//gripper fingers:x=19.2, y=32.0, z=45.0. cube= 32.0x5.0x45.0 lengthxwidthxheight
	
	const PI: real = 3.1415	
	const BASE_RADIUS: real = 0.15/2
	const SHOULDER_RADIUS: real = 0.14/2
	const UPPERARM_RADIUS: real = 0.085/2
	const FOREARM_RADIUS: real = 0.075/2
	const WRIST1_RADIUS: real = 0.075/2
	const WRIST2_RADIUS: real = 0.075/2
	const WRIST3_RADIUS: real = 0.075/2
	
	const BASELEN: real = 0.0988
	const SHOULDER_LINK_LENGTH: real = 0.13
	const UPPER_ARM_LINK_LENGTH: real = 0.540
	const FOREARM_LINK_LENGTH: real = 0.487
	const WRIST1_LINK_LENGTH: real = 0.102
	const WRIST2_LINK_LENGTH: real = 0.102
	const WRIST3_ARM_LINK_LENGTH: real = 0.047
	
	const MASS_BASE: real = 4.0
	const MASS1: real = 3.761
	const MASS2: real = 8.058
	const MASS3: real = 2.846
	const MASS4: real = 1.37
	const MASS5: real = 1.3
	const MASS6: real = 0.365 

	
	


	local link base_link { //base
		def {
			inertial information {
				mass MASS_BASE kg
			}	

		}
		local body base_link_collision {
			def {
				cylinder ( radius = BASE_RADIUS , length = BASELEN )
			}
			pose {
				x = 0.0
				y = 0.0
				z = 0.0
				roll = 0.0
				pitch = 0.0
				yaw = 0.0 //
			}
		}
		jref shoulder_pan_joint = Revolute {
			annotation Revolute  {
				axis=Axis{
					xyz = (|0,0,1|)
					dynamics = Dynamics {
						damping = 10
						
					}
					limit = Limit {
						lower = -2*PI
						upper = 2*PI
						velocity = PI/2
						effort = 1000
					}
				}
			}
			
		instantiation AXIS = (|0,0,1|)
			aref M1 = ServoMotor {
				relation shoulder_pan_joint.tau == M1.T
			}
			flexibly connected to shoulder_link
			pose {
				x = 0.0
				y = 0.0 //0.13387//0.0
				z = 0.0988 //0.0//0.0988
				roll = 0.0
				pitch = 0.0
				yaw = 0.0
			}
		}
		sref FSJ1 = ForceSensor
		sref VSJ1 = VelocitySensor
		sref TSJ1 = TorqueSensor
		sref PSJ1 = PositionSensor
		pose {
			x = 0.0
			y = 0.0
			z = 0.0
			roll = 0.0
			pitch = 0.0
			yaw = PI
		}
	}
	
	local link shoulder_link {
		def {
		inertial information {
				mass MASS1 kg
				pose {
					x = 0.0
					y = 0.00193
					z = -0.02561
					roll = 0.0
					pitch = 0.0
					yaw = 0.0
				}
			}
		}
		local body shoulder_link_collision {
			def {
				cylinder ( radius = SHOULDER_RADIUS , length = SHOULDER_LINK_LENGTH ) //LEN1
			}
			pose {
				x = 0.0
				y = 0.0 //0.00193
				z = SHOULDER_LINK_LENGTH/2 - BASELEN/2 //-0.02561
				roll = 0.0
				pitch = 0.0
				yaw = PI/2
			}
		}
		jref shoulder_lift_joint = Revolute {
			annotation Revolute  {
				axis=Axis{
					xyz = (|0,1,0|)
					dynamics = Dynamics {
						damping = 10
					}
					limit = Limit {
						lower = -2*PI
						upper = 2*PI
						velocity = PI/2
						effort = 1000
					}
				}
			}
		instantiation AXIS = (|0,1,0|) //(|0,1,0|)
			aref M2 = ServoMotor {
				relation shoulder_lift_joint.tau == M2.T
			}
			flexibly connected to upper_arm_link
			pose {
				x = 0.0
				y = SHOULDER_RADIUS
				z = 0.0
				roll = 0.0
				pitch = 0.0
				yaw = 0.0
			}
		}
		sref FSJ2 = ForceSensor
		sref VSJ2 = VelocitySensor
		sref TSJ2 = TorqueSensor
		sref PSJ2 = PositionSensor
		pose {
			x = 0.0
			y = 0.0 //-0.13387
			z = 0.089159
			roll = 0.0
			pitch = 0.0
			yaw = 0.0
		}
	}
	local link upper_arm_link {
		def {
		inertial information {
				mass MASS2 kg
				pose {
					x = 0.0
					y = -0.024201
					z = 0.2125
					roll = 0.0
					pitch = 0.0
					yaw = 0.0
				}
			}
		}
		local body upper_arm_link_collision {
			def {
				cylinder ( radius = UPPERARM_RADIUS , length = UPPER_ARM_LINK_LENGTH )
			}
			pose {
				x = 0.0
				y = 0.0
				z = UPPER_ARM_LINK_LENGTH/2 - SHOULDER_LINK_LENGTH/2 //0.2125
				roll = 0.0
				pitch = 0.0
				yaw = 0.0
			}
		}
		jref elbow_joint = Revolute {
			annotation Revolute  {
				axis=Axis{
					xyz = (|0,1,0|)
					dynamics = Dynamics {
						damping = 10
					}
					limit = Limit {
						lower = -2*PI
						upper = 2*PI
						velocity = PI/2
						effort = 1000
					}
				}
			}
		instantiation AXIS = (|0,1,0|)
			aref M3 = ServoMotor {
				relation elbow_joint.tau == M3.T
			}
			flexibly connected to forearm_link
			pose {
				x = 0.0
				y = -UPPERARM_RADIUS
				z = (UPPER_ARM_LINK_LENGTH-2*SHOULDER_RADIUS)
				roll = 0.0
				pitch = 0.0
				yaw = 0.0
			}
		}
		sref FSJ3 = ForceSensor
		sref VSJ3 = VelocitySensor
		sref TSJ3 = TorqueSensor
		sref PSJ3 = PositionSensor
		pose {
			x = 0.0
			y = 0.13585
			z = 0.089159
			roll = PI
			pitch = PI/2
			yaw = PI
		}
	}
	
	local link forearm_link {
		def {
		inertial information {
				mass MASS3 kg
			}
		}
		local body forearm_link_collision {
			def {
				cylinder ( radius = FOREARM_RADIUS , length = FOREARM_LINK_LENGTH-0.116 ) //shorter to avoid self-collision
			}
			pose {
				x = 0.0
				y = 0.0
				z =  FOREARM_LINK_LENGTH/2 - 0.116
				roll = 0.0
				pitch = 0.0
				yaw = 0.0
			}
		}
		jref wrist_1_joint = Revolute {
			annotation Revolute  {
				axis=Axis{
					xyz = (|0,1,0|)
					dynamics = Dynamics {
						damping = 10
					}
					limit = Limit {
						lower = -2*PI
						upper = 2*PI
						velocity = PI/2
						effort = 1000
					}
				}
			}
		instantiation AXIS = (|0,1,0|)
			aref M4 = ServoMotor {
				relation wrist_1_joint.tau == M4.T
			}
			flexibly connected to wrist_1_link
			pose {
				x = 0.0
				y = 0.0 //2*FOREARM_RADIUS
				z = (FOREARM_LINK_LENGTH-2.5*FOREARM_RADIUS)
				roll = 0.0
				pitch = 0.0
				yaw = 0.0
			}
		}
		sref FSJ4 = ForceSensor
		sref VSJ4 = VelocitySensor
		sref TSJ4 = TorqueSensor
		sref PSJ4 = PositionSensor
		pose {
			x = 0.425
			y = 0.01615
			z = 0.089159
			roll = PI
			pitch = PI/2
			yaw = PI
		}
	}
	local link wrist_1_link {
		def {
		inertial information {
				mass MASS4 kg
			}
		}
		local body wrist_1_link_collision {
			def {
				cylinder ( radius = WRIST1_RADIUS , length = WRIST1_LINK_LENGTH )
			}
			pose {
				x = 0.0
				y = 0.0
				z = WRIST1_LINK_LENGTH/2 - FOREARM_RADIUS - 0.015
				roll = PI/2
				pitch = 0.0
				yaw = 0.0
			}
		}
		jref wrist_2_joint = Revolute {
			annotation Revolute  {
				axis=Axis{
					xyz = (|0,0,-1|)
					dynamics = Dynamics {
						damping = 10
					}
					limit = Limit {
						lower = -2*PI
						upper = 2*PI
						velocity = PI/2
						effort = 1000
					}
				}
			}
		instantiation AXIS = (|0,0,-1|)
			aref M5 = ServoMotor {
				relation wrist_2_joint.tau == M5.T
			}
			flexibly connected to wrist_2_link
			pose {
				x = 0.0
				y = WRIST1_LINK_LENGTH-WRIST2_RADIUS/6
				z = WRIST1_RADIUS
				roll = 0.0
				pitch = 0.0
				yaw = 0.0
			}
		}
		sref FSJ5 = ForceSensor
		sref VSJ5 = VelocitySensor
		sref TSJ5 = TorqueSensor
		sref PSJ5 = PositionSensor
		pose {
			x = 0.81725
			y = 0.01615
			z = 0.089159
			roll = PI
			pitch = 0.0
			yaw = PI
		}
	}
	local link wrist_2_link {
		def {
		inertial information {
				mass MASS5 kg
			}
		}
		local body wrist_2_link_collision {
			def {
				cylinder ( radius = WRIST2_RADIUS , length = WRIST2_LINK_LENGTH )
			}
			pose {
				x = 0.0
				y = 0.0
				z = WRIST2_LINK_LENGTH/2 -0.06
				roll = 0.0
				pitch = 0.0
				yaw = 0.0
			}
		}
		jref wrist_3_joint = Revolute {
			annotation Revolute  {
				axis=Axis{
					xyz = (|0,1,0|)
					dynamics = Dynamics {
						damping = 10
					}
					limit = Limit {
						lower = -2*PI
						upper = 2*PI
						velocity = PI/2
						effort = 1000
					}
				}
			}
		instantiation AXIS = (|0,1,0|)
			aref M6 = ServoMotor {
				relation wrist_3_joint.tau == M6.T
			}
			flexibly connected to wrist_3_link
			pose {
				x = 0.0
				y = WRIST2_RADIUS
				z = WRIST2_LINK_LENGTH
				roll = 0.0
				pitch = 0.0
				yaw = 0.0
			}
		}
		sref FSJ6 = ForceSensor
		sref VSJ6 = VelocitySensor
		sref TSJ6 = TorqueSensor
		sref PSJ6 = PositionSensor
		pose {
			x = 0.81725
			y = 0.10915
			z = 0.089159
			roll = PI
			pitch = 0.0
			yaw = PI
		}
	}
	local link wrist_3_link {
		fixed to link_2fg7_base in Gripper
		def {
		inertial information {
				mass MASS6 kg
			}
		}
		local body wrist_3_link_collision {
			def {
				cylinder ( radius = WRIST3_RADIUS , length = WRIST3_ARM_LINK_LENGTH )
			}
			pose {
				x = 0.0
				y = 0.0
				z = WRIST3_ARM_LINK_LENGTH/2 - WRIST2_RADIUS/2
				roll = PI/2
				pitch = 0.0
				yaw = 0.0
			}
		}
		pose {
			x = 0.81725
			y = 0.10915
			z = -0.005491
			roll = PI
			pitch = 0.0
			yaw = PI
		}
	}
	part Gripper = Gripper {
		
	}
	
	

}

pmodel Gripper {
	//From rest of model TODO need to ensure information is not duplicated!
	const WRIST3_RADIUS: real = 0.075/2
	const PI: real = 3.1415	
	// OnRobot 2FG7 gripper
	const GRIPPER_BODY_LENGTH: real = 0.071
	const GRIPPER_BODY_WIDTH: real = 0.09
	const GRIPPER_BODY_HEIGHT: real = 0.1445
	const GRIPPER_FINGER_LENGTH: real = 0.032
	const GRIPPER_FINGER_WIDTH: real = 0.005
	const GRIPPER_FINGER_HEIGHT: real = 0.045	
	const GRIP_WIDTH_MAX: real = 0.073
	const GRIP_WIDTH_MIN: real = 0.035
	const GRIPPER_MASS: real = 1.1
	local link link_2fg7_base {
		def {
		inertial information {
				mass 1.2646523179240972 kg
			}
		}
		local body link_2fg7_box {
			def {
				box (length = GRIPPER_BODY_LENGTH, width = GRIPPER_BODY_WIDTH, height = GRIPPER_BODY_HEIGHT )
			}
			pose {
				x = 0.0
				y = 0.0
				z = 0.0
				roll = 0.0
				pitch = 0.0
				yaw = 0.0
			} 
		}
		pose {
			x = 0.81725 
			y = 0.10915 + WRIST3_RADIUS*3
			z = -0.005491
			roll = -PI/2
			pitch = 0.0
			yaw = 0.0
		}
		aref GR1 = Gripper //perhaps not needed if the finger joints are successfully added
		
		jref leftFingerGripper = Prismatic {
			annotation Prismatic  {
				axis=Axis{
					xyz = (|0,0,-1|)
					dynamics = Dynamics {
						damping = 1000
					}
					limit = Limit {
						lower = -2*PI
						upper = 2*PI
						velocity = 1
						effort = 1000
					}
				}
			}
		instantiation AXIS = (|0,0,-1|)
			aref leftFingerMotor = ServoMotor {
				relation leftFingerGripper.tau == leftFingerMotor.T
			}
			pose {
				x = 0.0
				y = -0.032239 
				z = GRIPPER_BODY_HEIGHT/2
				roll = -PI/2 //0.0
				pitch = 0.0
				yaw = 0.0
			}
			flexibly connected to leftFingerLink
		}
		sref FSLF = ForceSensor
		sref VSLF = VelocitySensor
		sref TSLF = TorqueSensor
		sref PSLF = PositionSensor
		
		jref rightFingerGripper = Prismatic {
			annotation Prismatic  {
				axis=Axis{
					xyz = (|0,0,1|)
					dynamics = Dynamics {
						damping = 1000
					}
					limit = Limit {
						lower = -2*PI
						upper = 2*PI
						velocity = 1
						effort = 1000
					}
				}
			}
		instantiation AXIS = (|0,0,1|)
			aref rightFingerMotor = ServoMotor {
				relation rightFingerGripper.tau == rightFingerMotor.T
			}
			
			pose {
				x = 0.0
				y = 0.032239
				z = GRIPPER_BODY_HEIGHT/2
				roll = -PI/2
				pitch = 0.0
				yaw = 0.0
			}
			flexibly connected to rightFingerLink
		}
		sref FSRF = ForceSensor
		sref VSRF = VelocitySensor
		sref TSRF = TorqueSensor
		sref PSRF = PositionSensor
	}
	
	
	local link rightFingerLink {
		def{
			inertial information {
				mass 0.023219383355922288 kg
			}
		}
		pose {
			x = 0.81725 
			y = 0.10915 - 0.029494 + WRIST3_RADIUS*2+GRIPPER_BODY_HEIGHT
			z = -0.005491 - 0.032239
			roll = -PI/2
			pitch = 0.0
			yaw = 0.0
		}
		
		local body rightFingerBody{
			def {
				box ( length = GRIPPER_FINGER_LENGTH, width = GRIPPER_FINGER_WIDTH, height = GRIPPER_FINGER_HEIGHT)
			}
			pose{
				x = 0.0
				y = 0.0
				z = 0.0
				roll = 0.0
				pitch = 0.0
				yaw = 0.0
			}
		}
		
	}
	
	local link leftFingerLink {
		def{
			inertial information {
				mass 0.023219383355922288 kg
			}
		}
		pose {
			x = 0.81725
			y = 0.10915- 0.029494 + WRIST3_RADIUS*2+GRIPPER_BODY_HEIGHT
			z = -0.005491 + 0.032239
			roll = -PI/2
			pitch = 0.0
			yaw = 0.0
		}
		
		local body leftFingerBody{
			def {
				box ( length = GRIPPER_FINGER_LENGTH, width = GRIPPER_FINGER_WIDTH, height = GRIPPER_FINGER_HEIGHT )
			}
			pose{
				x = 0.0
				y = 0.0
				z = 0.0
				roll = 0.0
				pitch = 0.0
				yaw = 0.0
			}
		}
		
		
	}
}actuator Gripper {
}

actuator ServoMotor {
	
	input dangle: real 
	input angular_vel: real //modified
	output T: real
	local Tm: real, Vemf: real, Tf: real 
	local V: real, i: real
	output theta: real, av: real, e: real
	
	const b: real, Ke: real, Kt: real
	const R: real, L: real
	const Kp: real, Ki: real, Kd: real
	
	//equation av == derivative(theta)
	equation av == angular_vel
	//if angular_vel == 0 then av == 0
	equation Tm == Kt*i
	equation Vemf == Ke*av
	equation Tf == b*av
	equation T == Tm - Tf
	equation V == i*R+L*derivative(i)+Vemf 
	equation e == dangle-theta //das - av
	equation V == Kp*e+Ki*integral(e,0,t)+Kd*derivative(e)
}
