/*���Ҫʵ����������ϵͳ��
* �ñ��̻� ���� �� ը�� ���������̣�ֻ�ܴ���������ͬ������ϵͳ���õ�һ��������λ���趨�ڶ�����ʼ��λ�ã�*/
#pragma once

#include "ParticleSys.h"
#include "Tail.h"

class Fireworks : public ParticleSys
{
public:
	Fireworks();

	void Init() override;
	void Run() override;
	void Render() override;

	
//private:
	Tail m_arrTail[MAX_PARTICLES];

};