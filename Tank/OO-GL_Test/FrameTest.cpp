#include "FrameTest.h"
#include <glut.h>

#include "MouseLimit.h"
#include "LinearMap.h"

#include <iostream>///////////////////////////////////
#include <list>

FrameTest::FrameTest()
{
}

FrameTest::FrameTest(int argc, char* argv[], std::string title, unsigned width, unsigned height)
:GLFramework(argc, argv, title, width, height)
{
	//������ֻ���� ���� �������
	m_light0 = new Light();
	m_camera0 = new Camera();

	//pCube = new TestCube();//���������ﴴ����Ҫô����ID����ʧ�ܣ�
}

/*����ɾ����������Init()�ﴴ����
* һ�������壨�ӵ�����Display()����ObjectList�ഴ���� */
void FrameTest::Init()
{
	m_init = new GlobalInit();

	/* ���������ʼ״̬ */

	float positionL[] = { 0, 400, 0, 1 };
	m_light0->SetLightPos(positionL);
	m_light0->TurnOnColorTrack();
	//m_light0->TurnOn(); //������Display�п���

	//�趨��Ϸ����
	keys = new Keys();

	viewAngleZ = 0;
	viewAngleY = 0;

	viewMode = 1; //�����ӽ�

	//�����λ���趨���������
	m_camera0->SetEyePos(2, 1, 0);
	m_camera0->SetTargetPos(0, 0, 0);
	SetCursorPos(m_WindowP->GetWidth() / 2, m_WindowP->GetHeight() / 2); //���ָ����������

	//��Ĵ���������
	m_fog = new Fog();
	m_fog->Apply();

	//������Ķ������������ﴴ���������ڹ������洴����Ҫô����ID�����ʧ�ܣ�
	m_axis = new Axis();

	pPlane = new TestPlane();
	pPlane->SetPos(20, 20, 10);

	pSkyBox = new SkyBox();

	pTankChassis = new TankChassis();
	pTankChassis->SetPos(2, 1, 0); //����λ��

	pTankTurret = new TankTurret();

	
	pTankBarrel = new TankBarrel();
	//pTankBarrel->SetPos(4.4, 2.5, 0);////////////////////////////////////////////////////////////

	isShoot = false;
	shootTimer = 0;
}

