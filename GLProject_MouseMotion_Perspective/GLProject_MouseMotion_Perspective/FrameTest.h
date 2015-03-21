#pragma once

#include "GLFramework.h"//#include "GlobalInit.h" //�������Ѿ�������
#include "Camera.h"

#include <list>

class FrameTest : public GLFramework
{
public:
	FrameTest();
	FrameTest(int argc, char* argv[], std::string title, unsigned width, unsigned height);

	/* ��д���ി�麯�� */
	void Init();
	void Display();	

	void MouseMotion(int x, int y);
	void MousePassiveMotion(int x, int y);

private:
	GlobalInit *m_init;
	Camera *m_camera0;

	//�����ĳһ���ӳ��Ƕ�
	float viewAngleZ; //Mouse�趨��Displayʹ��
	float viewAngleY;

	//�л������ӽǣ�1 true�������ӽǣ�0 false:�ϵ��ӽ�
	bool viewMode; //Keyboard�趨��Displayʹ��

};