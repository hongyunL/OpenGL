#pragma once
#include "world\DynamicObject.h"
/*��ͼģʽ������Ҫ��������Ҫ���գ�ʹ����ɫ*/
class Bird : public DynamicObject
{
public:
	Bird(void);

	/*��������С��ʱ����
	*������
	*1-3��λ��
	*4,5��ˮƽת�ǡ�����
	*6�����ٶ�*/
	void setInitStatus(float x, float y, float z, float rotY, float rotZ, float velocity);

	/*�������ĵ�����*/
	void getCenCoordinate(float *pResultX, float *pResultY, float *pResultZ);

	/*������ײ�뾶*/
	float getRadius();

	/*����ɱʱ����*/
	void killed();

	/*��Ⱦ����Ļ��
	*����ֵ�����ʵ����Ⱦ�������Ƿ�ɾ��*/
	bool render() override;

protected:
	bool m_removable;
};
