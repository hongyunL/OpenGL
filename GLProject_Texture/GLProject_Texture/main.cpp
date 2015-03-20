#include <glut.h>//�����Ѿ�����<GL/gl.h>��<GL/glu.h>
#include <iostream>

#define BMP_Header_Length 54

/*Windows��ʹ�õ�BMP�ļ����ڿ�ʼ����һ���ļ�ͷ����СΪ54�ֽ�
*54���ֽ��Ժ������16ɫ��256ɫBMP������һ����ɫ����24λɫBMPû�����
*��һ���صĴ�СΪ3�ֽ�
*ͼ��Ŀ�Ⱥ͸߶ȶ���һ��32λ���������ļ��еĵ�ַ�ֱ�Ϊ0x0012��0x0016
*BMP�ļ�������һ�֡����롱�Ļ��ƣ�ÿһ���������ݵĳ���������4�ı����������һЩ����ʹ����4�ı���
*�����ڴ�ʱ��һ��ҪС�ģ�����ֱ��ʹ�á�ͼ��ĸ߶ȳ��Կ�ȳ���ÿһ���ص��ֽ��������������ռ�ĳ���
*/

//�����������ı��
GLuint texGround;
GLuint texWall;

/* ����power_of_two
* ���һ�������Ƿ�Ϊ2�������η�������ǣ�����1�����򷵻�0
* ʵ����ֻҪ�鿴�������λ���ж��ٸ������������1��������1�����򷵻�0
* �ڡ��鿴�������λ���ж��ٸ���ʱʹ����һ��С����
* ʹ��n &= (n-1)����ʹ��n�еļ���һ��������ԭ���ҿ����Լ�˼����
*/
int power_of_two(int n)
{
	if (n <= 0)
		return 0;
	return (n & (n - 1)) == 0;
}

//��ȡһ��BMP�ļ���Ϊ����.���ʧ�ܣ�����0;����ɹ�������������
GLuint load_texture(const char* file_name)
{
	/*������ﱨ��'fopen': This function or variable may be unsafe 
	* ����취��
	* ��Ŀ =������ =��c/c++  =��Ԥ������=�����Ԥ���������壬�༭������_CRT_SECURE_NO_WARNINGS
	*/

	// ���ļ������ʧ�ܣ�����
	FILE* pFile = fopen(file_name, "rb");
	if (pFile == 0)
		return 0;

	// ��ȡ�ļ���ͼ��Ŀ�Ⱥ͸߶�
	GLint width, height;
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);//��ȡ����ֵ��������ı���
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	// ����ÿ��������ռ�ֽ����������ݴ����ݼ����������ֽ���
	GLint total_bytes;
	{
		GLint line_bytes = width * 3;
		while (line_bytes % 4 != 0)
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	// �����������ֽ��������ڴ�
	GLubyte* pixels = 0;//��������
	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0)
	{
		fclose(pFile);
		return 0;
	}

	// ��ȡ��������
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// �ھɰ汾��OpenGL��
	// ���ͼ��Ŀ�Ⱥ͸߶Ȳ��ǵ������η�������Ҫ��������
	// ���ﲢû�м��OpenGL�汾�����ڶ԰汾�����ԵĿ��ǣ����ɰ汾����
	// ���⣬�����Ǿɰ汾�����°汾��
	// ��ͼ��Ŀ�Ⱥ͸߶ȳ�����ǰOpenGLʵ����֧�ֵ����ֵʱ��ҲҪ��������
	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		if (!power_of_two(width)
			|| !power_of_two(height)
			|| width > max
			|| height > max)
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
			if (new_pixels == 0)
			{
				free(pixels);
				fclose(pFile);
				return 0;
			}

			// ������������
			gluScaleImage(GL_RGB,
				width, height, GL_UNSIGNED_BYTE, pixels,
				new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			// �ͷ�ԭ�����������ݣ���pixelsָ���µ��������ݣ�����������width��height
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}

	// ����һ���µ�������
	GLuint texture_ID = 0;
	glGenTextures(1, &texture_ID);//(��������˭)
	if (texture_ID == 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// �ڰ�ǰ���Ȼ��ԭ���󶨵������ţ��Ա��������лָ�
	GLint last_texture_ID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture_ID);

	// ���µ������������������������
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//����ͼ��ʹ�õ�һ������������״��ʱ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//����ͼ��ʹ�õ�һ������������״��ʱ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//��������ĵ�һά����ֵ����1.0��С��0.0ʱ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//��������ĵڶ�ά����ֵ����1.0��С��0.0ʱ

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);//���ؼ���,ָ��������ͼ�Ͳ��ʻ�ϵķ�ʽ
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);//�����ά����

	glBindTexture(GL_TEXTURE_2D, last_texture_ID);

	// ֮ǰΪpixels������ڴ����ʹ��glTexImage2D�Ժ��ͷ�.��Ϊ��ʱ���������Ѿ���OpenGL���б�����һ�ݣ����ܱ����浽ר�ŵ�ͼ��Ӳ���У�
	free(pixels);
	return texture_ID;
}

void myDisplayTex(void)
{
	// �����Ļ
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �����ӽ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 21);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 5, 5, 0, 0, 0, 0, 0, 1);

	// ʹ�á��ء������������
	glBindTexture(GL_TEXTURE_2D, texGround);
	glBegin(GL_QUADS);//�������ĸ�������ɵ�һ�鵥�����ı���
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-8.0f, -8.0f, 0.0f);//��������+��������
	glTexCoord2f(0.0f, 5.0f); glVertex3f(-8.0f, 8.0f, 0.0f);
	glTexCoord2f(5.0f, 5.0f); glVertex3f(8.0f, 8.0f, 0.0f);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(8.0f, -8.0f, 0.0f);
	glEnd();

	// ʹ�á�ǽ���������դ��
	glBindTexture(GL_TEXTURE_2D, texWall);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 1.0f); glVertex3f(6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
	glEnd();

	// ��ת���ٻ���һ��
	glRotatef(-90, 0, 0, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 1.0f); glVertex3f(6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
	glEnd();

	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);//��������GLUTʹ��֮ǰ����һ��
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);//������ʾ��ʽ��ʹ��RGB��ɫ��������ģʽ
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("OpenGL�����е�������ͼ");//����ǰ�����õ���Ϣ��������

	glutDisplayFunc(&myDisplayTex);//����Ҫ��ͼʱ�������myDisplay����(myDisplayΪ�ص�����)

	// ��������һЩ��ʼ��
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);//��������
	texGround = load_texture("ground.bmp");
	texWall = load_texture("wall.bmp");

	glutMainLoop();
	return 0;
}
