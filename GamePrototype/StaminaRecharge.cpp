#include "pch.h"
#include "StaminaRecharge.h"
#include <utils.h>

StaminaRecharge::StaminaRecharge(Point2f Position):
	m_Position{Position},
	m_IsActive{true},
	COOLDOWN_TIME{25.f},
	m_Timer{0.f},
	SIZE{30.f}
{
}

Point2f StaminaRecharge::GetPosition()
{
	return m_Position;
}

bool StaminaRecharge::GetIsActive()
{
	return m_IsActive;
}

void StaminaRecharge::Update(float elapsedSec)
{
	if (m_Timer > 0)
	{
		m_Timer -= elapsedSec;
	}
	else
	{
		m_IsActive = true;
	}
}

void StaminaRecharge::Draw() const
{
	utils::SetColor(Color4f{ 0.f,1.f,0.f,1.f });
	if (m_IsActive)
	{
		utils::FillRect(m_Position, SIZE, SIZE);
	}
	else
	{
		utils::DrawRect(m_Position, SIZE, SIZE);
	}
	
}

void StaminaRecharge::WasUsed()
{
	m_IsActive = false;
	m_Timer = COOLDOWN_TIME;
}

float StaminaRecharge::GetSize()
{
	return SIZE;
}
