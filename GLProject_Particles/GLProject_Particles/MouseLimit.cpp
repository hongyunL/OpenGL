#include "MouseLimit.h"

/* ����MouseLimit��������Ӧ��������ڵ�ǰ���� */
MouseLimit::MouseLimit()
{
	m_hWnd = GetForegroundWindow();

	GetCursorPos(&pt);           //��д����������Ļ���Ͻǵ�����
	ScreenToClient(m_hWnd, &pt); //ת��Ϊ��������
}

MouseLimit::MouseLimit(HWND m_hWnd)
{
	this->m_hWnd = m_hWnd;

	GetCursorPos(&pt);           //��д����������Ļ���Ͻǵ�����
	ScreenToClient(m_hWnd, &pt); //ת��Ϊ��������
}

int MouseLimit::GetCursorX()
{
	return pt.x;
}

int MouseLimit::GetCursorY()
{
	return pt.y;
}

/*glut���Լ������Ƿ��������ڣ�
* �ٸ����������ʱ��λ��Ҳ����ʵ�ֻ��� */

/* ������������ƶ��ķ�Χ������ڹ���ʱָ�����Ǹ����� */
void MouseLimit::MouseMovLimitRL(int left, int right, MouseLimitMode mode)
{
	RECT windowRect;
	GetWindowRect(m_hWnd, &windowRect); //��ȡָ�������൱����Ļ�ķ�Χ���������ң�
	int screenW = windowRect.right - windowRect.left;
	int screenH = windowRect.top - windowRect.bottom;

	const int limitLeft = left;   //����ƶ���Χ�����
	const int limitRight = right; //����ƶ���Χ���ҽ�

	//GetCursorPos(&pt);           //��д����������Ļ���Ͻǵ�����
	//ScreenToClient(m_hWnd, &pt); //ת��Ϊ��������
	
	if (pt.x <= limitLeft){
		pt.x = limitRight - 1;
		ClientToScreen(m_hWnd, &pt); //����Ϊ�������Ļ��˵�����
		SetCursorPos(pt.x, pt.y);
	}
	else if (pt.x >= limitRight){
		pt.x = limitLeft + 9;
		ClientToScreen(m_hWnd, &pt); //����Ϊ�������Ļ�Ҷ˵�����
		SetCursorPos(pt.x, pt.y);
	}
}

//�Ӵ���������λ��ӳ�䵽�봰�����ĵĽǶ�rotY(����)��rotZ(����)
void MouseLimit::PosIntoAngleY(float left, float righat, float swingAngleL, float swingAngleR)
{
	mapAngleY.SetRange(left, righat, swingAngleL, swingAngleR);
}
void MouseLimit::PosIntoAngleZ(float top, float bottom, float elevationT, float elevationB)
{
	mapAngleZ.SetRange(top, bottom, elevationT, elevationB);
}

//�õ�ӳ����
float MouseLimit::GetMapAngleY(int x)
{
	return mapAngleY.Map(x);
}
float MouseLimit::GetMapAngleZ(int y)
{
	return mapAngleZ.Map(y);
}

/* ��ʾ���ָ�� */
void MouseLimit::Show()
{
	ShowCursor(true);
}

/* �������ָ�� */
void MouseLimit::Hide()
{
	ShowCursor(false);
}