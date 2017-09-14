#include "stdafx.h"
#include "Player.h"


Player::Player()
{
    m_epState = EP_IDLE;
	m_strName = "Garosh";
	m_hp = 100;
	m_mp = 50;
	m_atk = 15;
	m_def = 5;
}


Player::~Player()
{
}

void Player::GetDamage(int Dmg)
{
	m_hp -= (int)(Dmg * (m_def * 0.01));
	
	if (m_hp < 0)
	{
		//	Player Dead
	}
	else if (m_hp < 50)
	{
		//	Heal
	}
}

void Player::Idle()
{
}

void Player::Walk()
{
}

void Player::Run()
{
}

void Player::Attack()
{
}
