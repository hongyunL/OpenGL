#include "Camera.h"

#include <glut.h>
#include <math.h>
#include "MathConst.h"

#include <iostream>//////////////////////////////////////

Camera::Camera()
{
	SetEyePos(0.0f, 0.0f, 0.0f);
	SetTargetPos(1.0f, 0.0f, 0.0f);

	m_directionVector = GLPointf::CalculateVector(m_eyePos, m_targetPos);
	m_directionVector.Normalize();

	m_aspect = 75.0f;
	m_ratioWH = 1.3333333f; //��Լ��Ӧ�ڿ�640����480
	m_near = 0.1f;
	m_far = 700.0f;
}

/*�����˳ƻ�������
* ������
*	1.����
*	2.���Ұڽ�
*	3.��������*/
void Camera::SetViewAngleWithTargetFixed(float distance, float rotY, float rotZ)
{
	float rXZ = distance * cos(rotZ * MathConst::PI / 180); //��������ͶӰ��xzƽ���ĳ���

	m_eyePos.x = m_targetPos.x - rXZ * cos(rotY * MathConst::PI / 180);
	m_eyePos.y = m_targetPos.y - distance * sin(rotZ * MathConst::PI / 180);
	m_eyePos.z = m_targetPos.z + rXZ * sin(rotY * MathConst::PI / 180);

	m_directionVector = GLPointf::CalculateVector(m_eyePos, m_targetPos);
	m_directionVector.Normalize();
}

/*��һ�˳ƻ�����Χ
* ������
*	1.���Ұڽ�
*	2.��������*/
void Camera::SetViewAngleWithEyeFixed(float rotY, float rotZ)//���������Ҫ�趨rotZ
{
	//����������Ϊ1
	float rXZ = cos(rotZ * MathConst::PI / 180);//��xzƽ���ϵ�ͶӰ�ĳ���
	
	m_targetPos.x = m_eyePos.x + rXZ * cos(rotY * MathConst::PI / 180);
	m_targetPos.y = m_eyePos.y + sin(rotZ * MathConst::PI / 180);
	m_targetPos.z = m_eyePos.z - rXZ * sin(rotY * MathConst::PI / 180);

	m_directionVector = GLPointf::CalculateVector(m_eyePos, m_targetPos);
	m_directionVector.Normalize();
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
		m_eyePos.x, m_eyePos.y, m_eyePos.z,
		m_targetPos.x, m_targetPos.y, m_targetPos.z,
		0, 1, 0); 
}



