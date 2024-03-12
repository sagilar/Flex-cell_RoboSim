#![allow(unused_parens)]
#![allow(unused_imports)]
#![allow(dead_code)]
#![allow(unused_variables)]
#![allow(unused_mut)]
#![allow(non_snake_case)]
#![allow(non_camel_case_types)]

use nalgebra::{SVector,SMatrix};
use strum::Display;
use std::thread;
use std::sync::mpsc;
use std::sync::mpsc::{SyncSender, Receiver};
use std::sync::Barrier;
use std::sync::Arc;
use std::time::Duration;
use rand::prelude::*;
// These are only used for the interaction with the user and should be encapsulated in
// whatever extension mechanism that will be developed to allow integration with different
// simulators.
use std::io::Write;
use std::io::Read;
use std::rc::Rc;
use std::cell::RefCell;

use log::debug;
use simplelog::*;
use std::fs::File;

use serde::{Deserialize, Serialize};
use serde_json::Result;
use clap::{App,Arg};

#[derive(PartialEq,Display,Debug,Clone,Serialize,Deserialize)]
enum M_DiscreteGrippingArm_input {
	gripperClosed,
	moveCompleted,
	robotStopped,
	feasibleMoveDiscreteCommand,
	nonfeasibleMoveDiscreteCommand,
	closeGripperCommand,
	openGripperCommand,
	moveDiscreteCommand(MovementArgs),
	collision,
	gripperOpened,
	_done_,
	_terminate_,
}
#[derive(PartialEq,Display,Debug,Clone,Serialize,Deserialize)]
enum M_DiscreteGrippingArm_output {
	pick(f32,f32,f32),
	stop,
	reset,
	setvelocity(f32),
	movediscrete(i32,i32,i32,f32),
	place(f32,f32,f32),
	movecartesian(f32,f32,f32,f32),
	movejoint(f32),
	_done_,
}
#[derive(PartialEq,Display,Debug,Clone,Serialize,Deserialize)]
enum STATUS {
	ENTER_STATE,
	ENTER_CHILDREN,
	EXECUTE_STATE,
	EXIT_CHILDREN,
	EXIT_STATE,
	INACTIVE,
}
#[derive(PartialEq,Display,Debug,Clone,Serialize,Deserialize)]
enum RESULT {
	WAIT,
	CONT,
}
#[derive(PartialEq,Display,Debug,Clone,Serialize,Deserialize)]
enum STATES_sm {
	NONE,
	Idle,
	ArmMove,
	ArmStop,
	GripperClose,
	GripperOpen,
	ArmMoving,
	ArmStopping,
	GripperClosing,
	GripperOpening,
}
#[derive(PartialEq,Display,Debug,Clone,Serialize,Deserialize)]
enum C_cm_output {
	setvelocity(f32),
	pick(f32,f32,f32),
	place(f32,f32,f32),
	movediscrete(i32,i32,i32,f32),
	stop,
	reset,
	movejoint(f32),
	movecartesian(f32,f32,f32,f32),
	_done_,
}
#[derive(PartialEq,Display,Debug,Clone,Serialize,Deserialize)]
enum sm_output {
	place(f32,f32,f32),
	movecartesian(f32,f32,f32,f32),
	movejoint(f32),
	reset,
	setvelocity(f32),
	movediscrete(i32,i32,i32,f32),
	pick(f32,f32,f32),
	stop,
	_done_,
}
#[derive(PartialEq,Display,Debug,Clone,Serialize,Deserialize)]
enum TRANSITIONS_sm {
	NONE,
	sm_t1_1,
	sm_t3_1,
	sm_t2_3,
	sm_t4,
	sm_t5_2,
	sm_t2_nonfeasible,
	sm_t3_2,
	sm_t4_2,
	sm_t3,
	sm_t5_1,
	sm_t5_3,
	sm_t2,
	sm_t2_4,
	sm_t2_1,
	sm_t5,
	sm_t4_1,
	sm_t4_3,
	sm_t1,
	sm_t3_3,
	sm_t2_2,
	sm_t5_4,
	sm_t4_4,
}
#[derive(PartialEq,Display,Debug,Clone,Serialize,Deserialize)]
enum C_cm_input {
	feasibleMoveDiscreteCommand,
	closeGripperCommand,
	gripperOpened,
	collision,
	moveDiscreteCommand(MovementArgs),
	openGripperCommand,
	nonfeasibleMoveDiscreteCommand,
	moveCompleted,
	robotStopped,
	gripperClosed,
	_done_,
	_terminate_,
}
#[derive(PartialEq,Display,Debug,Clone,Serialize,Deserialize)]
enum sm_input {
	collision,
	moveDiscreteCommand(MovementArgs),
	openGripperCommand,
	closeGripperCommand,
	moveCompleted,
	feasibleMoveDiscreteCommand,
	nonfeasibleMoveDiscreteCommand,
	gripperOpened,
	gripperClosed,
	robotStopped,
	_done_,
	_terminate_,
}

#[derive(PartialEq,parse_display::Display,Debug,Clone,Copy,Serialize,Deserialize)]
#[display("(|{targetz}, {targety}, {targetx}|)")]
struct MovementArgs {
	#[display("targetz -> {:?}")]
	targetz:i32,
	#[display("targety -> {:?}")]
	targety:i32,
	#[display("targetx -> {:?}")]
	targetx:i32,
}
#[derive(PartialEq,parse_display::Display,Debug,Clone,Copy,Serialize,Deserialize)]
#[display("(|{opening_speed}, {lv}, {closing_diameter}, {closing_speed}, {MOTION_VEL}, {opening_diameter}, {av}, {TARGET_Z}, {TARGET_Y}, {PI}, {opening_force}, {closing_force}, {TARGET_X}, {margs}|)")]
struct sm_memory {
	#[display("opening_speed -> {:?}")]
	opening_speed:f32,
	#[display("lv -> {:?}")]
	lv:f32,
	#[display("closing_diameter -> {:?}")]
	closing_diameter:f32,
	#[display("closing_speed -> {:?}")]
	closing_speed:f32,
	#[display("MOTION_VEL -> {:?}")]
	MOTION_VEL:f32,
	#[display("opening_diameter -> {:?}")]
	opening_diameter:f32,
	#[display("av -> {:?}")]
	av:f32,
	#[display("TARGET_Z -> {:?}")]
	TARGET_Z:i32,
	#[display("TARGET_Y -> {:?}")]
	TARGET_Y:i32,
	#[display("PI -> {:?}")]
	PI:f32,
	#[display("opening_force -> {:?}")]
	opening_force:f32,
	#[display("closing_force -> {:?}")]
	closing_force:f32,
	#[display("TARGET_X -> {:?}")]
	TARGET_X:i32,
	#[display("margs -> {:?}")]
	margs:MovementArgs,
}
#[derive(PartialEq,parse_display::Display,Debug,Clone,Copy,Serialize,Deserialize)]
#[display("(|{collision}, {moveDiscreteCommand}, {moveDiscreteCommand_value}, {openGripperCommand}, {closeGripperCommand}, {moveCompleted}, {feasibleMoveDiscreteCommand}, {nonfeasibleMoveDiscreteCommand}, {gripperOpened}, {gripperClosed}, {robotStopped}, {_transition_}|)")]
struct sm_inputstate {
	#[display("collision -> {:?}")]
	collision:bool,
	#[display("moveDiscreteCommand -> {:?}")]
	moveDiscreteCommand:bool,
	#[display("moveDiscreteCommand_value -> {:?}")]
	moveDiscreteCommand_value:MovementArgs,
	#[display("openGripperCommand -> {:?}")]
	openGripperCommand:bool,
	#[display("closeGripperCommand -> {:?}")]
	closeGripperCommand:bool,
	#[display("moveCompleted -> {:?}")]
	moveCompleted:bool,
	#[display("feasibleMoveDiscreteCommand -> {:?}")]
	feasibleMoveDiscreteCommand:bool,
	#[display("nonfeasibleMoveDiscreteCommand -> {:?}")]
	nonfeasibleMoveDiscreteCommand:bool,
	#[display("gripperOpened -> {:?}")]
	gripperOpened:bool,
	#[display("gripperClosed -> {:?}")]
	gripperClosed:bool,
	#[display("robotStopped -> {:?}")]
	robotStopped:bool,
	#[display("_transition_ -> {:?}")]
	_transition_:TRANSITIONS_sm,
}
#[derive(PartialEq,parse_display::Display,Debug,Clone,Copy,Serialize,Deserialize)]
#[display("(|{done}, {state}, {target_state}, {status}, {en_SimDiscreteGrippingArmMovement_ArmStop_1_done}, {en_SimDiscreteGrippingArmMovement_ArmStop_1_counter}, {en_SimDiscreteGrippingArmMovement_GripperClose_1_done}, {en_SimDiscreteGrippingArmMovement_GripperClose_1_counter}, {en_SimDiscreteGrippingArmMovement_ArmMove_1_done}, {en_SimDiscreteGrippingArmMovement_ArmMove_1_counter}, {en_SimDiscreteGrippingArmMovement_GripperOpen_1_done}, {en_SimDiscreteGrippingArmMovement_GripperOpen_1_counter}|)")]
struct sm_state {
	#[display("done -> {:?}")]
	done:bool,
	#[display("state -> {:?}")]
	state:STATES_sm,
	#[display("target_state -> {:?}")]
	target_state:STATES_sm,
	#[display("status -> {:?}")]
	status:STATUS,
	#[display("en_SimDiscreteGrippingArmMovement_ArmStop_1_done -> {:?}")]
	en_SimDiscreteGrippingArmMovement_ArmStop_1_done:bool,
	#[display("en_SimDiscreteGrippingArmMovement_ArmStop_1_counter -> {:?}")]
	en_SimDiscreteGrippingArmMovement_ArmStop_1_counter:i32,
	#[display("en_SimDiscreteGrippingArmMovement_GripperClose_1_done -> {:?}")]
	en_SimDiscreteGrippingArmMovement_GripperClose_1_done:bool,
	#[display("en_SimDiscreteGrippingArmMovement_GripperClose_1_counter -> {:?}")]
	en_SimDiscreteGrippingArmMovement_GripperClose_1_counter:i32,
	#[display("en_SimDiscreteGrippingArmMovement_ArmMove_1_done -> {:?}")]
	en_SimDiscreteGrippingArmMovement_ArmMove_1_done:bool,
	#[display("en_SimDiscreteGrippingArmMovement_ArmMove_1_counter -> {:?}")]
	en_SimDiscreteGrippingArmMovement_ArmMove_1_counter:i32,
	#[display("en_SimDiscreteGrippingArmMovement_GripperOpen_1_done -> {:?}")]
	en_SimDiscreteGrippingArmMovement_GripperOpen_1_done:bool,
	#[display("en_SimDiscreteGrippingArmMovement_GripperOpen_1_counter -> {:?}")]
	en_SimDiscreteGrippingArmMovement_GripperOpen_1_counter:i32,
}

