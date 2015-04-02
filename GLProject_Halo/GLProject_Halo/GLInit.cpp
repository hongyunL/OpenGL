#include "GLInit.h"

GLenum GLInit::m_mode = GL_CCW;

/*
* ��ʼ����Ⱦ����(��ʹ��MeshModel֮ǰ����)
* ָ������
* �򿪱����޳�
* ����Ȳ���
* ��ƽ������
* �趨�����ɫΪ��ɫ
*
* ��vertex��������
*/
GLInit::GLInit(GLenum mode)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 640, 0, 480);

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_CULL_FACE);
	SetFrontFace(mode);

	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH); 

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 

	//�򿪶�������
	glEnableClientState(GL_VERTEX_ARRAY);
}

void GLInit::SetFrontFace(GLenum mode)
{
	glFrontFace(mode);
}
