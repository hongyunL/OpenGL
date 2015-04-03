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

#include "ViewManager.h"

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


void Object::PaintShadow(float vertex[][3], float lightPos[3])
{
	glDisable(GL_LIGHTING); //�رյƹ�

	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); //�ر���ɫ�����д��	

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);	//������ȱȽϺ���
	glDepthMask(GL_FALSE);	//�ر���Ȼ����д��

	glEnable(GL_STENCIL_TEST); //ʹ���ɰ建��

	glStencilFunc(GL_ALWAYS, 1, 0xffffffff);

	//�������ʱ�루�������ӵ㣩�Ķ���Σ�ͨ�����ɰ����Ȳ��ԣ�����ɰ��ֵ����1
	glFrontFace(GL_CCW);
	glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
	DoShadowPass(vertex, lightPos);

	//�����˳ʱ�루�������ӵ㣩�Ķ���Σ�ͨ�����ɰ����Ȳ��ԣ�����ɰ��ֵ����1
	glFrontFace(GL_CW);
	glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);
	DoShadowPass(vertex, lightPos);



	//����Ӱ��������ɫ

	glFrontFace(GL_CCW);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	glColor4f(0.0f, 0.0f, 0.0f, 0.4f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glStencilFunc(GL_NOTEQUAL, 0, 0xffffffff);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	ViewManager::ViewOrtho();

	glRectf(-1, -1, 1, 1);

	ViewManager::ViewPerspective();

	glDisable(GL_STENCIL_TEST);
	glDisable(GL_BLEND);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glEnable(GL_LIGHTING);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void Object::DoShadowPass(float vertex[][3], float lightPos[3])
{
	unsigned int k, jj;
	unsigned int p1, p2;
	GLPointf v1, v2;

	//��ģ���е�ÿһ����
	for (unsigned int i = 0; i < m_meshModel.vecFace.size(); i++)
	{
		//������ڵƹ��ǰ��
		if ( m_meshModel.vecFace[i].lighted )
		{
			//���ڱ��ƹ���������ÿһ�����ڵ���
			for (unsigned int j = 0; j < 3; j++)
			{
				k = m_meshModel.vecFace[i].neighbourFace[j];

				//����治���ڣ��򲻱��ƹ����䣬��ô������Ǳ߽�
				if ((!k) || (!m_meshModel.vecFace[k - 1].lighted))
				{
					// ��������������
					p1 = m_meshModel.vecFace[i].faceIndices[j];
					jj = (j + 1) % 3;
					p2 = m_meshModel.vecFace[i].faceIndices[jj];

					//����ߵĶ��㵽�ƹ�ķ��򣬲��Ŵ�shadowDepth��//����û�е�λ��
					v1.x = (vertex[p1][0] - lightPos[0]) * shadowDepth;
					v1.y = (vertex[p1][1] - lightPos[1]) * shadowDepth;
					v1.z = (vertex[p1][2] - lightPos[2]) * shadowDepth;

					v2.x = (vertex[p2][0] - lightPos[0]) * shadowDepth;
					v2.y = (vertex[p2][1] - lightPos[1]) * shadowDepth;
					v2.z = (vertex[p2][2] - lightPos[2]) * shadowDepth;

					//���ƹ�����Ӱ��߽����
					//glBegin(GL_TRIANGLES); //�����ķ�ʽ��������ë����״�ģ�
					glPushMatrix();
					glTranslatef(m_x, m_y, m_z);

					glBegin(GL_TRIANGLE_STRIP);
						glVertex3f(vertex[p1][0], vertex[p1][1], vertex[p1][2]);
						glVertex3f(vertex[p1][0] + v1.x, vertex[p1][1] + v1.y, vertex[p1][2] + v1.z);
						glVertex3f(vertex[p2][0], vertex[p2][1], vertex[p2][2]);
						glVertex3f(vertex[p2][0] + v2.x, vertex[p2][1] + v2.y, vertex[p2][2] + v2.z);
					glEnd();

					glPopMatrix();
				}
			}
		}
	}
}

void Object::SetLightedFaces(float lightPos[3])
{
	// ������Щ���ڵƹ��ǰ��
	for (unsigned int i = 0; i < m_meshModel.vecFace.size(); i++)
	{
		GLfloat side = m_meshModel.vecFace[i].planeEq.a*lightPos[0] +
			m_meshModel.vecFace[i].planeEq.b*lightPos[1] +
			m_meshModel.vecFace[i].planeEq.c*lightPos[2] +
			m_meshModel.vecFace[i].planeEq.d;

		if (side > 0)
			m_meshModel.vecFace[i].lighted = true;
		else
			m_meshModel.vecFace[i].lighted = false;

	}
}