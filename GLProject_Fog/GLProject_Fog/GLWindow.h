#pragma once

#include <Windows.h>
#include <string>

/** windows������ */
class GLWindow
{
public:
	/* ��ʼ��������windows���� */
	GLWindow();
	GLWindow(int argc, char* argv[], std::string title, unsigned width, unsigned height);

	/* �������� */
	void CreateGLWindow();

	/* ���ش��ڵĴ�С */
	int GetWidth();
	int GetHeight();

	/* ��ȡ���ڴ��ڵľ�� */
	HWND GetWindowHandle();

	/*���ڴ�С�ı�ص����� */
	void Reshape(unsigned newWidth, unsigned newHeight);

private:
	HWND m_hWnd; //���ھ�� 
	unsigned m_windowWidth;   
	unsigned m_windowHeight;  
	std::string m_title;
};