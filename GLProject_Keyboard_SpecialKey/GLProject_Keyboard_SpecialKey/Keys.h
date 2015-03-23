#pragma once

static const unsigned int MAX_KEYS = 256;

/** ������ */
class Keys												 
{
public:
	Keys();

	bool IsPressed(unsigned int key);   //�ж�ĳ�����Ƿ��� 
	void SetPressed(unsigned int key);  //����ĳ���������� 
	void SetReleased(unsigned int key); //����ĳ�������ͷ� 

private:
	void Clear(); //������еİ�����Ϣ 
	bool m_KeyDown[MAX_KEYS]; //����256��������״̬[ascii��]
};