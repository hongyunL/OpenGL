#pragma once

#include "GLPointf.h"
#include "GLVector3Df.h"
#include "Texture.h"

/*OpenGL�����᷽��
*	x�᣺��Ļ���½�->���½�
*	y�᣺��Ļ���½�->���Ͻ�
*	z�᣺����
* ����ڷŷ�������x��������ͷ������y��������
*/
class Camera{
public:
	Camera();

	void SetEyePos(float eyeX, float eyeY, float eyeZ);
	void SetTargetPos(float targetX, float targetY, float targetZ);

	/*�����˳ƻ�������
	* ������
	*	1.����	
	*	2.���Ұڽ�
	*	3.��������*/
	void SetViewAngleWithTargetFixed(float distance, float rotY, float rotZ);

	/*��һ�˳ƻ�����Χ
	* ������
	*	1.���Ұڽ�
	*	2.��������*/
	void SetViewAngleWithEyeFixed(float rotY, float rotZ);

	/* Ӧ������� */
	void Apply();

	/* ������Ұ���� */
	void UpdatePerspective(float aspect, float ratioWH);

	/* ����Ϊ����3D���� */

	//�����Ӿ����6����ķ���ϵ��
	void UpdateFrustum(); 
	//����͸��ҫ��
	void RenderLensFlare(GLPointf p); 

private:
	bool IsPointInFrustum(GLPointf p); //�ж�һ�����Ƿ����Ӿ�����
	bool IsOccluded(GLPointf p); //����ĳ�����Ƿ�λ�ڵ�ǰ���������ǰ��

	void RenderHalo(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLPointf p, GLfloat scale);
	void RenderGlow(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLPointf p, GLfloat scale);
	void RenderBigGlow(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLPointf p, GLfloat scale);
	void RenderStreaks(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLPointf p, GLfloat scale);

	GLPointf m_eyePos;
	GLPointf m_targetPos;

	/*������Ұ������*/
	float m_aspect;  //��Ұ��ȽǶ�
	float m_ratioWH; //��߱�
	float m_near;
	float m_far;

	//�Ӿ����6����ķ���ϵ��
	float m_Frustum[6][4];

	//��������
	Texture m_HaloTexture;
	Texture m_GlowTexture;
	Texture m_BigGlowTexture;
	Texture m_StreakTexture;

	//���߷���λ����
	GLVector3Df m_directionVector;

	//float m_HeadingDegrees;/////////////////////////////////////////////
	//float m_PitchDegrees;
};

inline void Camera::SetEyePos(float eyeX, float eyeY, float eyeZ)
{
	m_eyePos.x = eyeX;
	m_eyePos.y = eyeY;
	m_eyePos.z = eyeZ;
}

inline void Camera::SetTargetPos(float targetX, float targetY, float targetZ)
{
	m_targetPos.x = targetX;
	m_targetPos.y = targetY;
	m_targetPos.z = targetZ;
}