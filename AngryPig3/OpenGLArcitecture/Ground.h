#pragma once
#include "world\SolidObject.h"
/*���棨ˮƽ�ľ��Σ�
*��ͼ��ʽ������Ҫ��������Ҫ���գ�ʹ����ɫ*/
class Ground : public SolidObject
{
public:
	/*�յ��޲ι��죬���Ƽ�����*/
	Ground(void);

	Ground(float x0, float z0, float x1, float z1, float height, float r, float g, float b);

	/*��Ⱦ����Ļ��
	*����ֵ�����ʵ����Ⱦ�������Ƿ�ɾ��*/
	bool render() override;

protected:
	void setPosition(float x0, float z0, float x1, float z1, float height);
	void setColor(float r, float g, float b);

	float m_x0, m_z0;
	float m_x1, m_z1;
	float m_height;
	float m_r, m_g, m_b;
};
													  ;