#include "GLVector3Df.h"

#include <math.h>

GLVector3Df::GLVector3Df()
{
	i = 0.0f;
	j = 0.0f;
	k = 0.0f;

	length = sqrt(i*i + j*j + k*k);
}
GLVector3Df::GLVector3Df(float i, float j, float k)
{
	this->i = i;
	this->j = j;
	this->k = k;

	length = sqrt(i*i + j*j + k*k);
}

//�ӡ���������
GLVector3Df GLVector3Df::operator+(const GLVector3Df& other)
{
	return GLVector3Df(i + other.i, j + other.j, k + other.k);
}

GLVector3Df GLVector3Df::operator-(const GLVector3Df& other)
{
	return GLVector3Df(i - other.i, j - other.j, k - other.k);
}

GLVector3Df GLVector3Df::operator*(const float& length)
{
	return GLVector3Df(i * length, j * length, k * length);
}

//+= -= *=
GLVector3Df& GLVector3Df::operator+=(const GLVector3Df& other)
{
	i += other.i;
	j += other.j;
	k += other.k;

	return *this;
}

GLVector3Df& GLVector3Df::operator-=(const GLVector3Df& other)
{
	i -= other.i;
	j -= other.j;
	k -= other.k;

	return *this;
}

GLVector3Df& GLVector3Df::operator*=(const float& length)
{
	i *= length;
	j *= length;
	k *= length;

	return *this;
}

//��λ��
void GLVector3Df::Normalize()
{
	length = sqrt(i*i + j*j + k*k);

	i = i / length;
	j = j / length;
	k = k / length;
}

//��ֵ�Ϳ�������
GLVector3Df::GLVector3Df(const GLVector3Df& other)
{
	i = other.i;
	j = other.j;
	k = other.k;
}
GLVector3Df& GLVector3Df::operator = (const GLVector3Df& other)
{
	if (this == &other)//����Լ����Լ���ֵ
	{
		return *this;//�����κδ���
	}
	else
	{
		i = other.i;
		j = other.j;
		k = other.k;
	}
	return *this;
}