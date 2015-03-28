/*Ŀǰ����ֻ�������û��ʹ��������
* �����Ҫʹ�����������glFogi(GL_FOG_COORD_SRC,GL_FOG_COORD)��ʽ������������Ϊ�����
* ����glFogCoordf(x)��д�����꣡����
* ���������ǰ���ģ���ϵģ������������ڵģ�*/
#pragma once

#include <glut.h>

class Fog
{
public:
	Fog();

	void SetFogMode(unsigned int fogFilter);
	void SetFogColor(float r, float g, float b);
	void SetFogDensity(float density);
	void SetFogDepth(float near, float far);

	void Apply();

private:
	unsigned int m_fogMode[3]; //������ģʽ
	float m_fogColor[4];
};