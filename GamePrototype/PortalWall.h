#pragma once
#include "PortalWall.h"
enum class TeleportDirection 
{
	VerticalTeleport,
	HorizontalTeleport
};
class PortalWall
{
public:
	explicit PortalWall(Point2f leftPoint, Point2f RightPoint, TeleportDirection direction);
	void LinkPortals(Point2f leftPoint);
	void Draw() const;
	Point2f GetLeftWallPoint();
	Point2f GetRightWallPoint();
	TeleportDirection GetDirection();
	Point2f IsPlayerTouchingPortal(Point2f PlayerPosition, float PlayerSize);
private:
	Point2f m_LeftWallPoint;
	Point2f m_RightWallPoint;

	TeleportDirection m_Direction;

	Point2f m_TeleportPoint;

	TeleportDirection m_LinkedDirection;

	Point2f Teleport();
};

