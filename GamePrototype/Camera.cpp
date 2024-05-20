#include "pch.h"
#include "Camera.h"

Camera::Camera(float screenWidth, float screenHeight):
	m_ScreenWidth{screenWidth},
	m_ScrenHeight{screenHeight}
{
}

void Camera::Move(Point2f playerPos)
{
	glPushMatrix();
	if (playerPos.x - m_ScreenWidth / 2 > 0)
	{
		glTranslatef(-playerPos.x + m_ScreenWidth / 2, 0, 0);
	}
	if (playerPos.y - m_ScrenHeight/2 > 0)
	{
		glTranslatef(0, -playerPos.y + m_ScrenHeight / 2, 0);
	}
}

void Camera::Reset()
{
	glPopMatrix();
}
