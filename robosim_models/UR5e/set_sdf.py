#Author: Santiago Gil
import sys
from xml.etree import cElementTree as ET

filename = sys.argv[1]

tree = ET.parse(filename)
root = tree.getroot()


for link in root.iter('link'):
    for collision in link.iter('collision'):
        for surface in collision.iter('surface'):
            collision.remove(surface)


    for visual in link.iter('visual'):
        for surface in visual.iter('surface'):
            visual.remove(surface)



'''for joint in root.iter('joint'):
    elem = ET.SubElement(joint,'axis')
    for axis in joint.iter('axis'):
        elem = ET.SubElement(axis,'xyz')
        #if ("arm_world_joint" in joint.get('name')):
        #    elem.text = "0 0 1"
        if ("shoulder_pan_joint" in joint.get('name')):
            #elem.text = "0 0 1"
            elem.text = "0 0 1"
        if ("shoulder_lift_joint" in joint.get('name')):
            #elem.text = "0 -1 0"
            #elem.text = "0 -1 0"
            elem.text = "0 1 0"
        if ("elbow_joint" in joint.get('name')):
            #elem.text = "0 -1 0"
            elem.text = "0 1 0"

        if ("wrist_1_joint" in joint.get('name')):
            #elem.text = "0 1 0"
            #elem.text = "0 -1 0"
            elem.text = "0 1 0"
        if ("wrist_2_joint" in joint.get('name')):
            #elem.text = "0 0 -1"
            #elem.text = "0 0 -1"
            elem.text = "0 0 1"
        if ("wrist_3_joint" in joint.get('name')):
            #elem.text = "0 1 0"
            #elem.text = "0 -1 0"
            elem.text = "0 1 0"
        if ("rightFingerGripper" in joint.get('name')):
            #elem.text = "1 0 0"
            elem.text = "0 0 1"
        if ("leftFingerGripper" in joint.get('name')):
            elem.text = "0 0 -1"
'''

tree.write('modified_sdf.sdf')
