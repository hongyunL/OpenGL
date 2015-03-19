#include <glut.h>//�����Ѿ�����<GL/gl.h>��<GL/glu.h>

static GLfloat angle = 0.0f;

void myDisplayBlend(void);

/* �ڿ���ʱ���ã������ǰ����������ƶ�һ�첢���»��ƣ��ﵽ����Ч�� */
void myIdle(void)
{
	angle += 0.1f;
	if (angle >= 360.0f)
		angle = 0.0f;

	myDisplayBlend();
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

	glRotatef(angle, 0.0f, -1.0f, 0.0f);

	glTranslatef(0.0f, 0.0f, 0.5f);
	glutSolidSphere(0.3, 30, 30);
	glPopMatrix();

	// ���潫���ư�͸�������ˣ���˽���Ȼ�������Ϊֻ��
	glDepthMask(GL_FALSE);

	// ��(0.2, 0, -0.5)Ϊ���ģ�����һ���뾶Ϊ0.2�İ�͸����ɫ���壨��۲��������
	setMatirial(blue_color, 30.0);
	glPushMatrix();

	glRotatef(angle, 1.0f, 0.0f, 0.0f);

	glTranslatef(0.2f, 0.0f, -0.5f);
	glutSolidSphere(0.2, 30, 30);
	glPopMatrix();

	// ��(0.1, 0, 0)Ϊ���ģ�����һ���뾶Ϊ0.15�İ�͸����ɫ���壨��ǰ��������֮�䣩
	setMatirial(green_color, 30.0);
	glPushMatrix();

	glRotatef(angle, 0.0f, 0.0f, 1.0f);

	glTranslatef(0.1, 0, 0);
	glutSolidSphere(0.15, 30, 30);
	glPopMatrix();

	// ��ɰ�͸������Ļ��ƣ�����Ȼ������ָ�Ϊ�ɶ���д����ʽ
	glDepthMask(GL_TRUE);

	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);//��������GLUTʹ��֮ǰ����һ��
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);//������ʾ��ʽ��ʹ��RGB��ɫ��������ģʽ
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("OpenGL�����еĶ���");//����ǰ�����õ���Ϣ��������

	//����Ҫ��ͼʱ�������myDisplay����(myDisplayΪ�ص�����)
	glutDisplayFunc(&myDisplayBlend);

	glutIdleFunc(&myIdle);//����ʱ����

	glutMainLoop();
	return 0;
}
