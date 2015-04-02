#pragma once

#include "GLFramework.h"//#include "GLInit.h" //�������Ѿ�������

#include "Light.h"
#include "Camera.h"
#include "Keys.h"

class FrameTest : public GLFramework
{
public:
	FrameTest();
	FrameTest(int argc, char* argv[], std::string title, unsigned width, unsigned height);

	void DrawScene(GLenum mode);

	/* ��д���ി�麯�� */
	void Init();
	void Display();	

	void MouseMotion(int x, int y);
	void MousePassiveMotion(int x, int y);
	void MouseButton(int button, int state, int x, int y);

	void KeyboardSet(unsigned char key, int x, int y);
	void KeyboardUpSet(unsigned char key, int x, int y);

	void KeyboardRespond(); //��Timer�е���
	void SpecialKey(int key, int x, int y);

private:
	Light m_light0;
	Camera m_camera0;

	//���������û�����ò���ͬһ�������е�������Ա����
	Keys m_keys;

	//�����ĳһ���ӳ��Ƕ�
	float viewAngleZ; //Mouse�趨��Displayʹ��
	float viewAngleY;

	//�л������ӽǣ�1 true�������ӽǣ�0 false:�ϵ��ӽ�
	bool viewMode; //Keyboard�趨��Displayʹ��

};