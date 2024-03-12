#python

import math

def sysCall_init():
    # This is executed exactly once, the first time this script is executed
    sim = require('sim')
    simUI = require('simUI')
    self.bubbleRobBase = sim.getObject('.') # this is bubbleRob's handle
    self.leftMotor = sim.getObject("./leftMotor") # Handle of the left motor
    self.rightMotor = sim.getObject("./rightMotor") # Handle of the right motor
    self.noseSensor = sim.getObject("./sensingNose") # Handle of the proximity sensor
    self.minMaxSpeed = [50*math.pi/180, 300*math.pi/180] # Min and max speeds for each motor
    self.backUntilTime = -1 # Tells whether bubbleRob is in forward or backward mode
    self.robotCollection = sim.createCollection(0)
    sim.addItemToCollection(self.robotCollection, sim.handle_tree, self.bubbleRobBase, 0)
    self.distanceSegment = sim.addDrawingObject(sim.drawing_lines, 4, 0, -1, 1, [0, 1, 0])
    self.robotTrace = sim.addDrawingObject(sim.drawing_linestrip + sim.drawing_cyclic, 2, 0, -1, 200, [1, 1, 0], None, None, [1, 1, 0])
    self.graph = sim.getObject('./graph')
    # sim.destroyGraphCurve(self.graph, -1)
    self.distStream = sim.addGraphStream(self.graph, 'bubbleRob clearance', 'm', 0, [1, 0, 0])
    # Create the custom UI:
    xml = '<ui title="' + sim.getObjectAlias(self.bubbleRobBase, 1) + ' speed" closeable="false" resizeable="false" activate="false">'
    xml = xml + '<hslider minimum="0" maximum="100" on-change="speedChange_callback" id="1"/>'
    xml = xml + '<label text="" style="* {margin-left: 300px;}"/></ui>'
    self.ui = simUI.create(xml)
    self.speed = (self.minMaxSpeed[0] + self.minMaxSpeed[1]) * 0.5
    simUI.setSliderValue(self.ui, 1, 100 * (self.speed - self.minMaxSpeed[0]) / (self.minMaxSpeed[1] - self.minMaxSpeed[0]))

def sysCall_sensing():
    result, distData, *_ = sim.checkDistance(self.robotCollection, sim.handle_all)
    if result > 0:
        sim.addDrawingObjectItem(self.distanceSegment, None)
        sim.addDrawingObjectItem(self.distanceSegment, distData)
        sim.setGraphStreamValue(self.graph,self.distStream, distData[6])
    p = sim.getObjectPosition(self.bubbleRobBase)
    sim.addDrawingObjectItem(self.robotTrace, p)

def speedChange_callback(ui, id, newVal):
    self.speed = self.minMaxSpeed[0] + (self.minMaxSpeed[1] - self.minMaxSpeed[0]) * newVal / 100

def sysCall_actuation(): 
    result, *_ = sim.readProximitySensor(self.noseSensor) # Read the proximity sensor
    # If we detected something, we set the backward mode:
    if result > 0:
        self.backUntilTime = sim.getSimulationTime() + 4
    if self.backUntilTime < sim.getSimulationTime():
        # When in forward mode, we simply move forward at the desired speed
        sim.setJointTargetVelocity(self.leftMotor, self.speed)
        sim.setJointTargetVelocity(self.rightMotor, self.speed)
    else:
        # When in backward mode, we simply backup in a curve at reduced speed
        sim.setJointTargetVelocity(self.leftMotor, -self.speed / 2)
        sim.setJointTargetVelocity(self.rightMotor, -self.speed / 8)

def sysCall_cleanup(): 
    simUI.destroy(self.ui)

