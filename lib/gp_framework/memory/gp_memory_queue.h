#ifndef _GP_MEMORY_QUEUR_H
#define _GP_MEMORY_QUEUR_H

#include <assert.h>
//#include <g_base_type.h>

//#include <g_small_obj_allocator.h>

//#include <g_queue.h>

//�ΨӦs��O����϶�
//�@���@���s���b�@�_
//�ƹ�W�����O�s��

//����i�h��
//�|�����X��

//�i�H�Ψӻs�@�ƥ�queue

//�Ъ`�N,�o�Ӫ���i��|�Q�Φb�h�����
//�o�ɭԭn�D�`�p��

template <class MEMORY_SIZE_TYPE, DWORD ALLOCATE_MEMORY_SIZE>
class GMemoryQueue//:public GSmallAlloc <BYTE, 1024>
{
private:
	//�Ҧ����O���鳣�t�m�b�o��
	BYTE* pAllMemory ;

	DWORD CurBeginPos ;//�ثe��ƶ}�l���a��
	DWORD CurEndPos ;//�ثe��Ƶ������a��
	DWORD MaxMemorySize ;//�ثe�t�m���j�p

	DWORD MoveMemoryCount ;//�o�Ͳ��ʸ�ƪ�����
	DWORD ReAllocateCount ;//�o�ͭ��s�t�m������
	DWORD MemoryChangeCount ;//�O���馳�Q���ܦ�m������

private:
	void AppendMemory (DWORD newMaxSize)
	{
//		THREA_SAFE_CHECK () ;
		//�O���餣���ΤF,���ӭn�t�m��j��
		//�ӥB�n�H�t�m�����j�p�Ӱt�m
		//�p�G�@�f��t�ܦh��,�i��|�W�L�@����t�m���q
		//�o�ɭԭn�t�m�������q

		BYTE* pOriMem = pAllMemory ;

		int minBlockCount = newMaxSize/ALLOCATE_MEMORY_SIZE ;
		if (newMaxSize%ALLOCATE_MEMORY_SIZE != 0)
			minBlockCount = newMaxSize/ALLOCATE_MEMORY_SIZE+1 ;

		MaxMemorySize = minBlockCount*ALLOCATE_MEMORY_SIZE ;
		assert (MaxMemorySize >= newMaxSize) ;
		if (pAllMemory != NULL)
			pAllMemory = (BYTE*)realloc (pAllMemory, MaxMemorySize) ;
		else
			pAllMemory = (BYTE*)malloc (MaxMemorySize) ;

		//�L�k�t�m�O����
		if (pAllMemory == NULL)
		{
			assert (pAllMemory != NULL) ;
//			throw GMemoryAllocateFail () ;
		}

		ReAllocateCount ++ ;

		if (pOriMem !=  pAllMemory)
			MemoryChangeCount ++ ;
	}

public:
	DWORD getAllDataSize ()
	{
		return CurEndPos-CurBeginPos ;
	}

	DWORD getCurEndPos ()
	{
		return CurEndPos ;
	}

	//�p�GpData == NULL
	//�N��u�O�Qpush�@�ӪŶ��X�ӦӤw
	void* pushStream (DWORD dataSize)
	{
//		THREA_SAFE_CHECK () ;
		//���i�H�b�o��@���move���ʧ@
		//�]���i��|���ǥX�Ӫ����п��~

		//�upush���,���|���[��ƪ��j�p��T
		assert (dataSize > 0) ;

		//�s���j�p�t����T
		DWORD newEndPos = CurEndPos+dataSize ;

		if (newEndPos > MaxMemorySize)
		{
			//�O���餣��,�n�t�m�s��
			AppendMemory (newEndPos) ;
			assert (MaxMemorySize >= newEndPos) ;
		}

		//�ƻs���
		BYTE* pWritePos = pAllMemory+CurEndPos ;
		CurEndPos += dataSize ;

		assert (CurEndPos <= MaxMemorySize) ;

		return pWritePos ;
	}

