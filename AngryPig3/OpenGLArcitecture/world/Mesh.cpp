#include "Mesh.h"

#include <stdlib.h>

bool Mesh::m_usingIndex = true;
bool Mesh::m_usingLighting = true;
Mesh::ColorMode Mesh::m_colorMode = TEXTURE;

Mesh::Mesh()
{
}

Mesh::Mesh(unsigned vertexAmount, GLenum paintMode)
{
	m_vertexAmount = vertexAmount;
	m_paintMode = paintMode;
}

/*�������*/
void Mesh::clear()
{
	m_vertexArray.clear(); 
	m_normalArray.clear();
	m_colorArray.clear();
	m_textureArray.clear();
	m_indexArray.clear();
}

void Mesh::paint()
{
	/*װ������*/
	//��������
	glVertexPointer(m_vertexArray.getSize(), m_vertexArray.getType(), 0, m_vertexArray.getInfoPointer());
	//�����Ҫ��װ�뷨����
	if(m_usingLighting)
	{
		glNormalPointer(m_normalArray.getType(), 0, m_normalArray.getInfoPointer());
	}
	//������Ⱦģʽװ����ɫ��������
	if(TEXTURE == m_colorMode)
	{
		glTexCoordPointer(m_textureArray.getSize(), m_textureArray.getType(), 0, m_textureArray.getInfoPointer());
	}
	else
	{
		glColorPointer(m_colorArray.getSize(), m_colorArray.getType(), 0, m_colorArray.getInfoPointer());
	}

	/*ʹ��������Ⱦ*/
	if(m_usingIndex)
	{  
		glDrawElements(m_paintMode, m_vertexAmount, m_indexArray.getType(), m_indexArray.getInfoPointer());
	}
	else
	{
		glDrawArrays(m_paintMode, 0, m_vertexAmount);
	}

}

/*װ�ض�������*/
void Mesh::loadVertex(void *pSrc, int length, GLenum type, int size)
{
	m_vertexArray.loadArray(pSrc, length, type, size);
}
/*װ����ɫ*/
void Mesh::loadColor(void *pSrc, int length, GLenum type, int size)
{
	m_colorArray.loadArray(pSrc, length, type, size);
}
/*װ�ط�����*/
void Mesh::loadNormal(void *pSrc, int length, GLenum type)
{
	m_normalArray.loadArray(pSrc, length, type, 3);
}
/*װ������*/
void Mesh::loadIndex(void *pSrc, int length, GLenum type)
{
	m_indexArray.loadArray(pSrc, length, type, 1);
}

/*����*/
Mesh::~Mesh()
{
}

/*��ʼ����Ⱦ����*/
void Mesh::InitMesh(bool usingIndex, bool usingLighting, ColorMode colorMode, GLenum mode)
{
	glEnable(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT, GL_FILL);
	SetFrontFace(mode);

	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//�򿪶�������
	glEnableClientState(GL_VERTEX_ARRAY);
	SetRenderMode(usingIndex, usingLighting, colorMode);
}

/*���塰���桱�Ļ��Ʒ��򣬲���ΪGL_CCW����ʱ�룩��GL_CW��˳ʱ�룩*/
void Mesh::SetFrontFace(GLenum mode)
{
	glFrontFace(mode);
}

/*�趨�滭ģʽ*/
void Mesh::SetRenderMode(bool usingIndex, bool usingLighting, ColorMode colorMode)
{
	Mesh::m_usingIndex = usingIndex;
	Mesh::m_usingLighting = usingLighting;
	Mesh::m_colorMode = colorMode;

	if(usingLighting)
		glEnableClientState(GL_NORMAL_ARRAY);
	else
		glDisableClientState(GL_NORMAL_ARRAY);

	if(TEXTURE == colorMode)
	{
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);	
	}
	else
	{
		glEnableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
}
