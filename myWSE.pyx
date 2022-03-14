# distutils: language = c++
#cython: language_level=3

cimport numpy as np
import numpy as np

cimport cython
from libc.stdlib cimport malloc, free


cdef extern from "myWSE.h":



    cdef void myWSE_2D "myWeightedSampleElimination<cy::Vec<double,2>,double,2,int>"(double** data, int N, double* sample, int n)

    cdef void myWSE_10D "myWeightedSampleElimination<cy::Vec<double,10>,double,10,int>"(double** data, int N, double* sample, int n)



def py_myWSE(np.ndarray[np.double_t, ndim=2] data, n):

    cdef int N,dim
    N = data.shape[0]
    dim  = data.shape[1]

    cdef double **inputPoints = <double **> malloc(N*sizeof(double *))

    cdef np.ndarray[np.double_t, ndim=1, mode="c"] temp


    for i in range(N):
        temp = data[i,:]
        inputPoints[i]  = &temp[0]


    cdef np.ndarray[np.double_t, ndim=1, mode="c"] sample_c
    sample_c = np.ascontiguousarray(np.zeros((n*dim,)), dtype=np.double)

    if dim == 2:
        myWSE_2D(inputPoints, N, <double*>sample_c.data, n)
    elif dim == 10:
        myWSE_10D(inputPoints, N, <double*>sample_c.data, n)

    free(inputPoints)

    return sample_c.reshape(n, dim)