void FrameTest::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	/* �ƹ� */
	m_light0->TurnOn();


	/* ����� */
	float tankChassisPosX = 0, tankChassisPosY = 0, tankChassisPosZ = 0;
	pTankChassis->GetPos(&tankChassisPosX, &tankChassisPosY, &tankChassisPosZ);

	float viewDistance = 10; //��ͷ������֮��ľ��룻�ϵ��ӽǣ���Զ��ͷ
	if (viewMode) //��һ�˳�
	{
		//m_camera0->SetEyePos(0, 0.6, 0);
		m_camera0->SetEyePos(tankChassisPosX - 4, tankChassisPosY + 1.5, tankChassisPosZ);
		m_camera0->SetViewAngleWithEyeFixed(viewAngleY, viewAngleZ);
	}
	else //�ϵ��ӽ�
	{
		//m_camera0->SetTargetPos(0, 0, 0);
		m_camera0->SetTargetPos(tankChassisPosX, tankChassisPosY, tankChassisPosZ);
		m_camera0->SetViewAngleWithTargetFixed(viewDistance, viewAngleY, viewAngleZ);
	}
	m_camera0->UpdatePerspective(75, 1.3); //�����������������������
	m_camera0->Apply();


	/* ������Ⱦ */
	/* �Ȼ��ơ���͸�����塿�� */
	//��������������Ϊ(false, true, TEXTURE, GL_CCW, GL_TRIANGLES)����Ҫָ����
	m_axis->SetRenderMode(false, false, COLOR, GL_CCW, GL_LINES);
	m_axis->Render();

	

	//�ɻ��Զ���(20,20,0)ˮƽ����
	pPlane->Move(); //�˶���������Ҫ������䣡
	pPlane->SetRenderMode(false, true);
	pPlane->Render();
	pPlane->Forward();
	pPlane->TurnLeft();

	//̹�˵���
	pTankChassis->Move(); 
	pTankChassis->SetRenderMode();
	pTankChassis->Render();
	
	//̹������
	pTankTurret->SetPos(tankChassisPosX, tankChassisPosY + 1.5, tankChassisPosZ); 
	pTankTurret->SetRot(0, viewAngleY, viewAngleZ / 2);
	//pTankTurret->SetRot(0, -30, 15);
	pTankTurret->Move();
	pTankTurret->SetRenderMode();
	pTankTurret->Render();
	
	//̹����Ͳ
	pTankBarrel->SetPos(tankChassisPosX + 3, tankChassisPosY + 1.5, tankChassisPosZ); 
	pTankBarrel->SetRot(0, viewAngleY, viewAngleZ);
	//pTankBarrel->SetRot(0, -30, 30); //rotY��������ת30��
	pTankBarrel->Move();
	pTankBarrel->SetRenderMode();
	pTankBarrel->Render();

	//��պ�
	pSkyBox->SetRenderMode(false, true, TEXTURE, GL_CCW);
	pSkyBox->Render();
	pSkyBox->SetPos(0, 250, 0);

	/* �����߼����� */
	if (isShoot)
		Shoot();

	{
		float x = 0, y = 0, z = 0; //��ȡ�ӵ�λ��
		for (gunListIter = gunList.begin(); gunListIter != gunList.end(); gunListIter++)
		{
			//list�����ľ���ָ�룬������������ָ��Ĳ������ﲻ���б�����ָ���أ�
			(*gunListIter)->GetPos(&x, &y, &z);
			if (x > 200 || x < -100 ||
				y > 200 || y < -100 || 
				z > 200 || z <-100)
				(*gunListIter)->SetAvailable(false);
		}

		gunListIter = gunList.begin();
		while (true)
		{
			if (gunListIter == gunList.end())
			{
				//����б�Ϊ�գ�������ֱ�ӵ���list.end();
				//��һ��ѭ���У�����erase()������ɾ����������ǰָ���Ԫ�أ��п��ܵ��µ�����������list.end()
				//��һ��ѭ���У�������++Ҳ���ܵ��µ�����������list.end();
				break;
			}

			if (false == (*gunListIter)->IsAvailable()) //������������
			{
				delete(*gunListIter);
				gunListIter = gunList.erase(gunListIter);//erase:ʹ��Ϊ�����ĵ�����ʧЧ������ָ��õ�������һ�����ĵ�����
			}

			if (gunListIter != gunList.end()) //ȷ��������û��Խ�磡
				gunListIter++;
		}
	}

	for (gunListIter = gunList.begin(); gunListIter != gunList.end(); gunListIter++)
	{
		(*gunListIter)->Move();
		(*gunListIter)->SetRenderMode(false, true, COLOR, GL_CCW, GL_TRIANGLES);
		if ((*gunListIter)->IsAvailable())
			(*gunListIter)->Render(); 

		std::cout << "�б�Ԫ�ظ�����" << gunList.size() << std::endl;
		float x = 0, y = 0, z = 0;
		(*gunListIter)->GetPos(&x, &y, &z);
		std::cout << "Position:" << x << " " << y << " " << z << std::endl;
	}


	glFlush();
	glutSwapBuffers();
}

