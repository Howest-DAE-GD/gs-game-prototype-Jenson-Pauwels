#include "pch.h"
#include "Game.h"
#include <utils.h>
#include <iostream>

using namespace utils;
Game::Game(const Window& window)
	:BaseGame{ window },
	m_MazeWalls{},
	m_PlayerPtr{ new Player(Point2f{35, 35})},
	m_Camera{ new Camera(GetViewPort().width, GetViewPort().height) },
	parser{},
	LEVEL_SCALE{ 4.f },
	m_MazeExit(Point2f{1380,700})
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
	delete m_PlayerPtr;
	delete m_Camera;
}

void Game::Initialize( )
{
	parser.GetVerticesFromSvgFile("SmallMaze.svg", m_MazeWalls);
	for (size_t index = 0; index < m_MazeWalls.size(); index++)
	{
		for(size_t index2=0; index2 < m_MazeWalls[index].size(); index2++)
		{
			m_MazeWalls[index][index2].x *= LEVEL_SCALE;
			m_MazeWalls[index][index2].y *= LEVEL_SCALE;
		}
	}
	LinkPortals();
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	const UINT8* pStates = SDL_GetKeyboardState(nullptr);
	m_PlayerPtr->Update(elapsedSec, m_MazeWalls, pStates);
	m_MazeExit.Update(m_PlayerPtr->GetPosition());
	std::cout << m_PlayerPtr->GetPosition().x << " " << m_PlayerPtr->GetPosition().y << "\n";

	if (m_PlayerPtr->GetTeleportCoolDown() <= 0)
	{
		for (size_t index = 0; index < m_PortalWalls.size(); index++)
		{
			if (m_PortalWalls[index].IsPlayerTouchingPortal(m_PlayerPtr->GetPosition(), m_PlayerPtr->GetPlayerSize()) != Point2f{ -1,-1 })
			{
				m_PlayerPtr->SetPosition(m_PortalWalls[index].IsPlayerTouchingPortal(m_PlayerPtr->GetPosition(), m_PlayerPtr->GetPlayerSize()));
			}
		}
	}
	if (m_MazeExit.CheckIfPlayerMustTeleport())
	{
		m_PlayerPtr->ResetPosition();
	}
}

void Game::Draw( ) const
{
	ClearBackground( );
	m_Camera->Move(m_PlayerPtr->GetPosition());
	DrawMaze();
	DrawPortals();
	m_MazeExit.Draw();
	m_PlayerPtr->Draw();
	m_Camera->Reset();
	m_PlayerPtr->DrawSprintBar();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::DrawMaze() const
{
	for (size_t index = 0; index < m_MazeWalls.size(); index++)
	{
		SetColor(Color4f{ 1,0,0,1 });
		DrawPolygon(m_MazeWalls[index]);
	}
}

void Game::DrawPortals() const
{
	for (size_t index = 0; index < m_PortalWalls.size(); index++)
	{
		m_PortalWalls[index].Draw();
	}
}

void Game::LinkPortals()
{
	m_PortalWalls[0].LinkPortals(m_PortalWalls[1].GetLeftWallPoint());
	m_PortalWalls[1].LinkPortals(m_PortalWalls[0].GetLeftWallPoint());
}
