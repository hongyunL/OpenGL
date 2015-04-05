#include <glut.h>

#include "world\World.h"
#include "world\Camera.h"
#include "world\Light.h"

#include "MouseController.h"
#include "MapFunction.h"
#include "LinearMap.h"

#include <iostream>
using namespace std;

#include "GameWorld.h"

#include "Random.h"

GameWorld *pWorld;
Camera cam;

//void Timer(int value);
void Timer(int value){
	glutPostRedisplay();
	glutTimerFunc(20, Timer, 0);
}

void RenderScene(void){
	pWorld->onDisplay();
}				

void ChangeSize(int w, int h){
	pWorld->onChangeSize(w, h);
}

/*��������¼�*/
/*����Ϊ:��ǰ�������ڴ������Ͻǵ�λ��*/
void mouseOperation(int x, int y){
	MouseController mouse(pWorld->getRenderWindowHandle());

	const int EDGE = 30;
	const int limitLeft = EDGE;//����ƶ���Χ�����
	const int limitRight = pWorld->getWidth() - EDGE;//����ƶ���Χ���ҽ�

	mouse.limitMouseMovingDomainRL(limitLeft, limitRight);

	/*�����λ�ôӴ��ڵ׶ˣ����꣺ pWorld->getHeight()�������ڶ��ˣ����꣺0����ӳ�䵽
	*�������z����ӽǣ������ǣ���-90�ȵ�90�ȡ�*/
	LinearMap<float> mapAngleZ(pWorld->getHeight(), 0, -90, 90);
	//LinearMap<float> mapAngleZ(pWorld->getHeight(), 0, -30, 75);

	/*�����λ�ô���絽�ҽ硿ӳ�䵽�������y����ӽǴ�180�ȵ�-180�ȡ�*/
	LinearMap<float> mapAngleY(limitLeft, limitRight, 180, -180);
	//LinearMap<float> mapAngleY(limitLeft, limitRight, 60, -60);

	LinearMap<float> m(0, 600, -90, 90);
	float f = m.map(400);

	float viewAngleZ = mapAngleZ.map(y);
	float viewAngleY = mapAngleY.map(x);

	//cam.setCenterPos(5, 5, 2);
	//cam.setViewAngleWithCenterFixed(2, viewAngleY, viewAngleZ);
	cam.setEyePos(-2, 2, 0);
	cam.setViewAngleWithEyeFixed(viewAngleY, viewAngleZ);

	pWorld->setCannonAngle(viewAngleY, viewAngleZ);
	//pWorld->setCannonAngle(0, 0);
}

void DealMouseMove(int x,int y){
	mouseOperation(x,y);
}

void DealMouseDrag(int x, int y){
	mouseOperation(x, y);
}

void DealMouseButtonAction(int button, int state, int x, int y)
{
	if(GLUT_LEFT_BUTTON == button)
	{	
		if(GLUT_DOWN == state)
		{
			/*����������*/
			pWorld->onClick();
		}
		else
		{
			/*�ɿ�������*/
			pWorld->onRelease();
		}
	}
}

int main(int argc, char* argv[]){
	
	/*��������*/
	pWorld = new GameWorld(argc, argv, "AngryPig", 640, 480, 20, &cam);

	/*Ӧ�ù���*/
	float  ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	float  diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	Light light0(0);
	light0.setAmbient(ambientLight);
	light0.setDiffuse(diffuseLight);
	light0.turnOn();

	/*���������*/
	cam.setCenterPos(0, 0, 0);
	cam.setViewAngleWithCenterFixed(10, 0, 0);

	SetCursorPos(pWorld->getWidth() / 2, pWorld->getHeight() / 2);//���ָ����������

	/*ע��ص�����*/
	glutDisplayFunc(RenderScene);

	glutReshapeFunc(ChangeSize);

	glutMotionFunc(DealMouseMove); //�����ƶ��ص�����

	glutPassiveMotionFunc(DealMouseDrag); //���õ�ǰ���ڵı����ƶ��ص�����

	glutMouseFunc(DealMouseButtonAction); //ע�ᵱǰ���ڵ����ص�����

	glutTimerFunc(20, Timer, 0); //ע�ᰴһ��ʱ���������Ķ�ʱ���ص�����

	//glutKeyboardFunc(unsigned char key[]);

	/*������ѭ��*/
	glutMainLoop();

	return 0;
}