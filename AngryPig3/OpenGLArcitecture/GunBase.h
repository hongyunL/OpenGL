#pragma once
#include "world\SolidObject.h"
/*barrel����ǹ����
*��ͼģʽ������Ҫ��������Ҫ���գ�ʹ����ɫ*/
class GunBase : public SolidObject
{
public:
	GunBase(void);

	/*��Ⱦ����Ļ��
	*����ֵ�����ʵ����Ⱦ�������Ƿ�ɾ��*/
	bool render() override;
};