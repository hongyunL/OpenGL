#pragma once
#include "world\SolidObject.h"
/*barrel����ǹ����
*��ͼģʽ������Ҫ��������Ҫ���գ�ʹ����ɫ*/
class Castle : public SolidObject
{
public:
	Castle(void);

	/*��Ⱦ����Ļ��
	*����ֵ�����ʵ����Ⱦ�������Ƿ�ɾ��*/
	bool render() override;
};