#pragma once
#include "world\SolidObject.h"
/*barrel����ǹ����
*��ͼģʽ������Ҫ��������Ҫ���գ�ʹ����ɫ*/
class Pig : public SolidObject
{
public:
	Pig(void);

	/*��Ⱦ����Ļ��
	*����ֵ�����ʵ����Ⱦ�������Ƿ�ɾ��*/
	bool render() override;
};
