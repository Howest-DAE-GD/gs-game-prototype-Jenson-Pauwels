#pragma once
class Camera
{
public:
	Camera(float screenWidth, float screenHeight);
	void Move(Point2f playerPos);
	void Reset();
private:
	float m_ScreenWidth;
	float m_ScrenHeight;
};

