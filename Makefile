CC=gcc
CFLAGS=-I.
DEPS=fsLow.h FileSystemInfo.h 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

checkFunctions.o: checkFunctions.c
	$(CC) -o checkFunctions.c

checkFunctionsP1.o: checkFunctionsP1.c
	$(CC) -o checkFunctionsP1.c

closeFileSystem.o: closeFileSystem.c
	$(CC) -o closeFileSystem.c

driverFunctionP1.o: driverFunctionP1.c
	$(CC) -o driverFunctionP1.c

driverFunctionP2.o: driverFunctionP2.c
	$(CC) -o driverFunctionP2.c

driverFunctionP3.o: driverFunctionP3.c
	$(CC) -o driverFunctionP3.c

driverFunctionP4.o: driverFunctionP4.c
	$(CC) -o driverFunctionP4.c

FileSystemControl.o: FileSystemControl.c
	$(CC) -o FileSystemControl.c

fsDriver3.o: fsDriver3.c checkFunctions.c checkFunctionsP1.c closeFileSystem.c driverFunctionP1.c driverFunctionP2.c driverFunctionP3.c driverFunctionP4.c FileSystemControl.c fsLow.c hexdump.c 
	$(CC) -o fsDriver3.c

fsLow.o: fsLow.c
	$(CC) -o fsLow.c

hexdump.o: hexdump.c
	$(CC) -o hexdump.c

initializeFileSystem.o: initializeFileSystem.c 
	$(CC) -o initializeFileSystem.c

output: checkFunctions.c checkFunctionsP1.c closeFileSystem.c driverFunctionP1.c driverFunctionP2.c driverFunctionP3.c driverFunctionP4.c FileSystemControl.c fsDriver3.c fsLow.c hexdump.c initializeFileSystem.c
	$(CC) -o output checkFunctions.o checkFunctionsP1.o closeFileSystem.o driverFunctionP1.o driverFunctionP2.o driverFunctionP3.o driverFunctionP4.o FileSystemControl.o fsDriver3.o fsLow.o hexdump.o initializeFileSystem.o