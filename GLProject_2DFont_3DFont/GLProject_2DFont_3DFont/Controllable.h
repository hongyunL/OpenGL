#pragma once

/*interface���ɿ��Ƶ�*/
class Controllable
{
public:
	Controllable(){};

	/*ע�⣬��ö�������������������������಻��������������������
	* �������Ϊ�������������������������壬��Ϊ�����������ø��������� */
	virtual ~Controllable() = 0{}; 

	/* ���������д���溯��������ʵ�ֿ���Ϊ�գ� */

	//ǰ�����ˣ����������Ҫ�ָ����������Run��������ӣ�
	virtual void Forward() = 0;
	virtual void Backward() = 0;

	//����ת��
	virtual void TurnLeft() = 0;
	virtual void TurnRight() = 0;

	//��������
	virtual void Raise() = 0;
	virtual void Bow() = 0;

	//���Ҳ෭ //������ǹ�ܵ�ת�������õ���
	virtual void RollLeft() = 0;
	virtual void RollRight() = 0;
};