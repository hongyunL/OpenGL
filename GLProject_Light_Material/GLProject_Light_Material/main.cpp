#include <glut.h>//�����Ѿ�����<GL/gl.h>��<GL/glu.h>

static GLfloat angle = 0.0f;

void myDisplayLight(void);

//���ʡ����ա���ͼ�任
void myDisplayLight(void)
{
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

	glFlush();//��֤ǰ���OpenGL��������ִ�У��������������ڻ������еȴ���
	glutSwapBuffers();//����������
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);//��������GLUTʹ��֮ǰ����һ��
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);//������ʾ��ʽ��ʹ��RGB��ɫ��������ģʽ
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("OpenGL�����еĹ��ա����ʡ���ͼ�仯");//����ǰ�����õ���Ϣ��������

	//����Ҫ��ͼʱ�������myDisplay����(myDisplayΪ�ص�����)
	glutDisplayFunc(&myDisplayLight);

	glutMainLoop();
	return 0;
}
