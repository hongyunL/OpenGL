#pragma once

#include <Windows.h>
#include "LinearMap.h"

/* ����ƶ��� */
class MouseLimit{
protected:
	typedef enum{
		WRAP,      //��������һ�ࣨ����������λ�ó����ҽ磬�������Ƶ���紦��
		KNOCK_BACK //�ƻر߽��ڣ�����������λ�ó����ҽ磬��ֹ���������ƣ������ƻ��ҽ��ڲ���
	}MouseLimitMode;

public:
	HWND m_hWnd;

	/* ����Mouse��������Ӧ��������ڵ�ǰ���� */
	MouseLimit();
	MouseLimit(HWND m_hWnd);

	int GetCursorX();
	int GetCursorY();

	/* ������������ƶ��ķ�Χ������ڹ���ʱָ�����Ǹ����� */
	void MouseMovLimitRL(int left, int right, MouseLimitMode mode = MouseLimit::WRAP);
	/*������������ƶ��ķ�Χ������ڹ���ʱָ�����Ǹ�����*/
	//void limitMouseMovingDomainTB(int top, int bottom,  Controller::MouseLimitMode mode);

	//�Ӵ���������λ��ӳ�䵽�봰�����ĵĽǶ�rotY(����)��rotZ(����)
	void PosIntoAngleY(float left, float righat, float swingAngleL, float swingAngleR);
	void PosIntoAngleZ(float top, float bottom, float elevationT, float elevationB);

	float GetMapAngleY(int x);
	float GetMapAngleZ(int y);

	/*��ʾ���ָ��*/
	static void MouseLimit::Show();
	/*�������ָ��*/
	static void MouseLimit::Hide();

private:
	POINT pt;
	LinearMap<int> a;
	LinearMap<float> mapAngleY;
	LinearMap<float> mapAngleZ;
};