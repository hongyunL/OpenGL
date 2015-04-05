#pragma once

/*����
*�̶����ܹ��߽׶�������ʹ��8��*/
class Light
{
public:
	Light(void);

	/*������ţ�������ڣ�����0-7֮��*/
	Light(unsigned short id);

	/*�������Դ*/
	void turnOn();

	/*�ر������Դ*/
	void turnOff();

	/*�趨������*/
	void setAmbient(float *src);

	/*�趨ɢ���*/
	void setDiffuse(float *src);

	/*�򿪹��ա�ʹ�ù���ǰ�ȵ���
	*���������ա���ɫ׷��*/
	static void Enable();

	~Light(void);

protected:
	unsigned short m_id;

	float m_ambient[4];
	float m_diffuse[4];
};

