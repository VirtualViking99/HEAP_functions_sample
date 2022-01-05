#include "memory.h"


namespace SDK_METHOD_SAMPLE_COMMON
{
	/// 
	/// Heap Handle
	/// 
	HANDLE local_heap = NULL;


	//----------------------------------------------------------//


	/**
	*
	* Initialize Heap
	* 	
	*/
	DWORD InitializeHeap()
	{
		DWORD dwErr = ERROR_SUCCESS;

		local_heap = NULL; ///make sure glocal value is initialized

		local_heap = HeapCreate(

			0,			//serialize access to heap
			1,			//create 0-byte heap which will increase with allocations if necessary
			0);			//0 = heap is growable; limmited only by available memory

		if (!local_heap)
		{
			dwErr = GetLastError();
			printf("Initializeheap(): heap creation FAILED -- hit error %d", dwErr);
		}
		return dwErr;

	}

	//----------------------------------------------------------//

	/**
	* clean up local memory Heap:
	* this will free up memory in our heap
	* return a WIN32 error code if success or failure
	* 
	* Initializes heap handle back to NULL, to prevent handle from being used again.
	* 
	*/
	DWORD CleanupHeap()
	{
		DWORD dwErr = ERROR_SUCCESS;

		BOOL f_ok = true;

		//Creation check
		if (!local_heap)
		{
			printf("CleanupHEap(): heap has not been creted yet; goodbye");
			goto Label_Done;
		}

		//Free the heap
		f_ok = HeapDestroy(local_heap);

		if (!f_ok)
		{
			dwErr = GetLastError();
			printf("CleanupHeap(): Heap destruction failed -- hit error %d!", dwErr);
			goto Label_Done;
		}
	Label_Done:
		return dwErr;
	}

	/**
	* Allocate Memory using local Heap
	* @param  sizeInBytes  [in]  The byte-length of the buffer to allocate.
    * @param  ppBuffer     [out] Pointer to the new data buffer.
	* 
	* return Win32 error code, indicating success or failure.
	*             ERROR_INVALID_HANDLE - if AllocateMemory is called before InitializeHeap()
	*/

	DWORD AllocateMemory(
		IN     DWORD sizeInBytes,
		IN OUT PVOID* ppBuffer)
	{
		DWORD dwErr = ERROR_SUCCESS;


		//Sanity / Everything_Works checks
		if (ppBuffer == NULL)
		{
			printf("AllocateMemory(): Invalid buffer pointer passed in!");
			dwErr = ERROR_INVALID_PARAMETER;
			goto Label_Done;
		}
		if (!local_heap)
		{
			printf("CleanupHEap(): heap has not been creted yet; goodbye");
			dwErr = ERROR_INVALID_PARAMETER;
			goto Label_Done;
		}


	// Allocate a new memory block on the heap.  Use HEAP_ZERO_MEMORY to
	// initialize the memory block, so callers don't have to do so.
		*ppBuffer = (PBYTE)HeapAlloc(local_heap, HEAP_ZERO_MEMORY, sizeInBytes);

	//check if NULL
		if (*ppBuffer == NULL)
		{
			printf("AllocateMemory(): Not enough memory");
			dwErr = ERROR_OUTOFMEMORY;
			goto Label_Done;
		}
	Label_Done:
		return dwErr;
	}

	/**
	* Free Memory Allocations from local_heap
	*  @param  ppBuffer   [out] Pointer to the data buffer to free.
	*
	*
	* @return A Win32 error code, indicating success or failure.
	*             ERROR_INVALID_HANDLE - if FreeMemory is called before InitializeHeap().
	* 
	* Once called, intializes buffer to NULL so that calling function can't reference former allocation agai
	*
	*/
	DWORD FreeMemory(
		IN OUT PVOID* ppBuffer)
	{
		DWORD dwErr = ERROR_SUCCESS;
		BOOL  f_Ok = TRUE;

		// Sanity checks.
		if (ppBuffer == NULL)
		{
			printf("FreeMemory(): Invalid buffer pointer passed in!");
			dwErr = ERROR_INVALID_PARAMETER;
			goto Label_Done;
		}

		// Don't try to free NULL pointers
		if (*ppBuffer == NULL)
		{
			//silently ignore
			goto Label_Done;
		}

		//set f_Ok to HeapFree() call
		f_Ok = HeapFree(local_heap, 0, *ppBuffer);
		if (!f_Ok)
		{
			dwErr = GetLastError();
			printf("FreeMemory(): Error %d while freeing memory!", dwErr);
			goto Label_Done;
		}


		//Reinitialize buffer to NULL
		*ppBuffer = NULL;
	Label_Done:
		return dwErr;
	}


}