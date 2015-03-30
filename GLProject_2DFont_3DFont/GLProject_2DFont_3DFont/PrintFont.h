#pragma once

#include <glut.h>

#include <stdio.h>
#include <Windows.h> //��������

class PrintFont
{
public:
	PrintFont();

	GLvoid GenFont(GLvoid); //�޸���������Ĳ������������ⲿ�趨�������ԣ�
	GLvoid ApplyFont(GLvoid);
	GLvoid DestroyFont(GLvoid);

	virtual GLvoid BuildFont(GLvoid) = 0;
	virtual GLvoid KillFont(GLvoid) = 0; //killWindow()ʱ���ã�
	virtual GLvoid glPrint(GLint x, GLint y, char *string) = 0;

	//~PrintFont();
protected:
	//PrintFont(const PrintFont& other){}
	//PrintFont& operator=(const PrintFont& other){}

	HDC m_hDC; //�豸������
	GLuint m_base; //�����������ʾ�б�Ŀ�ʼλ��.�ַ���A������ʾ�б�����65,Ӧ��������ʾ�б��е�base + 65���λ��

private:
	HFONT m_font;	 //������
	HFONT m_oldFont; //�ɵ�������
};
