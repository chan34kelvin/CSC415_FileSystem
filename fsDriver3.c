int main(int argc, char *argv[]){

	char *fileName;
	long int volSize;
	long int blockSize;

	if(argc>3){
		fileName= argv[1];
		volSize= atoll(argv[2]);
		blockSize=atoll(argv[3]);
	}

	int retVal= startPartitionSystem(fileName, &volSize, &blockSize);

	if(retVal!=0){
		printf("File system terminated");
		return 0;
	}

	/*printf("Please enter a user file name: ");
	char userFileName[128];
	scanf("%s",userFileName);*/

	DirectoryEntryP name[10000];
	DirectoryEntry C;
	C.size= 800;
	long int count= sizeof(DirectoryEntryP);
	DirectoryEntryP C1= malloc(blockSize );
	C1= &C;
	printf("%d",sizeof(DirectoryEntryP));	
	LBAwrite (C1, 1,0);
	DirectoryEntryP C2= malloc(blockSize );
	LBAread (C2, 1,0);
	DirectoryEntry D;
	D.size=10;
	DirectoryEntryP D1= malloc(blockSize );
	D1= &D;
	LBAwrite (D1, 2,1);
	DirectoryEntryP D2= malloc(blockSize );
	LBAread (D2, 2, 1);
	printf("%d",D2->size);
	printf("%d",C2->size);
	closePartitionSystem();
	return 0;
  }
