#include "Fog.h"

Fog::Fog()
{
	m_fogMode[0] = GL_EXP;
	m_fogMode[1] = GL_EXP2;
	m_fogMode[2] = GL_LINEAR;

	glFogi(GL_FOG_MODE, m_fogMode[2]); // ����������ģʽ

	m_fogColor[0] = 0.5f;
	m_fogColor[1] = 0.5f;
	m_fogColor[2] = 0.5f;
	m_fogColor[3] = 1.0f;

	glFogfv(GL_FOG_COLOR, m_fogColor); //����ɫ
	glFogf(GL_FOG_DENSITY, 0.01f);     //������Ũ��

	glFogf(GL_FOG_START, 240.0f); //�����Ŀ�ʼλ��
	glFogf(GL_FOG_END, 300.0f);  //�����Ľ���λ��
}

void Fog::SetFogMode(unsigned int fogFilter)
{
	glFogi(GL_FOG_MODE, m_fogMode[fogFilter]);
}

void Fog::SetFogColor(float r, float g, float b)
{
	m_fogColor[0] = r;
	m_fogColor[1] = g;
	m_fogColor[2] = b;
	m_fogColor[3] = 1.0f;

	glFogfv(GL_FOG_COLOR, m_fogColor);
}

void Fog::SetFogDensity(float density)
{
	glFogf(GL_FOG_DENSITY, density);
}

void Fog::SetFogDepth(float near, float far)
{
	glFogf(GL_FOG_START, near);	//�����Ŀ�ʼλ��
	glFogf(GL_FOG_END, far);    //�����Ľ���λ��
}

void Fog::Apply()
{
	glHint(GL_FOG_HINT, GL_DONT_CARE); //����ϵͳ��μ�������
	glEnable(GL_FOG);
}