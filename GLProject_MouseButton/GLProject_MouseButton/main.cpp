#include "FrameTest.h"

#include <glut.h>

FrameTest *ft;

/* ����ĺ����������������Ա�����ж�Ӧ�Ļص����� */
void TimerCal(int value){
	glutPostRedisplay();
	glutTimerFunc(20, TimerCal, 0);
}

void DisplayCal()
{
	ft->Display();
}
void ReshapeCal(int x, int y)
{
	ft->Reshape(x, y);
}

void MouseMotionCal(int x, int y)
{
	ft->MouseMotion(x,y);
}
void MousePassiveMotionCal(int x, int y)
{
	ft->MousePassiveMotion(x, y);
}

void MouseButtonCal(int button, int state, int x, int y)
{
	ft->MouseButton(button, state, x, y);
}


int main(int argc, char *argv[])
{
	std::string title = "��갴���ļ���";
	unsigned width = 640;
	unsigned height = 480;

	ft = new FrameTest(argc, argv, title, width, height);

	ft->CreateGLWindow();
	ft->Init();

	glutDisplayFunc(DisplayCal);
	glutReshapeFunc(ReshapeCal);
	glutTimerFunc(20, TimerCal, 0); //ע�ᰴһ��ʱ���������Ķ�ʱ���ص�����

	glutMotionFunc(MouseMotionCal); //������������ʱ������϶����¼�
	glutPassiveMotionFunc(MousePassiveMotionCal); //��û����������ʱ������϶����¼�

	glutMouseFunc(MouseButtonCal);  //��갴��

	glutMainLoop();
	return 0;
}