#ifndef _SOUND_MAN_H_
#define _SOUND_MAN_H_

#include "Framework.h"
#include "cwaves.h"

//�n�������,���ӬO�@�ɪ�
//�H��Эק�sound buffer
//�ܦ��i�H�@��

//�N��@���n��
class Sound3D
{
private:
	enum {INVALID_SOURCE = 0xffffffff} ;
	ALuint      uiBuffer;
	ALuint      uiSource;  

public:

	bool IsEnd () ;//�O�_����

	bool Load (const char*) ;
	void Replay () ;

	bool Play (const char*) ;
	bool Play3D (const char*, float, float, float, bool) ;

	void Release () ;
	Sound3D () ;
} ;

//��y�n��
//�ΨӼ���j���ɮ�
class StreamSound
{
private:
	enum {NUMBUFFERS = 12} ;
	ALuint		    uiBuffers[NUMBUFFERS];
	ALuint		    uiSource;
	ALuint			uiBuffer;
	ALint			iState;
	CWaves*			pWaveLoader ;
	WAVEID			WaveID;
	ALint			iTotalBuffersProcessed ;
	WAVEFORMATEX	wfex;
	unsigned long	ulDataSize ;
	unsigned long	ulFrequency ;
	unsigned long	ulFormat ;
	unsigned long	ulBufferSize;
	unsigned long	ulBytesWritten;
	void *			pData ;
	bool bLoop ;

public:

	void Work () ;

	void Stop () ;
	bool Play (const char*, bool) ;
	void Release () ;

	StreamSound () ;
} ;

//#########################################################
//#########################################################
//#########################################################

#include <list>

//�n�����޲z��
class SoundMan
{
private:
	StreamSound BGM ;//�I������,�����O����,�]�i�H�O���ҭ���

	//�ΨӼ��񭵮�
	typedef std::list <Sound3D> LIST_SOUND ;
	LIST_SOUND ListSound ;

public:
	//�۰ʪ�����@�ӭ���
	//�b���w���y��
	//�����N��soundman�޲z
	//�I�s���ݭn�h�B�̪��󪺺޲z
	void PlaySound3D (const char*, float, float, float, bool) ;
	void PlaySound (const char*) ;

	void StopBGM () ;//�����I������
	void PlayBGM (const char*, bool) ;//����I������

	void SetListender (float, float, float, float, float, float) ;

	void Work () ;//�w���I�swork

	bool Init () ;
	void Release () ;
} ;

#endif