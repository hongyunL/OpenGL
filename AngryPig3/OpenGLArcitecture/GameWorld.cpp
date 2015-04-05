#include "GameWorld.h"
#include <vector>
#include <glut.h>
#include "model/BulletData.h"

#include "Random.h"
#include <iostream>///////////////////////////////////////////////////////

GameWorld::GameWorld(void)
{
}

GameWorld::GameWorld(int argc, char* argv[], std::string title, unsigned width, unsigned height, unsigned frameTimeMs, Camera *pCamera)
	: World(argc, argv, title, width, height, frameTimeMs, pCamera),
	ground(-15, 21, 60, -21, -0.1f, 0.4f, 0.4f, 0.17f)
{
	timeSinceLastShot = FIRE_INTERVAL;
	shooting = false;

	glClearColor(0.7f, 0.7f, 1.0f, 1.0f);

	p0.x = 1;
	p0.z = -2;
	p0.rotY = -30;
	p0.rotZ = 20;
	p1.x = 2;
	p1.z = 1;
	p1.rotY = 60;
	p1.rotZ = -10;

	for(int i = 0; i < (int)5; i ++)
	{
		aBows[i].x = 60;
		aBows[i].z = i*10-20;
	}



	/*for(int i = -20; i < 20; i+=2){
	for(int j = 35; j < 75; j+=2){
	createBird(60, 5, i, 180, j, 0.3f);
	}
	}*/
	//createBird(60, 5, 20, 180, 70, 0.3f);
}

void GameWorld::onDisplay()
{
	/*��Ϸ�߼�*/
	static unsigned timeSinceLastBirdCreated = 0;

	/*����С��*/
	if(20 == timeSinceLastBirdCreated)
	{
		float genBirdX,genBirdY,genBirdZ; //����С������λ��
		float genHoriAng,genElevAng;//����С��ĳ�ʼ�Ƕ�

		genBirdX = 56;
		genBirdZ = Random::GenFloat(-20.0,20.0);
		genBirdY = 2;

		genHoriAng = 180 + Random::GenFloat(-10.0,10.0);
		genElevAng	= Random::GenFloat(40.0,50.0);

		createBird(genBirdX,genBirdY,genBirdZ,genHoriAng,genElevAng,0.3f);
		timeSinceLastBirdCreated = 0;
	}
	else
	{
		timeSinceLastBirdCreated++;
	}

	/*�����ӵ�����*/
	if(timeSinceLastShot < FIRE_INTERVAL)
		timeSinceLastShot++;

	if(shooting)
	{
		if(FIRE_INTERVAL == timeSinceLastShot)
		{
			timeSinceLastShot = 0;
			shoot();
		}
	}

	std::list<Bird*>::iterator iterBird;  
	std::list<Bullet*>::iterator iterBullet;

	/*С������*/
	for(iterBird = m_listPBird.begin(); iterBird != m_listPBird.end(); iterBird++)
	{
		if(sphereHitsPlaneY(0, (*iterBird)->y, (*iterBird)->getRadius()))
		{
			(*iterBird)->killed();
		}
	}

	/*С�����Ǳ�*/
	for(iterBird = m_listPBird.begin(); iterBird != m_listPBird.end(); iterBird++)
	{
		if(sphereHitsPlaneX(-7, (*iterBird)->x, (*iterBird)->getRadius()))
		{
			(*iterBird)->killed();

			if(-12 < (*iterBird)->z && (*iterBird)->z < 12 && (*iterBird)->y < 8)
			{
				castleHit();
			}
		}
	}

	/*�����������ӵ���С������ײ���*/
	for(iterBullet = m_listPBullet.begin(); iterBullet != m_listPBullet.end(); iterBullet++)
	{
		for(iterBird = m_listPBird.begin(); iterBird != m_listPBird.end(); iterBird++)
		{
			if(bulletHitsBird(*iterBullet, *iterBird))
			{
				(*iterBullet)->hitTarget();
				(*iterBird)->killed();
			}
		}
	}


	/*��Ⱦ����*/
	ClearScreen();
	/*���Ʋ�͸������*/
	Mesh::SetRenderMode(false, true, Mesh::COLOR);
	barrel.render();
	base.render();
	mountain.render();
	castle.render();
	p0.render();
	p1.render();
	for(unsigned i = 0; i < 5; i++)
	{
		aBows[i].render();
	}

	ground.render();

	//����m_listPBird����������С��
	iterBird = m_listPBird.begin();
	while(iterBird != m_listPBird.end()){
		bool removable = (*iterBird)->render();
		if(removable)
		{
			//delete (*iterBird);
			iterBird = m_listPBird.erase(iterBird);
		}
		if(iterBird != m_listPBird.end())
		{
			iterBird++;
		}
	}

	/*����͸������*/
	Mesh::SetRenderMode(false, false, Mesh::COLOR);
	axis.render();

	Mesh::SetRenderMode(false, true, Mesh::COLOR);
	//����m_listPBullet�����������ӵ�
	iterBullet = m_listPBullet.begin();
	while(iterBullet != m_listPBullet.end()){
		bool removable = (*iterBullet)->render();

		if(removable)
		{
			//delete (*iterBullet);
			iterBullet = m_listPBullet.erase(iterBullet);
		}
		if(iterBullet != m_listPBullet.end())
		{
			iterBullet++;
		}
	}

	m_pCurCam->apply();

	RenderFinish();
}

