from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext
import numpy

setup(
      name = 'myWSE app',
      ext_modules=[
                   Extension('myWSE',
                             sources=['myWSE.pyx'],
                             extra_compile_args=['-stdlib=libc++','-std=c++11'],
                             language='c++',include_dirs=[numpy.get_include()])
                   ],
      cmdclass = {'build_ext': build_ext}
      )




