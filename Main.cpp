#include<Windows.h>
#include<iostream>
#include"memory.h"


using namespace SDK_METHOD_SAMPLE_COMMON;

int main()
{
	DWORD Return_Code = 0;

	Return_Code = InitializeHeap();

	if (Return_Code != NO_ERROR){
		goto Cleanup;
	}
	else {
		printf("Heap has been successfully Initialized!\n\n");
		goto Cleanup;
	}




Cleanup:

	//Cleanup Heap

	CleanupHeap();

	if (!CleanupHeap())
	{
		printf("WARNING: CLEANUP FAILED!!!!");
	}
	else
	{
		printf("Heap has been successfully Cleaned up!\n\n");
	}
	
	return Return_Code;

}