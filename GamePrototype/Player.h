#pragma once
#include<utils.h>
#include<vector>
using namespace utils;
enum class Direction
{
	none,
	up,
	left,
	down,
	right
};
class Player
{
public:
	Player(Point2f startPos);
	void Update(float elapsedsec,std::vector<std::vector<Point2f>> walls, const UINT8* pstates);
	void Draw() const;
	
	float GetPlayerSize();
	float GetTeleportCoolDown();
	Point2f GetPosition() const;
	void SetPosition(Point2f newPos);
	void ResetPosition();
	void DrawSprintBar() const;
private:
	float m_TeleportCooldown;

	float m_StandardSpeed;
	float m_DiagonalSpeed;

	float m_SprintTime;
	FLOAT m_SprintCoolDown;

	bool m_IsSprinting;

	Point2f m_Position;
	Point2f m_PlayerSpeed;
	Direction m_Direction;

	Point2f m_VerticalRayCastTopLeft;
	Point2f m_VerticalRayCastBottomLeft;
	Point2f m_VerticalRayCastTopRight;
	Point2f m_VerticalRayCastBottomRight;
	HitInfo m_VerticalHitInfo;

	Point2f m_HorizontalRayCastTopLeft;
	Point2f m_HorizontalRayCastTopRight;
	Point2f m_HorizontalRayCastBottomLeft;
	Point2f m_HorizontalRayCastBottomRight;
	HitInfo m_HorizontalHitInfo;
	const float m_OriginalPosition;

	const float PLAYER_SIZE;
	const float SPRINT_REGEN;

	// member functions
	void DoRaycast(std::vector<std::vector<Point2f>> walls);
	void DoMovement(const UINT8* pstates);
};