	void* pushStream (const void* pData, DWORD dataSize)
	{
//		THREA_SAFE_CHECK () ;
		//���i�H�b�o��@���move���ʧ@
		//�]���i��|���ǥX�Ӫ����п��~

		//�upush���,���|���[��ƪ��j�p��T
		assert (dataSize > 0) ;

		/*
		//�s���j�p�t����T
		DWORD newEndPos = CurEndPos+dataSize ;

		if (newEndPos > MaxMemorySize)
		{
			//�O���餣��,�n�t�m�s��
			AppendMemory (newEndPos) ;
			assert (MaxMemorySize >= newEndPos) ;
		}

		//�ƻs���
		BYTE* pWritePos = pAllMemory+CurEndPos ;
		*/

		void* pWritePos = pushStream (dataSize) ;
		if (pData != NULL)
			if (pWritePos != NULL)
				memcpy (pWritePos, pData, dataSize) ;
//		CurEndPos += dataSize ;

		assert (CurEndPos <= MaxMemorySize) ;

		return pWritePos ;
	}

	void alignMemory ()
	{
		//��O���骺�Ŧ�M��
		if (CurBeginPos > 0)//���Ū��a��
		{
			DWORD allDataSize = CurEndPos-CurBeginPos ;
			if (CurBeginPos  >= allDataSize)
			{
				//�p�G�������e�q���j�p�i�H��᭱����Ʃ��e��
				//�N���Ʃ��e��
				if (allDataSize > 0)
				{
					memmove (pAllMemory, pAllMemory+CurBeginPos, allDataSize) ;

					if (MoveMemoryCount < 0xffffffff)//�����o�Ӧ����z��
						MoveMemoryCount ++ ;
				}
				CurEndPos -= CurBeginPos ;
				CurBeginPos = 0 ;
			}
		}

	}

	//push�@���,�|���ͤj�p��T
	void pushBlock (const void* pData, DWORD dataSize)
	{
//		THREA_SAFE_CHECK () ;

		//ĵ�i,data���o�W�L�w�q���j�p,�_�h�|�z��
		//�Q���૬�ӽT�{��ƨS���z��
		MEMORY_SIZE_TYPE tmpSize = (MEMORY_SIZE_TYPE)dataSize ;
		assert (tmpSize == dataSize) ;

		//�i���Ʋ���,����stream���e��,�o�˥i�H�קK�O����L�����j
		alignMemory () ;

		//�����j�p
		pushStream (&dataSize, sizeof (tmpSize)) ;

		pushStream (pData, dataSize) ;

		assert (CurEndPos <= MaxMemorySize) ;
	}

	//�q���������,���O�q�e��,�Ъ`�N
	void popStreamTail (DWORD dataSize)
	{
		assert (dataSize <= (CurEndPos-CurBeginPos)) ;
		CurEndPos -= dataSize ;
	}

	void popStream (void* pData, DWORD dataSize)
	{
//		THREA_SAFE_CHECK () ;

		//���Ƨ�X��
		DWORD allDataSize = CurEndPos-CurBeginPos ;
		assert (allDataSize >= dataSize) ;

		memcpy (pData, pAllMemory+CurBeginPos, dataSize) ;
		CurBeginPos += dataSize ;
	}

	void cutStream (DWORD dataSize)
	{
//		THREA_SAFE_CHECK () ;

		//���Ƨ�X��
		DWORD allDataSize = CurEndPos-CurBeginPos ;
		assert (allDataSize >= dataSize) ;

		CurBeginPos += dataSize ;
	}

	void* peekStream (DWORD& dataSize)
	{
		if (CurEndPos > CurBeginPos)
		{
			dataSize = CurEndPos-CurBeginPos ;

			return pAllMemory+CurBeginPos ;
		}
		else
		{
			assert (CurEndPos == CurBeginPos) ;
			dataSize = 0 ;
			return NULL ;
		}
	}

	void* popStream (DWORD dataSize)
	{
//		THREA_SAFE_CHECK () ;

		//���Ƨ�X��
		DWORD allDataSize = CurEndPos-CurBeginPos ;
		assert (allDataSize >= dataSize) ;

		void* pDataPos = pAllMemory+CurBeginPos ;

		CurBeginPos += dataSize ;

		return pDataPos ;
	}

