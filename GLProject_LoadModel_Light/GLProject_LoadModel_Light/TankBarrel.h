#pragma once

#include "Object.h"

class TankBarrel : public Object
{
public:
	TankBarrel();

	void Render();

	void GetMuzzlePos(float *retX, float *retY, float *retZ); //�����ڿ�λ��

private:
	float m_speed;

};