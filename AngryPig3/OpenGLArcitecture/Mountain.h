#pragma once

#include "world\SolidObject.h"
/*��ͼģʽ������Ҫ��������Ҫ���գ�ʹ����ɫ*/
class Mountain : public SolidObject
{
public:
	Mountain(void);

	/*��Ⱦ����Ļ��
	*����ֵ�����ʵ����Ⱦ�������Ƿ�ɾ��*/
	virtual bool render() override;

	~Mountain(void);
};