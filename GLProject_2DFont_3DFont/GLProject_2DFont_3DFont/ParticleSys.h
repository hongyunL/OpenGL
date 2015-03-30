#pragma once

#include "Particles.h"

#define MAX_PARTICLES 100

/*��ʹ��run(),render()֮ǰ���رա���Ȳ��ԡ���֮���ٿ�����*/
class ParticleSys
{
public:
	ParticleSys();
	ParticleSys(int num);

	void SetAmount(int num);

	float GetAmount();
	//Particles GetParticle(int i);/////////////////////////////

	//~ParticleSys();

	Particles m_arrParticles[MAX_PARTICLES]; //������Ա��������ù������ţ�����

private:
	int m_num;
	

protected:
	virtual void Init() = 0;
	virtual void Run() = 0;
	virtual void Render() = 0;
};

inline void ParticleSys::SetAmount(int num)
{
	if (num < MAX_PARTICLES)
		m_num = num;
}

inline float ParticleSys::GetAmount()
{
	return m_num;
}