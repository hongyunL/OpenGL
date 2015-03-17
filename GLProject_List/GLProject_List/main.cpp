#include <glut.h>//�����Ѿ�����<GL/gl.h>��<GL/glu.h>
#include <iostream>

static GLfloat angle = 0.0f;

void myDisplayList(void);

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

		//glBegin( /* ��������������ϣ����ģʽ */);
		/* ������ʹ��glVertex*ϵ�к��� */
		/* ָ������ϣ���Ķ���λ�� */
		//glEnd();
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

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);//��������GLUTʹ��֮ǰ����һ��
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);//������ʾ��ʽ��ʹ��RGB��ɫ��������ģʽ
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("OpenGL�����е���ʾ�б�");//����ǰ�����õ���Ϣ��������

	//����Ҫ��ͼʱ�������myDisplay����(myDisplayΪ�ص�����)
	glutDisplayFunc(&myDisplayList);

	glutMainLoop();
	return 0;
}
