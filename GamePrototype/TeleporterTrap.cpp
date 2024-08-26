#include "pch.h"
#include "TeleporterTrap.h"
#include <utils.h>

using namespace utils;

TeleporterTrap::TeleporterTrap(Point2f position, float portalWidth, float portalHeight):
	m_Position{position},
	m_TrapWidth{portalWidth},
	m_TrapHeight{portalHeight},
	m_TrapActiveTime{3},
	m_TrapIdleTime{5},
	m_TrapPowerUpTime{1},
	m_TrapState{TrapState::Idle},
	m_PlayerNeedsToTeleport{false},
	m_Timer{5}
{
}

void TeleporterTrap::Update(float elapsedSec, Point2f playerPos, float playerSize)
{
	m_Timer -= elapsedSec;

	if (m_Timer <= 0)
	{
		switch(m_TrapState) 
		{
		case TrapState::Active:
			m_Timer = m_TrapIdleTime;
			m_TrapState = TrapState::Idle;
			break;
		case TrapState::Idle:
			m_Timer = m_TrapPowerUpTime;
			m_TrapState = TrapState::PoweringUp;
			break;
		case TrapState::PoweringUp:
			m_Timer = m_TrapActiveTime;
			m_TrapState = TrapState::Active;
			break;
		}
	}

	if (m_TrapState == TrapState::Active && (playerPos.x + playerSize > m_Position.x && playerPos.y + playerSize > m_Position.y && playerPos.x < m_Position.x + m_TrapWidth && playerPos.y < m_Position.y + m_TrapHeight))
	{
		m_PlayerNeedsToTeleport = true;
	}
}

void TeleporterTrap::Draw() const
{
	switch (m_TrapState)
	{
	case TrapState::Active:
		SetColor(Color4f{ 1.f,0.f,0.f,1.f });
		break;
	case TrapState::Idle:
		SetColor(Color4f{ 0.f,0.f,1.f,1.f });
		break;
	case TrapState::PoweringUp:
		SetColor(Color4f{ 1.f,0.64f,0.f,1.f });
		break;
	}
	FillRect(m_Position, m_TrapWidth, m_TrapHeight);
}

bool TeleporterTrap::GetPlayerNeedsToTeleport()
{
	return m_PlayerNeedsToTeleport;
}

void TeleporterTrap::PlayerHasTeleported()
{
	m_PlayerNeedsToTeleport = false;
}
