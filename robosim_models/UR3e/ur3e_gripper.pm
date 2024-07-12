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

sensor AngularPositionSensor {
	input input_angle: real
	output output_angle: real
	equation input_angle == output_angle
}

sensor PositionSensor {
	input input_position: real
	output output_position: real
	equation input_position == output_position
}

pmodel ur3e_gripper {
	
	const PI: real = 3.1415	
	const BASE_RADIUS: real = 0.13/2
	const SHOULDER_RADIUS: real = 0.09/2
	const UPPERARM_RADIUS: real = 0.07/2
	const FOREARM_RADIUS: real = 0.06/2
	const WRIST1_RADIUS: real = 0.06/2
	const WRIST2_RADIUS: real = 0.06/2
	const WRIST3_RADIUS: real = 0.06/2
	
	const BASELEN: real = 0.0988
	const SHOULDER_LINK_LENGTH: real = 0.105
	const SHOULDER_LINK_OFFSET: real = 0.105
	const UPPER_ARM_LINK_LENGTH: real = 0.32
	const FOREARM_LINK_LENGTH: real = 0.28
	const WRIST1_LINK_LENGTH: real = 0.102
	const WRIST1_LINK_OFFSET: real = 0.09
	const WRIST2_LINK_LENGTH: real = 0.07
	const WRIST3_ARM_LINK_LENGTH: real = 0.041
	
	const MASS_BASE: real = 2.4 //(11.2kg - masses)
	const MASS1: real = 1.98
	const MASS2: real = 3.4445
	const MASS3: real = 1.437
	const MASS4: real = 0.871
	const MASS5: real = 0.805
	const MASS6: real = 0.261

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
				yaw = 0.0//
			}
		}
		jref shoulder_pan_joint = Revolute {
			instantiation AXIS = (|0,0,1|)
			aref M1 = ServoMotor {
				relation shoulder_pan_joint.tau == M1.T
			}
			flexibly connected to shoulder_link
			pose {
				x = 0.0
				y = 0.0
				z = BASELEN
				roll = 0.0
				pitch = 0.0
				yaw = 0.0
			}
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
			
		}
		sref FSJ1 = ForceSensor
		sref VSJ1 = VelocitySensor
		sref TSJ1 = TorqueSensor
		sref APSJ1 = AngularPositionSensor
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
					y = 0.0
					z = -0.02
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
				y = 0.0
				z = SHOULDER_LINK_LENGTH/2 - BASELEN/2
				roll = 0.0
				pitch = 0.0
				yaw = PI/2
			}
		}
		jref shoulder_lift_joint = Revolute {
			instantiation AXIS = (|0,1,0|)//(|0,1,0|)
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
		}
		sref FSJ2 = ForceSensor
		sref VSJ2 = VelocitySensor
		sref TSJ2 = TorqueSensor
		sref APSJ2 = AngularPositionSensor
		pose {
			x = 0.0
			y = 0.0
			z = BASELEN
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
					x = 0.13
					y = 0.0
					z = 0.1157
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
				z = UPPER_ARM_LINK_LENGTH/2 - SHOULDER_LINK_LENGTH/2
				roll = 0.0
				pitch = 0.0
				yaw = 0.0
			}
		}
		jref elbow_joint = Revolute {
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
		}
		sref FSJ3 = ForceSensor
		sref VSJ3 = VelocitySensor
		sref TSJ3 = TorqueSensor
		sref APSJ3 = AngularPositionSensor
		pose {
			x = 0.0
			y = SHOULDER_LINK_OFFSET
			z = BASELEN
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
				cylinder ( radius = FOREARM_RADIUS , length = FOREARM_LINK_LENGTH-FOREARM_RADIUS) //shorter to avoid self-collision
			}
			pose {
				x = 0.0
				y = 0.0
				z =  FOREARM_LINK_LENGTH/2 - FOREARM_RADIUS
				roll = 0.0
				pitch = 0.0
				yaw = 0.0
			}
		}
		jref wrist_1_joint = Revolute {
			instantiation AXIS = (|0,1,0|)
			aref M4 = ServoMotor {
				relation wrist_1_joint.tau == M4.T
			}
			flexibly connected to wrist_1_link
			pose {
				x = 0.0
				y = 0.0
				z = FOREARM_LINK_LENGTH
				roll = 0.0
				pitch = 0.0
				yaw = 0.0
			}
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
		}
		sref FSJ4 = ForceSensor
		sref VSJ4 = VelocitySensor
		sref TSJ4 = TorqueSensor
		sref APSJ4 = AngularPositionSensor
		pose {
			x = UPPER_ARM_LINK_LENGTH - 0.1
			y = SHOULDER_LINK_OFFSET - WRIST1_LINK_OFFSET
			z = BASELEN
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
				z = 0.0//WRIST1_LINK_LENGTH/2 - WRIST2_RADIUS// - 0.015
				roll = PI/2
				pitch = 0.0
				yaw = 0.0
			}
		}
		jref wrist_2_joint = Revolute {
			instantiation AXIS = (|0,0,-1|)
			aref M5 = ServoMotor {
				relation wrist_2_joint.tau == M5.T
			}
			flexibly connected to wrist_2_link
			pose {
				x = 0.0
				y = WRIST1_LINK_LENGTH
				z = WRIST1_RADIUS
				roll = 0.0
				pitch = 0.0
				yaw = 0.0
			}
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
		}
		sref FSJ5 = ForceSensor
		sref VSJ5 = VelocitySensor
		sref TSJ5 = TorqueSensor
		sref APSJ5 = AngularPositionSensor
		pose {
			x = UPPER_ARM_LINK_LENGTH - 0.1   + FOREARM_LINK_LENGTH
			y = SHOULDER_LINK_OFFSET - WRIST1_LINK_OFFSET
			z = BASELEN
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
				z = WRIST2_LINK_LENGTH/2 - WRIST2_RADIUS
				roll = 0.0
				pitch = 0.0
				yaw = 0.0
			}
		}
		jref wrist_3_joint = Revolute {
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
		}
		sref FSJ6 = ForceSensor
		sref VSJ6 = VelocitySensor
		sref TSJ6 = TorqueSensor
		sref APSJ6 = AngularPositionSensor
		pose {
			x = UPPER_ARM_LINK_LENGTH - 0.1   + FOREARM_LINK_LENGTH
			y = SHOULDER_LINK_OFFSET - WRIST1_LINK_OFFSET + WRIST1_LINK_LENGTH
			z = BASELEN
			roll = PI
			pitch = 0.0
			yaw = PI
		}
	}
	local link wrist_3_link {
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
			x = UPPER_ARM_LINK_LENGTH - 0.1   + FOREARM_LINK_LENGTH
			y = SHOULDER_LINK_OFFSET - WRIST1_LINK_OFFSET + WRIST1_LINK_LENGTH
			z = BASELEN - WRIST2_LINK_LENGTH
			roll = PI
			pitch = 0.0
			yaw = PI
		}
	}
}

actuator Gripper {
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