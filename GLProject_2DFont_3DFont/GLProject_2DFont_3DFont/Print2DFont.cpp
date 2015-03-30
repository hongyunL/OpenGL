#include "Print2DFont.h"

#include <stdarg.h>	//��������ɱ������ͷ�ļ�(va_list)

Print2DFont::Print2DFont() 
: PrintFont()
{

}

GLvoid Print2DFont::BuildFont(GLvoid)
{
	GenFont();

	m_base = glGenLists(96); //96��������ʾ�б���������������������������ʼλ��

	ApplyFont();

	//����ʹ��wglUseFontBitmaps����(windows)�������Ĳ�����ʾ�ַ��õ���ʾ�б�(��ASCII�ַ�װ����ʾ�б�)
	wglUseFontBitmaps(m_hDC, 32, 96, m_base); //����96����ʾ�б����ƴ�ASCII��Ϊ32-128���ַ�

	DestroyFont();
}

GLvoid Print2DFont::KillFont(GLvoid)
{
	glDeleteLists(m_base, 96); //(begin,range)
}

//�����£� = ��0,0��
GLvoid Print2DFont::glPrint(GLint x, GLint y, char *string)
{
	char text[256]; //�������ִ�
	va_list ap;     //ָ��һ�������б��ָ��

	if (string == NULL)
		return;

	//���������д��뽫�����е����з���ת��Ϊ���ǵ��ַ���š�������ֺ�ת���ķ��ű��洢��һ������text���ַ����С�
	va_start(ap, string); //�����ɱ����
	//int vsprintf(char *string, char *format, va_list param); //��param ����ʽformatд���ַ���string��
	vsprintf(text, string, ap); //�Ѳ���ֵд���ַ��� 
	va_end(ap); //��������

	//glMatrixMode(GL_PROJECTION);
	//glPushMatrix();
	//glLoadIdentity();
	//gluOrtho2D(0.0, 640, 0.0, 480);

	//glMatrixMode(GL_MODELVIEW);
	//glPushMatrix();
	//glLoadIdentity();

	glColor3f(0, 1, 0);//��ɫ����
	glRasterPos2f(x, y); //ʹ�õ���������ϵ��

	glPushAttrib(GL_LIST_BIT);	//����ʾ�б�����ѹ�����Զ�ջ

	//ָ��һ��ƫ���������ƫ����������ʾ�б�������ӣ��Ի�����յ���ʾ�б�����
	glListBase(m_base - 32); //������ʾ�б�Ļ���ֵ��base-32�͵���0��Ȼ����ʾ�б��Ǵ�0ƫ��32����ʼ�ģ�

	//��ִ���б����еĸ������б�ֵ�����͡���Ҫ��ʾ���ı���
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	//������ʾ�б�����ַ���

	glPopAttrib();
	glColor3f(1, 1, 1); //�ָ�������ɫ��

	//glMatrixMode(GL_PROJECTION);
	//glPopMatrix();
	
	//glMatrixMode(GL_MODELVIEW);	
	//glPopMatrix();
}