/*
* ����һ�����壬����Ҫ������Ⱦģʽ�����������Ĭ��ֵ�������ʡ�ԣ���Ȼ���ٽ�����Ⱦ
* ��Ⱦģʽ��
*	bool usingIndex      �Ƿ�ʹ��������Ĭ��true
*	bool usingLighting   �Ƿ�ʹ�ù��գ�Ĭ��true����׷�����ù��ղ���
*	ColorMode colorMode  ��ɫģʽ��Ĭ��TEXTURE //�Զ���������ͼ
*	GLenum mode          �����桱�Ļ��Ʒ���GL_CCW����ʱ�룩��GL_CW��˳ʱ�룩Ĭ����ʱ��
*	GLenum paintMode     ͬglBegin()����
*/
#include "Object.h"
#include <math.h>
#include "ProjectToAxis.h"
#include "GLPointf.h"

Object::Object() 
{
	m_available = true;

	m_x = 0.0f;
	m_y = 0.0f;
	m_z = 0.0f;

	m_rotX = 0; //�෭��
	m_rotY = 0; //ת��
	m_rotZ = 0; //����

	m_usingIndex = false;
	m_usingLighting = true;
	m_colorMode = TEXTURE;
	m_mode = GL_CCW;
	m_paintMode = GL_TRIANGLES;
	//SetRenderModeӦ�÷��ڻ��Ƶ�ʱ����Ϊ��ʼ��ģ�͵�ʱ������û�ã�

	shadowDepth = 100;
}

void Object::SetRenderMode(
	bool usingIndex,
	bool usingLighting,
	ColorMode colorMode,
	GLenum mode,
	GLenum paintMode)
{
	m_usingIndex = usingIndex;
	m_usingLighting = usingLighting;
	m_colorMode = colorMode;
	m_mode = mode;
	m_paintMode = paintMode;

	if (usingLighting)
		glEnableClientState(GL_NORMAL_ARRAY);
	else
		glDisableClientState(GL_NORMAL_ARRAY);

	if (TEXTURE == colorMode)
	{
		glEnable(GL_TEXTURE_2D);
		m_meshModel.m_texture.Apply(); //�����ڻ���֮ǰ��������ͼ
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY); 
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
		glEnableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}


/* ���Ƴ�����������任����ת��ģ�� */
void Object::Paint(unsigned vertexAmount)
{
	glPushMatrix();
	
	glTranslatef(m_x, m_y, m_z);
	
	glRotatef(m_rotX, 1.0f, 0.0f, 0.0f); //�ڷ�ʱ�ĽǶȣ��͡�Move���޹أ�
	glRotatef(m_rotY, 0.0f, 1.0f, 0.0f);
	glRotatef(m_rotZ, 0.0f, 0.0f, 1.0f);
	
	PaintModel(vertexAmount);
	
	glPopMatrix();
}

/*���Ƴ���û�о�������任����ת��ģ�� */
void Object::PaintModel(unsigned vertexAmount)
{
	//ָ��ʹ�ö�������(size,type,stride,pointer)
	glVertexPointer(m_meshModel.m_vertexArray.GetSize(), m_meshModel.m_vertexArray.GetType(), 0, m_meshModel.m_vertexArray.GetInfoPointer());

	//�����Ҫ��װ�뷨����
	if (m_usingLighting)
	{
		glNormalPointer(m_meshModel.m_normalArray.GetType(), 0, m_meshModel.m_normalArray.GetInfoPointer());
	}

	//������Ⱦģʽװ����ɫ��������
	if (TEXTURE == m_colorMode)
	{
		glTexCoordPointer(m_meshModel.m_textureArray.GetSize(), m_meshModel.m_textureArray.GetType(), 0, m_meshModel.m_textureArray.GetInfoPointer());
	}
	else
	{
		glColorPointer(m_meshModel.m_colorArray.GetSize(), m_meshModel.m_colorArray.GetType(), 0, m_meshModel.m_colorArray.GetInfoPointer());
	}

	/* ����������Ԫ�صĵ����б� */
	if (m_usingIndex) //Ĭ�ϲ�ʹ������,ֻ��Axis��ָ����
	{
		//(mode,count,type,indices)��typeͬglBegin()�в�������ȡ��ǰ�����Ѿ����õ�����Ķ�������
		glDrawElements(m_paintMode, vertexAmount, m_meshModel.m_indexArray.GetType(), m_meshModel. m_indexArray.GetInfoPointer());
	}
	else
	{
		//(mode,first,count)��ֻ�ܰ�˳�������������
		glDrawArrays(m_paintMode, 0, vertexAmount);
	}
}
