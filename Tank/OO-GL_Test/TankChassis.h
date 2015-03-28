#pragma once

#include "Object.h"
#include "Controllable.h"
#include "Movable.h"

class TankChassis : public Object , public Movable , public Controllable
{
public:
	TankChassis();

	void Render();

	void SetSpeed(float speed);

	/* interface��Movable��ʵ�� */
	void Move(); 
	
	/* interface��Controllable��ʵ�� */
	//ǰ������
	void Forward();
	void Backward();

	//����ת��
	void TurnLeft();
	void TurnRight();

	void Raise(){}
	void Bow(){}
	void RollLeft(){}
	void RollRight(){}

private:
	float m_speed;
	float m_speedMax;  //��ֵ
	float m_speedMin;  //��ֵ         
	float m_speedAcceleration; //����������ֵ��ʵΪAcceleration - Recovery��
	float m_speedRecovery;

	float m_rotW;
	float m_rotWMax; //��ֵ
	float m_rotWMin; //��ֵ
	float m_rotWAcceleration;
	float m_rotWRecovery;
};