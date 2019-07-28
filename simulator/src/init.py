import pybullet as p
import time
import pybullet_data
import os

physicsClient = p.connect(p.GUI)#or p.DIRECT for non-graphical version
p.setAdditionalSearchPath(pybullet_data.getDataPath()) #optionally
p.setGravity(0,0,-10)
planeId = p.loadURDF("plane.urdf")
cubeStartPos = [0,0,1]
cubeStartOrientation = p.getQuaternionFromEuler([0,0,0])
boxId = p.loadURDF("../../yumi_description/urdf/yumi.urdf",cubeStartPos, cubeStartOrientation)
#p.setRealTimeSimulation(1)
for i in range (10000):
    maxForce = 1
    mode = p.TORQUE_CONTROL
    p.setJointMotorControl2(boxId, 1,
    controlMode=mode, 
    force=maxForce)
    p.stepSimulation()
    time.sleep(1./100.)
    print(i)
cubePos, cubeOrn = p.getBasePositionAndOrientation(boxId)
print(cubePos,cubeOrn)
p.disconnect()

