#pragma once
#include "world\SolidObject.h"
//һ��Ԥ�õ��࣬���Ի��Ƴ��᳤�Ⱦ�Ϊ10������ϵ��
//����x��Ϊ��ɫ��y��Ϊ��ɫ��z��Ϊ��ɫ
//��ͼģʽ������Ҫ����������Ҫ���գ�ʹ����ɫ
class Axis :
	public SolidObject
{
public:
	Axis(void);

	/*��Ⱦ����Ļ��
	*����ֵ�����ʵ����Ⱦ�������Ƿ�ɾ��*/
	virtual bool render();

	~Axis(void);
};

