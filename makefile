CC=gcc
CFLAGS=-I.
DEPS = FileSystemInfo.h fsLow.h

LIBS=-lm

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

fsdriver3: fsdriver3.o fsLow.o initializeFileSystem.o FileSystemControl.o driverFunctionP1.o driverFunctionP2.o driverFunctionP3.o driverFunctionP4.o checkFunctions.o checkFunctionsP1.o closeFileSystem.o
	$(CC) -o fsdriver3 fsLow.o fsdriver3.o initializeFileSystem.o FileSystemControl.o driverFunctionP1.o driverFunctionP2.o driverFunctionP3.o driverFunctionP4.o checkFunctions.o checkFunctionsP1.o closeFileSystem.o $(LIBS) 