// ��õ�ǰ�Ӿ����6��ƽ�淽�̵Ĳ���
void Camera::UpdateFrustum()
{
	GLfloat   clip[16];
	GLfloat   proj[16];
	GLfloat   modl[16];
	GLfloat   t;
	//����ͶӰ����
	glGetFloatv(GL_PROJECTION_MATRIX, proj);

	//����ģ�ͱ任����
	glGetFloatv(GL_MODELVIEW_MATRIX, modl);

	//������о��󣬼�������������ĳ˻�
	clip[0] = modl[0] * proj[0] + modl[1] * proj[4] + modl[2] * proj[8] + modl[3] * proj[12];
	clip[1] = modl[0] * proj[1] + modl[1] * proj[5] + modl[2] * proj[9] + modl[3] * proj[13];
	clip[2] = modl[0] * proj[2] + modl[1] * proj[6] + modl[2] * proj[10] + modl[3] * proj[14];
	clip[3] = modl[0] * proj[3] + modl[1] * proj[7] + modl[2] * proj[11] + modl[3] * proj[15];

	clip[4] = modl[4] * proj[0] + modl[5] * proj[4] + modl[6] * proj[8] + modl[7] * proj[12];
	clip[5] = modl[4] * proj[1] + modl[5] * proj[5] + modl[6] * proj[9] + modl[7] * proj[13];
	clip[6] = modl[4] * proj[2] + modl[5] * proj[6] + modl[6] * proj[10] + modl[7] * proj[14];
	clip[7] = modl[4] * proj[3] + modl[5] * proj[7] + modl[6] * proj[11] + modl[7] * proj[15];

	clip[8] = modl[8] * proj[0] + modl[9] * proj[4] + modl[10] * proj[8] + modl[11] * proj[12];
	clip[9] = modl[8] * proj[1] + modl[9] * proj[5] + modl[10] * proj[9] + modl[11] * proj[13];
	clip[10] = modl[8] * proj[2] + modl[9] * proj[6] + modl[10] * proj[10] + modl[11] * proj[14];
	clip[11] = modl[8] * proj[3] + modl[9] * proj[7] + modl[10] * proj[11] + modl[11] * proj[15];

	clip[12] = modl[12] * proj[0] + modl[13] * proj[4] + modl[14] * proj[8] + modl[15] * proj[12];
	clip[13] = modl[12] * proj[1] + modl[13] * proj[5] + modl[14] * proj[9] + modl[15] * proj[13];
	clip[14] = modl[12] * proj[2] + modl[13] * proj[6] + modl[14] * proj[10] + modl[15] * proj[14];
	clip[15] = modl[12] * proj[3] + modl[13] * proj[7] + modl[14] * proj[11] + modl[15] * proj[15];

	//��ȡ�����ƽ�淽��ϵ��
	m_Frustum[0][0] = clip[3] - clip[0];
	m_Frustum[0][1] = clip[7] - clip[4];
	m_Frustum[0][2] = clip[11] - clip[8];
	m_Frustum[0][3] = clip[15] - clip[12];
	t = GLfloat(sqrt(m_Frustum[0][0] * m_Frustum[0][0] + m_Frustum[0][1] * m_Frustum[0][1] + m_Frustum[0][2] * m_Frustum[0][2]));
	m_Frustum[0][0] /= t;
	m_Frustum[0][1] /= t;
	m_Frustum[0][2] /= t;
	m_Frustum[0][3] /= t;

	//��ȡ�����ƽ�淽��ϵ��
	m_Frustum[1][0] = clip[3] + clip[0];
	m_Frustum[1][1] = clip[7] + clip[4];
	m_Frustum[1][2] = clip[11] + clip[8];
	m_Frustum[1][3] = clip[15] + clip[12];
	t = GLfloat(sqrt(m_Frustum[1][0] * m_Frustum[1][0] + m_Frustum[1][1] * m_Frustum[1][1] + m_Frustum[1][2] * m_Frustum[1][2]));
	m_Frustum[1][0] /= t;
	m_Frustum[1][1] /= t;
	m_Frustum[1][2] /= t;
	m_Frustum[1][3] /= t;

	//��ȡ�����ƽ�淽��ϵ��
	m_Frustum[2][0] = clip[3] + clip[1];
	m_Frustum[2][1] = clip[7] + clip[5];
	m_Frustum[2][2] = clip[11] + clip[9];
	m_Frustum[2][3] = clip[15] + clip[13];
	t = GLfloat(sqrt(m_Frustum[2][0] * m_Frustum[2][0] + m_Frustum[2][1] * m_Frustum[2][1] + m_Frustum[2][2] * m_Frustum[2][2]));
	m_Frustum[2][0] /= t;
	m_Frustum[2][1] /= t;
	m_Frustum[2][2] /= t;
	m_Frustum[2][3] /= t;

	//��ȡ�����ƽ�淽��ϵ��
	m_Frustum[3][0] = clip[3] - clip[1];
	m_Frustum[3][1] = clip[7] - clip[5];
	m_Frustum[3][2] = clip[11] - clip[9];
	m_Frustum[3][3] = clip[15] - clip[13];
	t = GLfloat(sqrt(m_Frustum[3][0] * m_Frustum[3][0] + m_Frustum[3][1] * m_Frustum[3][1] + m_Frustum[3][2] * m_Frustum[3][2]));
	m_Frustum[3][0] /= t;
	m_Frustum[3][1] /= t;
	m_Frustum[3][2] /= t;
	m_Frustum[3][3] /= t;

	//��ȡԶ���ƽ�淽��ϵ��
	m_Frustum[4][0] = clip[3] - clip[2];
	m_Frustum[4][1] = clip[7] - clip[6];
	m_Frustum[4][2] = clip[11] - clip[10];
	m_Frustum[4][3] = clip[15] - clip[14];
	t = GLfloat(sqrt(m_Frustum[4][0] * m_Frustum[4][0] + m_Frustum[4][1] * m_Frustum[4][1] + m_Frustum[4][2] * m_Frustum[4][2]));
	m_Frustum[4][0] /= t;
	m_Frustum[4][1] /= t;
	m_Frustum[4][2] /= t;
	m_Frustum[4][3] /= t;

	//��ȡ�����ƽ�淽��ϵ��
	m_Frustum[5][0] = clip[3] + clip[2];
	m_Frustum[5][1] = clip[7] + clip[6];
	m_Frustum[5][2] = clip[11] + clip[10];
	m_Frustum[5][3] = clip[15] + clip[14];
	t = GLfloat(sqrt(m_Frustum[5][0] * m_Frustum[5][0] + m_Frustum[5][1] * m_Frustum[5][1] + m_Frustum[5][2] * m_Frustum[5][2]));
	m_Frustum[5][0] /= t;
	m_Frustum[5][1] /= t;
	m_Frustum[5][2] /= t;
	m_Frustum[5][3] /= t;
}

