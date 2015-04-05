#include "Camera.h"

#include <glut.h>
#include <math.h>
#include "../MathConst.h"

Camera::Camera()
{
	setEyePos(0.0f, 0.0f, 0.0f);
	setCenterPos(1.0f, 0.0f, 0.0f);

	m_aspect = 90.0f;
	m_ratioWH = 1.3333333f;//��Լ��Ӧ�ڿ�640����480
	m_near = 0.1f;
	m_far = 200.0f;

	setRatioWH(m_ratioWH);
}

/*�趨�۾����۲�㣩λ��*/
void Camera::setEyePos(float eyeX, float eyeY, float eyeZ)
{
	m_eyeX = eyeX;
	m_eyeY = eyeY;
	m_eyeZ = eyeZ;
}

/*�趨�۲����ģ����۲�㣩λ��*/
void Camera::setCenterPos(float centerX, float centerY, float centerZ)
{
	m_centerX = centerX;
	m_centerY = centerY;
	m_centerZ = centerZ;
}

/*�̶�����λ�ã����ݹ۲�Ƕȣ��Ƕ��ƣ��趨�۾�λ��
*������
*1.ˮƽ��ת�Ƕȣ���y����ת�ĽǶȣ�
*2.̧���Ƕȣ���z����ת�ĽǶȣ�*/
void Camera::setViewAngleWithCenterFixed(float distance, float rotY, float rotZ)
{
	float rXZ = distance * cos(rotZ * MathConst::A_TO_R);//��������ͶӰ��xzƽ���ĳ���

	m_eyeX = m_centerX - rXZ * cos(rotY * MathConst::A_TO_R);
	m_eyeZ = m_centerZ + rXZ * sin(rotY * MathConst::A_TO_R);
	m_eyeY = m_centerY - distance * sin(rotZ * MathConst::A_TO_R);
}

/*�̶��۾�λ�ã����ݹ۲�Ƕȣ��Ƕ��ƣ��趨�۲��λ�ã��൱�ڵ�һ�ӽǣ�*/
void Camera::setViewAngleWithEyeFixed(float rotY, float rotZ)
{
	//����������Ϊ1

	float rXZ = cos(rotZ * MathConst::A_TO_R);//��xzƽ���ϵ�ͶӰ�ĳ���

	m_centerX = m_eyeX + rXZ * cos(rotY * MathConst::A_TO_R);
	m_centerZ = m_eyeZ - rXZ * sin(rotY * MathConst::A_TO_R);
	m_centerY = m_eyeY + sin(rotZ * MathConst::A_TO_R);
}

/*�����߱�*/
void Camera::setRatioWH(float ratioWH)
{
	m_ratioWH = ratioWH;
	updatePerspective();
}

/*Ӧ�����������������ӽ�*/
void Camera::apply()
{
	glLoadIdentity();

	gluLookAt(
		m_eyeX, m_eyeY, m_eyeZ,
		m_centerX, m_centerY, m_centerZ,
		0, 1, 0);
}

/*ʹ�������������Ұ����*/
/*�����ӽǺ�ָ�����״̬ΪmodelView*/
void Camera::updatePerspective()
{
	//�޸�״̬ΪͶӰ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//�Ƕȣ���߱ȣ�����Զ
	gluPerspective(m_aspect, m_ratioWH, m_near, m_far);

	//�ָ�״̬Ϊģ����ͼ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}