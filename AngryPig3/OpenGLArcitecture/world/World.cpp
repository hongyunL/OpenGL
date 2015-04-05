#include "World.h"

#include <glut.h>
#include "Light.h"
#include "Mesh.h"

World::World()
{
}

/*���첢��ʼ��
*�趨�ӿڴ�С
*�趨֡����
*�󶨲���ʼ�������*/
World::World(int argc, char* argv[], std::string title, unsigned width, unsigned height, unsigned frameTimeMs, Camera *pCamera)
{
	m_portWidth = width;
	m_portHeight = height;

	m_frameTimeMs = frameTimeMs;

	bindCamera(pCamera);

	/*��ʼ������*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(m_portWidth, m_portHeight);

	glutCreateWindow(title.c_str());

	m_hRenderWindow = WindowFromDC(wglGetCurrentDC());

	/*�趨��Ⱦ����*/
	//�趨��Ⱦģ��ʱ�Ĳ���
	Mesh::InitMesh(true, false, Mesh::COLOR);

	//�򿪹���
	Light::Enable();

	//��2D������ͼ
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

/*�������
*ͬʱ�����������������Ŀ�߱�*/
void World::bindCamera(Camera *pCamera)
{
	m_pCurCam = pCamera;
	pCamera->setRatioWH((float)m_portWidth / (float)m_portHeight);
}

/*ÿ����ʾ����ʱִ�еĲ���*/
void World::onDisplay()
{
	ClearScreen();

	//�����������Ϸ�߼�
	//�Լ���������

	m_pCurCam->apply();

	RenderFinish();
}

/*��Ļ��С�ı�ʱִ�еĲ���*/
void World::onChangeSize(unsigned newW, unsigned newH)
{
	m_portWidth = newW;
	m_portHeight = newH;

	glViewport(0, 0, newW, newH);

	m_pCurCam->setRatioWH((float)m_portWidth / (float)m_portHeight);
}

/*��ȡ�ӿڿ��*/
unsigned World::getWidth()
{
	return m_portWidth;
}

/*��ȡ�ӿڸ߶�*/
unsigned World::getHeight()
{
	return m_portHeight;
}

/*��ȡ���ڴ��ڵľ��*/
HWND World::getRenderWindowHandle()
{
	return m_hRenderWindow;
}

/*��Ⱦǰ����*/
void World::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// ������ɫ&��Ȼ�����
}

/*������Ⱦ����*/
void World::RenderFinish()
{
	glutSwapBuffers();
}