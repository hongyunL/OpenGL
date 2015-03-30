#include "FireworksFrame.h"
#include <glut.h>

#include "MouseLimit.h"
#include "LinearMap.h"

#include <iostream>///////////////////////////////////
//#include <list>

#include "Texture.h"

FireworksFrame::FireworksFrame()
{
}

FireworksFrame::FireworksFrame(int argc, char* argv[], std::string title, unsigned width, unsigned height)
:GLFramework(argc, argv, title, width, height)
{
	//������ֻ���� ���� �������
	//m_light0 = new Light();
	m_camera0 = new Camera();

	//pCube = new TestCube();//���������ﴴ����Ҫô����ID����ʧ�ܣ�
}

/*����ɾ����������Init()�ﴴ����
* һ�������壨�ӵ�����Display()����ObjectList�ഴ���� */
void FireworksFrame::Init()
{
	m_init = new GlobalInit();

	/* ���������ʼ״̬ */

	//�趨��Ϸ����
	keys = new Keys();

	//��ʾ����
	font.BuildFont();
	
	//font3D.UseTex(true);////////////////////////////////////////////////
	font3D.BuildFont();

	viewAngleZ = 0;
	viewAngleY = 0;

	viewMode = 0; //�����ӽ�

	//�����λ���趨���������
	m_camera0->SetEyePos(2, 1, 1);
	m_camera0->SetTargetPos(0, 0, 0);
	SetCursorPos(m_WindowP->GetWidth() / 2, m_WindowP->GetHeight() / 2); //���ָ����������

	//������Ķ������������ﴴ���������ڹ������洴����Ҫô����ID�����ʧ�ܣ�
	m_axis = new Axis();


	isShoot = false;
	shootTimer = 0;

	t.LoadTexture("stars.bmp");
}

void FireworksFrame::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* ����� */

	float viewDistance = 10; //��ͷ������֮��ľ��룻�ϵ��ӽǣ���Զ��ͷ
	if (viewMode) //��һ�˳�
	{
		//m_camera0->SetEyePos(-200, 100, 0); //���̻�
		m_camera0->SetEyePos(-5, 5, 5);
		m_camera0->SetViewAngleWithEyeFixed(viewAngleY, viewAngleZ);
	}
	else //�ϵ��ӽ�
	{
		m_camera0->SetTargetPos(0, 0, 0);
		m_camera0->SetViewAngleWithTargetFixed(viewDistance, viewAngleY, viewAngleZ);
	}
	m_camera0->UpdatePerspective(75, 1.3); //�����������������������
	m_camera0->Apply();

	//��ʾ����
	char *string = "HAPPY NEW YEAR";
	font.glPrint(4, 5, string);

	string = "FGHIJ";
	font3D.glPrint(3, 0, string);

	/* ������Ⱦ */
	/* �Ȼ��ơ���͸�����塿�� */
	//��������������Ϊ(false, true, TEXTURE, GL_CCW, GL_TRIANGLES)����Ҫָ����
	m_axis->SetRenderMode(false, false, COLOR, GL_CCW, GL_LINES);
	m_axis->Render();

	glEnable(GL_TEXTURE_2D);
	t.Apply();

	glBegin(GL_TRIANGLE_STRIP);

	glTexCoord2d(1, 1); glVertex3f(1500, 1500, -1500);
	glTexCoord2d(0, 1); glVertex3f(1500, 1500, 1500);
	glTexCoord2d(1, 0); glVertex3f(-1500, 1500, -1500);
	glTexCoord2d(0, 0); glVertex3f(-1500, 1500, 1500);

	glEnd();


	/* �����߼����� */
	if (isShoot)
		Shoot();

	m_fireworksListIter = m_fireworksList.begin();
	while (true)
	{
		if (m_fireworksListIter == m_fireworksList.end())
		{
			//����б�Ϊ�գ�������ֱ�ӵ���list.end();
			//��һ��ѭ���У�����erase()������ɾ����������ǰָ���Ԫ�أ��п��ܵ��µ�����������list.end()
			//��һ��ѭ���У�������++Ҳ���ܵ��µ�����������list.end();
			break;
		}

		if (!(*m_fireworksListIter)->m_arrParticles[69].GetActive()) //������������
		{
			delete(*m_fireworksListIter);
			m_fireworksListIter = m_fireworksList.erase(m_fireworksListIter);//erase:ʹ��Ϊ�����ĵ�����ʧЧ������ָ��õ�������һ�����ĵ�����
		}

		if (m_fireworksListIter != m_fireworksList.end()) //ȷ��������û��Խ�磡
			m_fireworksListIter++;
	}

	/* ��͸�����塿�����ڻ����겻͸������֮�������ȷ���ƣ��� */
	//����ϵͳ
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D); //��������ϵͳû��ʹ������

	for (m_fireworksListIter = m_fireworksList.begin(); m_fireworksListIter != m_fireworksList.end(); m_fireworksListIter++)
	{
		if ((*m_fireworksListIter)->m_arrParticles[50].GetActive())
		{
			(*m_fireworksListIter)->Render();
			(*m_fireworksListIter)->Run();
		}
	}
	glEnable(GL_DEPTH_TEST);
	glColor3f(1, 1, 1); //�ָ�����ײ���ɫ����

	glFlush();
	glutSwapBuffers();
}

void FireworksFrame::MouseMotion(int x, int y)
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

void FireworksFrame::MousePassiveMotion(int x, int y)
{
	MouseMotion(x, y);
}

void FireworksFrame::MouseButton(int button, int state, int x, int y)
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

void FireworksFrame::KeyboardSet(unsigned char key, int x, int y)//�趨����
{
	keys->SetPressed(key);
	if (key == ' ') //���������л��ӽǲŲ��ᱻһֱ��⣡
		viewMode = !viewMode;
}

void FireworksFrame::KeyboardUpSet(unsigned char key, int x, int y)
{
	keys->SetReleased(key);
}

void FireworksFrame::KeyboardRespond()//��Timer�������Ӧ����
{
	if (keys->IsPressed('w'))
	{
		std::cout << "W����" << std::endl;
	}

	if (keys->IsPressed('s'))
	{
		std::cout << "S����" << std::endl;
	}

	if (keys->IsPressed('a'))
	{
		std::cout << "A����" << std::endl;
	}

	if (keys->IsPressed('d'))
	{
		std::cout << "D����" << std::endl;
	}

}

void FireworksFrame::SpecialKey(int key, int x, int y)
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
void FireworksFrame::Shoot()
{
	std::cout << "shootTimer:" << shootTimer << std::endl;

	if (0 == shootTimer)
	{
		/*��ָ���ظ�����������ʱ��
		* ÿ�ض�Ҫ������һ��ָ�룬
		* ��ָֹ���޸��˶�������ݣ�ÿ����һ��gunBarrel�Ͷ��һ���ٶȣ�
		* ��û�취����������������һ���ϵ㣩��
		*/
		pParticle = new Fireworks();
		pParticle->Init();

		m_fireworksList.push_back(pParticle);

		shootTimer = 3; //��취��һ���°������̷��䣿
	}
	else
		shootTimer--;
}