#pragma once
#include "world\SolidObject.h"
/*barrel����ǹ����
*��ͼģʽ������Ҫ��������Ҫ���գ�ʹ����ɫ*/
class GunBarrel : public SolidObject
{
public:
	GunBarrel(void);

	/*�������ڹ�ǰ�˵�����*/
	void countLeftFrontCoord(float *pRetX, float *pRetY, float *pRetZ);

	/*�������ڹ�ǰ�˵�����*/
	void countRightFrontCoord(float *pRetX, float *pRetY, float *pRetZ);


	/*��Ⱦ����Ļ��
	*����ֵ�����ʵ����Ⱦ�������Ƿ�ɾ��*/
	bool render() override;
};

