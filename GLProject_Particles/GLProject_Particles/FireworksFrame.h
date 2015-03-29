#pragma once

#include "GLFramework.h"//#include "GlobalInit.h" //�������Ѿ�������
#include "Light.h"
#include "Camera.h"
#include "Axis.h"
#include "Fireworks.h"
#include "Keys.h"

/* �Զ���ģ�� */
#include <list> //���̻�

class FireworksFrame : public GLFramework
{
public:
	FireworksFrame();
	FireworksFrame(int argc, char* argv[], std::string title, unsigned width, unsigned height);

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
	Axis *m_axis;

	Keys *keys;

	/* �Զ���ģ�� */



	/* ���ڲ�ȫ�ֱ���������Э���ӽǡ����������ߡ����̰�������Ӧ */
	
	//�����ĳһ���ӳ��Ƕ�
	float viewAngleZ; //Mouse�趨��Displayʹ��
	float viewAngleY;

	//�л������ӽǣ�1 true�������ӽǣ�0 false:�ϵ��ӽ�
	bool viewMode; //Keyboard�趨��Displayʹ��

	bool isShoot; //Keyboard�趨��Displayʹ��
	int shootTimer;


	Fireworks *pParticle;

	std::list<Fireworks*> m_fireworksList;
	std::list<Fireworks*>::iterator m_fireworksListIter;

	Texture t;
	

	/* �ڲ�ʹ�õĺ��� */
	void Shoot();

};