interface MoveI {
	movejoint( av : real)
	movecartesian( x:real, y:real, z:real, v : real)
	movediscrete( X : int , Y : int, Z: int, v:real)
	stop()
	reset()
	setvelocity(v:real)
	var feasible : boolean
	var completed : boolean
}

interface CommandI{
	event moveDiscreteCommand
	event feasibleMoveDiscreteCommand
	event nonfeasibleMoveDiscreteCommand
	event openGripperCommand
	event closeGripperCommand
	event moveCompleted
	event robotStopped
	event gripperOpened
	event gripperClosed
}

interface CollisionI {
	event collision
}

interface GripperI {
	pick( diameter : real , speed : real, force : real)
	place( diameter : real , speed : real, force : real)
}

controller DiscreteGrippingArmMovement {
	cycleDef cycle == 1
	requires MoveI
	requires GripperI
	uses CollisionI
	uses CommandI
	sref sm = SimDiscreteGrippingArmMovement
	
}

stm SimDiscreteGrippingArmMovement {
	cycleDef cycle == 1
	const PI: real, lv : real, av : real
	const TARGET_X:int, TARGET_Y:int, TARGET_Z:int 
	const MOTION_VEL:real
	const opening_diameter:real, opening_speed:real, opening_force:real 
	const closing_diameter:real, closing_speed:real, closing_force:real 
	input context {
		uses CollisionI
		uses CommandI
	}
	output context {
		requires MoveI
		requires GripperI
	} 
	
	initial i1 
	
	state Idle {
	}
	
	state ArmMove{
		entry $movediscrete(TARGET_X , TARGET_Y,TARGET_Z,MOTION_VEL)
	}
	
	state ArmStop{
		entry $stop()
	}
	
	state GripperClose{
		entry $pick( closing_diameter , closing_speed , closing_force )
	}
	
	state GripperOpen{
		entry $place( opening_diameter , opening_speed , opening_force)
	}
	
	state ArmMoving {
		
	}
	
	state ArmStopping {
		
	}
	
	state GripperClosing {
		
	}
	
	state GripperOpening {
		
	}
	
	/*state ArmMoving {
		entry $movediscrete(TARGET_X , TARGET_Y,TARGET_Z,MOTION_VEL)
	}
	
	state ArmStopping {
		entry $stop()
	}
	
	state GripperClosing {
		entry $pick( closing_diameter , closing_speed , closing_force )
	}
	
	state GripperOpening {
		entry $place( opening_diameter , opening_speed , opening_force)
	}*/
	
	junction J2
	
	junction J3
	
	junction J4
	
	junction J5
	
	transition t1 {
		from i1
		to Idle
	}
	
	transition t2 {
		from Idle to ArmMove
		condition $moveDiscreteCommand
	}
	
	transition t2_1 {
		from ArmMove to ArmMoving
		condition $feasibleMoveDiscreteCommand
	}
	
	transition t2_2 {
		from ArmMoving to J2
		exec 
	}
	
	transition t2_3 {
		from J2 to ArmMoving
		condition not ($collision \/ $moveCompleted)
	}
	
	transition t2_4 {
		from J2 to ArmStop
		condition $collision \/ $moveCompleted
	}
	
	transition t2_nonfeasible {
		from ArmMove to Idle
		condition $nonfeasibleMoveDiscreteCommand
	}
	
	transition t3 {
		from ArmStop to ArmStopping
	}
	
	transition t3_1 {
		from ArmStopping to J3
		exec
	}
	
	transition t3_2 {
		from J3 to ArmStopping
		condition not $robotStopped
	}
	
	transition t3_3 {
		from J3 to Idle
		condition $robotStopped
	}
	
	transition t4 {
		from Idle to GripperClose
		condition $closeGripperCommand
	}
	
	transition t4_1 {
		from GripperClose to GripperClosing
	}
	
	transition t4_2 {
		from GripperClosing to J4
		exec
	}
	
	transition t4_3 {
		from J4 to GripperClosing
		condition not $gripperClosed
	}
	
	transition t4_4 {
		from J4 to Idle
		condition $gripperClosed
	}
	
	transition t5 {
		from Idle to GripperOpen
		condition $openGripperCommand
	}
	
	transition t5_1 {
		from GripperOpen to GripperOpening
	}
	
	transition t5_2 {
		from GripperOpening to J5
		exec
	}
	
	transition t5_3 {
		from J5 to GripperOpening
		condition not $gripperOpened
	}
	
	transition t5_4 {
		from J5 to Idle
		condition $gripperOpened
	}
	
	
	/*transition t1 {
		from i1
		to Idle
	}
	
	transition t2 {
		from Idle to ArmMoving
		condition $feasibleMoveDiscreteCommand
		//condition not $collision
	}
	
	transition t2_nonfeasible {
		from Idle to Idle
		condition $nonfeasibleMoveDiscreteCommand
	}
	
	transition t3 {
		from ArmMoving to ArmStopping
		condition $moveCompleted
	}
	
	transition t3_collision {
		from ArmMoving to ArmStopping
		condition $collision
	}
	
	transition t4 {
		from ArmStopping to Idle
		condition $robotStopped
	}
	
	transition t5 {
		from Idle to GripperClosing
		condition $closeGripperCommand
	}
	
	transition t6 {
		from GripperClosing to Idle
		condition $gripperClosed
	}
	
	transition t7 {
		from Idle to GripperOpening
		condition $openGripperCommand
	}
	
	transition t8 {
		from GripperOpening to Idle
		condition $gripperOpened
	}*/
}

module DiscreteGrippingArm {
	cycleDef cycle == 1
	robotic platform RoboticArmGripper {
		provides MoveI
		provides GripperI
		uses CollisionI
		uses CommandI
	}

	cref cm = DiscreteGrippingArmMovement
	connection RoboticArmGripper on collision to cm on collision ( _async )
	connection RoboticArmGripper on moveDiscreteCommand to cm on moveDiscreteCommand ( _async )
	connection RoboticArmGripper on feasibleMoveDiscreteCommand to cm on feasibleMoveDiscreteCommand ( _async )
	connection RoboticArmGripper on nonfeasibleMoveDiscreteCommand to cm on nonfeasibleMoveDiscreteCommand ( _async )
	connection RoboticArmGripper on moveCompleted to cm on moveCompleted ( _async )
	connection RoboticArmGripper on robotStopped to cm on robotStopped ( _async )
	connection RoboticArmGripper on closeGripperCommand to cm on closeGripperCommand ( _async )
	connection RoboticArmGripper on gripperClosed to cm on gripperClosed ( _async )
	connection RoboticArmGripper on openGripperCommand to cm on openGripperCommand ( _async )
	connection RoboticArmGripper on gripperOpened to cm on gripperOpened ( _async )
}
