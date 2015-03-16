#include <glut.h>//�����Ѿ�����<GL/gl.h>��<GL/glu.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static GLfloat angle = 0.0f;

void myDisplayLight(void);
void myDisplayList(void);
void myDisplayBlend(void);

#define WindowWidth  400
#define WindowHeight 400
#define BMP_Header_Length 54

/*Windows��ʹ�õ�BMP�ļ����ڿ�ʼ����һ���ļ�ͷ����СΪ54�ֽ�
*54���ֽ��Ժ������16ɫ��256ɫBMP������һ����ɫ����24λɫBMPû�����
*��һ���صĴ�СΪ3�ֽ�
*ͼ��Ŀ�Ⱥ͸߶ȶ���һ��32λ���������ļ��еĵ�ַ�ֱ�Ϊ0x0012��0x0016
*BMP�ļ�������һ�֡����롱�Ļ��ƣ�ÿһ���������ݵĳ���������4�ı����������һЩ����ʹ����4�ı���
*�����ڴ�ʱ��һ��ҪС�ģ�����ֱ��ʹ�á�ͼ��ĸ߶ȳ��Կ�ȳ���ÿһ���ص��ֽ��������������ռ�ĳ���
*/

//��ͼ
void grab(void)
{
	glReadBuffer(GL_FRONT);//�Ա�֤��ȡ�����������þ�����ʾ������

	// �����������ݵ�ʵ�ʳ���
	GLint i = WindowWidth * 3;// �õ�ÿһ�е��������ݳ���
	while (i % 4 != 0)// �������ݣ�ֱ��i�ǵı���
		++i;
	GLint PixelDataLength = i * WindowHeight;

	// �����ڴ�ʹ��ļ�
	GLubyte* pPixelData = (GLubyte*)malloc(PixelDataLength);//BMP�ļ�β����������
	if (pPixelData == 0)
		exit(0);

	FILE* pDummyFile = fopen("dummy.bmp", "rb");
	if (pDummyFile == 0)
		exit(0);

	FILE* pWritingFile = fopen("grab.bmp", "wb");
	if (pWritingFile == 0)
		exit(0);

	// ��ȡ����
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glReadPixels(0, 0, WindowWidth, WindowHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);

	// ��dummy.bmp���ļ�ͷ����Ϊ���ļ����ļ�ͷ
	GLubyte  BMP_Header[BMP_Header_Length];//BMPͷ54�ֽڵ�����

	fread(BMP_Header, sizeof(BMP_Header), 1, pDummyFile);
	fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);
	fseek(pWritingFile, 0x0012, SEEK_SET);

	i = WindowWidth;
	GLint j = WindowHeight;
	fwrite(&i, sizeof(i), 1, pWritingFile);
	fwrite(&j, sizeof(j), 1, pWritingFile);

	// д����������
	fseek(pWritingFile, 0, SEEK_END);
	fwrite(pPixelData, PixelDataLength, 1, pWritingFile);

	// �ͷ��ڴ�͹ر��ļ�
	fclose(pDummyFile);
	fclose(pWritingFile);
	free(pPixelData);
}

/* �ڿ���ʱ���ã������ǰ����������ƶ�һ�첢���»��ƣ��ﵽ����Ч�� */
void myIdle(void)
{
	//++day;
	//if (day >= 360) day = 0;

	angle += 1.0f;
	if (angle >= 360.0f)
		angle = 0.0f;

	myDisplayBlend();
}

//����֡�٣�һ�����ڲ��ŵĻ�����Ŀ��FPS������myDisplayLight()��ʹ��
double CalFrequency()
{
	static int count;
	static double save;
	static clock_t last, current;
	double timegap;

	++count;
	if (count <= 50)
		return save;
	count = 0;
	last = current;
	current = clock();
	timegap = (current - last) / (double)CLK_TCK;
	save = 50.0 / timegap;
	return save;
}

