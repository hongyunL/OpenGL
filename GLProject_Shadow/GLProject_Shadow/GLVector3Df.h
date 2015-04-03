#pragma once

class GLVector3Df
{
public:
	GLVector3Df();
	GLVector3Df(float i, float j, float k);

	//�ӡ���������
	GLVector3Df operator+(const GLVector3Df& other);
	GLVector3Df operator-(const GLVector3Df& other);
	GLVector3Df operator*(const float& length);

	//+= -= *=
	GLVector3Df& operator+=(const GLVector3Df& other);
	GLVector3Df& operator-=(const GLVector3Df& other);
	GLVector3Df& operator*=(const float& length);

	//��λ��
	void Normalize();

	//��ֵ�Ϳ�������
	GLVector3Df(const GLVector3Df& other);
	GLVector3Df& operator=(const GLVector3Df& other);
	//~GLPointf();

	//Ϊ��ʹ�÷��㣬��ɹ��еģ���ûд��m_��
	float i;
	float j;
	float k;
	float length;
};