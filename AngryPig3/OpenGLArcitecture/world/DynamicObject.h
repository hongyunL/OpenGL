#pragma once

#include "SolidObject.h"

class DynamicObject	: public SolidObject
{
public:
	DynamicObject();

	/*��Ⱦ����Ļ��
	*����ֵ�����ʵ����Ⱦ�������Ƿ�ɾ��*/
	virtual bool render() override;

	float vx;
	float vy;
	float vz;
};