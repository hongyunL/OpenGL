#include "PrintFont.h"

PrintFont::PrintFont()
{
	//hDC = wglGetCurrentDC(); //��ȡ������
	m_hDC = GetDC(GetForegroundWindow());
	m_base = 0;
}

GLvoid PrintFont::GenFont(GLvoid)
{
	m_font = CreateFont(
		-24,	 //����߶�
		0,		 //�����ȣ�0ΪĬ�ϱ���
		0,		 //�������ת�Ƕ� Angle Of Escapement
		0,		 //������ߵ���ת�Ƕ�Orientation Angle
		FW_BOLD, //�������������ϸ��
		FALSE,	 //�Ƿ�ʹ��б��
		FALSE,	 //�Ƿ�ʹ���»���
		FALSE,	 //�Ƿ�ʹ��ɾ����
		ANSI_CHARSET,	     //�����ַ���
		OUT_TT_PRECIS,		 //�������
		CLIP_DEFAULT_PRECIS, //�ü�����
		ANTIALIASED_QUALITY, //�������������ݣ�
		FF_DONTCARE | DEFAULT_PITCH, //Family And Pitch
		"Courier New");			     //��������
}

GLvoid PrintFont::ApplyFont(GLvoid)
{
	m_oldFont = (HFONT)SelectObject(m_hDC, m_font); //ѡ��������Ҫ������
}

GLvoid PrintFont::DestroyFont(GLvoid)
{
	SelectObject(m_hDC, m_oldFont); //ѡ��ԭ��������

	DeleteObject(m_font);	//ɾ������
}