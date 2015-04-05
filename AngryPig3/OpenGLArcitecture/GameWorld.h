#pragma once
#include "world\World.h"

#include <list>

#include "Axis.h"
#include "GunBarrel.h"
#include "Mountain.h"
#include "Ground.h"
#include "Castle.h"
#include "Pig.h"
#include "Bow.h"
#include "Bird.h"
#include "GunBase.h"
#include "Bullet.h"

class GameWorld : public World
{
public:
	GameWorld(void);

	/*���첢��ʼ��
	*�趨�ӿڴ�С
	*�趨֡����
	*�󶨲���ʼ�������*/
	GameWorld(int argc, char* argv[], std::string title, unsigned width, unsigned height, unsigned frameTimeMs, Camera *pCamera);

	virtual void onDisplay() override;

	/*������Ͳ��ָ��*/
	void setCannonAngle(float angY, float angZ);

	/*�������*/
	void onClick();
	/*�ɿ����*/
	void onRelease();

	~GameWorld(void);

protected:
	/*��̨����*/
	void shoot();

	/*����1���ӵ�*/
	void createBullet(float x, float y, float z, float rotY, float rotZ, float velocity);

	/*����1ֻС��*/
	void createBird(float x, float y, float z, float rotY, float rotZ, float velocity);

	/*С����ӵ��Ƿ���ײ*/
	bool bulletHitsBird(Bullet *pBullet, Bird *pBird);

	/*�������������ƽ��*/
	float countPointDis2(float x0, float y0, float z0, float x1, float y1, float z1);

	/*����������ָ��ƽ���Ƿ��ཻ
	*planeX��ʾx��ƽ�棬����ֱ��x���ƽ��*/
	bool sphereHitsPlaneX(float planeX , float sphereX, float r);
	/*planeY��ʾy��ƽ�棬����ֱ��y���ƽ��*/
	bool sphereHitsPlaneY(float planeY , float sphereY, float r);

	/*�Ǳ���С�����*/
	void castleHit();

	/*�ӷ�*/
	void score();

	std::list<Bullet*> m_listPBullet;
	std::list<Bird*> m_listPBird;

	Axis axis;
	GunBarrel barrel;
	GunBase base;
	Mountain mountain;
	Ground ground;
	Castle castle;
	Pig p0, p1;
	Bow aBows[5];

	bool shooting;
	int timeSinceLastShot;
	static const int FIRE_INTERVAL = 4;
};

