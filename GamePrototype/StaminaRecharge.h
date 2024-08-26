#pragma once
class StaminaRecharge
{
public:
	StaminaRecharge(Point2f Position);
	Point2f GetPosition();
	bool GetIsActive();
	void Update(float elapsedSec);
	void Draw() const;
	void WasUsed();
	float GetSize();
private:
	Point2f m_Position;
	bool m_IsActive;
	const float COOLDOWN_TIME;
	float m_Timer;
	const float SIZE;
};