//���ա���ͼ�任
void myDisplayLight(void)
{
	double FPS = CalFrequency();
	std::cout<<FPS<<"\n", FPS;

	glEnable(GL_DEPTH_TEST);//��Ȳ���
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//�����Ȼ���

	glMatrixMode(GL_PROJECTION);//���õ�ǰ�����ľ���Ϊ��ͶӰ����
	glLoadIdentity();//�ѵ�ǰ��������Ϊ��λ����
	gluPerspective(75, 1, 1, 400);//����ǰ�Ŀ��ӿռ�����Ϊ͸��ͶӰ�ռ䣨�Ƕȣ���߱ȣ�����Զ��

	glMatrixMode(GL_MODELVIEW);//���õ�ǰ�����ľ���Ϊ��ģ����ͼ����
	glLoadIdentity();
	gluLookAt(0, -200, 200, 0, 0, 0, 0, 0, 1);//�����λ�ã��������������Ϸ���

	// ����̫����Դ������һ�ְ�ɫ�Ĺ�Դ
	{
		GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //λ�ã���4������Ϊ0��������Զ��
		GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };  //��η����ǿ��
		GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  //�������ǿ��
		GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //���淴���ǿ��

		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position); //�����Ź�Դ��ʲô���ԣ����ó�ʲô��
		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

		glEnable(GL_LIGHT0);   //���ù�Դ
		glEnable(GL_LIGHTING); //��������
		//glEnable(GL_DEPTH_TEST);
	}

	// ����̫���Ĳ��ʲ�����̫��
	{
		GLfloat sun_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };  //��η����ǿ��
		GLfloat sun_mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };  //�������ǿ��
		GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f }; //���淴���ǿ��
		GLfloat sun_mat_emission[] = { 0.5f, 0.0f, 0.0f, 1.0f }; //������ɫ
		GLfloat sun_mat_shininess = 0.0f;                        //������ָ���������ֲڳ̶�

		glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient); //���棬�ĸ����ԣ����ó�ʲô��
		glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);

		glutSolidSphere(69, 20, 20);
	}

	// �������Ĳ��ʲ����Ƶ���
	{
		GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
		GLfloat earth_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
		GLfloat earth_mat_specular[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat earth_mat_shininess = 30.0f;

		glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);

		glRotatef(angle, 0.0f, -1.0f, 0.0f);
		glTranslatef(150, 0.0f, 0.0f);
		glutSolidSphere(30, 20, 20);
	}

	//static int day = 200; // day�ı仯����0��359

	// ���ƺ�ɫ�ġ�̫����
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glutSolidSphere(69, 20, 20);//���뾶�����ߣ�γ�ߣ�
	// ������ɫ�ġ�����
	//glColor3f(0.0f, 0.0f, 1.0f);
	//glRotatef(day / 360.0*360.0, 0.0f, 0.0f, -1.0f);//��ת
	//glTranslatef(150, 0.0f, 0.0f);//�ƶ�
	//glutSolidSphere(15, 20, 20);
	// ���ƻ�ɫ�ġ�������
	//glColor3f(1.0f, 1.0f, 0.0f);
	//glRotatef(day / 30.0*360.0 - day / 360.0*360.0, 0.0f, 0.0f, -1.0f);
	//glTranslatef(38, 0.0f, 0.0f);
	//glutSolidSphere(4, 20, 20);

	glFlush();//��֤ǰ���OpenGL��������ִ�У��������������ڻ������еȴ���
	glutSwapBuffers();//����������
}

//��myDisplayBlend()��ʹ��
void setLight(void)
{
	static const GLfloat light_position[] = { 1.0f, 1.0f, -1.0f, 1.0f };
	static const GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	static const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

//��myDisplayBlend()��ʹ��
void setMatirial(const GLfloat mat_diffuse[4], GLfloat mat_shininess)
{
	static const GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static const GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
}

//���
void myDisplayBlend(void)
{
	// ����һЩ������ɫ
	const static GLfloat red_color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	const static GLfloat green_color[] = { 0.0f, 1.0f, 0.0f, 0.3333f };
	const static GLfloat blue_color[] = { 0.0f, 0.0f, 1.0f, 0.5f };

	// ʹ��Ĭ�ϵ�RGBA�����ֵ�����Ļ
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ������ϲ����û������
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//(Դ���ӣ�Ŀ������)

	// ���ù�Դ
	setLight();

	// ��(0, 0, 0.5)Ϊ���ģ�����һ���뾶Ϊ0.3�Ĳ�͸����ɫ���壨��۲�����Զ��
	setMatirial(red_color, 30.0);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.5f);
	glutSolidSphere(0.3, 30, 30);
	glPopMatrix();

	// ���潫���ư�͸�������ˣ���˽���Ȼ�������Ϊֻ��
	glDepthMask(GL_FALSE);

	// ��(0.2, 0, -0.5)Ϊ���ģ�����һ���뾶Ϊ0.2�İ�͸����ɫ���壨��۲��������
	setMatirial(blue_color, 30.0);
	glPushMatrix();
	glTranslatef(0.2f, 0.0f, -0.5f);
	glutSolidSphere(0.2, 30, 30);
	glPopMatrix();

	// ��(0.1, 0, 0)Ϊ���ģ�����һ���뾶Ϊ0.15�İ�͸����ɫ���壨��ǰ��������֮�䣩
	setMatirial(green_color, 30.0);
	glPushMatrix();
	glTranslatef(0.1, 0, 0);
	glutSolidSphere(0.15, 30, 30);
	glPopMatrix();

	// ��ɰ�͸������Ļ��ƣ�����Ȼ������ָ�Ϊ�ɶ���д����ʽ
	glDepthMask(GL_TRUE);

	glutSwapBuffers();
}

