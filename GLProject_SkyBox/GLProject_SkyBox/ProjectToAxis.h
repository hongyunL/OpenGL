#pragma once

#include <math.h>

/*
* ��ע��openGLʹ��GL����ϵ��x���ң�y���ϣ�z���⣻��
*
* �����ٶȴ�С���ó��ȱ�ʾ����horiAng(ˮƽ���ϵ�ͶӰ��x��������ļн�)��elevAng���ٶȷ�����ˮƽ��ļнǣ������ǣ�
* ��������x\y\z���ϵ�ͶӰ����
* ����ġ��ٶȡ���ȫ���ٶȣ��൱���˶����г�����Եľֲ��ٶȾ������ڳ������߶�
*/
class ProjectToAxis
{
public :
	//�ֲ�����ϵ ת���� ��������ϵ
	static void CountProjectLenOnAxis(
		float *lenX, float *lenY, float *lenZ,
		float length,float horiAng,float elevAng)
	{
		*lenX = length*cos(elevAng*3.14 / 180)*cos(horiAng*3.14 / 180);
		*lenY = length*sin(elevAng*3.14 / 180);
		*lenZ = length*cos(elevAng*3.14 / 180)*sin(horiAng*3.14 / 180);
	}
};