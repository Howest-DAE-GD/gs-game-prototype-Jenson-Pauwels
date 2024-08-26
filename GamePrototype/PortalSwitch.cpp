#include "pch.h"
#include "PortalSwitch.h"
#include <utils.h>

using namespace utils;

PortalSwitch::PortalSwitch(Point2f position, Point2f otherPosition) :
	m_Position{},
	m_IsOn{ false },
	m_HasTeleportedPlayer{false}
{
	if (rand()%2 == 0)
	{
		m_Position = position ;
	}
	else
	{
		m_Position = otherPosition;
	}
}

void PortalSwitch::Draw() const
{
	if (!m_IsOn)
	{
		SetColor(Color4f{ 1.f, 0.75f, 0.79f, 1.f });
	}
	else
	{
		SetColor(Color4f{ 0.f, 1.f, 0.f, 1.f });
	}
	DrawRect(m_Position, 50, 50);
}

void PortalSwitch::Update(Point2f playerPos)
{
	if(playerPos.x > m_Position.x && playerPos.y > m_Position.y && playerPos.x < m_Position.x +50 && playerPos.y < m_Position.y + 50 )
	{
		m_IsOn = true;
	}
}

bool PortalSwitch::GetIsOn() const
{
	return m_IsOn;
}

bool PortalSwitch::ShouldPlayerTeleport()
{
	if (m_IsOn && !m_HasTeleportedPlayer)
	{
		m_HasTeleportedPlayer = true;
		return true;
	}
	return false;
}
