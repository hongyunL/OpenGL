#pragma once

class WorldObject{
public:
	WorldObject();

	/*��Ⱦ����Ļ��
	*����ֵ�����ʵ����Ⱦ�������Ƿ�ɾ��*/
	virtual bool render() = 0;
};