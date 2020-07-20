HDF_INCLUDE = -I $(HDF5_HOME)/include
HDF_LIB = -L $(HDF5_HOME)/lib

MPICC = mpicc
 COPTS = -Wall -O0
# COPTS += -g -fPIC -Wstrict-aliasing -fstrict-aliasing
#COPTS += -D  _DEBUG_

all:
	$(MPICC) $(COPTS) $(HDF_INCLUDE) main.c $(HDF_LIB) -lhdf5

create:
	$(MPICC) $(COPTS) $(HDF_INCLUDE) create.c $(HDF_LIB) -lhdf5

read:
	$(MPICC) $(COPTS) $(HDF_INCLUDE) read.c $(HDF_LIB) -lhdf5

clean:
	rm -f *.o a.out

