#pragma once
#include "PortalSwitch.h"
class PortalExit
{
public:
	PortalExit(Point2f position);
	void Draw() const;
	void Update(Point2f PlayerPos, float elapsedSec);
	bool CheckIfPlayerMustTeleport();
	bool GetGameMustReset();
	void GameReset();
private:
	Point2f m_Position;
	PortalSwitch m_FirstSwitch;
	PortalSwitch m_SecondSwitch;
	PortalSwitch m_ThirdSwitch;
	bool m_PlayerEnteredPortal;
	float m_ResetTimer;
	float m_PrinterTimer;
	bool m_GameMustReset;
};

