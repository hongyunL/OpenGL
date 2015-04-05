#include "Light.h"

#include <glut.h>
#include <string.h>

Light::Light(void)
{
	m_id = 0;
	memset(m_ambient, 0, sizeof(m_ambient));
	memset(m_diffuse, 0, sizeof(m_diffuse));
	glLightfv(GL_LIGHT0 + m_id, GL_AMBIENT, m_ambient);
    glLightfv(GL_LIGHT0 + m_id, GL_DIFFUSE, m_diffuse);
}

/*������ţ�������ڣ�����0-7֮��*/
Light::Light(unsigned short id)
{
	m_id = id;
	memset(m_ambient, 0, sizeof(m_ambient));
	memset(m_diffuse, 0, sizeof(m_diffuse));
	glLightfv(GL_LIGHT0 + m_id, GL_AMBIENT, m_ambient);
    glLightfv(GL_LIGHT0 + m_id, GL_DIFFUSE, m_diffuse);
}

/*�������Դ*/
void Light::turnOn()
{
	glEnable(GL_LIGHT0 + m_id);
}

/*�ر������Դ*/
void Light::turnOff()
{
	glDisable(GL_LIGHT0 + m_id);
}

/*�趨������*/
void Light::setAmbient(float *src)
{
	memcpy(m_ambient, src, sizeof(m_ambient));
	glLightfv(GL_LIGHT0 + m_id, GL_AMBIENT, m_ambient);
}

/*�趨ɢ���*/
void Light::setDiffuse(float *src)
{
	memcpy(m_diffuse, src, sizeof(m_diffuse));
	glLightfv(GL_LIGHT0 + m_id, GL_DIFFUSE, m_diffuse);
}

void Light::Enable()
{
	//�򿪹���
	glEnable(GL_LIGHTING);
	//����ɫ׷��
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

Light::~Light(void)
{
}
