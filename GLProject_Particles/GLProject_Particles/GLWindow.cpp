#include "GLWindow.h" 

#include <glut.h>

/* ���캯�� */
GLWindow::GLWindow()
{
}

GLWindow::GLWindow(int argc, char* argv[], std::string title, unsigned width, unsigned height)
{
	m_hWnd = WindowFromDC(wglGetCurrentDC());

	m_windowWidth = width;
	m_windowHeight = height;
	m_title = title;

	/*��ʼ������*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
}

/* �������� */
void GLWindow::CreateGLWindow()
{
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(m_windowWidth, m_windowHeight);
	glutCreateWindow(m_title.c_str());
}

/* ���ش��ڵĴ�С */
int GLWindow::GetWidth()
{
	return m_windowWidth;
}

int GLWindow::GetHeight()
{
	return m_windowHeight;
}

/* ��ȡ���ڴ��ڵľ�� */
HWND GLWindow::GetWindowHandle()
{
	return m_hWnd;
}

/* ���ڴ�С�ı�ʱ��֪ͨOpenGL������С */
void GLWindow::Reshape(unsigned newWidth, unsigned newHeight)
{
	m_windowWidth = newWidth;
	m_windowHeight = newHeight;
	glViewport(0, 0, newWidth, newHeight); //���������ӿ�

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45.0f, (float)width / (float)height, 1.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
