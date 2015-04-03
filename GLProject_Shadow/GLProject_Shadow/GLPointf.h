#pragma once

#include "GLVector3Df.h"

class GLPointf
{
public:
	GLPointf();
	GLPointf(float x, float y, float z);

	//�� = �� + ����
	GLPointf operator+(const GLVector3Df& vector);
	GLPointf operator-(const GLVector3Df& vector);

	GLPointf& operator+=(const GLVector3Df& vector);
	GLPointf& operator-=(const GLVector3Df& vector);

	//���� = ��2 - ��1
	static GLVector3Df CalculateVector(const GLPointf& point1, const GLPointf& point2);

	//��ֵ�Ϳ�������
	GLPointf(const GLPointf& other);
	GLPointf& operator=(const GLPointf& other);
	//~GLPointf();

	//Ϊ��ʹ�÷��㣬��ɹ��еģ���ûд��m_��
	float x;
	float y;
	float z;
};
