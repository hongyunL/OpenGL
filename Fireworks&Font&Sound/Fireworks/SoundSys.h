#pragma once

#include "fmod_errors.h"
#include "fmod.hpp"

#include <windows.h> 

#pragma comment(lib, "fmodex_vc.lib") //����Ƶ����뵽������

#include <map>

class SoundSys
{
public:
	SoundSys();

	bool CheckVersion(unsigned int version); //�Ƿ�Ϊ��ǰ֧�ֵİ汾

	void CreatSys(unsigned int channelMax); //ָ�����ɵ����������ĸ���

	void LoadSound(char *fileName); //���е����෽����Ӧ�÷���bool�ͣ�

	bool PlayMusic(char *fileName); //���ű������֣���Ӧ������ͣ���ܣ�����3D��Ч����Ӧ����3D�������ù��ܣ����¹���
	bool PlaySoundEffect(char *fileName); //���Ŷ��ݵ���Ч��û����ͣ���ܣ�û��3D��Ч

	bool SetPause(char *fileName, bool pause);
	bool Stop(char *fileName);

	void Use3DSound(bool used3D);

	bool SetSrcAttributes(char* fileName, FMOD_VECTOR srcPos, FMOD_VECTOR srcVel); //�趨��Դ��λ�ú��ٶ�(channel)
	bool SetEarAttributes(FMOD_VECTOR earPos, FMOD_VECTOR earVel, FMOD_VECTOR earForward, FMOD_VECTOR earUp); //�趨����λ�á��ٶȡ���ǰ�������Ϸ���(system)
	void Update3DEffect();

	void ExitSys();
	//~SoundSys();

private:
	//SoundSys(const SoundSys& other){}
	//SoundSys& operator=(const SoundSys& other){}

	void ErrCheck(FMOD_RESULT result);

	FMOD_RESULT result;
	FMOD::System * system;

	bool m_use3DSound;

	/* һ��sound���Բ��Ŷ�Σ�ÿ�β��Ŷ���õ��µ�channel�����һ��channelֻ�ܲ���һ�� *//////////ÿ�β��ţ�����//////////////////////
	std::map<char*, FMOD::Sound*> m_soundsMap;
	std::map<char*, FMOD::Sound*>::iterator m_soundIter;

	std::map<FMOD::Sound*, FMOD::Channel*> m_channelMap;
	std::map<FMOD::Sound*, FMOD::Channel*>::iterator m_channelIter;
};

inline
void SoundSys::Use3DSound(bool used3D)
{
	m_use3DSound = used3D;
}