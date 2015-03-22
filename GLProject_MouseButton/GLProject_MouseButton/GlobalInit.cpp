#include "GlobalInit.h"

GLenum GlobalInit::m_mode = GL_CCW;

/*
* ��ʼ����Ⱦ����(��ʹ��MeshModel֮ǰ����)
* ָ������
* �򿪱����޳�
* ����Ȳ���
* ��ƽ������
* �趨�����ɫΪ��ɫ
* �򿪻�ϣ��趨alpha��Ϸ���
* ��vertex��������
*/
GlobalInit::GlobalInit(GLenum mode)
{
	glEnable(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT, GL_FILL);
	SetFrontFace(mode);

	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH); //���п����

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//�򿪶�������
	glEnableClientState(GL_VERTEX_ARRAY);
}

void GlobalInit::SetFrontFace(GLenum mode)
{
	glFrontFace(mode);
}
