#pragma once

#include "Object.h"

class TankChassis : public Object
{
public:
	TankChassis();

	void Render();

	void SetSpeed(float speed);

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