fn main() -> std::result::Result<(), String> {
	let matches = App::new("SimCacheCons")
						.version("1.0.0")
						.about("Simulation of RoboSim model SimCacheCons")
						.arg(Arg::with_name("record")
							.short('r')
							.long("record")
							.value_name("FILE")
							.help("Records the state of a simulation in a file.")
							.takes_value(true)
						).arg(Arg::with_name("replay")
							.short('p')
							.long("replay")
							.value_name("FILE")
							.help("Replays the simulation with the contents of a file")
							.takes_value(true)
						).get_matches();
	
	let _ = WriteLogger::init(
		LevelFilter::Trace, Config::default(), File::create("test.log").unwrap());
	
	let _args: Vec<String> = std::env::args().collect();
    if _args.len() <= 0 {
        eprintln!("error: Not enough arguments.");
            std::process::exit(1);
    }
    
    // TODO: This record and replay mechanism needs to be generalised for multiple
    // statemachine and controllers. Currently, only the recording functionality
    // is implemented and only records data for one state machine.
    
    let replay_value = matches.value_of("replay").and_then(|s|Some(s.to_string()));
	let record_value = matches.value_of("record").and_then(|s|Some(s.to_string()));

	let replayFile = if let Some(s) = replay_value {
		let file = std::fs::File::create(s);
		match file {
			Ok(f) => Some(f),
			Err(e) => { eprintln!("{}", e); std::process::exit(1) }
		}
	} else {
		None
	};

	let (send_data, recv_data)= mpsc::channel::<Option<String>>();
	
	let recording = record_value.is_some();

	let recorder = {
		let mut code = 0;
		let mut first = true;
		thread::spawn(move || {
			let mut recordFile = if let Some(s) = record_value {
				let mut file = std::fs::OpenOptions::new()
					.write(true)
					.append(false)
					.create(true)
					.truncate(true)
					.open(s);
				 match file {
					Ok(mut f) => { Some(f) },
					Err(e) => { eprintln!("{}", e); std::process::exit(1) }
				}
			} else {
				None
			};
			
			// TODO: Uncomment some of the commented sections below to 
			// record the state at each cycle. Also, comment the final
			// treatment of lastState.
			// This was changed to avoid writing to a file too much.
			// For replaying, the final state is all that is needed.
			// Adding extra information about the inputs and output
			// would be beneficial to reproduce the interactions
			// that led to the final state.
			
			// if let Some(file) = &mut recordFile {
			// 	file.write_all(b"[\n").expect("Writing to record file");
			// }
			let mut terminate = false;
			let mut lastState = None;
			while !terminate {
				let value = recv_data.recv();
				match value {
					Ok(v) => {
						match v {
							Some(state) => {
								lastState = Some(state);
								// if let Some(file) = &mut recordFile {
								// 	if !first {
								// 		file.write_all(b",\n").expect("Failed to write to record file");
								// 	} else {
								// 		first = false;
								// 	}
								// 	file.write_all(state.as_bytes()).expect("Failed to write to record file");
								// }
							},
							None => {
								terminate = true;
							}
						}

					},
					Err(e) => {
						terminate = true;
						code = 1;
						eprintln!("Failed to receive debug value.");
					}
				}
			}

			// if let Some(file) = &mut recordFile {
			// 	file.write_all(b"\n]\n").expect("Writing to record file");
			// }

			println!("\nTerminating application.");

			if let Some(file) = &mut recordFile {
				if let Some(state) = lastState {
					println!("Saving last state");
					file.write_all(state.as_bytes()).expect("Failed to write to record file");
				} else {
					println!("No state to save");
				}
				file.sync_all().expect("Failed to synchronise recorded file.");
			}

			std::process::exit(code);
		})
	};
	
	let ctrlc_send = send_data.clone();
	ctrlc::set_handler(move || {
		ctrlc_send.send(None).expect("Failed to send termination signal.");
	}).expect("Failed to setup ctrl-c handler.");
	
	// Module channel declarations;
	let (send_start_DiscreteGrippingArm, recv_start_DiscreteGrippingArm) = mpsc::sync_channel(0);
	let (send_end_DiscreteGrippingArm, recv_end_DiscreteGrippingArm) = mpsc::sync_channel(0);
	let (send_start_cm, recv_start_cm) = mpsc::sync_channel(0);
	let (send_end_cm, recv_end_cm) = mpsc::sync_channel(0);
	let (send_start_sm, recv_start_sm) = mpsc::sync_channel(0);
	let (send_end_sm, recv_end_sm) = mpsc::sync_channel(0);
	// Instantiate threads;
	let control_thread = {
	                       	thread::spawn(move || {
	                     		let mut terminate__: bool = false;
	                     		while !terminate__ {
	                     			{
	                     				let mut inputdone: bool = false;
	                     				while !inputdone {
	                     					{
	                     						let _s0: String;
	                     						_s0 = format!("{}", "Enter an event:");
	                     						print!("{}", _s0);
	                     						std::io::stdout().flush().unwrap();
	                     					}
	                     					let mut _event_: String;
	                     					let mut _temp_ = String::new();
	                     					std::io::stdin().read_line(&mut _temp_).expect("Failed to read input.");
	                     					_event_ = _temp_.as_str().trim().to_string();
	                     					match (_event_).as_str() {
	                     						"nonfeasibleMoveDiscreteCommand" => {
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "Found event nonfeasibleMoveDiscreteCommand");
	                     								println!("{}", _s0);	std::io::stdout().flush().unwrap();
	                     							}
	                     							send_start_DiscreteGrippingArm.send(M_DiscreteGrippingArm_input::nonfeasibleMoveDiscreteCommand).unwrap();
	                     						},
	                     						"closeGripperCommand" => {
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "Found event closeGripperCommand");
	                     								println!("{}", _s0);	std::io::stdout().flush().unwrap();
	                     							}
	                     							send_start_DiscreteGrippingArm.send(M_DiscreteGrippingArm_input::closeGripperCommand).unwrap();
	                     						},
	                     						"" => {
	                     							send_start_DiscreteGrippingArm.send(M_DiscreteGrippingArm_input::_done_).unwrap();
	                     							inputdone = true;
	                     						},
	                     						"collision" => {
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "Found event collision");
	                     								println!("{}", _s0);	std::io::stdout().flush().unwrap();
	                     							}
	                     							send_start_DiscreteGrippingArm.send(M_DiscreteGrippingArm_input::collision).unwrap();
	                     						},
	                     						"gripperOpened" => {
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "Found event gripperOpened");
	                     								println!("{}", _s0);	std::io::stdout().flush().unwrap();
	                     							}
	                     							send_start_DiscreteGrippingArm.send(M_DiscreteGrippingArm_input::gripperOpened).unwrap();
	                     						},
	                     						"feasibleMoveDiscreteCommand" => {
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "Found event feasibleMoveDiscreteCommand");
	                     								println!("{}", _s0);	std::io::stdout().flush().unwrap();
	                     							}
	                     							send_start_DiscreteGrippingArm.send(M_DiscreteGrippingArm_input::feasibleMoveDiscreteCommand).unwrap();
	                     						},
	                     						"robotStopped" => {
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "Found event robotStopped");
	                     								println!("{}", _s0);	std::io::stdout().flush().unwrap();
	                     							}
	                     							send_start_DiscreteGrippingArm.send(M_DiscreteGrippingArm_input::robotStopped).unwrap();
	                     						},
	                     						"openGripperCommand" => {
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "Found event openGripperCommand");
	                     								println!("{}", _s0);	std::io::stdout().flush().unwrap();
	                     							}
	                     							send_start_DiscreteGrippingArm.send(M_DiscreteGrippingArm_input::openGripperCommand).unwrap();
	                     						},
	                     						"gripperClosed" => {
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "Found event gripperClosed");
	                     								println!("{}", _s0);	std::io::stdout().flush().unwrap();
	                     							}
	                     							send_start_DiscreteGrippingArm.send(M_DiscreteGrippingArm_input::gripperClosed).unwrap();
	                     						},
	                     						"moveCompleted" => {
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "Found event moveCompleted");
	                     								println!("{}", _s0);	std::io::stdout().flush().unwrap();
	                     							}
	                     							send_start_DiscreteGrippingArm.send(M_DiscreteGrippingArm_input::moveCompleted).unwrap();
	                     						},
	                     						"moveDiscreteCommand" => {
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "Found event moveDiscreteCommand");
	                     								println!("{}", _s0);	std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "Enter value for event moveDiscreteCommand of type MovementArgs. Each attribute will be requested one at a time. ");
	                     								println!("{}", _s0);	std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let mut _value_: MovementArgs = MovementArgs {
	                     								                                	targetz: 0_i32,
	                     								                                	targety: 0_i32,
	                     								                                	targetx: 0_i32
	                     								                                };
	                     								{
	                     									{
	                     										let _s0: String;
	                     										_s0 = format!("{}", "Enter value for attribute targetz of type integer: ");
	                     										print!("{}", _s0);
	                     										std::io::stdout().flush().unwrap();
	                     									}
	                     									{
	                     										let mut _svalue_: String;
	                     										let mut _temp_ = String::new();
	                     										std::io::stdin().read_line(&mut _temp_).expect("Failed to read input.");
	                     										_svalue_ = _temp_.as_str().trim().to_string();
	                     										let mut _targetz_value_: i32 = 0_i32;
	                     										_targetz_value_ = (_svalue_).parse::<i32>().unwrap();
	                     										(_value_).targetz = _targetz_value_;
	                     									}
	                     								}
	                     								{
	                     									{
	                     										let _s0: String;
	                     										_s0 = format!("{}", "Enter value for attribute targety of type integer: ");
	                     										print!("{}", _s0);
	                     										std::io::stdout().flush().unwrap();
	                     									}
	                     									{
	                     										let mut _svalue_: String;
	                     										let mut _temp_ = String::new();
	                     										std::io::stdin().read_line(&mut _temp_).expect("Failed to read input.");
	                     										_svalue_ = _temp_.as_str().trim().to_string();
	                     										let mut _targety_value_: i32 = 0_i32;
	                     										_targety_value_ = (_svalue_).parse::<i32>().unwrap();
	                     										(_value_).targety = _targety_value_;
	                     									}
	                     								}
	                     								{
	                     									{
	                     										let _s0: String;
	                     										_s0 = format!("{}", "Enter value for attribute targetx of type integer: ");
	                     										print!("{}", _s0);
	                     										std::io::stdout().flush().unwrap();
	                     									}
	                     									{
	                     										let mut _svalue_: String;
	                     										let mut _temp_ = String::new();
	                     										std::io::stdin().read_line(&mut _temp_).expect("Failed to read input.");
	                     										_svalue_ = _temp_.as_str().trim().to_string();
	                     										let mut _targetx_value_: i32 = 0_i32;
	                     										_targetx_value_ = (_svalue_).parse::<i32>().unwrap();
	                     										(_value_).targetx = _targetx_value_;
	                     									}
	                     								}
	                     								send_start_DiscreteGrippingArm.send(M_DiscreteGrippingArm_input::moveDiscreteCommand(_value_)).unwrap();
	                     							}
	                     						},
	                     						"$end" => {
	                     							send_start_DiscreteGrippingArm.send(M_DiscreteGrippingArm_input::_terminate_).unwrap();
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "Terminating system. One more cycle will run before this program ends.");
	                     								println!("{}", _s0);	std::io::stdout().flush().unwrap();
	                     							}
	                     							terminate__ = true;
	                     							inputdone = true;
	                     						},
	                     						_ => {
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", format!("{}{}","Unknown event: ", _event_));
	                     								println!("{}", _s0);	std::io::stdout().flush().unwrap();
	                     							}
	                     						}
	                     					}
	                     				}
	                     			}
	                     			{
	                     				let mut outputdone: bool = false;
	                     				while !outputdone {
	                     					let mut _output_: M_DiscreteGrippingArm_output;
	                     					_output_ = recv_end_DiscreteGrippingArm.recv().unwrap();
	                     					match _output_ {
	                     						M_DiscreteGrippingArm_output::movecartesian(_aux1_, _aux2_, _aux3_, _aux4_) => {
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "output movecartesian");
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "(");
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", _aux1_);
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", ",");
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", _aux2_);
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", ",");
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", _aux3_);
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", ",");
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", _aux4_);
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", ")");
	                     								println!("{}", _s0);	std::io::stdout().flush().unwrap();
	                     							}
	                     						},
	                     						M_DiscreteGrippingArm_output::setvelocity(_aux1_) => {
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "output setvelocity");
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "(");
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", _aux1_);
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", ")");
	                     								println!("{}", _s0);	std::io::stdout().flush().unwrap();
	                     							}
	                     						},
	                     						M_DiscreteGrippingArm_output::movediscrete(_aux1_, _aux2_, _aux3_, _aux4_) => {
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "output movediscrete");
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "(");
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", _aux1_);
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", ",");
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", _aux2_);
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", ",");
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", _aux3_);
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", ",");
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", _aux4_);
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", ")");
	                     								println!("{}", _s0);	std::io::stdout().flush().unwrap();
	                     							}
	                     						},
	                     						M_DiscreteGrippingArm_output::reset => {
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "output reset");
	                     								println!("{}", _s0);	std::io::stdout().flush().unwrap();
	                     							}
	                     						},
	                     						M_DiscreteGrippingArm_output::place(_aux1_, _aux2_, _aux3_) => {
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "output place");
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "(");
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", _aux1_);
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", ",");
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", _aux2_);
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", ",");
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", _aux3_);
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", ")");
	                     								println!("{}", _s0);	std::io::stdout().flush().unwrap();
	                     							}
	                     						},
	                     						M_DiscreteGrippingArm_output::stop => {
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "output stop");
	                     								println!("{}", _s0);	std::io::stdout().flush().unwrap();
	                     							}
	                     						},
	                     						M_DiscreteGrippingArm_output::movejoint(_aux1_) => {
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "output movejoint");
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "(");
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", _aux1_);
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", ")");
	                     								println!("{}", _s0);	std::io::stdout().flush().unwrap();
	                     							}
	                     						},
	                     						M_DiscreteGrippingArm_output::pick(_aux1_, _aux2_, _aux3_) => {
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "output pick");
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "(");
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", _aux1_);
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", ",");
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", _aux2_);
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", ",");
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", _aux3_);
	                     								print!("{}", _s0);
	                     								std::io::stdout().flush().unwrap();
	                     							}
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", ")");
	                     								println!("{}", _s0);	std::io::stdout().flush().unwrap();
	                     							}
	                     						},
	                     						M_DiscreteGrippingArm_output::_done_ => {
	                     							outputdone = true;
	                     							{
	                     								let _s0: String;
	                     								_s0 = format!("{}", "---------------------");
	                     								println!("{}", _s0);	std::io::stdout().flush().unwrap();
	                     							}
	                     						},
	                     					}
	                     				}
	                     			}
	                     		}
	                     	})
	                     };		
	let mod_DiscreteGrippingArm_thread_thread = {
	                                              	thread::spawn(move || {
	                                            		let mut terminate__: bool = false;
	                                            		while !terminate__ {
	                                            			{
	                                            				let mut inputDone: bool = false;
	                                            				while !inputDone {
	                                            					{
	                                            						let _s0: String;
	                                            						_s0 = format!("{}", "- Waiting for input on channel start_DiscreteGrippingArm");
	                                            						debug!("{}", _s0);
	                                            					}
	                                            					let mut _input_: M_DiscreteGrippingArm_input;
	                                            					_input_ = recv_start_DiscreteGrippingArm.recv().unwrap();
	                                            					{
	                                            						let _s0: String;
	                                            						_s0 = format!("{}", "- Read input on channel start_DiscreteGrippingArm");
	                                            						debug!("{}", _s0);
	                                            					}
	                                            					match _input_ {
	                                            						M_DiscreteGrippingArm_input::gripperClosed => {
	                                            							send_start_cm.send(C_cm_input::gripperClosed).unwrap();
	                                            						},
	                                            						M_DiscreteGrippingArm_input::moveCompleted => {
	                                            							send_start_cm.send(C_cm_input::moveCompleted).unwrap();
	                                            						},
	                                            						M_DiscreteGrippingArm_input::robotStopped => {
	                                            							send_start_cm.send(C_cm_input::robotStopped).unwrap();
	                                            						},
	                                            						M_DiscreteGrippingArm_input::feasibleMoveDiscreteCommand => {
	                                            							send_start_cm.send(C_cm_input::feasibleMoveDiscreteCommand).unwrap();
	                                            						},
	                                            						M_DiscreteGrippingArm_input::nonfeasibleMoveDiscreteCommand => {
	                                            							send_start_cm.send(C_cm_input::nonfeasibleMoveDiscreteCommand).unwrap();
	                                            						},
	                                            						M_DiscreteGrippingArm_input::closeGripperCommand => {
	                                            							send_start_cm.send(C_cm_input::closeGripperCommand).unwrap();
	                                            						},
	                                            						M_DiscreteGrippingArm_input::openGripperCommand => {
	                                            							send_start_cm.send(C_cm_input::openGripperCommand).unwrap();
	                                            						},
	                                            						M_DiscreteGrippingArm_input::moveDiscreteCommand(_aux1_) => {
	                                            							send_start_cm.send(C_cm_input::moveDiscreteCommand(_aux1_)).unwrap();
	                                            						},
	                                            						M_DiscreteGrippingArm_input::collision => {
	                                            							send_start_cm.send(C_cm_input::collision).unwrap();
	                                            						},
	                                            						M_DiscreteGrippingArm_input::gripperOpened => {
	                                            							send_start_cm.send(C_cm_input::gripperOpened).unwrap();
	                                            						},
	                                            						M_DiscreteGrippingArm_input::_done_ => {
	                                            							send_start_cm.send(C_cm_input::_done_).unwrap();
	                                            							inputDone = true;
	                                            						},
	                                            						M_DiscreteGrippingArm_input::_terminate_ => {
	                                            							send_start_cm.send(C_cm_input::_terminate_).unwrap();
	                                            							terminate__ = true;
	                                            						},
	                                            					}
	                                            				}
	                                            			}
	                                            			{
	                                            				let _s0: String;
	                                            				_s0 = format!("{}", "Finished reading inputs of module DiscreteGrippingArm");
	                                            				debug!("{}", _s0);
	                                            			}
	                                            			mod_DiscreteGrippingArm_step(&send_start_cm
	                                            			                             , &recv_end_cm);
	                                            			{
	                                            				let mut outputDone: bool = false;
	                                            				while !outputDone {
	                                            					let mut _output_: C_cm_output;
	                                            					_output_ = recv_end_cm.recv().unwrap();
	                                            					match _output_ {
	                                            						C_cm_output::pick(_aux1_, _aux2_, _aux3_) => {
	                                            							send_end_DiscreteGrippingArm.send(M_DiscreteGrippingArm_output::pick(_aux1_,_aux2_,_aux3_)).unwrap();
	                                            						},
	                                            						C_cm_output::stop => {
	                                            							send_end_DiscreteGrippingArm.send(M_DiscreteGrippingArm_output::stop).unwrap();
	                                            						},
	                                            						C_cm_output::reset => {
	                                            							send_end_DiscreteGrippingArm.send(M_DiscreteGrippingArm_output::reset).unwrap();
	                                            						},
	                                            						C_cm_output::setvelocity(_aux1_) => {
	                                            							send_end_DiscreteGrippingArm.send(M_DiscreteGrippingArm_output::setvelocity(_aux1_)).unwrap();
	                                            						},
	                                            						C_cm_output::movediscrete(_aux1_, _aux2_, _aux3_, _aux4_) => {
	                                            							send_end_DiscreteGrippingArm.send(M_DiscreteGrippingArm_output::movediscrete(_aux1_,_aux2_,_aux3_,_aux4_)).unwrap();
	                                            						},
	                                            						C_cm_output::place(_aux1_, _aux2_, _aux3_) => {
	                                            							send_end_DiscreteGrippingArm.send(M_DiscreteGrippingArm_output::place(_aux1_,_aux2_,_aux3_)).unwrap();
	                                            						},
	                                            						C_cm_output::movecartesian(_aux1_, _aux2_, _aux3_, _aux4_) => {
	                                            							send_end_DiscreteGrippingArm.send(M_DiscreteGrippingArm_output::movecartesian(_aux1_,_aux2_,_aux3_,_aux4_)).unwrap();
	                                            						},
	                                            						C_cm_output::movejoint(_aux1_) => {
	                                            							send_end_DiscreteGrippingArm.send(M_DiscreteGrippingArm_output::movejoint(_aux1_)).unwrap();
	                                            						},
	                                            						C_cm_output::_done_ => {
	                                            							send_end_DiscreteGrippingArm.send(M_DiscreteGrippingArm_output::_done_).unwrap();
	                                            							outputDone = true;
	                                            						},
	                                            					}
	                                            				}
	                                            			}
	                                            		}
	                                            	})
	                                            };		
	let stm_sm_thread = {
	                    	let stm_sm_record = send_data.clone();
	                      	thread::spawn(move || {
	                    		// state machine variable declarations;
	                    		let mut inputstate: sm_inputstate = sm_inputstate {
	                    		                                    	collision: false,
	                    		                                    	moveDiscreteCommand: false,
	                    		                                    	moveDiscreteCommand_value: MovementArgs {
	                    		                                    		targetz: 0_i32,
	                    		                                    		targety: 0_i32,
	                    		                                    		targetx: 0_i32
	                    		                                    	},
	                    		                                    	openGripperCommand: false,
	                    		                                    	closeGripperCommand: false,
	                    		                                    	moveCompleted: false,
	                    		                                    	feasibleMoveDiscreteCommand: false,
	                    		                                    	nonfeasibleMoveDiscreteCommand: false,
	                    		                                    	gripperOpened: false,
	                    		                                    	gripperClosed: false,
	                    		                                    	robotStopped: false,
	                    		                                    	_transition_: TRANSITIONS_sm::NONE
	                    		                                    };
	                    		let mut state: sm_state = sm_state {
	                    		                          	done: false,
	                    		                          	state: STATES_sm::NONE,
	                    		                          	target_state: STATES_sm::NONE,
	                    		                          	status: STATUS::ENTER_STATE,
	                    		                          	en_SimDiscreteGrippingArmMovement_ArmStop_1_done: false,
	                    		                          	en_SimDiscreteGrippingArmMovement_ArmStop_1_counter: 0_i32,
	                    		                          	en_SimDiscreteGrippingArmMovement_GripperClose_1_done: false,
	                    		                          	en_SimDiscreteGrippingArmMovement_GripperClose_1_counter: 0_i32,
	                    		                          	en_SimDiscreteGrippingArmMovement_ArmMove_1_done: false,
	                    		                          	en_SimDiscreteGrippingArmMovement_ArmMove_1_counter: 0_i32,
	                    		                          	en_SimDiscreteGrippingArmMovement_GripperOpen_1_done: false,
	                    		                          	en_SimDiscreteGrippingArmMovement_GripperOpen_1_counter: 0_i32
	                    		                          };
	                    		let mut memorystate: sm_memory = sm_memory {
	                    		                                 	opening_speed: 0.0_f32 as f32,
	                    		                                 	lv: 0.0_f32 as f32,
	                    		                                 	closing_diameter: 0.0_f32 as f32,
	                    		                                 	closing_speed: 0.0_f32 as f32,
	                    		                                 	MOTION_VEL: 0.0_f32 as f32,
	                    		                                 	opening_diameter: 0.0_f32 as f32,
	                    		                                 	av: 0.0_f32 as f32,
	                    		                                 	TARGET_Z: 0_i32,
	                    		                                 	TARGET_Y: 0_i32,
	                    		                                 	PI: 0.0_f32 as f32,
	                    		                                 	opening_force: 0.0_f32 as f32,
	                    		                                 	closing_force: 0.0_f32 as f32,
	                    		                                 	TARGET_X: 0_i32,
	                    		                                 	margs: MovementArgs {
	                    		                                 		targetz: 0_i32,
	                    		                                 		targety: 0_i32,
	                    		                                 		targetx: 0_i32
	                    		                                 	}
	                    		                                 };
	                    		// state machine loop;
	                    		while !(state).done {
	                    			{
	                    				{
	                    					let _s0: String;
	                    					_s0 = format!("{}", "- Waiting for input on channel start_sm");
	                    					debug!("{}", _s0);
	                    				}
	                    				let mut inputDone: bool = false;
	                    				while !inputDone {
	                    					let mut _input_: sm_input;
	                    					_input_ = recv_start_sm.recv().unwrap();
	                    					{
	                    						let _s0: String;
	                    						_s0 = format!("{}", "- Read input on channel start_sm");
	                    						debug!("{}", _s0);
	                    					}
	                    					match _input_ {
	                    						sm_input::collision => {
	                    							(inputstate).collision = true;
	                    						},
	                    						sm_input::moveDiscreteCommand(_aux_) => {
	                    							(inputstate).moveDiscreteCommand = true;
	                    							(inputstate).moveDiscreteCommand_value = _aux_;
	                    						},
	                    						sm_input::openGripperCommand => {
	                    							(inputstate).openGripperCommand = true;
	                    						},
	                    						sm_input::closeGripperCommand => {
	                    							(inputstate).closeGripperCommand = true;
	                    						},
	                    						sm_input::moveCompleted => {
	                    							(inputstate).moveCompleted = true;
	                    						},
	                    						sm_input::feasibleMoveDiscreteCommand => {
	                    							(inputstate).feasibleMoveDiscreteCommand = true;
	                    						},
	                    						sm_input::nonfeasibleMoveDiscreteCommand => {
	                    							(inputstate).nonfeasibleMoveDiscreteCommand = true;
	                    						},
	                    						sm_input::gripperOpened => {
	                    							(inputstate).gripperOpened = true;
	                    						},
	                    						sm_input::gripperClosed => {
	                    							(inputstate).gripperClosed = true;
	                    						},
	                    						sm_input::robotStopped => {
	                    							(inputstate).robotStopped = true;
	                    						},
	                    						sm_input::_done_ => {
	                    							inputDone = true;
	                    						},
	                    						sm_input::_terminate_ => {
	                    							inputDone = true;
	                    						},
	                    					}
	                    				}
	                    			}
	                    			let mut ret: RESULT = RESULT::CONT;
	                    			while ret == RESULT::CONT {
	                    				let mut temp_: String;
	                    				temp_ = print_sm_state(&mut state);
	                    				{
	                    					let _s0: String;
	                    					_s0 = format!("{}", temp_);
	                    					debug!("{}", _s0);
	                    				}
	                    				ret = stm_sm_step(&mut state, &mut inputstate, &mut memorystate, &send_end_sm);
	                    			}
	                    			send_end_sm.send(sm_output::_done_).unwrap();
	                    			// update clocks;
	                    			// reset input events;
	                    			(inputstate).openGripperCommand = false;
	                    			(inputstate).moveDiscreteCommand = false;
	                    			(inputstate).nonfeasibleMoveDiscreteCommand = false;
	                    			(inputstate).robotStopped = false;
	                    			(inputstate).gripperClosed = false;
	                    			(inputstate).gripperOpened = false;
	                    			(inputstate).feasibleMoveDiscreteCommand = false;
	                    			(inputstate).moveCompleted = false;
	                    			(inputstate).closeGripperCommand = false;
	                    			(inputstate).collision = false;
	                    			{
	                    				let _s0: String;
	                    				_s0 = format!("{}", "		Sent output _done_ on channel end_sm");
	                    				debug!("{}", _s0);
	                    			}
	                    			{
	                    					let state_str = serde_json::to_string(&state).expect("Failed to serialise state of state machine stm_sm");
	                    					let memory_str = serde_json::to_string(&memorystate).expect("Failed to serialise memorystate of state machine stm_sm");
	                    				let snapshot = format!("{{\"state\": {},\"memory\": {}}}",state_str,memory_str);
	                    				stm_sm_record.send(Some(snapshot)).expect("Failed to send data to recorder."); 
	                    			}
	                    		}
	                    	})
	                    };		
	let ctrl_cm_thread_thread = {
	                              	thread::spawn(move || {
	                            		let mut terminate__: bool = false;
	                            		while !terminate__ {
	                            			{
	                            				let mut inputDone: bool = false;
	                            				while !inputDone {
	                            					{
	                            						let _s0: String;
	                            						_s0 = format!("{}", "- Waiting for input on channel start_cm");
	                            						debug!("{}", _s0);
	                            					}
	                            					let mut _input_: C_cm_input;
	                            					_input_ = recv_start_cm.recv().unwrap();
	                            					{
	                            						let _s0: String;
	                            						_s0 = format!("{}", "- Read input on channel start_cm");
	                            						debug!("{}", _s0);
	                            					}
	                            					match _input_ {
	                            						C_cm_input::feasibleMoveDiscreteCommand => {
	                            							send_start_sm.send(sm_input::feasibleMoveDiscreteCommand).unwrap();
	                            						},
	                            						C_cm_input::closeGripperCommand => {
	                            							send_start_sm.send(sm_input::closeGripperCommand).unwrap();
	                            						},
	                            						C_cm_input::gripperOpened => {
	                            							send_start_sm.send(sm_input::gripperOpened).unwrap();
	                            						},
	                            						C_cm_input::collision => {
	                            							send_start_sm.send(sm_input::collision).unwrap();
	                            						},
	                            						C_cm_input::moveDiscreteCommand(_aux1_) => {
	                            							send_start_sm.send(sm_input::moveDiscreteCommand(_aux1_)).unwrap();
	                            						},
	                            						C_cm_input::openGripperCommand => {
	                            							send_start_sm.send(sm_input::openGripperCommand).unwrap();
	                            						},
	                            						C_cm_input::nonfeasibleMoveDiscreteCommand => {
	                            							send_start_sm.send(sm_input::nonfeasibleMoveDiscreteCommand).unwrap();
	                            						},
	                            						C_cm_input::moveCompleted => {
	                            							send_start_sm.send(sm_input::moveCompleted).unwrap();
	                            						},
	                            						C_cm_input::robotStopped => {
	                            							send_start_sm.send(sm_input::robotStopped).unwrap();
	                            						},
	                            						C_cm_input::gripperClosed => {
	                            							send_start_sm.send(sm_input::gripperClosed).unwrap();
	                            						},
	                            						C_cm_input::_done_ => {
	                            							send_start_sm.send(sm_input::_done_).unwrap();
	                            							inputDone = true;
	                            						},
	                            						C_cm_input::_terminate_ => {
	                            							send_start_sm.send(sm_input::_terminate_).unwrap();
	                            							terminate__ = true;
	                            						},
	                            					}
	                            				}
	                            			}
	                            			{
	                            				let _s0: String;
	                            				_s0 = format!("{}", "	Finished reading inputs of controller cm");
	                            				debug!("{}", _s0);
	                            			}
	                            			ctrl_cm_step(&send_start_sm
	                            			             , &recv_end_sm);
	                            			{
	                            				let mut outputDone: bool = false;
	                            				while !outputDone {
	                            					let mut _output_: sm_output;
	                            					_output_ = recv_end_sm.recv().unwrap();
	                            					match _output_ {
	                            						sm_output::reset => {
	                            							send_end_cm.send(C_cm_output::reset).unwrap();
	                            						},
	                            						sm_output::movecartesian(_aux1_, _aux2_, _aux3_, _aux4_) => {
	                            							send_end_cm.send(C_cm_output::movecartesian(_aux1_,_aux2_,_aux3_,_aux4_)).unwrap();
	                            						},
	                            						sm_output::place(_aux1_, _aux2_, _aux3_) => {
	                            							send_end_cm.send(C_cm_output::place(_aux1_,_aux2_,_aux3_)).unwrap();
	                            						},
	                            						sm_output::movejoint(_aux1_) => {
	                            							send_end_cm.send(C_cm_output::movejoint(_aux1_)).unwrap();
	                            						},
	                            						sm_output::movediscrete(_aux1_, _aux2_, _aux3_, _aux4_) => {
	                            							send_end_cm.send(C_cm_output::movediscrete(_aux1_,_aux2_,_aux3_,_aux4_)).unwrap();
	                            						},
	                            						sm_output::setvelocity(_aux1_) => {
	                            							send_end_cm.send(C_cm_output::setvelocity(_aux1_)).unwrap();
	                            						},
	                            						sm_output::stop => {
	                            							send_end_cm.send(C_cm_output::stop).unwrap();
	                            						},
	                            						sm_output::pick(_aux1_, _aux2_, _aux3_) => {
	                            							send_end_cm.send(C_cm_output::pick(_aux1_,_aux2_,_aux3_)).unwrap();
	                            						},
	                            						sm_output::_done_ => {
	                            							send_end_cm.send(C_cm_output::_done_).unwrap();
	                            							outputDone = true;
	                            						},
	                            					}
	                            				}
	                            			}
	                            		}
	                            	})
	                            };		
	control_thread.join().unwrap();
	mod_DiscreteGrippingArm_thread_thread.join().unwrap();
	stm_sm_thread.join().unwrap();
	ctrl_cm_thread_thread.join().unwrap();
	
	println!("System successfully terminated.");
	return Ok(())
}

	fn print_STATUS(value:&mut STATUS)  -> String {
		match value {
			STATUS::ENTER_STATE => {
				return ("ENTER_STATE").to_string();
			},
			STATUS::ENTER_CHILDREN => {
				return ("ENTER_CHILDREN").to_string();
			},
			STATUS::EXECUTE_STATE => {
				return ("EXECUTE_STATE").to_string();
			},
			STATUS::EXIT_CHILDREN => {
				return ("EXIT_CHILDREN").to_string();
			},
			STATUS::EXIT_STATE => {
				return ("EXIT_STATE").to_string();
			},
			STATUS::INACTIVE => {
				return ("INACTIVE").to_string();
			},
		}
	}
	fn mod_DiscreteGrippingArm_step(send_start_cm: &SyncSender<C_cm_input>, recv_end_cm: &Receiver<C_cm_output>)  {
		{
			let _s0: String;
			_s0 = format!("{}", "Started step of module DiscreteGrippingArm");
			debug!("{}", _s0);
		}
		{
			let _s0: String;
			_s0 = format!("{}", "Finished step of module DiscreteGrippingArm");
			debug!("{}", _s0);
		}
	}
	fn print_sm_state(state:&mut sm_state)  -> String {
		let mut temp1_: String;
		temp1_ = print_STATES_sm(&mut (state).state);
		let mut temp2_: String;
		temp2_ = print_STATUS(&mut (state).status);
		return format!("{}{}",format!("{}{}",format!("{}{}",temp1_, " ("), temp2_), ")");
	}
	fn en_SimDiscreteGrippingArmMovement_ArmStop_1(state:&mut sm_state, inputstate:&mut sm_inputstate, memory:&mut sm_memory, send_output: &SyncSender<sm_output>)  -> RESULT {
		{
			let _s0: String;
			_s0 = format!("{}", "Running entry action 1 of state SimDiscreteGrippingArmMovement_ArmStop.");
			debug!("{}", _s0);
		}
		if (state).en_SimDiscreteGrippingArmMovement_ArmStop_1_counter == 0_i32 {
			send_output.send(sm_output::stop).unwrap();
			(*state).en_SimDiscreteGrippingArmMovement_ArmStop_1_counter = 1_i32;
			return RESULT::CONT;
		} else {
			(state).en_SimDiscreteGrippingArmMovement_ArmStop_1_done = true;
			return RESULT::CONT;
		}
	}
	fn SimDiscreteGrippingArmMovement_J4(state:&mut sm_state, inputstate:&mut sm_inputstate, memorystate:&mut sm_memory, send_output: &SyncSender<sm_output>)  -> RESULT {
		if !(inputstate).gripperClosed {
			(*state).state = STATES_sm::GripperClosing;
			(*state).status = STATUS::ENTER_STATE;
			return RESULT::CONT;
		} else if (inputstate).gripperClosed {
			(*state).state = STATES_sm::Idle;
			(*state).status = STATUS::ENTER_STATE;
			return RESULT::CONT;
		} else {
			return RESULT::CONT;
		}
	}
	fn SimDiscreteGrippingArmMovement_J2(state:&mut sm_state, inputstate:&mut sm_inputstate, memorystate:&mut sm_memory, send_output: &SyncSender<sm_output>)  -> RESULT {
		if !((inputstate).collision || (inputstate).moveCompleted) {
			(*state).state = STATES_sm::ArmMoving;
			(*state).status = STATUS::ENTER_STATE;
			return RESULT::CONT;
		} else if (inputstate).collision || (inputstate).moveCompleted {
			(*state).state = STATES_sm::ArmStop;
			(*state).status = STATUS::ENTER_STATE;
			return RESULT::CONT;
		} else {
			return RESULT::CONT;
		}
	}
	fn en_SimDiscreteGrippingArmMovement_GripperClose_1(state:&mut sm_state, inputstate:&mut sm_inputstate, memory:&mut sm_memory, send_output: &SyncSender<sm_output>)  -> RESULT {
		{
			let _s0: String;
			_s0 = format!("{}", "Running entry action 1 of state SimDiscreteGrippingArmMovement_GripperClose.");
			debug!("{}", _s0);
		}
		if (state).en_SimDiscreteGrippingArmMovement_GripperClose_1_counter == 0_i32 {
			send_output.send(sm_output::pick((memory).closing_diameter,(memory).closing_speed,(memory).closing_force)).unwrap();
			(*state).en_SimDiscreteGrippingArmMovement_GripperClose_1_counter = 1_i32;
			return RESULT::CONT;
		} else {
			(state).en_SimDiscreteGrippingArmMovement_GripperClose_1_done = true;
			return RESULT::CONT;
		}
	}
	fn print_STATES_sm(value:&mut STATES_sm)  -> String {
		match value {
			STATES_sm::NONE => {
				return ("NONE").to_string();
			},
			STATES_sm::Idle => {
				return ("Idle").to_string();
			},
			STATES_sm::ArmMove => {
				return ("ArmMove").to_string();
			},
			STATES_sm::ArmStop => {
				return ("ArmStop").to_string();
			},
			STATES_sm::GripperClose => {
				return ("GripperClose").to_string();
			},
			STATES_sm::GripperOpen => {
				return ("GripperOpen").to_string();
			},
			STATES_sm::ArmMoving => {
				return ("ArmMoving").to_string();
			},
			STATES_sm::ArmStopping => {
				return ("ArmStopping").to_string();
			},
			STATES_sm::GripperClosing => {
				return ("GripperClosing").to_string();
			},
			STATES_sm::GripperOpening => {
				return ("GripperOpening").to_string();
			},
		}
	}
	fn en_SimDiscreteGrippingArmMovement_ArmMove_1(state:&mut sm_state, inputstate:&mut sm_inputstate, memory:&mut sm_memory, send_output: &SyncSender<sm_output>)  -> RESULT {
		{
			let _s0: String;
			_s0 = format!("{}", "Running entry action 1 of state SimDiscreteGrippingArmMovement_ArmMove.");
			debug!("{}", _s0);
		}
		if (state).en_SimDiscreteGrippingArmMovement_ArmMove_1_counter == 0_i32 {
			send_output.send(sm_output::movediscrete(((memory).margs).targetx,((memory).margs).targety,((memory).margs).targetz,(memory).MOTION_VEL)).unwrap();
			(*state).en_SimDiscreteGrippingArmMovement_ArmMove_1_counter = 1_i32;
			return RESULT::CONT;
		} else {
			(state).en_SimDiscreteGrippingArmMovement_ArmMove_1_done = true;
			return RESULT::CONT;
		}
	}
	fn stm_sm_step(state:&mut sm_state, inputstate:&mut sm_inputstate, memorystate:&mut sm_memory, send_output: &SyncSender<sm_output>)  -> RESULT {
		{
			let _s0: String;
			_s0 = format!("{}", "		Running step of state machine SimDiscreteGrippingArmMovement");
			debug!("{}", _s0);
		}
		match (*state).state {
			STATES_sm::NONE => {
				{
					let _s0: String;
					_s0 = format!("{}", "		Executing initial junction of SimDiscreteGrippingArmMovement");
					debug!("{}", _s0);
				}
				{
					(*state).state = STATES_sm::Idle;
				}
				return RESULT::CONT;
			},
			STATES_sm::Idle => {
				match (*state).status {
					STATUS::ENTER_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Entering state Idle");
							debug!("{}", _s0);
						}
						{
							(*state).status = STATUS::ENTER_CHILDREN;
							return RESULT::CONT;
						}
					},
					STATUS::ENTER_CHILDREN => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Entering children of state Idle");
							debug!("{}", _s0);
						}
						(*state).status = STATUS::EXECUTE_STATE;
						{
							(*inputstate)._transition_ = TRANSITIONS_sm::NONE;
						}
						return RESULT::CONT;
					},
					STATUS::EXECUTE_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Executing state Idle");
							debug!("{}", _s0);
						}
						if (*inputstate)._transition_ == TRANSITIONS_sm::NONE {
							if !((inputstate).moveDiscreteCommand || (inputstate).openGripperCommand || (inputstate).closeGripperCommand) {
								(*inputstate)._transition_ = TRANSITIONS_sm::sm_t1_1;
								(*state).status = STATUS::EXIT_CHILDREN;
								return RESULT::WAIT;
							} else if (inputstate).openGripperCommand {
								(*inputstate)._transition_ = TRANSITIONS_sm::sm_t5;
								(*state).status = STATUS::EXIT_CHILDREN;
								return RESULT::CONT;
							} else if (inputstate).closeGripperCommand {
								(*inputstate)._transition_ = TRANSITIONS_sm::sm_t4;
								(*state).status = STATUS::EXIT_CHILDREN;
								return RESULT::CONT;
							} else if (inputstate).moveDiscreteCommand {
								(*memorystate).margs = (inputstate).moveDiscreteCommand_value;
								(*inputstate)._transition_ = TRANSITIONS_sm::sm_t2;
								(*state).status = STATUS::EXIT_CHILDREN;
								return RESULT::CONT;
							} else {
								return RESULT::CONT;
							}
						} else {
							return RESULT::CONT;
						}
					},
					STATUS::EXIT_CHILDREN => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Exiting children of state Idle");
							debug!("{}", _s0);
						}
						(*state).status = STATUS::EXIT_STATE;
						return RESULT::CONT;
					},
					STATUS::EXIT_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Exiting state Idle");
							debug!("{}", _s0);
						}
						{
							if (*inputstate)._transition_ == TRANSITIONS_sm::sm_t1_1 {
								(*state).state = STATES_sm::Idle;
								(*state).status = STATUS::ENTER_STATE;
								return RESULT::CONT;
							} else if (*inputstate)._transition_ == TRANSITIONS_sm::sm_t5 {
								(*state).state = STATES_sm::GripperOpen;
								(*state).status = STATUS::ENTER_STATE;
								return RESULT::CONT;
							} else if (*inputstate)._transition_ == TRANSITIONS_sm::sm_t4 {
								(*state).state = STATES_sm::GripperClose;
								(*state).status = STATUS::ENTER_STATE;
								return RESULT::CONT;
							} else if (*inputstate)._transition_ == TRANSITIONS_sm::sm_t2 {
								(*state).state = STATES_sm::ArmMove;
								(*state).status = STATUS::ENTER_STATE;
								return RESULT::CONT;
							} else {
								(*state).status = STATUS::INACTIVE;
								(*state).state = STATES_sm::NONE;
								return RESULT::CONT;
							}
						}
					},
					STATUS::INACTIVE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		State Idle is inactive");
							debug!("{}", _s0);
						}
						return RESULT::CONT;
					},
				}
			},
			STATES_sm::ArmMove => {
				match (*state).status {
					STATUS::ENTER_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Entering state ArmMove");
							debug!("{}", _s0);
						}
						if !(state).en_SimDiscreteGrippingArmMovement_ArmMove_1_done {
							let mut _ret_: RESULT;
							_ret_ = en_SimDiscreteGrippingArmMovement_ArmMove_1(state, inputstate, memorystate, &send_output);
							return _ret_;
						} else {
							(*state).status = STATUS::ENTER_CHILDREN;
							(*state).en_SimDiscreteGrippingArmMovement_ArmMove_1_done = false;
							(*state).en_SimDiscreteGrippingArmMovement_ArmMove_1_counter = 0_i32;
							return RESULT::CONT;
						}
					},
					STATUS::ENTER_CHILDREN => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Entering children of state ArmMove");
							debug!("{}", _s0);
						}
						(*state).status = STATUS::EXECUTE_STATE;
						{
							(*inputstate)._transition_ = TRANSITIONS_sm::NONE;
						}
						return RESULT::CONT;
					},
					STATUS::EXECUTE_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Executing state ArmMove");
							debug!("{}", _s0);
						}
						if (*inputstate)._transition_ == TRANSITIONS_sm::NONE {
							if (inputstate).feasibleMoveDiscreteCommand {
								(*inputstate)._transition_ = TRANSITIONS_sm::sm_t2_1;
								(*state).status = STATUS::EXIT_CHILDREN;
								return RESULT::CONT;
							} else if (inputstate).nonfeasibleMoveDiscreteCommand {
								(*inputstate)._transition_ = TRANSITIONS_sm::sm_t2_nonfeasible;
								(*state).status = STATUS::EXIT_CHILDREN;
								return RESULT::CONT;
							} else {
								return RESULT::CONT;
							}
						} else {
							return RESULT::CONT;
						}
					},
					STATUS::EXIT_CHILDREN => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Exiting children of state ArmMove");
							debug!("{}", _s0);
						}
						(*state).status = STATUS::EXIT_STATE;
						return RESULT::CONT;
					},
					STATUS::EXIT_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Exiting state ArmMove");
							debug!("{}", _s0);
						}
						{
							if (*inputstate)._transition_ == TRANSITIONS_sm::sm_t2_1 {
								(*state).state = STATES_sm::ArmMoving;
								(*state).status = STATUS::ENTER_STATE;
								return RESULT::CONT;
							} else if (*inputstate)._transition_ == TRANSITIONS_sm::sm_t2_nonfeasible {
								(*state).state = STATES_sm::Idle;
								(*state).status = STATUS::ENTER_STATE;
								return RESULT::CONT;
							} else {
								(*state).status = STATUS::INACTIVE;
								(*state).state = STATES_sm::NONE;
								return RESULT::CONT;
							}
						}
					},
					STATUS::INACTIVE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		State ArmMove is inactive");
							debug!("{}", _s0);
						}
						return RESULT::CONT;
					},
				}
			},
			STATES_sm::ArmStop => {
				match (*state).status {
					STATUS::ENTER_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Entering state ArmStop");
							debug!("{}", _s0);
						}
						if !(state).en_SimDiscreteGrippingArmMovement_ArmStop_1_done {
							let mut _ret_: RESULT;
							_ret_ = en_SimDiscreteGrippingArmMovement_ArmStop_1(state, inputstate, memorystate, &send_output);
							return _ret_;
						} else {
							(*state).status = STATUS::ENTER_CHILDREN;
							(*state).en_SimDiscreteGrippingArmMovement_ArmStop_1_done = false;
							(*state).en_SimDiscreteGrippingArmMovement_ArmStop_1_counter = 0_i32;
							return RESULT::CONT;
						}
					},
					STATUS::ENTER_CHILDREN => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Entering children of state ArmStop");
							debug!("{}", _s0);
						}
						(*state).status = STATUS::EXECUTE_STATE;
						{
							(*inputstate)._transition_ = TRANSITIONS_sm::NONE;
						}
						return RESULT::CONT;
					},
					STATUS::EXECUTE_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Executing state ArmStop");
							debug!("{}", _s0);
						}
						if (*inputstate)._transition_ == TRANSITIONS_sm::NONE {
							if true {
								(*inputstate)._transition_ = TRANSITIONS_sm::sm_t3;
								(*state).status = STATUS::EXIT_CHILDREN;
								return RESULT::CONT;
							} else {
								return RESULT::CONT;
							}
						} else {
							return RESULT::CONT;
						}
					},
					STATUS::EXIT_CHILDREN => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Exiting children of state ArmStop");
							debug!("{}", _s0);
						}
						(*state).status = STATUS::EXIT_STATE;
						return RESULT::CONT;
					},
					STATUS::EXIT_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Exiting state ArmStop");
							debug!("{}", _s0);
						}
						{
							if (*inputstate)._transition_ == TRANSITIONS_sm::sm_t3 {
								(*state).state = STATES_sm::ArmStopping;
								(*state).status = STATUS::ENTER_STATE;
								return RESULT::CONT;
							} else {
								(*state).status = STATUS::INACTIVE;
								(*state).state = STATES_sm::NONE;
								return RESULT::CONT;
							}
						}
					},
					STATUS::INACTIVE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		State ArmStop is inactive");
							debug!("{}", _s0);
						}
						return RESULT::CONT;
					},
				}
			},
			STATES_sm::GripperClose => {
				match (*state).status {
					STATUS::ENTER_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Entering state GripperClose");
							debug!("{}", _s0);
						}
						if !(state).en_SimDiscreteGrippingArmMovement_GripperClose_1_done {
							let mut _ret_: RESULT;
							_ret_ = en_SimDiscreteGrippingArmMovement_GripperClose_1(state, inputstate, memorystate, &send_output);
							return _ret_;
						} else {
							(*state).status = STATUS::ENTER_CHILDREN;
							(*state).en_SimDiscreteGrippingArmMovement_GripperClose_1_done = false;
							(*state).en_SimDiscreteGrippingArmMovement_GripperClose_1_counter = 0_i32;
							return RESULT::CONT;
						}
					},
					STATUS::ENTER_CHILDREN => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Entering children of state GripperClose");
							debug!("{}", _s0);
						}
						(*state).status = STATUS::EXECUTE_STATE;
						{
							(*inputstate)._transition_ = TRANSITIONS_sm::NONE;
						}
						return RESULT::CONT;
					},
					STATUS::EXECUTE_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Executing state GripperClose");
							debug!("{}", _s0);
						}
						if (*inputstate)._transition_ == TRANSITIONS_sm::NONE {
							if true {
								(*inputstate)._transition_ = TRANSITIONS_sm::sm_t4_1;
								(*state).status = STATUS::EXIT_CHILDREN;
								return RESULT::CONT;
							} else {
								return RESULT::CONT;
							}
						} else {
							return RESULT::CONT;
						}
					},
					STATUS::EXIT_CHILDREN => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Exiting children of state GripperClose");
							debug!("{}", _s0);
						}
						(*state).status = STATUS::EXIT_STATE;
						return RESULT::CONT;
					},
					STATUS::EXIT_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Exiting state GripperClose");
							debug!("{}", _s0);
						}
						{
							if (*inputstate)._transition_ == TRANSITIONS_sm::sm_t4_1 {
								(*state).state = STATES_sm::GripperClosing;
								(*state).status = STATUS::ENTER_STATE;
								return RESULT::CONT;
							} else {
								(*state).status = STATUS::INACTIVE;
								(*state).state = STATES_sm::NONE;
								return RESULT::CONT;
							}
						}
					},
					STATUS::INACTIVE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		State GripperClose is inactive");
							debug!("{}", _s0);
						}
						return RESULT::CONT;
					},
				}
			},
			STATES_sm::GripperOpen => {
				match (*state).status {
					STATUS::ENTER_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Entering state GripperOpen");
							debug!("{}", _s0);
						}
						if !(state).en_SimDiscreteGrippingArmMovement_GripperOpen_1_done {
							let mut _ret_: RESULT;
							_ret_ = en_SimDiscreteGrippingArmMovement_GripperOpen_1(state, inputstate, memorystate, &send_output);
							return _ret_;
						} else {
							(*state).status = STATUS::ENTER_CHILDREN;
							(*state).en_SimDiscreteGrippingArmMovement_GripperOpen_1_done = false;
							(*state).en_SimDiscreteGrippingArmMovement_GripperOpen_1_counter = 0_i32;
							return RESULT::CONT;
						}
					},
					STATUS::ENTER_CHILDREN => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Entering children of state GripperOpen");
							debug!("{}", _s0);
						}
						(*state).status = STATUS::EXECUTE_STATE;
						{
							(*inputstate)._transition_ = TRANSITIONS_sm::NONE;
						}
						return RESULT::CONT;
					},
					STATUS::EXECUTE_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Executing state GripperOpen");
							debug!("{}", _s0);
						}
						if (*inputstate)._transition_ == TRANSITIONS_sm::NONE {
							if true {
								(*inputstate)._transition_ = TRANSITIONS_sm::sm_t5_1;
								(*state).status = STATUS::EXIT_CHILDREN;
								return RESULT::CONT;
							} else {
								return RESULT::CONT;
							}
						} else {
							return RESULT::CONT;
						}
					},
					STATUS::EXIT_CHILDREN => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Exiting children of state GripperOpen");
							debug!("{}", _s0);
						}
						(*state).status = STATUS::EXIT_STATE;
						return RESULT::CONT;
					},
					STATUS::EXIT_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Exiting state GripperOpen");
							debug!("{}", _s0);
						}
						{
							if (*inputstate)._transition_ == TRANSITIONS_sm::sm_t5_1 {
								(*state).state = STATES_sm::GripperOpening;
								(*state).status = STATUS::ENTER_STATE;
								return RESULT::CONT;
							} else {
								(*state).status = STATUS::INACTIVE;
								(*state).state = STATES_sm::NONE;
								return RESULT::CONT;
							}
						}
					},
					STATUS::INACTIVE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		State GripperOpen is inactive");
							debug!("{}", _s0);
						}
						return RESULT::CONT;
					},
				}
			},
			STATES_sm::ArmMoving => {
				match (*state).status {
					STATUS::ENTER_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Entering state ArmMoving");
							debug!("{}", _s0);
						}
						{
							(*state).status = STATUS::ENTER_CHILDREN;
							return RESULT::CONT;
						}
					},
					STATUS::ENTER_CHILDREN => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Entering children of state ArmMoving");
							debug!("{}", _s0);
						}
						(*state).status = STATUS::EXECUTE_STATE;
						{
							(*inputstate)._transition_ = TRANSITIONS_sm::NONE;
						}
						return RESULT::CONT;
					},
					STATUS::EXECUTE_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Executing state ArmMoving");
							debug!("{}", _s0);
						}
						if (*inputstate)._transition_ == TRANSITIONS_sm::NONE {
							if true {
								(*inputstate)._transition_ = TRANSITIONS_sm::sm_t2_2;
								(*state).status = STATUS::EXIT_CHILDREN;
								return RESULT::WAIT;
							} else {
								return RESULT::CONT;
							}
						} else {
							return RESULT::CONT;
						}
					},
					STATUS::EXIT_CHILDREN => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Exiting children of state ArmMoving");
							debug!("{}", _s0);
						}
						(*state).status = STATUS::EXIT_STATE;
						return RESULT::CONT;
					},
					STATUS::EXIT_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Exiting state ArmMoving");
							debug!("{}", _s0);
						}
						{
							if (*inputstate)._transition_ == TRANSITIONS_sm::sm_t2_2 {
								let mut _ret_: RESULT;
								_ret_ = SimDiscreteGrippingArmMovement_J2(state, inputstate, memorystate, &send_output);
								return _ret_;
							} else {
								(*state).status = STATUS::INACTIVE;
								(*state).state = STATES_sm::NONE;
								return RESULT::CONT;
							}
						}
					},
					STATUS::INACTIVE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		State ArmMoving is inactive");
							debug!("{}", _s0);
						}
						return RESULT::CONT;
					},
				}
			},
			STATES_sm::ArmStopping => {
				match (*state).status {
					STATUS::ENTER_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Entering state ArmStopping");
							debug!("{}", _s0);
						}
						{
							(*state).status = STATUS::ENTER_CHILDREN;
							return RESULT::CONT;
						}
					},
					STATUS::ENTER_CHILDREN => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Entering children of state ArmStopping");
							debug!("{}", _s0);
						}
						(*state).status = STATUS::EXECUTE_STATE;
						{
							(*inputstate)._transition_ = TRANSITIONS_sm::NONE;
						}
						return RESULT::CONT;
					},
					STATUS::EXECUTE_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Executing state ArmStopping");
							debug!("{}", _s0);
						}
						if (*inputstate)._transition_ == TRANSITIONS_sm::NONE {
							if true {
								(*inputstate)._transition_ = TRANSITIONS_sm::sm_t3_1;
								(*state).status = STATUS::EXIT_CHILDREN;
								return RESULT::WAIT;
							} else {
								return RESULT::CONT;
							}
						} else {
							return RESULT::CONT;
						}
					},
					STATUS::EXIT_CHILDREN => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Exiting children of state ArmStopping");
							debug!("{}", _s0);
						}
						(*state).status = STATUS::EXIT_STATE;
						return RESULT::CONT;
					},
					STATUS::EXIT_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Exiting state ArmStopping");
							debug!("{}", _s0);
						}
						{
							if (*inputstate)._transition_ == TRANSITIONS_sm::sm_t3_1 {
								let mut _ret_: RESULT;
								_ret_ = SimDiscreteGrippingArmMovement_J3(state, inputstate, memorystate, &send_output);
								return _ret_;
							} else {
								(*state).status = STATUS::INACTIVE;
								(*state).state = STATES_sm::NONE;
								return RESULT::CONT;
							}
						}
					},
					STATUS::INACTIVE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		State ArmStopping is inactive");
							debug!("{}", _s0);
						}
						return RESULT::CONT;
					},
				}
			},
			STATES_sm::GripperClosing => {
				match (*state).status {
					STATUS::ENTER_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Entering state GripperClosing");
							debug!("{}", _s0);
						}
						{
							(*state).status = STATUS::ENTER_CHILDREN;
							return RESULT::CONT;
						}
					},
					STATUS::ENTER_CHILDREN => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Entering children of state GripperClosing");
							debug!("{}", _s0);
						}
						(*state).status = STATUS::EXECUTE_STATE;
						{
							(*inputstate)._transition_ = TRANSITIONS_sm::NONE;
						}
						return RESULT::CONT;
					},
					STATUS::EXECUTE_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Executing state GripperClosing");
							debug!("{}", _s0);
						}
						if (*inputstate)._transition_ == TRANSITIONS_sm::NONE {
							if true {
								(*inputstate)._transition_ = TRANSITIONS_sm::sm_t4_2;
								(*state).status = STATUS::EXIT_CHILDREN;
								return RESULT::WAIT;
							} else {
								return RESULT::CONT;
							}
						} else {
							return RESULT::CONT;
						}
					},
					STATUS::EXIT_CHILDREN => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Exiting children of state GripperClosing");
							debug!("{}", _s0);
						}
						(*state).status = STATUS::EXIT_STATE;
						return RESULT::CONT;
					},
					STATUS::EXIT_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Exiting state GripperClosing");
							debug!("{}", _s0);
						}
						{
							if (*inputstate)._transition_ == TRANSITIONS_sm::sm_t4_2 {
								let mut _ret_: RESULT;
								_ret_ = SimDiscreteGrippingArmMovement_J4(state, inputstate, memorystate, &send_output);
								return _ret_;
							} else {
								(*state).status = STATUS::INACTIVE;
								(*state).state = STATES_sm::NONE;
								return RESULT::CONT;
							}
						}
					},
					STATUS::INACTIVE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		State GripperClosing is inactive");
							debug!("{}", _s0);
						}
						return RESULT::CONT;
					},
				}
			},
			STATES_sm::GripperOpening => {
				match (*state).status {
					STATUS::ENTER_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Entering state GripperOpening");
							debug!("{}", _s0);
						}
						{
							(*state).status = STATUS::ENTER_CHILDREN;
							return RESULT::CONT;
						}
					},
					STATUS::ENTER_CHILDREN => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Entering children of state GripperOpening");
							debug!("{}", _s0);
						}
						(*state).status = STATUS::EXECUTE_STATE;
						{
							(*inputstate)._transition_ = TRANSITIONS_sm::NONE;
						}
						return RESULT::CONT;
					},
					STATUS::EXECUTE_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Executing state GripperOpening");
							debug!("{}", _s0);
						}
						if (*inputstate)._transition_ == TRANSITIONS_sm::NONE {
							if true {
								(*inputstate)._transition_ = TRANSITIONS_sm::sm_t5_2;
								(*state).status = STATUS::EXIT_CHILDREN;
								return RESULT::WAIT;
							} else {
								return RESULT::CONT;
							}
						} else {
							return RESULT::CONT;
						}
					},
					STATUS::EXIT_CHILDREN => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Exiting children of state GripperOpening");
							debug!("{}", _s0);
						}
						(*state).status = STATUS::EXIT_STATE;
						return RESULT::CONT;
					},
					STATUS::EXIT_STATE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		Exiting state GripperOpening");
							debug!("{}", _s0);
						}
						{
							if (*inputstate)._transition_ == TRANSITIONS_sm::sm_t5_2 {
								let mut _ret_: RESULT;
								_ret_ = SimDiscreteGrippingArmMovement_J5(state, inputstate, memorystate, &send_output);
								return _ret_;
							} else {
								(*state).status = STATUS::INACTIVE;
								(*state).state = STATES_sm::NONE;
								return RESULT::CONT;
							}
						}
					},
					STATUS::INACTIVE => {
						{
							let _s0: String;
							_s0 = format!("{}", "		State GripperOpening is inactive");
							debug!("{}", _s0);
						}
						return RESULT::CONT;
					},
				}
			},
		}
	}
	fn ctrl_cm_step(send_start_sm: &SyncSender<sm_input>, recv_end_sm: &Receiver<sm_output>)  {
		{
			let _s0: String;
			_s0 = format!("{}", "	Started step of controller cm");
			debug!("{}", _s0);
		}
	}
	fn SimDiscreteGrippingArmMovement_J3(state:&mut sm_state, inputstate:&mut sm_inputstate, memorystate:&mut sm_memory, send_output: &SyncSender<sm_output>)  -> RESULT {
		if (inputstate).robotStopped {
			(*state).state = STATES_sm::Idle;
			(*state).status = STATUS::ENTER_STATE;
			return RESULT::CONT;
		} else if !(inputstate).robotStopped {
			(*state).state = STATES_sm::ArmStopping;
			(*state).status = STATUS::ENTER_STATE;
			return RESULT::CONT;
		} else {
			return RESULT::CONT;
		}
	}
	fn SimDiscreteGrippingArmMovement_J5(state:&mut sm_state, inputstate:&mut sm_inputstate, memorystate:&mut sm_memory, send_output: &SyncSender<sm_output>)  -> RESULT {
		if (inputstate).gripperOpened {
			(*state).state = STATES_sm::Idle;
			(*state).status = STATUS::ENTER_STATE;
			return RESULT::CONT;
		} else if !(inputstate).gripperOpened {
			(*state).state = STATES_sm::GripperOpening;
			(*state).status = STATUS::ENTER_STATE;
			return RESULT::CONT;
		} else {
			return RESULT::CONT;
		}
	}
	fn en_SimDiscreteGrippingArmMovement_GripperOpen_1(state:&mut sm_state, inputstate:&mut sm_inputstate, memory:&mut sm_memory, send_output: &SyncSender<sm_output>)  -> RESULT {
		{
			let _s0: String;
			_s0 = format!("{}", "Running entry action 1 of state SimDiscreteGrippingArmMovement_GripperOpen.");
			debug!("{}", _s0);
		}
		if (state).en_SimDiscreteGrippingArmMovement_GripperOpen_1_counter == 0_i32 {
			send_output.send(sm_output::place((memory).opening_diameter,(memory).opening_speed,(memory).opening_force)).unwrap();
			(*state).en_SimDiscreteGrippingArmMovement_GripperOpen_1_counter = 1_i32;
			return RESULT::CONT;
		} else {
			(state).en_SimDiscreteGrippingArmMovement_GripperOpen_1_done = true;
			return RESULT::CONT;
		}
	}



