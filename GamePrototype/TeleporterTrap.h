#pragma once
#include <utils.h>
enum class TrapState {
	Active,
	Idle,
	PoweringUp
};

class TeleporterTrap
{
public:
	TeleporterTrap(Point2f position, float portalLength, float portalHeight);

	void Update(float elapsedSec, Point2f playerPos, float playerSize);
	void Draw() const;

	bool GetPlayerNeedsToTeleport();
	void PlayerHasTeleported();
private:
	Point2f m_Position;

	const float m_TrapWidth;
	const float m_TrapHeight;

	const float m_TrapActiveTime;
	const float m_TrapIdleTime;
	const float m_TrapPowerUpTime;

	TrapState m_TrapState;

	bool m_PlayerNeedsToTeleport;

	float m_Timer;
};

