#pragma once

#include <Windows.h>
#include <string>

#include "Camera.h"

class World{
public:
	/*��Ҫʹ���޲ι���*/
	World();

	/*���첢��ʼ��
	*�趨�ӿڴ�С
	*�趨֡����
	*�󶨲���ʼ�������*/
	World(int argc, char* argv[], std::string title, unsigned width, unsigned height, unsigned frameTimeMs, Camera *pCamera);

	/*�������*/
	void bindCamera(Camera *pCamera);

	/*ÿ����ʾ����ʱִ�еĲ���
	*��glutDisplayFunc()�ص����Ǹ������ĺ�����Ӧ�ð���world.onDisplay()
	*ʹ��ǰ��Ҫ�������
	*��дʱӦ��ʵ�֣�
	*1.֡�߼����㣺ִ������������Ϸ�߼�
	*2.��Ⱦ�����������������Ƶ�������
	*3.�ӽǱ任������һ��Cameraʵ����apply()���������Բ��ø�ʵ�����ӽ�*/
	virtual void onDisplay();

	/*��Ļ��С�ı�ʱִ�еĲ���
	*��glutReshapeFunc()�ص����Ǹ������ĺ�����Ӧ�ð���world.onChangeSize()
	*ʹ��ǰ��Ҫ�������
	*��дʱӦ��ʵ�֣�
	*1.������Ⱦ��߱ȣ�����һ��Cameraʵ����setRatioWH(�¿�߱�)������������Ұ�Ŀ�߱�*/
	virtual void onChangeSize(unsigned newW, unsigned newH);

	/*��ȡ�ӿڿ��*/
	unsigned getWidth();

	/*��ȡ�ӿڸ߶�*/
	unsigned getHeight();

	/*��ȡ���ڴ��ڵľ��*/
	HWND getRenderWindowHandle();

protected:
	/*��Ⱦǰ����*/
	static void ClearScreen();

	/*������Ⱦ����*/
	static void RenderFinish();

	/*ָ��ǰ���õ��������ָ��*/
	Camera *m_pCurCam;

	/*�ӿڿ��*/
	unsigned m_portWidth;
	unsigned m_portHeight;

	/*֡���ȣ��Ժ����*/
	unsigned m_frameTimeMs;

	/*��Ⱦ���ڵľ��*/
	HWND m_hRenderWindow;
};