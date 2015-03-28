#pragma once

#include <glut.h>
#include <string>

/*��ά��ͼ����
* ʹ��BMP���͵��ⲿͼƬ
* ���ܣ���������ļ��غ�Ӧ��*/
class Texture{
public:
	Texture();

	/*Ӧ��Ϊ��ǰ����*/
	void Apply();

	//װ���������ʧ�ܣ�����0������ɹ�������������
	GLuint LoadTexture(std::string fileName);

private:
	GLuint m_texId;   //Apply()��ʱ����
	GLint m_texWidth; //ResizeBMP()��ʱ����
	GLint m_texHeight;

	//��ȡһ��24λBMP�ļ���Ϊ����
	unsigned char* LoadBMP(std::string fileName);

	//���һ�������Ƿ�Ϊ2�������η�������ǣ�����1�����򷵻�0
	bool IsIntegerSquareOfTwo(int n);

	/*�ھɰ汾��OpenGL��
	* ���ͼ��Ŀ�Ⱥ͸߶Ȳ��ǵ������η�������Ҫ��������
	* ���ﲢû�м��OpenGL�汾�����ڶ԰汾�����ԵĿ��ǣ����ɰ汾����
	* ���⣬�����Ǿɰ汾�����°汾��
	* ��ͼ��Ŀ�Ⱥ͸߶ȳ�����ǰOpenGLʵ����֧�ֵ����ֵʱ��ҲҪ��������*/
	bool ResizeBMP(GLint *width, GLint *height, GLubyte *pixels);
};