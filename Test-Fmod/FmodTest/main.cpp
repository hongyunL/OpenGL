#include "fmod_errors.h"
#include "fmod.hpp"

#include <stdio.h>  
#include <windows.h> 
//#include <conio.h>

#pragma comment(lib, "fmodex_vc.lib") //����Ƶ����뵽������

void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s/n", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

int main()
{
	FMOD_RESULT result;
	FMOD::System * system;

	/* ����Fmod��ϵͳ */
	result = FMOD::System_Create(&system);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s/n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	/* ��ʼ��Fmodϵͳinit���� */
	result = system->init(1, FMOD_INIT_NORMAL, 0); //ʹ����1����������
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s/n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	/* ���汾�� */   
	unsigned int version;
	result = system->getVersion(&version);
	ERRCHECK(result);

	if (version < FMOD_VERSION)
	{
		printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x/n", version, FMOD_VERSION);
		return 0;
	}

	/* ������������������С����Զ���� */

	

	/* ����ý���ļ������� */  
	FMOD::Sound *sound;

	//stream(�� System::createStream����)��������ʱ���룬��ʹ�ú��ٵ��ڴ���Ϊ���壬�����Ϊʲô���ļ������stream��ԭ��
	result = system->createStream("Idina Menzel-Let It Go.mp3", FMOD_3D, 0, &sound); //������ʽ��FMOD_NONBLOCKING
	   
	ERRCHECK(result);

	//�������Ҫ�������soundʵ����������������ܶ�(��ѭ��)���Ϳ���ʡȥchannel��һ����channel������һ��������ʵ��
	FMOD::Channel *channel; //����Channel����   

	//����ý���ļ��ĳ���   
	unsigned int lenms;

	result = sound->getLength(&lenms, FMOD_TIMEUNIT_MS);
	ERRCHECK(result);

	printf("Total CD length %02d:%02d/n", lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100);


	result = system->playSound(FMOD_CHANNEL_FREE, sound, true, &channel);

	//��ͣʱ�趨����
	result = channel->setVolume(0.5f);
	ERRCHECK(result);

	//����������ſ�ʼ����
	result = channel->setPaused(false);
	ERRCHECK(result);

	Sleep(lenms * 60 * 1000);//һ��Ҫsleepһ�£�Ҫ��Ȼ�������Ϸ����ˣ��������������Ǻ�   
	ERRCHECK(result);

	/* ����������λ�ü��ٶ� */

	/* �õ���ǰ�ɵõ���2D��3D��������Ŀ */

	/* ����3D��λ���ٶȺͷ��� */

	/* ��Ӧ���̲��� */

	/* �رղ��ͷ���Դ */

	return 0;
}