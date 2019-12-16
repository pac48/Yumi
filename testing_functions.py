import numpy as np
from numpy import linalg as LA

# def test(a, b):
#     sum=a+b
#
#     return (sum)
#
# print (test(2,1))
# print (test(3,4))
# print(np.pi)
# print(np.eye(3))

def getR(zi, zj):

    zj=zj/LA.norm(zj)
    zi=zi/LA.norm(zi)

    theta=np.arctan2(LA.norm(np.cross(zi,zj)), np.dot(zi,zj))
    k=np.cross(zi,zj)
    k=k/LA.norm(k)

    K = np.array([
        [0, -k[2], k[1]],
        [k[2], 0, -k[0]],
        [-k[1], k[0], 0]
    ])

    R = np.eye(3) + np.sin(theta)*K + (1-np.cos(theta))*np.power(K, 2)
    return (R)

def findR(t1):

    R1=np.array([
    [np.cos(t1), -np.sin(t1), 0, 0],
    [np.sin(t1), np.cos(t1), 0, 0],
    [0,0,1,0],
    [0,0,0,1]
        ])
    return(R1)

N= findR(180)

x=np.array([
    [1, 2, 3],
    [4, 5, 6]
])
y=np.array([
    [0,1,0],
    [1,0,1]
])
def simple_mult_matrix(x,y):
    z=np.ones(len(x[:,1]), len(x[1,:]))

    for i in range(len(x[:,1])):
        print(i)
        for j in range(len(x[1,:])):
            print(j)
            z[i, j] = x[i, j] * y[i, j]
    return (z)

z=simple_mult_matrix(x,y)
print(z)
