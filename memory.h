#ifndef _MEMORY_H_
#define _MEMORY_H_


#pragma once
#include<Windows.h>
#include<iostream>

namespace SDK_METHOD_SAMPLE_COMMON
{
	///heap Handle
	extern HANDLE local_heap;

	///setup private heap
	DWORD InitializeHeap();

	///cleanup heap
	DWORD CleanupHeap();

	/// Allocate memory on our heap.
	DWORD
		AllocateMemory(
			IN     DWORD sizeInBytes,
			IN OUT PVOID* pBuffer
		);

	DWORD
		FreeMemory(
			IN OUT PVOID* pBuffer
		);
}/// end namespace "SDK_METHOD_SAMPLE_COMMON"

#endif // !_MEMORY_H_