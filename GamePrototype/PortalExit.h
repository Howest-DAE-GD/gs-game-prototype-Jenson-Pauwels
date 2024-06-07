#pragma once
#include "PortalSwitch.h"
class PortalExit
{
public:
	PortalExit(Point2f position);
	void Draw() const;
	void Update(Point2f PlayerPos);
	bool CheckIfPlayerMustTeleport();
private:
	Point2f m_Position;
	PortalSwitch m_FirstSwitch;
	PortalSwitch m_SecondSwitch;
	PortalSwitch m_ThirdSwitch;
	bool m_PlayerEnteredPortal;
};

