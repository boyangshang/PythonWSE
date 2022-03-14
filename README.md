# PythonWSE

This is a python wrapper of the Weighted Sample Elinmination method proposed by Cem Yuksel ([[1]](#1)). 

Installation
---------------

It can be installed using the following cammand from terminal:

```
python setup.py install
```

USAGE
---------------
One can use this wrapper in Python 3 as follows. 

```python
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
```


NOTES
---------------
To use this wrapper for dimensions other than 2 or 10, the file 'myWSE.pyx' needs to be modified. I will take dimension = 20 as an example here.

- Define a new function for dimension 20 after line 17 :
```python
    cdef void myWSE_20D "myWeightedSampleElimination<cy::Vec<double,20>,double,20,int>"(double** data, int N, double* sample, int n)
```

- Add the following after line 43:
```python
    elif dim == 20:
        myWSE_20D(inputPoints, N, <double*>sample_c.data, n)
```

## References
<a id="1">[1]</a> 
Yuksel, C (2015). 
Sample Elimination for Generating Poisson Disk Sample Sets. 
Computer Graphics Forum (Proceedings of EUROGRAPHICS 2015), 34, 2, 2015
