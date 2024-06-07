#pragma once
#include "BaseGame.h"
#include "Player.h"
#include <vector>
#include <SVGParser.h>
#include "Camera.h"
#include "PortalWall.h"
#include "PortalExit.h"
class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:
	Player* m_PlayerPtr;
	Camera* m_Camera;
	std::vector<std::vector<Point2f>> m_MazeWalls;
	std::vector<PortalWall> m_PortalWalls
	{
		PortalWall(Point2f{1,26}, Point2f{226,26}, TeleportDirection::VerticalTeleport),
		PortalWall(Point2f{1,2974}, Point2f{158,2974}, TeleportDirection::VerticalTeleport)
	};
	PortalExit m_MazeExit;
	SVGParser parser;
	const float LEVEL_SCALE;
	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
	void DrawMaze() const;
	void DrawPortals() const;
	void LinkPortals();
};