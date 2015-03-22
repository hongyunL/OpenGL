/**
*	������ڼ̳�����������º�����ʵ��
*
*	void Init(); //ί��GlobalInit��ʵ��
*
*	Display(); //glutDisplayFunc()�Ļص�����������glClear()
*
*	MouseMotion();
*	MousePassiveMotion();
*	MouseButtion();
*
*	KeyboardSet()
*	KeyboardUpSet()
*	KeyboardRespond()
*	SpecialKey()
*
*	ʹ��ʱ��Ҫ��main()�����б�д���º�������ΪglutDisplayFunc()ֻ������ͨ����ָ�룬���������Ա����ָ��
*		void DisplayCal()
*		{
*			object->Display();
*		}
*/

#pragma once

#include "GLWindow.h"
#include "GlobalInit.h"

/** �����ĳ������࣬�̳�����������OpenGL���� */
class GLFramework
{
public:
	//virtual ~GLFramework() {}; //���������� 

	/* ���캯�� */
	GLFramework();
	GLFramework(int argc, char* argv[], std::string title, unsigned width, unsigned height);

	/* ί��GLWindow�ഴ�����ڣ��Լ�ʵ�ִ��ڱ仯ʱ�Ļص����� */
	void CreateGLWindow();
	void Reshape(unsigned newWidth, unsigned newHeight);

protected:
	/* ����ĺ������뱻�̳���ʵ�֣���ɻ�����OpenGL��Ⱦ����*/
	virtual void Init() = 0;
	virtual void Display() = 0; 

	virtual void MouseMotion(int x, int y) = 0;
	virtual void MousePassiveMotion(int x, int y) = 0;
	virtual void MouseButton(int button, int state, int x, int y) = 0;

	//virtual void KeyboardSet(unsigned char key, int x, int y) = 0; //�趨�����������ͷ�
	//virtual void KeyboardUpSet(unsigned char key, int x, int y) = 0;

	//virtual void KeyboardRespond() = 0; //��Timer�е���
	//virtual void SpecialKey(int key, int x, int y) = 0;

	GLWindow *m_WindowP; 
};