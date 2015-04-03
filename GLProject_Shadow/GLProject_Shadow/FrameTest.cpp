#include "FrameTest.h"
#include <glut.h>

#include "MouseLimit.h"
#include "LinearMap.h"

#include <iostream>///////////////////////////////////
#include <list>

#include "GLPointf.h" //����#include "GLVector3Df.h"


FrameTest::FrameTest()
{
}

FrameTest::FrameTest(int argc, char* argv[], std::string title, unsigned width, unsigned height)
:GLFramework(argc, argv, title, width, height), 
m_light0(), 
m_camera0(), 
m_keys()
{
	//pCube = new TestCube();//���������ﴴ����Ҫô����ID����ʧ�ܣ�
}

/*����ɾ����������Init()�ﴴ����
* һ�������壨�ӵ�����Display()����ObjectList�ഴ���� */
void FrameTest::Init()
{
	GLInit m_init;

	glClearStencil(0); //�����ɰ�ֵ

	/* ���������ʼ״̬ */

	float positionL[] = { 100, 400, 0, 1 }; 
	m_light0.SetLightPos(positionL);
	m_light0.TurnOnColorTrack();
	//m_light0->TurnOn(); //������Display�п�����

	viewAngleZ = 0;
	viewAngleY = 0;

	viewMode = 0; 

	//�����λ��
	m_camera0.UpdateFrustum();
	m_camera0.SetEyePos(0, 0, 0);
	m_camera0.SetTargetPos(0, 0, 0);
	SetCursorPos(m_WindowP->GetWidth() / 2, m_WindowP->GetHeight() / 2); //���ָ����������


	//������Ķ������������ﴴ���������ڹ������洴����Ҫô����ID�����ʧ�ܣ�
	pPlane = new TestPlane();
	pPlane->SetPos(0, 5, 0);

	pSkyBox = new SkyBox();

}

void FrameTest::Display()
{
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); //ģ�建����

	/* �ƹ� */
	m_light0.TurnOn();

	/* ����� */

	float viewDistance = 20; //��ͷ������֮��ľ��룻�ϵ��ӽǣ���Զ��ͷ
	if (viewMode) //��һ�˳�
	{
		m_camera0.SetEyePos(0, 0, 0);
		m_camera0.SetViewAngleWithEyeFixed(viewAngleY, viewAngleZ);
	}
	else //�ϵ��ӽ�
	{
		m_camera0.SetTargetPos(0, 0, 0);
		m_camera0.SetViewAngleWithTargetFixed(viewDistance, viewAngleY, viewAngleZ);
	}
	m_camera0.UpdatePerspective(75, 1.3); //�����������������������
	m_camera0.Apply();

	float lightPos[4];
	glGetLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	GLPointf lp;
	lp.x = lightPos[0];
	lp.y = lightPos[1];
	lp.z = lightPos[2];

	//m_camera0.RenderLensFlare(lp);

	DrawScene(GL_RENDER);

	/* �����߼����� */

	glFlush();
	glutSwapBuffers();
}

/* ������Ⱦ */
void FrameTest::DrawScene(GLenum mode)
{
	//�ƹ⴦����һ����̫����
	float lightPos[4];
	glGetLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glPushMatrix();
	glDisable(GL_TEXTURE_2D);
	glColor3f(1, 1, 0.5);
	glTranslatef(lightPos[0], lightPos[1], lightPos[2]);
	glTranslatef(0, 20, 0);
	glutSolidSphere(5, 20, 20);
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glPopMatrix();

	
	glColor3f(1, 1, 1);
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(1, 1, 0);

	glutSolidSphere(2, 20, 20);

	glTranslatef(0, -3, 0);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	glRotatef(60, 0.0f, 1.0f, 0.0f);

	glRectf(-10, -10, 10, 10);

	glEnable(GL_TEXTURE_2D);
	glPopMatrix();

	//�ɻ��Զ���(20,20,0)ˮƽ����
	pPlane->Move(); //�˶���������Ҫ������䣡
	pPlane->SetRenderMode(false, true);

	pPlane->Render();
	pPlane->SetLightedFaces(lightPos);
	pPlane->RenderShadow(lightPos);

	//��պ�
	pSkyBox->SetRenderMode(false, true, TEXTURE, GL_CCW);
	pSkyBox->Render();
	pSkyBox->SetPos(0, 240, 0);

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
		}
		else
		{
			/*�ɿ�������*/
			std::cout << "�ɿ�������" << std::endl;
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
	m_keys.SetPressed(key);
	if (key == ' ') //���������л��ӽǲŲ��ᱻһֱ��⣡
		viewMode = !viewMode;
}

void FrameTest::KeyboardUpSet(unsigned char key, int x, int y)
{
	m_keys.SetReleased(key);
}

void FrameTest::KeyboardRespond()//��Timer�������Ӧ����
{
	if (m_keys.IsPressed('w'))
	{
		std::cout << "W����" << std::endl;
	}

	if (m_keys.IsPressed('s'))
	{
		std::cout << "S����" << std::endl;
	}

	if (m_keys.IsPressed('a'))
	{
		std::cout << "A����" << std::endl;
	}

	if (m_keys.IsPressed('d'))
	{
		std::cout << "D����" << std::endl;
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
