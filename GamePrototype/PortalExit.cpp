#include "pch.h"
#include "PortalExit.h"
#include <utils.h>

using namespace utils;

PortalExit::PortalExit(Point2f position) :
	m_Position{position},
	m_FirstSwitch{ Point2f{51,2828} },
	m_SecondSwitch{Point2f{2926,51}},
	m_ThirdSwitch{Point2f{2864,2854}},
	m_PlayerEnteredPortal{false}
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

	DrawEllipse(m_Position, 150, 150);
	m_FirstSwitch.Draw();
	m_SecondSwitch.Draw();
	m_ThirdSwitch.Draw();
}

void PortalExit::Update(Point2f PlayerPos)
{
	m_FirstSwitch.Update(PlayerPos);
	m_SecondSwitch.Update(PlayerPos);
	m_ThirdSwitch.Update(PlayerPos);

	if (PlayerPos.x > m_Position.x - 150 && PlayerPos.y > m_Position.y - 150 && PlayerPos.x < m_Position.x + 150 && PlayerPos.y < m_Position.y + 150 && m_FirstSwitch.GetIsOn() && m_SecondSwitch.GetIsOn() && m_ThirdSwitch.GetIsOn())
	{
		m_PlayerEnteredPortal = true;
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
