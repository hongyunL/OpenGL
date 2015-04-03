#pragma once

#include "Object.h"
#include "Controllable.h"
#include "Movable.h"

class TestPlane : public Object , public Controllable , public Movable
{
public:
	TestPlane();

	void Render();

	void RenderShadow(float lightPos[4]);

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


inline void TestPlane::SetSpeed(float speed)
{
	m_speed = speed;
}

//ǰ������
inline void TestPlane::Forward()
{
	if (m_speed < m_speedMax)
		m_speed += m_speedAcceleration; //����������ֵ��ʵΪAcceleration - Recovery��
}
inline void TestPlane::Backward()
{
	if (m_speed > m_speedMin)
		m_speed -= m_speedAcceleration;
}

//����ת��
inline void TestPlane::TurnLeft()
{
	if (m_rotW < m_rotWMax)
		m_rotW += m_rotWAcceleration;
}
inline void TestPlane::TurnRight()
{
	if (m_rotW > m_rotWMin)
		m_rotW -= m_rotWAcceleration;
}