void FrameTest::MouseMotion(int x, int y)
{
	MouseLimit *pMouse = new MouseLimit();
	//MouseLimit mouse(m_WindowP->GetWindowHandle());//��������������ˣ�

	//����ƶ����ҷ�Χ
	const int EDGE = 30;
	const int limitLeft = EDGE;
	const int limitRight = m_WindowP->GetWidth() - EDGE;

	pMouse->MouseMovLimitRL(limitLeft, limitRight);

	//�Ӵ���������λ��ӳ�䵽�봰�����ĵĽǶ�rotY(����)��rotZ(����)
	pMouse->PosIntoAngleY(limitLeft, limitRight, 180, -180);
	pMouse->PosIntoAngleZ(m_WindowP->GetHeight(), 0, -90, 90);
	//pMouse->PosIntoAngleZ(m_WindowP->GetHeight(), 0, -20, 60);/////////////////////////

	viewAngleY = pMouse->GetMapAngleY(x);
	viewAngleZ = pMouse->GetMapAngleZ(y);
}

void FrameTest::MousePassiveMotion(int x, int y)
{
	MouseMotion(x, y);
}

void FrameTest::MouseButton(int button, int state, int x, int y)
{
	if (GLUT_LEFT_BUTTON == button)
	{
		if (GLUT_DOWN == state)
		{
			/*����������*/
			std::cout << "����������" << std::endl;
			isShoot = true;
			
		}
		else
		{
			/*�ɿ�������*/
			std::cout << "�ɿ�������" << std::endl;
			isShoot = false;
		}
	}
	if (GLUT_RIGHT_BUTTON == button)
	{
		if (GLUT_DOWN == state)
		{
			/*����������*/
			std::cout << "��������Ҽ�" << std::endl;
		}
		else
		{
			/*�ɿ�������*/
			std::cout << "�ɿ�����Ҽ�" << std::endl;
		}
	}
}

void FrameTest::KeyboardSet(unsigned char key, int x, int y)//�趨����
{
	keys->SetPressed(key);
	if (key == ' ') //���������л��ӽǲŲ��ᱻһֱ��⣡
		viewMode = !viewMode;
}

void FrameTest::KeyboardUpSet(unsigned char key, int x, int y)
{
	keys->SetReleased(key);
}

void FrameTest::KeyboardRespond()//��Timer�������Ӧ����
{
	if (keys->IsPressed('w'))
	{
		std::cout << "W����" << std::endl;
		pTankChassis->Forward();

	}

	if (keys->IsPressed('s'))
	{
		std::cout << "S����" << std::endl;
		pTankChassis->Backward();

	}

	if (keys->IsPressed('a'))
	{
		std::cout << "A����" << std::endl;
		pTankChassis->TurnLeft();

	}

	if (keys->IsPressed('d'))
	{
		std::cout << "D����" << std::endl;
		pTankChassis->TurnRight();

	}

}

void FrameTest::SpecialKey(int key, int x, int y)
{
	if (key == GLUT_KEY_F1)
	{
		std::cout << "F1ȫ��ģʽ��" << std::endl;
		//Reshape(1024, 768);
	}
	if (key == GLUT_KEY_F2)
	{
		exit(0);
	}
}


/* �ڲ�ʹ�õĺ��� */
void FrameTest::Shoot()
{
	std::cout << "shootTimer:" << shootTimer << std::endl;

	if (0 == shootTimer)
	{
		/*��ָ���ظ�����������ʱ��
		* ÿ�ض�Ҫ������һ��ָ�룬
		* ��ָֹ���޸��˶�������ݣ�ÿ����һ��gunBarrel�Ͷ��һ���ٶȣ�
		* ��û�취����������������һ���ϵ㣩��
		*/
		TankShell *pShell = new TankShell();
		pShell->SetSpeed(-1.0f); //��������Ϊģ�������ˣ�
		pShell->SetRot(0, viewAngleY + 180, -viewAngleZ);
		//pShell->SetRot(0, -30 + 180, -30);

		float muzzleX = 0, muzzleY = 0, muzzleZ = 0;
		pTankBarrel->GetMuzzlePos(&muzzleX, &muzzleY, &muzzleZ);
		pShell->SetPos(muzzleX, muzzleY, muzzleZ);

		gunList.push_back(pShell);

		shootTimer = 5; //��취��һ���°������̷��䣿
	}
	else
		shootTimer--;
}