//�㡢�ߡ�����Ρ����㡢��ʾ�б�
void myDisplayList(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

	//glShadeModel(GL_SMOOTH);   // ƽ����ʽ����Ҳ��Ĭ�Ϸ�ʽ��������ʹ�ò�ͬ��ɫʱ�н���Ч��
	//glShadeModel(GL_FLAT);     // ��ɫ��ʽ

	//glColor3f(0.0f, 1.0f, 1.0f);

	// glPointSize(5.0f);//���õ��С

	//glEnable(GL_LINE_STIPPLE);//��������
	//glLineStipple(2, 0x0F0F);//������ʽ
	//glLineWidth(10.0f);

	//glPolygonMode(GL_FRONT, GL_FILL); // ��������Ϊ���ģʽ
	//glPolygonMode(GL_BACK, GL_LINE);  // ���÷���Ϊ����ģʽ
	//glFrontFace(GL_CCW);              // ������ʱ�뷽��Ϊ����


	//glBegin( /* ��������������ϣ����ģʽ */);
	/* ������ʹ��glVertex*ϵ�к��� */
	/* ָ������ϣ���Ķ���λ�� */
	//glEnd();

	#define ColoredVertex(c, v) do{ glColor3fv(c); glVertex3fv(v); }while(0)//

	static int list = 0;
	if (list == 0)
	{
		// �����ʾ�б����ڣ��򴴽�
		GLfloat
			PointA[] = { 0.5f, -sqrt(6.0f) / 12, -sqrt(3.0f) / 6 },
			PointB[] = { -0.5f, -sqrt(6.0f) / 12, -sqrt(3.0f) / 6 },
			PointC[] = { 0.0f, -sqrt(6.0f) / 12, sqrt(3.0f) / 3 },
			PointD[] = { 0.0f, sqrt(6.0f) / 4, 0 };
		GLfloat
			ColorR[] = { 1, 0, 0 },
			ColorG[] = { 0, 1, 0 },
			ColorB[] = { 0, 0, 1 },
			ColorY[] = { 1, 1, 0 };

		list = glGenLists(1);
		glNewList(list, GL_COMPILE); //���µ�����ֻ��װ�뵽��ʾ�б������ڲ�ִ������
		glBegin(GL_TRIANGLES);       //��ÿ��������Ϊһ��������������
		// ƽ��ABC
		ColoredVertex(ColorR, PointA);
		ColoredVertex(ColorG, PointB);
		ColoredVertex(ColorB, PointC);
		// ƽ��ACD
		ColoredVertex(ColorR, PointA);
		ColoredVertex(ColorB, PointC);
		ColoredVertex(ColorY, PointD);
		// ƽ��CBD
		ColoredVertex(ColorB, PointC);
		ColoredVertex(ColorG, PointB);
		ColoredVertex(ColorY, PointD);
		// ƽ��BAD
		ColoredVertex(ColorG, PointB);
		ColoredVertex(ColorR, PointA);
		ColoredVertex(ColorY, PointD);
		glEnd();
		glEndList();

		glEnable(GL_DEPTH_TEST);
	}

	// �Ѿ���������ʾ�б���ÿ�λ�����������ʱ��������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef(angle, 1, 0.5, 0);//�൱����ת������������
	glCallList(list);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

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
	//grab();//����
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);//��������GLUTʹ��֮ǰ����һ��
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);//������ʾ��ʽ��ʹ��RGB��ɫ��������ģʽ
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("��һ��OpenGL����");//����ǰ�����õ���Ϣ��������

	glutDisplayFunc(&myDisplayTex);//����Ҫ��ͼʱ�������myDisplay����(myDisplayΪ�ص�����)
	//glutDisplayFunc(&myDisplayList);
	//glutDisplayFunc(&myDisplayBlend);
	//glutDisplayFunc(&myDisplayLight);

	//glutIdleFunc(&myIdle);//����ʱ����

	// ��������һЩ��ʼ��
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);//��������
	texGround = load_texture("ground.bmp");
	texWall = load_texture("wall.bmp");

	glutMainLoop();
	return 0;
}
