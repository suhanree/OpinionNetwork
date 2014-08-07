This code is using gsl library.
To compile include directory for gsl should be given correctly. (Ex. /home/Suhan/library/include)
To link, -lgsl -lgslcblas option should be added, too.

g++ lsf.C -lgsl -lgslblas -o lsf
