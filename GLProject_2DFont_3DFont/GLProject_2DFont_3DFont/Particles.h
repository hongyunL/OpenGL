#pragma once

class Particles
{
public:
	Particles();
	Particles(
		float size, 
		float life,
		float r, float g, float b, 
		float x, float y, float z, 
		float speedX, float speedY, float speedZ, 
		float accelX, float accelY, float accelZ);

	void SetSize(float size);
	void SetLife(float life);
	void SetFade(float fade);
	void SetActive(bool active);

	void SetColor(float r, float g, float b);
	void SetPos(float x, float y, float z);
	void SetSpeed(float speedX, float speedY, float speedZ);
	void SetAccel(float accelX, float accelY, float accelZ);

	float GetSize();
	float GetLife();
	float GetFade();
	bool GetActive();

	void GetColor(float &r, float &g, float &b);
	void GetPos(float &x, float &y, float &z);
	void GetSpeed(float &speedX, float &speedY, float &speedZ);
	void GetAccel(float &accelX, float &accelY, float &accelZ);

	//~Particles();

private:
	//Particles(const Particles& other){}				 //˽�еĿ������캯��
	//Particles& operator=(const Particles& other){} //˽�еĸ�ֵ����

	float m_size; //������ģ�����ӣ�size�ǰ뾶��

	bool  m_active; //�Ƿ񼤻�
	float m_life;   //����ֵ����������ʱ���alphֵ
	float m_fade;   //˥���ٶ�

	float m_r, m_g, m_b;
	float m_posX, m_posY, m_posZ;
	float m_speedX, m_speedY, m_speedZ;
	float m_accelX, m_accelY, m_accelZ;
};


/*Set()��Get()Ӧ���������Ҷ�����ͷ�ļ���
*��inline ���������ڵ��øú�����ÿ���ı��ļ��ж��塱*/

inline void Particles::SetSize(float size)
{
	m_size = size;
}
inline void Particles::SetLife(float life)
{
	m_life = life;
}
inline void Particles::SetFade(float fade)
{
	m_fade = fade;
}
inline void Particles::SetActive(bool active)
{
	m_active = active;
}

//inline
inline void Particles::SetColor(float r, float g, float b)
{
	m_r = r;
	m_g = g;
	m_b = b;
}
inline void Particles::SetPos(float x, float y, float z)
{
	m_posX = x;
	m_posY = y;
	m_posZ = z;
}
inline void Particles::SetSpeed(float speedX, float speedY, float speedZ)
{
	m_speedX = speedX;
	m_speedY = speedY;
	m_speedZ = speedZ;
}
inline void Particles::SetAccel(float accelX, float accelY, float accelZ)
{
	m_accelX = accelX;
	m_accelY = accelY;
	m_accelZ = accelZ;
}


inline float Particles::GetSize()
{
	return m_size;
}
inline float Particles::GetLife()
{
	return m_life;
}
inline float Particles::GetFade()
{
	return m_fade;
}
inline bool Particles::GetActive()
{
	return m_active;
}

inline void Particles::GetColor(float &r, float &g, float &b)
{
	r = m_r;
	g = m_g;
	b = m_b;
}
inline void Particles::GetPos(float &x, float &y, float &z)
{
	x = m_posX;
	y = m_posY;
	z = m_posZ;
}
inline void Particles::GetSpeed(float &speedX, float &speedY, float &speedZ)
{
	speedX = m_speedX;
	speedY = m_speedY;
	speedZ = m_speedZ;
}
inline void Particles::GetAccel(float &accelX, float &accelY, float &accelZ)
{
	accelX = m_accelX;
	accelY = m_accelY;
	accelZ = m_accelZ;
}