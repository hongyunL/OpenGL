#pragma once
#include "Object.h"
#include "Movable.h"

/*��ͼģʽ������Ҫ��������Ҫ���գ�ʹ����ɫ*/
class TankShell : public Object , public Movable
{
public:
	TankShell(void);

	void SetSpeed(float speed);

	/* interface��Movable��ʵ�� */
	void Move();

	void Render();

private:
	float m_speed;
};
