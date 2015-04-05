#pragma once

#include <iostream>
#include <math.h>
using namespace std;

/*3ά������������float�ͱ�ʾ��ʹ�ñ�׼����ϵ��x���⣬y���ң�z���ϣ�ˮƽת���Գ���x�᷽��Ϊ0��
*��ע��openGLʹ��GL����ϵ��x���ң�y���ϣ�z���⣻ˮƽת���Գ���x�᷽��Ϊ0�㡿
*�����ٶȴ�С���ó��ȱ�ʾ����horiAng(ˮƽ���ϵ�ͶӰ��x��������ļн�)��elevAng���ٶȷ�����ˮƽ��ļнǣ������ǣ�
*��������x\y\z���ϵ�ͶӰ����*/
class Vector3f
{
public :
	Vector3f()
	{
		x=0;
		y=0;
		z=0;
	}

	void countProjectLenOnAxis(float length,float horiAng,float elevAng)
	{
		x = length*cos(elevAng*3.14/180)*cos(horiAng*3.14/180);
		y = length*cos(elevAng*3.14/180)*sin(horiAng*3.14/180);
		z = length*sin(elevAng*3.14/180);
	}
	
	double getX()
	{
		return x;
	}
	double getY()
	{
		return y;
	}
	double getZ()
	{
		return z;
	}

private :
	double x;
	double y;
	double z;
};