#include "Print3DFont.h"

Print3DFont::Print3DFont()
:PrintFont()
{
	m_usingTex = false;
}

GLvoid Print3DFont::BuildFont(GLvoid)
{
	m_tex.LoadTexture("mingzhuta.bmp");

	m_base = glGenLists(256);

	GenFont(); //3D����ֻ����ʾTrueType���壡
	ApplyFont();

	wglUseFontOutlines(
		m_hDC,				//���õ�ǰ�����豸������ľ��
		0,					//���ڴ�����ʾ�б�����ĵ�һ���ַ���ASCIIֵ
		255,				//�ַ���
		m_base,				//һ����ʾ�б������
		0.0f,				//����Ĺ⻬�ȣ�ԽСԽ�⻬��0.0Ϊ��⻬��״̬
		0.2f,				//��z����ͻ���ľ���
		WGL_FONT_POLYGONS,	//ʹ�ö�����������ַ���ÿ��������ж����ķ���
		m_gmf);				//һ���������ζ������ݵ�����ĵ�ַ��ÿ������Ԫ��������Ӧ����ʾ�б��ַ���������� 

	DestroyFont();
}

GLvoid Print3DFont::KillFont(GLvoid)
{
	glDeleteLists(m_base, 256); //(begin,range)
}

GLvoid Print3DFont::glPrint(GLint x, GLint y, char *string)
{
	//float length = 0; //��ѯ�ַ����ĳ���///////////////�Ժ�һ�����õ���

	char text[256]; //�������ִ�
	va_list ap;     //ָ��һ�������б��ָ��

	if (string == NULL)
		return;

	va_start(ap, string);       //�����ɱ����
	vsprintf(text, string, ap); //�Ѳ���ֵд���ַ��� 
	va_end(ap);					//��������

	//for (unsigned int loop = 0; loop<(strlen(text)); loop++)	//���������ַ����ĳ���
	//{
	//	length += gmf[text[loop]].gmfCellIncX;
	//}

	glPushMatrix();

	glColor3f(0, 1, 0);
	//glTranslatef(-length / 2, 0.0f, 0.0f);	//���ַ������������
	glTranslatef(x, y, 0);

	glPushAttrib(GL_LIST_BIT);			

	if (true == m_usingTex)
	{
		//��������ӳ��ģʽ
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glEnable(GL_TEXTURE_GEN_S);	//ʹ���Զ���������
		glEnable(GL_TEXTURE_GEN_T);

		glEnable(GL_TEXTURE_2D);
		m_tex.Apply();
	}

	glListBase(m_base);	//������ʾ�б�Ļ���ֵΪ0
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text); //������ʾ�б�����ַ���

	if (true == m_usingTex)
	{
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
	}

	glPopAttrib();
	glPopMatrix();

	glColor3f(1, 1, 1); //�ָ�������ɫ��
}