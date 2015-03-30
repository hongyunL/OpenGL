#include "Camera.h"

#include <glut.h>
#include <math.h>
#include "MathConst.h"

#include <iostream>

/*OpenGL�����᷽��
*	x�᣺��Ļ���½�->���½�
*	y�᣺��Ļ���½�->���Ͻ�
*	z�᣺����
* ����ڷŷ�������x��������ͷ������y��������
*/
Camera::Camera()
{
	SetEyePos(0.0f, 0.0f, 0.0f);
	SetTargetPos(1.0f, 0.0f, 0.0f);

	m_aspect = 90.0f;
	m_ratioWH = 1.3333333f; //��Լ��Ӧ�ڿ�640����480
	m_near = 0.1f;
	m_far = 3000.0f;
}

void Camera::SetEyePos(float eyeX, float eyeY, float eyeZ)
{
	m_eyeX = eyeX;
	m_eyeY = eyeY;
	m_eyeZ = eyeZ;
}

void Camera::SetTargetPos(float targetX, float targetY, float targetZ)
{
	m_targetX = targetX;
	m_targetY = targetY;
	m_targetZ = targetZ;
}

/*�����˳ƻ�������
* ������
*	1.����
*	2.���Ұڽ�
*	3.��������*/
void Camera::SetViewAngleWithTargetFixed(float distance, float rotY, float rotZ)
{
	float rXZ = distance * cos(rotZ * MathConst::PI / 180); //��������ͶӰ��xzƽ���ĳ���

	m_eyeX = m_targetX - rXZ * cos(rotY * MathConst::PI / 180);
	m_eyeZ = m_targetZ + rXZ * sin(rotY * MathConst::PI / 180);
	m_eyeY = m_targetY - distance * sin(rotZ * MathConst::PI / 180);
}

/*��һ�˳ƻ�����Χ
* ������
*	1.���Ұڽ�
*	2.��������*/
void Camera::SetViewAngleWithEyeFixed(float rotY, float rotZ)//���������Ҫ�趨rotZ
{
	//����������Ϊ1
	float rXZ = cos(rotZ * MathConst::PI / 180);//��xzƽ���ϵ�ͶӰ�ĳ���

	m_targetX = m_eyeX + rXZ * cos(rotY * MathConst::PI / 180);
	m_targetZ = m_eyeZ - rXZ * sin(rotY * MathConst::PI / 180);
	m_targetY = m_eyeY + sin(rotZ * MathConst::PI / 180);
}

/* ʹ�������������Ұ���� */
void Camera::UpdatePerspective(float aspect, float ratioWH)
{
	m_aspect = aspect;
	m_ratioWH = ratioWH;

	//�޸�״̬ΪͶӰ����
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//�Ƕȣ���߱ȣ�����Զ
	gluPerspective(m_aspect, m_ratioWH, m_near, m_far);

	//�ָ�״̬Ϊģ����ͼ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*Ӧ�����������������ӽ�*/
void Camera::Apply()
{
	glLoadIdentity();

	gluLookAt(
		m_eyeX, m_eyeY, m_eyeZ,
		m_targetX, m_targetY, m_targetZ,
		0, 1, 0); 
}