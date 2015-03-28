#pragma once

#include "GLFramework.h"//#include "GlobalInit.h" //�������Ѿ�������

#include "Light.h"
#include "Camera.h"
#include "Fog.h"
#include "Axis.h"

#include "Keys.h"

/* �Զ���ģ�� */
#include "TestPlane.h" //AI

#include "TankChassis.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "TankShell.h"

#include "SkyBox.h"

#include <list>

class FrameTest : public GLFramework
{
public:
	FrameTest();
	FrameTest(int argc, char* argv[], std::string title, unsigned width, unsigned height);

	/* ��д���ി�麯�� */
	void Init();
	void Display();	

	void MouseMotion(int x, int y);
	void MousePassiveMotion(int x, int y);
	void MouseButton(int button, int state, int x, int y);

	void KeyboardSet(unsigned char key, int x, int y);
	void KeyboardUpSet(unsigned char key, int x, int y);

	void KeyboardRespond(); //��Timer�е���
	void SpecialKey(int key, int x, int y);

private:
	GlobalInit *m_init;
	Light *m_light0;
	Camera *m_camera0;
	Fog *m_fog;
	Axis *m_axis;

	Keys *keys;

	/* �Զ���ģ�� */

	std::list<TankShell*> gunList; //һ�������壬��Ҫ��ʱɾ��ȷ����ĳ������
	std::list<TankShell*>::iterator gunListIter;

	TestPlane *pPlane;
	
	TankChassis *pTankChassis;
	TankTurret *pTankTurret;
	TankBarrel *pTankBarrel;

	SkyBox *pSkyBox;

	/* ���ڲ�ȫ�ֱ���������Э���ӽǡ����������ߡ����̰�������Ӧ */
	
	//�����ĳһ���ӳ��Ƕ�
	float viewAngleZ; //Mouse�趨��Displayʹ��
	float viewAngleY;

	//�л������ӽǣ�1 true�������ӽǣ�0 false:�ϵ��ӽ�
	bool viewMode; //Keyboard�趨��Displayʹ��

	bool isShoot; //Keyboard�趨��Displayʹ��
	int shootTimer;

	/* �ڲ�ʹ�õĺ��� */

	void Shoot();

};