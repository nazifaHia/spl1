#include <windows.h>
#include <stdio.h>
#define BUF_SIZE 256

int main(int argc ,LPTSTR argv[])
{
	HANDLE hIn,hOut;
	DWORD nIn,nOut;
	CHAR buffer[BUF_SIZE];


	if(argc!=3)
	{
		printf("usages:cp file1 file2");
		return 1;
	}

	hIn=CreateFile(argv[1],GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

	if(hIn==INVALID_HANDLE_VALUE)
	{
		printf("can't open input file ERROR:%x\n", GetLastError());
		return 2;
	}


	hOut=CreateFile(argv[2],GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hOut==INVALID_HANDLE_VALUE)
	{
		printf("Can't open output file %x\n",GetLastError());
		return 3;
	}

	while(ReadFile(hIn,buffer,BUF_SIZE,&nIn,NULL)&nIn>0)
	{
		WriteFile(hOut,buffer,nIn,&nOut,NULL);
		if(nIn!=nOut)
		{
			printf("fatal error %x\n",GetLastError());
			return 4;
		}
	}

	CloseHandle(hIn);
	CloseHandle(hOut);


	return 0;
}
