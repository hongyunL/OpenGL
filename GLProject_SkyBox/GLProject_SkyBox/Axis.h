#pragma once

#include "Object.h"

/*һ��Ԥ�õ��࣬���Ի��Ƴ��᳤�Ⱦ�Ϊ10������ϵ��
* ����x��Ϊ��ɫ��y��Ϊ��ɫ��z��Ϊ��ɫ
* ��ͼģʽ������Ҫ����������Ҫ���գ�ʹ����ɫ */
class Axis : public Object
{
public:
	Axis();

	void InitList();
	void Render();
};
