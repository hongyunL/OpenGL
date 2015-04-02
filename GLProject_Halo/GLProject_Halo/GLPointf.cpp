#include "GLPointf.h"

GLPointf::GLPointf()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}
GLPointf::GLPointf(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

//�� ��
GLPointf GLPointf::operator+(const GLVector3Df& vector)
{
	return GLPointf(x + vector.i, y + vector.j, z + vector.k);
}

GLPointf GLPointf::operator-(const GLVector3Df& vector)
{
	return GLPointf(x - vector.i, y - vector.j, z - vector.k);
}

//+= -=
GLPointf& GLPointf::operator+=(const GLVector3Df& vector)
{
	x += vector.i;
	y += vector.j;
	z += vector.k;

	return *this;
}

GLPointf& GLPointf::operator-=(const GLVector3Df& vector)
{
	x -= vector.i;
	y -= vector.j;
	z -= vector.k;

	return *this;
}

//���� = ��2 - ��1
GLVector3Df GLPointf::CalculateVector(const GLPointf& point1, const GLPointf& point2)
{
	return GLVector3Df(point2.x - point1.x, point2.y - point1.y, point2.z - point1.z);
}

//��ֵ�Ϳ�������
GLPointf::GLPointf(const GLPointf& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}
GLPointf& GLPointf::operator = (const GLPointf& other)
{
	if (this == &other)//����Լ����Լ���ֵ
	{
		return *this;//�����κδ���
	}
	else
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}
	return *this;
}