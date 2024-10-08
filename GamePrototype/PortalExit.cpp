#include "pch.h"
#include "PortalExit.h"
#include <utils.h>
#include <iostream>

using namespace utils;

PortalExit::PortalExit(Point2f position) :
	m_Position{position},
	m_FirstSwitch{ Point2f{51,2828}, Point2f{353, 2835 }},
	m_SecondSwitch{Point2f{2926,51}, Point2f{2711, 2366}},
	m_ThirdSwitch{ Point2f{2864,2854}, Point2f{2841, 1701}},
	m_PlayerEnteredPortal{false},
	m_ResetTimer{180},
	m_PrinterTimer{1},
	m_GameMustReset{false}
{
}

void PortalExit::Draw() const
{
	if (m_FirstSwitch.GetIsOn() && m_SecondSwitch.GetIsOn() && m_ThirdSwitch.GetIsOn())
	{
		if (!m_PlayerEnteredPortal)
		{
			SetColor(Color4f{ 0.f,1.f,0.f,1.f });
		}
		else
		{
			SetColor(Color4f{ 0.f,0.f,1.f,1.f });
		}
	}
	else
	{
		SetColor(Color4f{ 1.f,0.f,0.f,1.f });
	}

	DrawEllipse(m_Position, 150, 150);

	if (m_FirstSwitch.GetIsOn())
	{
		SetColor(Color4f{ 0.f,1.f,0.f,1.f });
		FillEllipse(Point2f{ 1330, 900 }, 15,15);
	}
	else
	{
		SetColor(Color4f{ 1.f,0.f,0.f,1.f });
		FillEllipse(Point2f{ 1330, 900 }, 15, 15);
	}
	if (m_SecondSwitch.GetIsOn())
	{
		SetColor(Color4f{ 0.f,1.f,0.f,1.f });
		FillEllipse(Point2f{ 1370, 900 }, 15, 15);
	}
	else
	{
		SetColor(Color4f{ 1.f,0.f,0.f,1.f });
		FillEllipse(Point2f{ 1370, 900 }, 15, 15);
	}
	if (m_ThirdSwitch.GetIsOn())
	{
		SetColor(Color4f{ 0.f,1.f,0.f,1.f });
		FillEllipse(Point2f{ 1410, 900 }, 15, 15);
	}
	else
	{
		SetColor(Color4f{ 1.f,0.f,0.f,1.f });
		FillEllipse(Point2f{ 1410, 900 }, 15, 15);
	}

	
	m_FirstSwitch.Draw();
	m_SecondSwitch.Draw();
	m_ThirdSwitch.Draw();
}

void PortalExit::Update(Point2f PlayerPos, float elapsedSec)
{
	m_FirstSwitch.Update(PlayerPos);
	m_SecondSwitch.Update(PlayerPos);
	m_ThirdSwitch.Update(PlayerPos);

	if (PlayerPos.x > m_Position.x - 150 && PlayerPos.y > m_Position.y - 150 && PlayerPos.x < m_Position.x + 150 && PlayerPos.y < m_Position.y + 150 && m_FirstSwitch.GetIsOn() && m_SecondSwitch.GetIsOn() && m_ThirdSwitch.GetIsOn())
	{
		m_PlayerEnteredPortal = true;
		std::cout << "You escaped the looooping maze\n";
	}

	if ((m_FirstSwitch.GetIsOn() || m_SecondSwitch.GetIsOn() || m_ThirdSwitch.GetIsOn()) && !m_PlayerEnteredPortal)
	{
		m_ResetTimer -= elapsedSec;
		m_PrinterTimer -= elapsedSec;
		if (m_PrinterTimer <= 0)
		{
			m_PrinterTimer = 1;
			std::cout << (int)m_ResetTimer << "\n";
		}
		if (m_ResetTimer <= 0)
		{
			m_GameMustReset = true;
			m_FirstSwitch.Reset();
			m_SecondSwitch.Reset();
			m_ThirdSwitch.Reset();
			m_ResetTimer = 60.f;
			m_PrinterTimer = 1.f;
		}
	}
}

bool PortalExit::CheckIfPlayerMustTeleport()
{
	if (m_FirstSwitch.ShouldPlayerTeleport() || m_SecondSwitch.ShouldPlayerTeleport() || m_ThirdSwitch.ShouldPlayerTeleport())
	{
		return true;
	}
	return false;
}

bool PortalExit::GetGameMustReset()
{
	return m_GameMustReset;
}

void PortalExit::GameReset()
{
	m_GameMustReset = false;
}
