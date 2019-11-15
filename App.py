import numpy as np
from numpy import linalg as LA

num=5
arr1 = np.array([4, 3, 6])
arr2 = np.array([2, 5, -3]) - arr1


# arr3 = np.cross(arr1, arr2)
# arr3 = np.cross(arr1, arr2)
arr3 = np.cross(arr1/LA.norm(arr1), arr2/LA.norm(arr2))
arr4 = np.array([
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
])
# x=np.power(2,2)
# print(arr4[1,0:1])
# x=np.cos(45)
# print(-arr4[1,:])
# y=np.zeros((4,4))
# R=np.eye(3)
# d[0:3,0:3]=R
R0_1=[5., 5., -0. ]
MD_1=[100, 100, 100]
T0_1H=np.eye(4)
# T0_1H[0:3, 0:3]=R0_1
# T0_1H[0:3, 3]=MD_1 # Joint_1 = Joint_1 - RP; everything with respect to RP at 0 0 0
# T0_1H[3, 0:3]=0
y=np.ones((6,6))
y[0:3,0]=[5, 5, 5]#T0_1H

j=np.array([
    [0, 1, 3],
    [R0_1[0], R0_1[1], -R0_1[2]],
    [1, 1, 1],
    [0,0,0]
])
# y[0:3, 4]=R0_1
print(len(j[0,:]))