	bool hasBlock ()
	{
		//���ˬd�O�_���������Ѥj�p���e�q
		DWORD allDataSize = CurEndPos-CurBeginPos ;
		if (allDataSize < sizeof (MEMORY_SIZE_TYPE))
		{
			//�e�q����
			return false ;
		}

		//���o�j�p
		MEMORY_SIZE_TYPE& curBlockSize = 
								*((MEMORY_SIZE_TYPE*)(pAllMemory+CurBeginPos)) ;


		//�p���ƬO�_����
		if (curBlockSize > (allDataSize-sizeof (MEMORY_SIZE_TYPE)))
		{
			//�e�q����
			return false ;
		}

		return true ;
	}

	//pop�X�@���,�p�G�S������,�Ǧ^NULL
	void* popBlock (MEMORY_SIZE_TYPE& size)
	{
//		THREA_SAFE_CHECK () ;
		if (!hasBlock ())
			return NULL ;

		MEMORY_SIZE_TYPE& curBlockSize = 
								*((MEMORY_SIZE_TYPE*)(pAllMemory+CurBeginPos)) ;

		//�e�q����
		size = curBlockSize ;

		//��ڪ����
		void* pData = pAllMemory+CurBeginPos+sizeof (MEMORY_SIZE_TYPE) ;
		CurBeginPos += sizeof (MEMORY_SIZE_TYPE)+curBlockSize ;

		return pData ;
	}

	void detach (BYTE* pMem, DWORD dataSize)
	{
		assert (pAllMemory == pMem) ;
		assert (CurEndPos == dataSize) ;
		assert (MaxMemorySize == dataSize) ;

		pAllMemory = NULL ;
		CurEndPos = 0 ;
		MaxMemorySize = 0 ;

		assert (CurBeginPos != 0) ;
		assert (ReAllocateCount == 0) ;
		assert (MemoryChangeCount == 0) ;
		assert (MoveMemoryCount == 0) ;

		CurBeginPos = 0 ;
	}

	//�o�O�@�ӯS���\��
	//�Ψӹ����@���J�s���O����
	///Detach�@�w�n����I�s
	GMemoryQueue (BYTE* pMem, DWORD dataSize):pAllMemory(pMem),
															CurEndPos(dataSize),MaxMemorySize(dataSize),
															ReAllocateCount(0),CurBeginPos(0),
															MemoryChangeCount(0),MoveMemoryCount(0)
	{
	}

	GMemoryQueue ():pAllMemory(NULL),CurBeginPos(0),CurEndPos(0),
															MaxMemorySize(0),ReAllocateCount(0),
															MemoryChangeCount(0),MoveMemoryCount(0)
	{
	}

	void release ()
	{
		assert (CurEndPos <= MaxMemorySize) ;
//		assert (CurBeginPos == CurEndPos) ;
		if (pAllMemory != NULL)
		{
			assert (MaxMemorySize > 0) ;
			free (pAllMemory) ;
			pAllMemory = NULL ;
		}
		CurBeginPos = 0 ;
		CurEndPos = 0 ;
		MaxMemorySize = 0 ;
		ReAllocateCount = 0 ;
		MemoryChangeCount = 0 ;
		MoveMemoryCount = 0 ;
	}

	~GMemoryQueue ()
	{
		release () ;
	}
} ;

//#########################################################

template <DWORD MEMORY_SIZE>
class GLocalMemory//:public GSmallAlloc <BYTE, 1024>
{
private:
	char Buffer[MEMORY_SIZE] ;
	DWORD CurSize ;

public:
	void* getBuffer ()
	{
		return (void*) Buffer ;
	}

	DWORD getBufferSize ()
	{
		return MEMORY_SIZE ;
	}

	DWORD getDataSize ()
	{
		return CurSize ;
	}

	void setDataSize (DWORD size)
	{
		CurSize = size ;
	}
} ;

#endif