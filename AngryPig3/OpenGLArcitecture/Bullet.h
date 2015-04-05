#pragma once
#include "world\DynamicObject.h"
/*��̨���ӵ�
*��ͼģʽ������Ҫ����������Ҫ���գ�ʹ����ɫ*/
class Bullet : public DynamicObject
{
public:
	Bullet(void);

	/*���ݳ�ʼλ�úͽǶ�{ˮƽת�ǡ�����}����������*
	*����λ��
	*���ýǶ�
	*���ó��ٶ�*/
	void setInitStatus(float x, float y, float z, float rotY, float rotZ, float velocity);

	/*����ǰ�˵�����*/
	void getFrontCoord(float *pRetX, float *pRetY, float *pRetZ);

	/*����β�˵�����*/
	void getBackCoord(float *pRetX, float *pRetY, float *pRetZ);

	/*������Ŀ��ʱ����*/
	void hitTarget();

	/*��Ⱦ����Ļ��
	*����ֵ�����ʵ����Ⱦ�������Ƿ�ɾ��*/
	bool render() override;

protected:
	unsigned m_time;//�Ѿ����ڵ�ʱ��
	bool m_removable;//�Ƿ����ɾ��
};
