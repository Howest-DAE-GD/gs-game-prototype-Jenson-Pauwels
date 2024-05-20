#include "pch.h"
#include "PortalWall.h"
#include <utils.h>
#include <vector>
using namespace utils;

PortalWall::PortalWall(Point2f leftPoint, Point2f RightPoint, TeleportDirection direction):
	m_LeftWallPoint{leftPoint},
	m_RightWallPoint{RightPoint},
	m_Direction{direction},
	m_LinkedDirection{}
{
}

void PortalWall::LinkPortals(Point2f leftPoint)
{
	m_TeleportPoint = leftPoint;
}

void PortalWall::Draw() const
{
	SetColor(Color4f{ 0,1,0,1 });
	DrawLine(m_LeftWallPoint, m_RightWallPoint);
}

Point2f PortalWall::GetLeftWallPoint()
{
	return m_LeftWallPoint;
}

Point2f PortalWall::GetRightWallPoint()
{
	return m_RightWallPoint;
}

TeleportDirection PortalWall::GetDirection()
{
	return m_Direction;
}

Point2f PortalWall::IsPlayerTouchingPortal(Point2f PlayerPosition, float PlayerSize)
{
	Point2f newPos{-1,-1};
	HitInfo hitInfo{};
	std::vector<Point2f> ImaginaryPlayer
	{ 
		PlayerPosition,
		Point2f{PlayerPosition.x + PlayerSize, PlayerPosition.y },
		Point2f{PlayerPosition.x, PlayerPosition.y + PlayerSize},
		Point2f{PlayerPosition.x + PlayerSize, PlayerPosition.y + PlayerSize }
	};
	if (Raycast(ImaginaryPlayer,m_LeftWallPoint, m_RightWallPoint, hitInfo))
	{
		newPos= Teleport();
	}
	
	
	return newPos;
}

Point2f PortalWall::Teleport()
{
	Point2f newPos{-1,-1};
	if (m_LinkedDirection == TeleportDirection::HorizontalTeleport)
	{
		newPos = m_TeleportPoint;
		return newPos;
	}
	else
	{
		newPos = m_TeleportPoint;
		return newPos;
	}
	return newPos;
}