/*������Ͳ��ָ��*/
void GameWorld::setCannonAngle(float angY, float angZ)
{
	barrel.rotY = angY;
	barrel.rotZ = angZ;
}

/*�������*/
void GameWorld::onClick()
{
	shooting = true;
}

/*�ɿ����*/
void GameWorld::onRelease()
{
	shooting = false;
}

void GameWorld::shoot()
{
	float x, y, z;
	barrel.countLeftFrontCoord(&x, &y, &z);
	createBullet(x, y, z, barrel.rotY, barrel.rotZ, BulletData::VELOCITY);

	barrel.countRightFrontCoord(&x, &y, &z);
	createBullet(x, y, z, barrel.rotY, barrel.rotZ, BulletData::VELOCITY);
}

void GameWorld::createBullet(float x, float y, float z, float rotY, float rotZ, float velocity)
{
	Bullet *pBullet = new Bullet;
	pBullet->setInitStatus(x, y, z, rotY, rotZ, velocity);

	m_listPBullet.push_back(pBullet);
}

void GameWorld::createBird(float x, float y, float z, float rotY, float rotZ, float velocity)
{
	Bird *pBird = new Bird;
	pBird->setInitStatus(x, y, z, rotY, rotZ, velocity);

	m_listPBird.push_back(pBird);
}

/*С����ӵ��Ƿ���ײ*/
//�������ӵ�ǰ�к�����ֻҪ��һ����ײ���϶���ײ
bool GameWorld::bulletHitsBird(Bullet *pBullet, Bird *pBird)
{
	float birdX = pBird->x;
	float birdY = pBird->y;
	float birdZ = pBird->z;
	float r = pBird->getRadius();

	float bulletX, bulletY, bulletZ;//�����㣨���˵㼰�е㣩������

	pBullet->getFrontCoord(&bulletX, &bulletY, &bulletZ);
	if(countPointDis2(birdX, birdY, birdZ, bulletX, bulletY, bulletZ) < r * r)
		return true;

	if(countPointDis2(birdX, birdY, birdZ, pBullet->x, pBullet->y, pBullet->z) < r * r)
		return true;

	pBullet->getBackCoord(&bulletX, &bulletY, &bulletZ);
	if(countPointDis2(birdX, birdY, birdZ, bulletX, bulletY, bulletZ) < r)
		return true;


	return false;
}

/*�������������ƽ��*/
float GameWorld::countPointDis2(float x0, float y0, float z0, float x1, float y1, float z1)
{
	return 
		(x1-x0) * (x1-x0) +
		(y1-y0) * (y1-y0) +
		(z1-z0) * (z1-z0);
}

/*����������ָ��ƽ���Ƿ��ཻ
*planeX��ʾx��ƽ�棬����ֱ��x���ƽ��*/
bool GameWorld::sphereHitsPlaneX(float planeX , float sphereX, float r)
{
	bool isIntersect = false;
	if(abs(sphereX - planeX) <= abs(r)){
		isIntersect = true;
	}
	return isIntersect;
}
/*planeY��ʾy��ƽ�棬����ֱ��y���ƽ��*/
bool GameWorld::sphereHitsPlaneY(float planeY , float sphereY, float r)
{
	bool isIntersect = false;
	if(abs(sphereY - planeY) <= abs(r)){
		isIntersect = true;
	}
	return isIntersect;
}

/*�Ǳ���С�����*/
void GameWorld::castleHit()
{
}

	/*�ӷ�*/
void GameWorld::score()
{
}

GameWorld::~GameWorld(void)
{

}
