# PythonWSE

This is a python wrapper of the Weighted Sample Elinmination method proposed by Cem Yuksel. It can be installed using the following cammand from terminal:

'''
python setup.py install
'''

Then one can use this wrapper in Python 3 as follows. 

'''python
import myWSE

##to generate synthetic data for this example
import numpy as np
N = 10**4
dimension = 2
data = np.random.normal(0, 1.0, size = (N,dimension))

##subsampling via WSE
#subsample size
nmax = 2000
sample_wse = myWSE.py_myWSE(data, nmax)
#sample_wse is a numpy array of size (nmax, dimension), with each row corresponding to a selected subsample point
'''


NOTE:
To use this wrapper for dimensions other than 2 or 10, the file 'myWSE.pyx' needs to be modified as below. I will take dimension = 20 as an example here.

First, add the following before the definiation of function 'py_myWSE':
'''
cdef extern from "myWSE.h":

    cdef void myWSE_20D "myWeightedSampleElimination<cy::Vec<double,20>,double,20,int>"(double** data, int N, double* sample, int n)
'''

Then, call above defined function 'myWSE_20D':
'''

'''

