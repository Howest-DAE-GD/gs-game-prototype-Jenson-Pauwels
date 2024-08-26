#include "pch.h"
#include "Player.h"
#include <utils.h>

using namespace utils;

Player::Player(Point2f startPos) :
	m_Position{ startPos },
	m_PlayerSpeed{},
	m_Direction{ Direction::none },
	PLAYER_SIZE{ 25 },
	m_OriginalPosition{ startPos },
	m_TeleportCooldown{},
	m_StandardSpeed{ 120.f },
	m_DiagonalSpeed{ 80.f },
	SPRINT_REGEN{ 0.5 },
	m_SprintTime{ 10.f },
	m_IsSprinting{false},
	m_SprintCoolDown{0.f},
	m_RechargeCollectible1{Point2f{330, 1291}},
	m_RechargeCollectible2{Point2f{2459, 126}}
{
}

void Player::Update(float elapsedsec, std::vector<std::vector<Point2f>> walls, const UINT8* pstates)
{
	m_TeleportCooldown -= elapsedsec;

	DoMovement(pstates);

	m_Position.x += m_PlayerSpeed.x * elapsedsec;
	m_Position.y += m_PlayerSpeed.y * elapsedsec;

	m_RechargeCollectible1.Update(elapsedsec);
	m_RechargeCollectible2.Update(elapsedsec);

	if (m_Position.x + PLAYER_SIZE > m_RechargeCollectible1.GetPosition().x && m_Position.y + PLAYER_SIZE > m_RechargeCollectible1.GetPosition().y && m_Position.x < m_RechargeCollectible1.GetPosition().x + m_RechargeCollectible1.GetSize() && m_Position.y < m_RechargeCollectible1.GetPosition().y + m_RechargeCollectible1.GetSize() && m_RechargeCollectible1.GetIsActive())
	{
		m_SprintTime = 10;
		m_SprintCoolDown = 0;
		m_RechargeCollectible1.WasUsed();
	}

	if (m_Position.x + PLAYER_SIZE > m_RechargeCollectible2.GetPosition().x && m_Position.y + PLAYER_SIZE > m_RechargeCollectible2.GetPosition().y && m_Position.x < m_RechargeCollectible2.GetPosition().x + m_RechargeCollectible2.GetSize() && m_Position.y < m_RechargeCollectible2.GetPosition().y + m_RechargeCollectible2.GetSize() && m_RechargeCollectible2.GetIsActive())
	{
		m_SprintTime = 10;
		m_SprintCoolDown = 0;
		m_RechargeCollectible2.WasUsed();
	}

	if (m_IsSprinting && (m_PlayerSpeed.x != 0 || m_PlayerSpeed.y != 0))
	{
		m_SprintTime -= elapsedsec;
	}
	else if (m_SprintTime < 10)
	{
		m_SprintTime += SPRINT_REGEN * elapsedsec;
		m_SprintCoolDown -= elapsedsec;
	}

	DoRaycast(walls);
}

void Player::Draw() const
{
	SetColor(Color4f{ 1.f, 1.f, 1.f,1.f });
	DrawRect(m_Position, PLAYER_SIZE, PLAYER_SIZE);

	m_RechargeCollectible1.Draw();
	m_RechargeCollectible2.Draw();

	SetColor(Color4f{ 1.f, 0.f, 0.f,1.f });
	/*DrawLine(m_VerticalRayCastTopLeft, m_VerticalRayCastBottomLeft);
	DrawLine(m_VerticalRayCastTopRight, m_VerticalRayCastBottomRight);
	DrawLine(m_HorizontalRayCastTopLeft, m_HorizontalRayCastTopRight);
	DrawLine(m_HorizontalRayCastBottomLeft, m_HorizontalRayCastBottomRight);*/
}

