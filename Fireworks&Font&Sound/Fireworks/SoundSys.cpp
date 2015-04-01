#include "SoundSys.h"

#include <stdio.h>  

const int DISTANCEFACTOR = 1; //�����ɼ���Χ
const int INTERFACE_UPDATETIME = 50; //����ʱ��˯��ʱ��

SoundSys::SoundSys()
{
	m_use3DSound = false;
}

void SoundSys::ErrCheck(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s/n", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

bool SoundSys::CheckVersion(unsigned int version)
{
	result = system->getVersion(&version);
	ErrCheck(result);

	if (version < FMOD_VERSION)
	{
		printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x/n", version, FMOD_VERSION);
		return false;
	}
	else
	{
		return true;
	}
}

void SoundSys::CreatSys(unsigned int channelMax)
{
	/* ����Fmod��ϵͳ */
	result = FMOD::System_Create(&system);
	ErrCheck(result);

	/* ���������Ĭ�ϵĳ�ʼ������������������һϵ�г�ʼ��ϵͳ�ĺ��� */

	/* ��ʼ��Fmodϵͳinit���� */
	result = system->init(channelMax, FMOD_INIT_NORMAL, 0); //ʹ����1����������
	ErrCheck(result);
}

void SoundSys::LoadSound(char *fileName)
{
	FMOD::Sound *sound;

	//stream(�� System::createStream����)��������ʱ���룬��ʹ�ú��ٵ��ڴ���Ϊ���壬�����Ϊʲô���ļ������stream��ԭ��
	result = system->createStream(fileName, FMOD_3D, 0, &sound); //��ʱĬ��Ϊ3D��Ч
	ErrCheck(result);

	//����ý���ļ��ĳ���   
	//unsigned int lenms;
	//result = sound->getLength(&lenms, FMOD_TIMEUNIT_MS);
	//ErrCheck(result);
	//printf("Total CD length %02d:%02d/n", lenms / 1000 / 60, lenms / 1000 % 60, lenms / 10 % 100);

	if (true == m_use3DSound)
	{
		sound->set3DMinMaxDistance(2.0f * DISTANCEFACTOR, 10000.0f * DISTANCEFACTOR); //�ɼ�������Χ
	}

	m_soundsMap.insert(std::pair<char*, FMOD::Sound*>(fileName, sound));
}

bool SoundSys::PlayMusic(char *fileName)
{
	//���������ҵ�sound
	FMOD::Sound *sound;
	m_soundIter = m_soundsMap.find(fileName);
	if (m_soundIter != m_soundsMap.end())
	{
		sound = m_soundIter->second;
	}
	else
	{
		return false;
	}

	//�������Ҫ�������soundʵ����������������ܶ�(��ѭ��)���Ϳ���ʡȥchannel��һ����channel������һ��������ʵ��
	FMOD::Channel *channel;

	//ʹ��FMOD_CHANNEL_FREE�Ļ�ϵͳÿ�ض����Զ�����һ��δʹ�õ�channel����
	result = system->playSound(FMOD_CHANNEL_FREE, sound, true, &channel); //���paused��Ϊfalse�Ļ����տ�ʼ����ȫ��������

	m_channelMap.insert(std::pair<FMOD::Sound*, FMOD::Channel*>(sound, channel));

	//��ͣʱ�趨����
	result = channel->setVolume(0.5f);
	ErrCheck(result);

	//����������ſ�ʼ����
	result = channel->setPaused(false);
	ErrCheck(result);

	return true;
}

bool SoundSys::PlaySoundEffect(char *fileName)
{
	//���������ҵ�sound
	FMOD::Sound *sound;
	m_soundIter = m_soundsMap.find(fileName);
	if (m_soundIter != m_soundsMap.end())
	{
		sound = m_soundIter->second;
	}
	else
	{
		return false;
	}

	//ʹ��FMOD_CHANNEL_FREE�Ļ�ϵͳÿ�ض����Զ�����һ��δʹ�õ�channel����
	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, 0); 
}

bool SoundSys::SetPause(char *fileName, bool pause)
{
	//�ҵ�sound
	FMOD::Sound *sound;
	m_soundIter = m_soundsMap.find(fileName);
	if (m_soundIter != m_soundsMap.end())
	{
		sound = m_soundIter->second;
	}
	else
	{
		return false;
	}

	//�ҵ�channel
	FMOD::Channel *channel;
	m_channelIter = m_channelMap.find(sound);
	if (m_channelIter != m_channelMap.end())
	{
		channel = m_channelIter->second;
	}
	else
	{
		return false;
	}

	result = channel->setPaused(pause);
	ErrCheck(result);
}

bool SoundSys::Stop(char *fileName)
{
	//���������ҵ�sound
	FMOD::Sound *sound;
	m_soundIter = m_soundsMap.find(fileName);
	if (m_soundIter != m_soundsMap.end())
	{
		sound = m_soundIter->second;
	}
	else
	{
		return false;
	}

	SetPause(fileName, true);
	sound->release();

	m_soundsMap.erase(m_soundIter); //ɾ��sound

	//����sound�ҵ�channel
	m_channelIter = m_channelMap.find(sound);
	if (m_channelIter != m_channelMap.end())
	{
		m_channelMap.erase(m_channelIter); //ɾ��channel
	}
	else
	{
		return false;
	}

	return true;
}

//ǰ��Ϊ�����ᣬ��Ϊ���أ��Ϸ�Ϊ����
bool SoundSys::SetSrcAttributes(char *fileName, FMOD_VECTOR srcPos, FMOD_VECTOR srcVel) //channel
{
	//�ҵ�sound
	FMOD::Sound *sound;
	m_soundIter = m_soundsMap.find(fileName);
	if (m_soundIter != m_soundsMap.end())
	{
		sound = m_soundIter->second;
	}
	else
	{
		return false;
	}

	//�ҵ�channel
	FMOD::Channel *channel;
	m_channelIter = m_channelMap.find(sound);
	if (m_channelIter != m_channelMap.end())
	{
		channel = m_channelIter->second;
	}
	else
	{
		return false;
	}

	//result = channel->set3DAttributes(&srcPos, &srcVel); 
	result = channel->set3DAttributes(&srcPos, NULL);//�������Ҫ���涼����ЧӦ��srcVel��NULL����
	ErrCheck(result);

	return true;
}

bool SoundSys::SetEarAttributes(FMOD_VECTOR earPos, FMOD_VECTOR earVel, FMOD_VECTOR earForward, FMOD_VECTOR earUp) //system
{
	result = system->set3DListenerAttributes(0, &earPos, &earVel, &earForward, &earUp);
	ErrCheck(result);

	return true;
}

void SoundSys::Update3DEffect()
{
	system->update();
	Sleep(INTERFACE_UPDATETIME - 1);
}

void SoundSys::ExitSys()
{
	//�Զ����channel��sound���ͷţ��Ұ����˶�System::close�ĵ���
	result = system->release(); 
}