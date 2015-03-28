#include "TankChassis.h"
#include "TankChassisData.h"

#include "MathConst.h"
#include <math.h>
#include "ProjectToAxis.h"

#include <iostream>///////////////////////////////

TankChassis::TankChassis() : Object()
{
	m_meshModel.LoadMeshDataWithTexFrom3DE(TankChassisData::vertexNum,
		TankChassisData::face_indicies, sizeof(TankChassisData::face_indicies),
		TankChassisData::vertices, sizeof(TankChassisData::vertices),
		TankChassisData::normals, sizeof(TankChassisData::normals),
		std::string(TankChassisData::texureFileName),
		TankChassisData::textures, sizeof(TankChassisData::textures));

	m_speed = 0;
	m_speedMax = 0.2;
	m_speedMin = -0.2;
	m_speedAcceleration = 0.02;
	m_speedRecovery = 0.01;

	m_rotY = 0; //��ǰת��

	m_rotW = 0; //���̿��Ƶ���rotW��
	m_rotWMax = 1;
	m_rotWMin = -1;
	m_rotWAcceleration = 0.04; //ʵ�ʵı仯�ٶ�Ϊ0.04-0.02��
	m_rotWRecovery = 0.02;
}

void TankChassis::SetSpeed(float speed)
{
	m_speed = speed;
}

//�̳и���ķ�����������෭�ǡ�����ָ�
void TankChassis::Move()
{
	/* ����״̬�ָ� */
	if (m_rotW > 0)
		m_rotW -= m_rotWRecovery; //��1ÿ�ؼ���0.02��0Ҳ��תһ���
	if (m_rotW < 0)
		m_rotW += m_rotWRecovery;

	m_rotY += m_rotW;

	//ֻ��ת�Ǻ�����Ӱ���ٶȷ��򣬲෭�ǲ�Ӱ���ٶȷ���
	float lenX = 0;
	float lenY = 0;
	float lenZ = 0;
	ProjectToAxis::CountProjectLenOnAxis(&lenX, &lenY, &lenZ, m_speed, m_rotY, m_rotZ);

	m_x += lenX;
	m_y += lenY;
	m_z -= lenZ;

}

//ǰ������
void TankChassis::Forward()
{
	if (m_speed < m_speedMax)
		m_speed += m_speedAcceleration; //����������ֵ��ʵΪAcceleration - Recovery��
}
void TankChassis::Backward()
{
	if (m_speed > m_speedMin)
		m_speed -= m_speedAcceleration;
}

//����ת��
void TankChassis::TurnLeft()
{
	if (m_rotW < m_rotWMax)
		m_rotW += m_rotWAcceleration;
}
void TankChassis::TurnRight()
{
	if (m_rotW > m_rotWMin)
		m_rotW -= m_rotWAcceleration;
}

void TankChassis::Render()
{
	Paint(TankChassisData::vertexNum);
}