//����һ�����Բ�Ƿ����Ӿ�����
bool Camera::IsPointInFrustum(GLPointf p)
{
	for (unsigned int i = 0; i < 6; i++)
	{
		if (m_Frustum[i][0] * p.x + m_Frustum[i][1] * p.y + m_Frustum[i][2] * p.z + m_Frustum[i][3] < 0)
		{
			return(false);
		}
	}
	return(true);
}

//����ĳ�����Ƿ�λ�ڵ�ǰ�����������ǰ��
bool Camera::IsOccluded(GLPointf p)
{
	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16];
	GLdouble winx, winy, winz;
	GLdouble flareZ;
	GLfloat bufferZ;

	glGetIntegerv(GL_VIEWPORT, viewport);
	glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);

	// ���ض���p�ڵ�λ�������е�λ��
	gluProject(p.x, p.y, p.z, mvmatrix, projmatrix, viewport, &winx, &winy, &winz);
	flareZ = winz;

	// ��ȡ��(winx,winy)���������
	glReadPixels(winx, winy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &bufferZ);

	// ����������С�ڵ�����꣬�򷵻�true
	if (bufferZ < flareZ)
		return true;
	else
		return false;
}

//����͸��ҫ��
void Camera::RenderLensFlare(GLPointf lightPos) 
{
	// ������ǵĹ�Դ�����ǵ����߷�Χ�ڣ��������
	if (IsPointInFrustum(lightPos) == true)
	{
		//�����Դ���������ߵľ���
		GLfloat lengthFromEyeToLight = sqrt(
			(lightPos.x - m_eyePos.x)*(lightPos.x - m_eyePos.x) +
			(lightPos.y - m_eyePos.y)*(lightPos.y - m_eyePos.y) +
			(lightPos.z - m_eyePos.z)*(lightPos.z - m_eyePos.z));
		//std::cout << m_directionVector.i << " " << m_directionVector.j << " " << m_directionVector.k << std::endl;

		//�����ӳ�����������
		GLVector3Df vFromEyeToLight = m_directionVector * lengthFromEyeToLight;
		//std::cout << vFromEyeToLight.i << " " << vFromEyeToLight.j << " " << vFromEyeToLight.k << std::endl;

		//��������λ��
		GLPointf ptIntersect = m_eyePos;
		//std::cout << ptIntersect.x << " " << ptIntersect.y << " " << ptIntersect.z << std::endl;

		ptIntersect += vFromEyeToLight;
		//std::cout << ptIntersect.x << " " << ptIntersect.y << " " << ptIntersect.z << std::endl;

		//�������㵽��Դ������
		GLVector3Df vFromLightToIntersect = GLPointf::CalculateVector(lightPos, ptIntersect);

		//�������㵽��Դ�ľ���
		GLfloat lengthFromLightToIntersect = vFromLightToIntersect.length;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glDepthMask(GL_FALSE);//�����
		glEnable(GL_TEXTURE_2D);
		if (false == IsOccluded(lightPos))	//������οɼ�
		{
			//std::cout << lightPos.x <<" "<<lightPos.y<<" "<<lightPos.z << std::endl;

			//��Ⱦ�м�Ĺ���
			RenderBigGlow(0.60f, 0.60f, 0.8f, 1.0f, lightPos, 16.0f); //����һ��

			GLPointf pt;
			pt = lightPos;

			pt += vFromLightToIntersect * 0.05f;
			RenderStreaks(0.60f, 0.60f, 0.8f, 1.0f, pt, 16.0f);

			pt += vFromLightToIntersect * 0.08f;
			RenderGlow(0.8f, 0.8f, 1.0f, 0.5f, lightPos, 3.5f);
			//std::cout << pt.x << " " << pt.y << " " << pt.z << std::endl; //������ȷ

			//���Ƶ����ν���λ�õ�0.1���Ĺ���
			pt += vFromLightToIntersect * 0.1f;
			RenderGlow(0.9f, 0.6f, 0.4f, 0.5f, pt, 0.6f);
			//std::cout << vFromLightToIntersect.i << " " << vFromLightToIntersect.j << " " << vFromLightToIntersect.k<<std::endl;

			//���Ƶ����ν���λ�õ�0.15���Ĺ���
			pt += vFromLightToIntersect * 0.15f;
			RenderHalo(0.8f, 0.5f, 0.6f, 0.5f, pt, 1.7f);

			//���Ƶ����ν���λ�õ�0.175���Ĺ���
			pt += vFromLightToIntersect * 0.175f;
			RenderHalo(0.9f, 0.2f, 0.1f, 0.5f, pt, 0.83f);

			//���Ƶ����ν���λ�õ�0.285���Ĺ���
			pt += vFromLightToIntersect * 0.285f;
			RenderHalo(0.7f, 0.7f, 0.4f, 0.5f, pt, 1.6f);

			//���Ƶ����ν���λ�õ�0.2755���Ĺ���
			pt += vFromLightToIntersect * 0.2755f;
			RenderGlow(0.9f, 0.9f, 0.2f, 0.5f, pt, 0.8f);

			//���Ƶ����ν���λ�õ�0.4755���Ĺ���
			pt += vFromLightToIntersect * 0.4755f;
			RenderGlow(0.93f, 0.82f, 0.73f, 0.5f, pt, 1.0f);

			//���Ƶ����ν���λ�õ�0.49���Ĺ���
			pt += vFromLightToIntersect * 0.49f;
			RenderHalo(0.7f, 0.6f, 0.5f, 0.5f, pt, 1.4f);

			//���Ƶ����ν���λ�õ�0.65���Ĺ���
			pt += vFromLightToIntersect * 0.65f;
			RenderGlow(0.7f, 0.8f, 0.3f, 0.5f, pt, 1.8f);

			//���Ƶ����ν���λ�õ�0.63���Ĺ���
			pt += vFromLightToIntersect * 0.63f;
			RenderGlow(0.4f, 0.3f, 0.2f, 0.5f, pt, 1.4f);

			//���Ƶ����ν���λ�õ�0.8���Ĺ���
			pt += vFromLightToIntersect * 0.8f;
			RenderHalo(0.7f, 0.5f, 0.5f, 0.5f, pt, 1.4f);

			//���Ƶ����ν���λ�õ�0.7825���Ĺ���
			pt += vFromLightToIntersect * 0.7825f;
			RenderGlow(0.8f, 0.5f, 0.1f, 0.5f, pt, 0.6f);

			//���Ƶ����ν���λ�õ�1.0���Ĺ���
			pt += vFromLightToIntersect;
			RenderHalo(0.5f, 0.5f, 0.7f, 0.5f, pt, 1.7f);

			//���Ƶ����ν���λ�õ�0.975���Ĺ���
			pt += vFromLightToIntersect * 0.975f;
			RenderGlow(0.4f, 0.1f, 0.9f, 0.5f, pt, 2.0f);

		}
		glDisable(GL_BLEND);
		glDepthMask(GL_TRUE);
		glDisable(GL_TEXTURE_2D);
		glColor3f(1.0, 1.0, 1.0);
	}
}

