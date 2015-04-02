/*
* ����һ�����壬����Ҫ������Ⱦģʽ�����������Ĭ��ֵ�������ʡ�ԣ���Ȼ���ٽ�����Ⱦ
* ��Ⱦģʽ��
*	bool usingIndex      �Ƿ�ʹ��������Ĭ��true
*	bool usingLighting   �Ƿ�ʹ�ù��գ�Ĭ��true����׷�����ù��ղ���
*	ColorMode colorMode  ��ɫģʽ��Ĭ��TEXTURE //�Զ���������ͼ
*	GLenum mode          �����桱�Ļ��Ʒ���GL_CCW����ʱ�룩��GL_CW��˳ʱ�룩Ĭ����ʱ��
*	GLenum paintMode     ͬglBegin()����
*/

/*
* OpenGL�����᷽��
*	x�᣺��Ļ���½�->���½�
*	y�᣺��Ļ���½�->���Ͻ�
*	z�᣺����
* ����ڷŷ�������x��������ͷ������y��������
*/

#pragma once

#include "MeshModel.h"
#include "MathConst.h"

enum ColorMode{ COLOR, TEXTURE };

class Object
{
public:
	Object();

	/* OpenGL��״̬��������ÿһ��Ҫ���Ƶ����壬��Ҫ���趨������Ⱦģʽ */
	void SetRenderMode(
		bool usingIndex = false, 
		bool usingLighting = true, 
		ColorMode colorMode = TEXTURE, 
		GLenum mode = GL_CCW,
		GLenum paintMode = GL_TRIANGLES);

	void SetPos(float x, float y, float z);
	void SetRot(float rotX, float rotY, float rotZ);

	void GetPos(float *x, float *y, float *z);

	/* Ĭ���ƶ���ʽ�µĻ��ƣ�rotX,rotY,rotZ����ת���Ķ����������� */
	void Paint(unsigned vertexAmount); //�����趨�õ���Ⱦģʽ�����Ƴ�����������任����ת��ģ��

	/* �Զ����ƶ���ʽ�µĻ��� */
	void PaintModel(unsigned vertexAmount); //���Ƴ���û�о�������任����ת��ģ��

	/* �Ƿ�Ϊһ�������壨���ӵ��� */
	void SetAvailable(bool available);
	bool IsAvailable();

protected:
	int shadowDepth;

	/* �����Ƿ񻹼���ʹ�ã���Ⱦ�� */
	bool m_available;

	/* ��������λ�� */
	float m_x;
	float m_y;
	float m_z;

	float m_rotX; //������ס X�� ����ת�Ƕȣ����෭��
	float m_rotY; //������ס Y�� ����ת�Ƕȣ���ת��
	float m_rotZ; //������ס Z�� ����ת�Ƕȣ�������

	/* ��Ⱦ״̬ */
	bool m_usingIndex;
	bool m_usingLighting;
	ColorMode m_colorMode;
	GLenum m_mode;
	GLenum m_paintMode;

	MeshModel m_meshModel;
};

inline void Object::SetPos(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}
inline void Object::SetRot(float rotX, float rotY, float rotZ)
{
	m_rotX = rotX;
	m_rotY = rotY;
	m_rotZ = rotZ;
}

inline void Object::GetPos(float *x, float *y, float *z)
{
	*x = m_x;
	*y = m_y;
	*z = m_z;
}

/* �Ƿ�Ϊһ�������壨���ӵ��� */
inline void Object::SetAvailable(bool available)
{
	m_available = available;
}
inline bool Object::IsAvailable()
{
	return m_available;
}