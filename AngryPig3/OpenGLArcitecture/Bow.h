#pragma once
#include "world\SolidObject.h"
/*barrel����ǹ����
*��ͼģʽ������Ҫ��������Ҫ���գ�ʹ����ɫ*/
class Bow : public SolidObject
{
public:
	Bow(void);

	/*��Ⱦ����Ļ��
	*����ֵ�����ʵ����Ⱦ�������Ƿ�ɾ��*/
	bool render() override;
};
