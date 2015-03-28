/* 
* ȱ�پ۹�Ƶ�Ч�������� 
* ȱ�����ù�Դ�Ĺ��ղ��ʣ�����
*/
#pragma once

class Light
{
public:
	Light(void);
	/* �����Ź�Դ��λ�ã���η����ǿ�ȣ�������ǿ�ȣ����淴��ǿ�ȣ� */
	Light(unsigned short id, float positionL[], float ambientL[], float diffuseL[], float specularL[]);

	void SetLightPos(float positionL[]);

	void TurnOn();
	void TurnOff();

	static void TurnOnColorTrack(); //�������ջ������ɫ��������ɫ׷�ٿ�����ʾ��ɫ

	~Light(void);

protected:
	unsigned short m_id;

	float m_positionL[4];
	float m_ambientL[4];
	float m_diffuseL[4];
	float m_specularL[4];
};

