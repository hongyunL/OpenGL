#include "MouseController.h"

/*����MouseController��������Ӧ��������ڵ�ǰ����*/
MouseController::MouseController(){
	windowHdl = GetForegroundWindow();
}

/*����MouseController��������Ӧ���������ָ������*/
MouseController::MouseController(HWND windowHdl){
	this->windowHdl = windowHdl;
}

/*������������ƶ��ķ�Χ������ڹ���ʱָ�����Ǹ�����*/
void MouseController::limitMouseMovingDomainRL(int left, int right, MouseLimitMode mode){
	RECT windowRect;
	GetWindowRect(windowHdl, &windowRect);//��ȡָ�������൱����Ļ�ķ�Χ���������ң�

	int screenW = windowRect.right - windowRect.left;
	int screenH = windowRect.top - windowRect.bottom;

	const int limitLeft = left;//����ƶ���Χ�����
	const int limitRight = right;//����ƶ���Χ���ҽ�
	/*	  limitLeft	    		limitRight
	��					   ��
	|					                    |
	|					                    |
	<-edge->|<-------���з�Χ------>|<-edge->
	|					                    |
	|					                    |
	|					                    |
	<----------------��������--------------->
	*/
	POINT pt;

	GetCursorPos(&pt);//��д����������Ļ���Ͻǵ�����
	ScreenToClient(windowHdl, &pt);//ת��Ϊ��������

	if(pt.x <= limitLeft){
		pt.x = limitRight-1;
		ClientToScreen(windowHdl, &pt);//��pt������Ӵ�������ת��Ϊ�������Ļ������
		SetCursorPos(pt.x, pt.y);
	}else if(pt.x >= limitRight){
		pt.x = limitLeft+9;
		ClientToScreen(windowHdl, &pt);//��pt������Ӵ�������ת��Ϊ�������Ļ������
		SetCursorPos(pt.x, pt.y);
	}
}

/*��ʾ���ָ��*/
void MouseController::Show(){
	ShowCursor(true);
}

/*�������ָ��*/
void MouseController::Hide(){
	ShowCursor(false);
}