#pragma once

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

#include <glut.h>

class GlobalInit
{
public:
	/*���塰���桱�Ļ��Ʒ��򣬲���ΪGL_CCW����ʱ�룩��GL_CW��˳ʱ�룩*/
	GlobalInit(GLenum mode = GL_CCW);

	void SetFrontFace(GLenum mode);

protected:
	static GLenum m_mode;
};