void Camera::RenderHalo(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLPointf p, GLfloat scale)
{
	GLPointf q[4];

	q[0].x = (p.x - scale);
	q[0].y = (p.z - scale);

	q[1].x = (p.x - scale);
	q[1].y = (p.z + scale);

	q[2].x = (p.x + scale);
	q[2].y = (p.z - scale);

	q[3].x = (p.x + scale);
	q[3].y = (p.z + scale);
	//std::cout << p.x << " " << p.y << " " << p.z << std::endl; //Ϊʲô�ڶ� - ��Ϊ������������

	glPushMatrix();
	glTranslatef(p.x, p.y, p.z);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);//ת������
	//glRotatef(-m_HeadingDegrees, 0.0f, 1.0f, 0.0f);
	//glRotatef(-m_PitchDegrees, 1.0f, 0.0f, 0.0f);

	m_HaloTexture.LoadTexture("halo.bmp");
	m_HaloTexture.Apply();

	glColor4f(r, g, b, a);

	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(q[0].x, q[0].y);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(q[1].x, q[1].y);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(q[2].x, q[2].y);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(q[3].x, q[3].y);
	glEnd();
	glPopMatrix();
}

void Camera::RenderGlow(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLPointf p, GLfloat scale)
{
	GLPointf q[4];

	q[0].x = (p.x - scale);
	q[0].y = (p.z - scale);

	q[1].x = (p.x - scale);
	q[1].y = (p.z + scale);

	q[2].x = (p.x + scale);
	q[2].y = (p.z - scale);

	q[3].x = (p.x + scale);
	q[3].y = (p.z + scale);

	glPushMatrix();
	glTranslatef(p.x, p.y, p.z);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);//ת������
	//glRotatef(-m_HeadingDegrees, 0.0f, 1.0f, 0.0f);
	//glRotatef(-m_PitchDegrees, 1.0f, 0.0f, 0.0f);

	m_GlowTexture.LoadTexture("glow.bmp");
	m_GlowTexture.Apply();
	
	glColor4f(r, g, b, a);

	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(q[0].x, q[0].y);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(q[1].x, q[1].y);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(q[2].x, q[2].y);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(q[3].x, q[3].y);
	glEnd();
	glPopMatrix();
}

