#include "TestPlane.h"
#include "TestPlaneData.h"

#include "MathConst.h"
#include <math.h>
#include "ProjectToAxis.h"

TestPlane::TestPlane() : Object()
{
	m_meshModel.LoadMeshDataWithTexFrom3DE(TestPlaneData::vertexNum,
		TestPlaneData::face_indicies, sizeof(TestPlaneData::face_indicies),
		TestPlaneData::vertices, sizeof(TestPlaneData::vertices),
		TestPlaneData::normals, sizeof(TestPlaneData::normals),
		std::string(TestPlaneData::texureFileName),
		TestPlaneData::textures, sizeof(TestPlaneData::textures));

	m_speed = 0;			   
	m_speedMax = 0.3;
	m_speedMin = -0.3; 
	m_speedAcceleration = 0.02; 
	m_speedRecovery = 0.01;     

	m_rotY = 0; //��ǰת��

	m_rotW = 0; //���̿��Ƶ���rotW��
	m_rotWMax = 1;
	m_rotWMin = -1;
	m_rotWAcceleration = 0.04; //ʵ�ʵı仯�ٶ�Ϊ0.04-0.02��
	m_rotWRecovery = 0.02;

	m_rotZ = 0; //��ǰ����
}

void TestPlane::SetSpeed(float speed)
{
	m_speed = speed;
}

/*���� �ٶȡ�ת�ǡ����� ���� λ��
* ����״̬�Ļָ� */
void TestPlane::Move()
{
	/* ����״̬�ָ� */
	if (m_rotW > 0) 
		m_rotW -= m_rotWRecovery; //��1ÿ�ؼ���0.02��0Ҳ��תһ���
	if (m_rotW < 0)
		m_rotW += m_rotWRecovery;

	m_rotY += m_rotW;

	/* ����෭ ���ٶ��Ի���Ϊ��λ */
	//					  ���ٶȡ����ٶ�
	//����ʽ��tan�� =  ----------------���ȴ���෭�ĽǶ�
	//					     �������ٶ� 
	//angel = atan(slope)
	//x �ķ����к���ֵtan - 1x�����ص�ֵ��[-pi / 2, pi / 2] ֮��
	//m_rotX = -atan(m_rotW * MathConst::A_TO_R * m_speed / MathConst::PHYSICS_G)*10000*5; //ûЧ������//�ر�С����

	//ֻ��ת�Ǻ�����Ӱ���ٶȷ��򣬲෭�ǲ�Ӱ���ٶȷ���
	float lenX = 0;
	float lenY = 0;
	float lenZ = 0;
	ProjectToAxis::CountProjectLenOnAxis(&lenX, &lenY, &lenZ, m_speed, m_rotY, m_rotZ);

	m_x += lenX;
	m_y += lenY;
	m_z -= lenZ; //��-������Ϊx�����Ϊz�ĸ����򣬶�rotY������ת�ģ�
}


//ǰ������
void TestPlane::Forward()
{
	if (m_speed < m_speedMax)
		m_speed += m_speedAcceleration; //����������ֵ��ʵΪAcceleration - Recovery��
}
void TestPlane::Backward()
{
	if (m_speed > m_speedMin)
		m_speed -= m_speedAcceleration;
}

//����ת��
void TestPlane::TurnLeft()
{
	if (m_rotW < m_rotWMax)
		m_rotW += m_rotWAcceleration;
}
void TestPlane::TurnRight()
{
	if (m_rotW > m_rotWMin)
		m_rotW -= m_rotWAcceleration;
}


void TestPlane::Render()
{
	Paint(TestPlaneData::vertexNum); //Ĭ���ƶ���ʽ�µĻ���
}