#include <glut.h>

#include "stdio.h"

const GLint pickSize = 32;
int winWidth = 400, winHeight = 400;

void Initial(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void DrawRect(GLenum mode)
{
	if (mode == GL_SELECT) 
		glPushName(1); //ѹ���ջ
	glColor3f(1.0f, 0.0f, 0.0f);
	//glRectf(60.0f, 50.0f, 150.0f, 150.0f);
	glPushMatrix();
	glTranslatef(1, 0, 0);
	glutSolidSphere(1.0f, 20.0f, 20.0f);
	glPopMatrix();

	if (mode == GL_SELECT) 
		glPushName(2); //ѹ���ջ
	glColor3f(0.0f, 1.0f, 0.0f);
	//glRectf(230.0f, 50.0f, 330.0f, 150.0f);
	glPushMatrix();
	glTranslatef(1, 0, 2);
	glutSolidSphere(2.0f, 20.0f, 20.0f);
	glPopMatrix();

	if (mode == GL_SELECT) 
		glPushName(3); //ѹ���ջ
	glColor3f(0.0f, 0.0f, 1.0f);
	//glRectf(140.0f, 140.0f, 240.0f, 240.0f);
	glPushMatrix();
	glTranslatef(1, 0, 6);
	glutSolidSphere(2.0f, 20.0f, 20.0f);
	glPopMatrix();
}

void ProcessPicks(GLint nPicks, GLuint pickBuffer[])
{
	GLint i;
	GLuint name, *ptr;
	printf("ѡ�е���ĿΪ%d��\n", nPicks);

	ptr = pickBuffer;
	for (i = 0; i<nPicks; i++){
		name = *ptr;	  //ѡ��ͼԪ�ڶ�ջ�е�λ��
		ptr += 3;		  //�������ֺ������Ϣ
		ptr += name - 1;  //����λ����Ϣ���ѡ�е�ͼԪ����

		if (*ptr == 1)
		{
			printf("��ѡ���˺�ɫͼԪ\n");
		}
		if (*ptr == 2)
		{
			printf("��ѡ������ɫͼԪ\n");
		}
		if (*ptr == 3)
		{
			printf("��ѡ������ɫͼԪ\n");
		}
		ptr++;
	}
	printf("\n\n");
}

void ChangeSize(int w, int h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		-10, 5, 0,
		1, 0, 3,  
		0, 1, 0);

	{
		GLfloat sun_light_position[] = { 0.0f, 20.0f, 0.0f, 1.0f }; //λ�ã���4������Ϊ0��������Զ��
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

		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	}

	DrawRect(GL_RENDER);

	glFlush();
}

void MousePlot(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
	GLuint pickBuffer[pickSize];
	GLint nPicks, vp[4];

	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
		glSelectBuffer(pickSize, pickBuffer); //����ѡ�񻺳���
		glRenderMode(GL_SELECT); //����ѡ��ģʽ
		glInitNames();   //��ʼ�����ֶ�ջ

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		glGetIntegerv(GL_VIEWPORT, vp);
		//����һ��10��10��ѡ������
		gluPickMatrix(
			GLdouble(xMouse),		   //�趨����ѡ���Ĵ�С������ʰȡ���󣬾�������Ĺ�ʽ 
			GLdouble(vp[3] - yMouse),  //viewport[3]������Ǵ��ڵĸ߶ȣ���������ת��ΪOpenGL���� 
			10.0, 10.0,				   //ѡ���Ĵ�СΪ10��10
			vp);					   //�ӿ���Ϣ�������ӿڵ���ʼλ�úʹ�С 

		//gluOrtho2D(0.0, winWidth, 0.0, winHeight); //ʰȡ�������ͶӰ���������Ϳ�����ѡ���Ŵ�Ϊ������һ���� 

		gluPerspective(45.0f, (GLfloat) (vp[2]-vp[0])/(GLfloat) (vp[3]-vp[1]), 0.1f, 100.0f);
		glMatrixMode(GL_MODELVIEW);

		DrawRect(GL_SELECT);

		//�ָ�ͶӰ�任
		glMatrixMode(GL_PROJECTION);
		glPopMatrix(); 
		glMatrixMode(GL_MODELVIEW);


		glFlush();

		//���ѡ�񼯲����
		nPicks = glRenderMode(GL_RENDER); //�õ�ѡ���������Ŀ
		if( 0 != nPicks )
			ProcessPicks(nPicks, pickBuffer);

		glutPostRedisplay();
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("ʰȡ����");
	glutDisplayFunc(Display);
	glutReshapeFunc(ChangeSize);
	glutMouseFunc(MousePlot);
	Initial();
	glutMainLoop();
	return 0;
}