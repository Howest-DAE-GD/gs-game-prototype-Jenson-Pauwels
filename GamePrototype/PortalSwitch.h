#pragma once
class PortalSwitch
{
public:
	PortalSwitch(Point2f position, Point2f otherPosition);
	void Draw() const;
	void Update(Point2f playerPos);
	bool GetIsOn() const;
	bool ShouldPlayerTeleport();
private:
	Point2f m_Position;
	bool m_IsOn;
	bool m_HasTeleportedPlayer;
};

