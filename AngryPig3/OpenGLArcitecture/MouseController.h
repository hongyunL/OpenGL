#pragma once

#include <Windows.h>

/*��װ�˶����Ĳ���*/
class MouseController{
protected:
	typedef enum{
		WRAP,//��������һ�ࣨ����������λ�ó����ҽ磬�������Ƶ���紦��
		KNOCK_BACK//�ƻر߽��ڣ�����������λ�ó����ҽ磬��ֹ���������ƣ������ƻ��ҽ��ڲ���
	}MouseLimitMode;//�����������ƶ�

public:
	HWND windowHdl;

	/*����MouseController��������Ӧ��������ڵ�ǰ����*/
	MouseController();

	/*����MouseController��������Ӧ���������ָ������*/
	MouseController(HWND windowHdl);

	/*������������ƶ��ķ�Χ������ڹ���ʱָ�����Ǹ�����*/
	void limitMouseMovingDomainRL(int left, int right, MouseLimitMode mode = MouseController::WRAP);

	/*������������ƶ��ķ�Χ������ڹ���ʱָ�����Ǹ�����*/
	//void limitMouseMovingDomainTB(int top, int bottom,  Controller::MouseLimitMode mode);

	/*��ʾ���ָ��*/
	static void MouseController::Show();

	/*�������ָ��*/
	static void MouseController::Hide();
};