void Player::DoMovement(const UINT8* pstates)
{
	if (pstates[SDL_SCANCODE_LEFT] && pstates[SDL_SCANCODE_RIGHT] && pstates[SDL_SCANCODE_UP] && pstates[SDL_SCANCODE_DOWN])
	{
		m_PlayerSpeed.x = 0.f;
		m_PlayerSpeed.y = 0.f;
	}
	else if (pstates[SDL_SCANCODE_LEFT] && pstates[SDL_SCANCODE_UP] && pstates[SDL_SCANCODE_DOWN])
	{
		m_PlayerSpeed.x = 0.f;
		m_PlayerSpeed.y = 0.f;
	}
	else if (pstates[SDL_SCANCODE_LEFT] && pstates[SDL_SCANCODE_DOWN] && pstates[SDL_SCANCODE_RIGHT])
	{
		m_PlayerSpeed.x = 0.f;
		m_PlayerSpeed.y = 0.f;
	}
	else if (pstates[SDL_SCANCODE_LEFT] && pstates[SDL_SCANCODE_UP] && pstates[SDL_SCANCODE_RIGHT])
	{
		m_PlayerSpeed.x = 0.f;
		m_PlayerSpeed.y = 0.f;
	}
	else if (pstates[SDL_SCANCODE_RIGHT] && pstates[SDL_SCANCODE_UP] && pstates[SDL_SCANCODE_DOWN])
	{
		m_PlayerSpeed.x = 0.f;
		m_PlayerSpeed.y = 0.f;
	}
	else if (pstates[SDL_SCANCODE_UP] && pstates[SDL_SCANCODE_DOWN])
	{
		m_PlayerSpeed.x = 0.f;
		m_PlayerSpeed.y = 0.f;
	}
	else if (pstates[SDL_SCANCODE_LEFT] && pstates[SDL_SCANCODE_UP])
	{
		m_PlayerSpeed.x = -m_DiagonalSpeed;
		m_PlayerSpeed.y = m_DiagonalSpeed;
	}
	else if (pstates[SDL_SCANCODE_LEFT] && pstates[SDL_SCANCODE_DOWN])
	{
		m_PlayerSpeed.x = -m_DiagonalSpeed;
		m_PlayerSpeed.y = -m_DiagonalSpeed;
	}
	else if (pstates[SDL_SCANCODE_RIGHT] && pstates[SDL_SCANCODE_UP])
	{
		m_PlayerSpeed.x = m_DiagonalSpeed;
		m_PlayerSpeed.y = m_DiagonalSpeed;
	}
	else if (pstates[SDL_SCANCODE_RIGHT] && pstates[SDL_SCANCODE_DOWN])
	{
		m_PlayerSpeed.x = m_DiagonalSpeed;
		m_PlayerSpeed.y = -m_DiagonalSpeed;
	}
	else if (pstates[SDL_SCANCODE_LEFT])
	{
		m_PlayerSpeed.x = -m_StandardSpeed;
		m_PlayerSpeed.y = 0.f;
		m_Direction = Direction::left;
	}
	else if (pstates[SDL_SCANCODE_RIGHT]) 
	{
		m_PlayerSpeed.x = m_StandardSpeed;
		m_PlayerSpeed.y = 0.f;
		m_Direction = Direction::right;
	}
	else if (pstates[SDL_SCANCODE_UP]) 
	{
		m_PlayerSpeed.x = 0.f;
		m_PlayerSpeed.y = m_StandardSpeed;
		m_Direction = Direction::up;
	}
	else if (pstates[SDL_SCANCODE_DOWN])
	{
		 m_PlayerSpeed.x = 0.f;
		 m_PlayerSpeed.y = -m_StandardSpeed;
		 m_Direction = Direction::down;
	}
	else
	{
		m_PlayerSpeed.x = 0.f;
		m_PlayerSpeed.y = 0.f;
		m_Direction = Direction::none;
	}

	if (pstates[SDL_SCANCODE_LSHIFT] && m_SprintTime >=0 && m_SprintCoolDown <= 0)
	{
		m_StandardSpeed = 240.f;
		m_DiagonalSpeed = 160.f;
		m_IsSprinting = true;
	}
	else
	{
		if (m_SprintTime <= 0)
		{
			m_SprintCoolDown = 3.f;
		}
		m_StandardSpeed = 120.f;
		m_DiagonalSpeed = 80.f;
		m_IsSprinting = false;
	}
}