void Camera::RenderBigGlow(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLPointf p, GLfloat scale)
{
	GLPointf q[4];

	q[0].x = (p.x - scale);
	q[0].y = (p.z - scale);

	q[1].x = (p.x - scale);
	q[1].y = (p.z + scale);

	q[2].x = (p.x + scale);
	q[2].y = (p.z - scale);

	q[3].x = (p.x + scale);
	q[3].y = (p.z + scale);

	glPushMatrix();
	glTranslatef(p.x, p.y, p.z);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);//ת������
	//glRotatef(-m_HeadingDegrees, 0.0f, 1.0f, 0.0f);
	//glRotatef(-m_PitchDegrees, 1.0f, 0.0f, 0.0f);

	m_BigGlowTexture.LoadTexture("bigGlow.bmp");
	m_BigGlowTexture.Apply();
	
	glColor4f(r, g, b, a);

	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(q[0].x, q[0].y);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(q[1].x, q[1].y);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(q[2].x, q[2].y);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(q[3].x, q[3].y);
	glEnd();
	glPopMatrix();
}

void Camera::RenderStreaks(GLfloat r, GLfloat g, GLfloat b, GLfloat a, GLPointf p, GLfloat scale)
{
	GLPointf q[4];

	q[0].x = (p.x - scale);
	q[0].y = (p.z - scale);

	q[1].x = (p.x - scale);
	q[1].y = (p.z + scale);

	q[2].x = (p.x + scale);
	q[2].y = (p.z - scale);

	q[3].x = (p.x + scale);
	q[3].y = (p.z + scale);

	glPushMatrix();
	glTranslatef(p.x, p.y, p.z);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);//ת������
	//glRotatef(-m_HeadingDegrees, 0.0f, 1.0f, 0.0f);
	//glRotatef(-m_PitchDegrees, 1.0f, 0.0f, 0.0f);

	m_StreakTexture.LoadTexture("streak.bmp");
	m_StreakTexture.Apply();
	
	glColor4f(r, g, b, a);

	glBegin(GL_TRIANGLE_STRIP);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(q[0].x, q[0].y);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(q[1].x, q[1].y);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(q[2].x, q[2].y);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(q[3].x, q[3].y);
	glEnd();
	glPopMatrix();
}