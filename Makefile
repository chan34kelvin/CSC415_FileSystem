CC=gcc
CFLAGS=-I.
DEPS=fsLow.h FileSystemInfo.h fsDriver3.c checkFunctions.c checkFunctionsP1.c closeFileSystem.c driverFunctionP1.c driverFunctionP2.c driverFunctionP3.c driverFunctionP4.c FileSystemControl.c fsLow.c hexdump.c 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

fsDriver3.o: fsDriver3.o checkFunctions.o checkFunctionsP1.o closeFileSystem.o driverFunctionP1.o driverFunctionP2.o driverFunctionP3.o driverFunctionP4.o FileSystemControl.o fsLow.o hexdump.o 
	$(CC) -o fsDriver3 fsDriver3.o

checkFunctions: checkFunctions.o
	$(CC) -o  checkFunctions checkFunctions.o

checkFunctionsP1.o: checkFunctionsP1.o
	$(CC) -o checkFunctionsP1 checkFunctionsP1.o

closeFileSystem.o: closeFileSystem.o
	$(CC) -o closeFileSystem closeFileSystem.o

driverFunctionP1.o: driverFunctionP1.o
	$(CC) -o driverFunctionP1 driverFunctionP1.o

driverFunctionP2.o: driverFunctionP2.o
	$(CC) -o driverFunctionP2 driverFunctionP2.o

driverFunctionP3.o: driverFunctionP3.o
	$(CC) -o driverFunctionP3 driverFunctionP3.o

driverFunctionP4.o: driverFunctionP4.o
	$(CC) -o driverFunctionP4 driverFunctionP4.o

FileSystemControl.o: FileSystemControl.o
	$(CC) -o FileSystemControl FileSystemControl.o

fsLow.o: fsLow.o
	$(CC) -o fsLow fsLow.o

hexdump.o: hexdump.o
	$(CC) -o hexdump hexdump.o

initializeFileSystem.o: initializeFileSystem.o 
	$(CC) -o initializeFileSystem initializeFileSystem.o

output: checkFunctions.o checkFunctionsP1.o closeFileSystem.o driverFunctionP1.o driverFunctionP2.o driverFunctionP3.o driverFunctionP4.o FileSystemControl.o fsDriver3.o fsLow.o hexdump.o initializeFileSystem.o
	$(CC) -o output checkFunctions.o checkFunctionsP1.o closeFileSystem.o driverFunctionP1.o driverFunctionP2.o driverFunctionP3.o driverFunctionP4.o FileSystemControl.o fsDriver3.o fsLow.o hexdump.o initializeFileSystem.o