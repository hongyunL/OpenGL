#include "GLFramework.h"  
#include <glut.h>

/** ���캯�� */
GLFramework::GLFramework()
{
}

GLFramework::GLFramework(int argc, char* argv[], std::string title, unsigned width, unsigned height)
{
	m_WindowP = new GLWindow(argc, argv, title, width, height);
}

/* ί��GLWindow�ഴ�����ڣ��Լ�ʵ�ִ��ڱ仯ʱ�Ļص����� */
void GLFramework::CreateGLWindow()
{
	m_WindowP->CreateGLWindow();
}

void GLFramework::Reshape(unsigned newWidth, unsigned newHeight)
{
	m_WindowP->Reshape(newWidth, newHeight);
}
