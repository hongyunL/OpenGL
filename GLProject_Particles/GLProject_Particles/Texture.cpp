#include "Texture.h"
#include <iostream>

Texture::Texture()
{
	m_texId = 0;
	m_texWidth = 0;
	m_texHeight = 0;
}

/*Ӧ��Ϊ��ǰ����*/
void Texture::Apply()
{
	glBindTexture(GL_TEXTURE_2D, m_texId); //////////////////////////////////�Ӳ���glEnable(GL_TEXTURE_2D);������
}

/*���һ�������Ƿ�Ϊ2�������η�������ǣ�����1�����򷵻�0
* ʵ����ֻҪ�鿴�������λ���ж��ٸ������������1��������1�����򷵻�0
* �ڡ��鿴�������λ���ж��ٸ���ʱʹ����һ��С����
* ʹ��n &= (n-1)����ʹ��n�еļ���һ��������ԭ���ҿ����Լ�˼����
*/
bool Texture::IsIntegerSquareOfTwo(int n)
{
	if (n <= 0)
		return 0;
	return (n & (n - 1)) == 0;
}

/*�ھɰ汾��OpenGL��
* ���ͼ��Ŀ�Ⱥ͸߶Ȳ��ǵ������η�������Ҫ��������
* ���ﲢû�м��OpenGL�汾�����ڶ԰汾�����ԵĿ��ǣ����ɰ汾����
* ���⣬�����Ǿɰ汾�����°汾��
* ��ͼ��Ŀ�Ⱥ͸߶ȳ�����ǰOpenGLʵ����֧�ֵ����ֵʱ��ҲҪ��������*/
bool Texture::ResizeBMP(GLint *width, GLint *height, GLubyte *pixels)
{
	GLint max;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
	if (!IsIntegerSquareOfTwo(*width)
		|| !IsIntegerSquareOfTwo(*height)
		|| *width > max
		|| *height > max)
	{
		const GLint new_width = 256;
		const GLint new_height = 256; // �涨���ź��µĴ�СΪ�߳���������

		GLint new_line_bytes, new_total_bytes;
		GLubyte* new_pixels = 0;

		// ����ÿ����Ҫ���ֽ��������ֽ���
		new_line_bytes = new_width * 3;
		while (new_line_bytes % 4 != 0)
			++new_line_bytes;
		new_total_bytes = new_line_bytes * new_height;

		// �����ڴ�
		new_pixels = (GLubyte*)malloc(new_total_bytes);

		// ������������
		gluScaleImage(GL_RGB,
			*width, *height, GL_UNSIGNED_BYTE, pixels,
			new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

		// �ͷ�ԭ�����������ݣ���pixelsָ���µ��������ݣ�����������width��height
		free(pixels);
		pixels = new_pixels;
		*width = new_width;
		*height = new_height;
		return 1;
	}
	return 0;
}

unsigned char* Texture::LoadBMP(std::string fileName)
{
	FILE* pFile = fopen(fileName.c_str(), "rb"); //ȱ�ټ���Ƿ�򿪳ɹ���

	//��ȡ�ļ���ͼ��Ŀ�Ⱥ͸߶ȣ�Ϊ�˼������ط����ڴ��С
	GLint width, height;
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, 54, SEEK_SET);

	//����ÿ��������ռ�ֽ����������ݴ����ݼ����������ֽ���
	GLint totalBytes;
	{
		GLint lineBytes = width * 3;
		while (lineBytes % 4 != 0)
			++lineBytes;
		totalBytes = lineBytes * height;
	}

	//�����������ֽ��������ڴ�
	GLubyte* pixels = 0; //��������
	pixels = (GLubyte*)malloc(totalBytes); //ȱ�ټ�������Ƿ�Ϊ0��

	//��ȡ��������
	fread(pixels, totalBytes, 1, pFile); //ȱ�ټ���Ƿ��ȡ�ɹ���

	//��ͼ��Ŀ�Ⱥ͸߶ȳ�����ǰOpenGLʵ����֧�ֵ����ֵʱ����Ҫ��������
	if (ResizeBMP(&width, &height, pixels))
		std::cout << "�����Ѿ�������Ϊ2�������η��Լ����ʴ�С" << std::endl;
	
	m_texWidth = width;
	m_texHeight = height;

	fclose(pFile);
	return pixels;
}

//װ���������ʧ�ܣ�����0������ɹ�������������
GLuint Texture::LoadTexture(std::string fileName)
{
	GLubyte* pixels = LoadBMP(fileName);

	//����һ���µ�������
	GLuint texID = 0;
	glGenTextures(1, &texID); //(��������˭)
	//std::cout << "����ID���䣺" << texID << std::endl;

	if (texID == 0)
	{
		free(pixels);
		return 0;
	}
	//std::cout << "������仰��˵������ID����ɹ��ˣ�" << texID << std::endl;

	// �ڰ�ǰ���Ȼ��ԭ���󶨵������ţ��Ա��������лָ�
	GLint last_texture_ID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture_ID);

	//���µ������������������������
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //����ͼ��ʹ�õ�һ������������״��ʱ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //����ͼ��ʹ�õ�һ������������״��ʱ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     //��������ĵ�һά����ֵ����1.0��С��0.0ʱ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     //��������ĵڶ�ά����ֵ����1.0��С��0.0ʱ

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);       //���ؼ���,ָ��������ͼ�Ͳ��ʻ�ϵķ�ʽ

	/*�����ά����
	* ��ʹ��mipmap���������������gluBuild2DMipmaps() */
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_texWidth, m_texHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, m_texWidth, m_texHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);

	glBindTexture(GL_TEXTURE_2D, last_texture_ID);

	/*֮ǰΪpixels������ڴ����ʹ��glTexImage2D�Ժ��ͷ�.
	* ��Ϊ��ʱ���������Ѿ���OpenGL���б�����һ�ݣ����ܱ����浽ר�ŵ�ͼ��Ӳ���У� */
	free(pixels);

	m_texId = texID; 
	return texID;
}