void Player::DrawSprintBar() const
{
	SetColor(Color4f{ 1.f,0.f,0.f,1.f });
	DrawRect(30.f, 40.f, 150.f, 30.f);
	if (m_SprintCoolDown > 0)
	{
		SetColor(Color4f{ 0.f, 0.f, 0.f, 1.f });
	}
	else
	{
		SetColor(Color4f{ 1.f, 0.f, 0.f,1.f });
	}
	FillRect(30.f, 41.f, 150.f * m_SprintTime / 10, 29.f);
}

float Player::GetPlayerSize()
{
	return PLAYER_SIZE;
}

float Player::GetTeleportCoolDown()
{
	return m_TeleportCooldown;
}

Point2f Player::GetPosition() const
{
	return m_Position;
}

void Player::SetPosition(Point2f newPos)
{
	m_Position = newPos;
	m_TeleportCooldown = 3.f;
}

void Player::ResetPosition(bool fullReset)
{
	m_Position.x = m_OriginalPosition.x;
	m_Position.y = m_OriginalPosition.y;
	if (fullReset)
	{
		m_SprintTime = 10.f;
	}
}

void Player::DoRaycast(std::vector<std::vector<Point2f>> walls)
{
	m_VerticalRayCastTopLeft.x = m_Position.x;
	m_VerticalRayCastTopLeft.y = m_Position.y + PLAYER_SIZE + 1;
	m_VerticalRayCastBottomLeft.x = m_Position.x;
	m_VerticalRayCastBottomLeft.y = m_Position.y - 1;

	m_VerticalRayCastTopRight.x = m_Position.x + PLAYER_SIZE;
	m_VerticalRayCastTopRight.y = m_Position.y + PLAYER_SIZE + 1;
	m_VerticalRayCastBottomRight.x = m_Position.x + PLAYER_SIZE;
	m_VerticalRayCastBottomRight.y = m_Position.y - 1;

	m_HorizontalRayCastTopLeft.x = m_Position.x - 1;
	m_HorizontalRayCastTopLeft.y = m_Position.y + PLAYER_SIZE;
	m_HorizontalRayCastTopRight.x = m_Position.x + PLAYER_SIZE + 1;
	m_HorizontalRayCastTopRight.y = m_Position.y + PLAYER_SIZE;

	m_HorizontalRayCastBottomLeft.x = m_Position.x - 1;
	m_HorizontalRayCastBottomLeft.y = m_Position.y;
	m_HorizontalRayCastBottomRight.x = m_Position.x + PLAYER_SIZE + 1;
	m_HorizontalRayCastBottomRight.y = m_Position.y;
	
	for (size_t index = 0; index < walls.size(); index++)
	{
		if (Raycast(walls[index], m_VerticalRayCastTopLeft, m_VerticalRayCastBottomLeft, m_VerticalHitInfo) || Raycast(walls[index], m_VerticalRayCastTopRight, m_VerticalRayCastBottomRight, m_VerticalHitInfo))
		{
			
			if (m_PlayerSpeed.y > 0)
			{
				m_Position.y = m_VerticalHitInfo.intersectPoint.y - PLAYER_SIZE - 1;
			}
			else
			{
				m_Position.y = m_VerticalHitInfo.intersectPoint.y + 1;
			}
			m_PlayerSpeed.y = 0;
		}
		if (Raycast(walls[index], m_HorizontalRayCastTopLeft, m_HorizontalRayCastTopRight, m_HorizontalHitInfo) || Raycast(walls[index], m_HorizontalRayCastBottomLeft, m_HorizontalRayCastBottomRight, m_HorizontalHitInfo))
		{
			
			if (m_PlayerSpeed.x < 0)
			{
				m_Position.x = m_HorizontalHitInfo.intersectPoint.x + 1;
			}
			else
			{
				m_Position.x = m_HorizontalHitInfo.intersectPoint.x - PLAYER_SIZE - 1;
			}
			m_PlayerSpeed.x = 0;
		}
	}
	
}
