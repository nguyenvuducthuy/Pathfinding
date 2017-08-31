// Author : Lewis Ward
// Date: 29/08/2017
#include "Player.h"

Player::Player()
{
	TargetLocation = Location;
	ActorTexture = new Texture("images/player.bmp");
}

Player::~Player()
{
	// ActorTexture is deleted by ~Actor
}

//void Player::Draw(SDL_Renderer* r)
//{
//	SDL_Rect destRect;
//	destRect.w = 20;
//	destRect.h = 20;
//	destRect.x = Position.x * 20;
//	destRect.y = Position.y * 20;
//	SDL_RenderCopy(r, PlayerTexture->texture(), NULL, &destRect);
//}

void Player::Update(float dt)
{
		// movement speed
		float speed = 5.0f;

		// update player to move closer to the next waypoint
		Location.x += (TargetLocation.x - Location.x) * speed * dt;
		Location.y += (TargetLocation.y - Location.y) * speed * dt;

		if (IsAtPathEnd() || NewPath)
		{
			SetAtPathEnd(false);
			Path = Pathfinder->FindPath(GetLocation(), *MouseLocation / 20);
			NewPath = false;
		}
		
		// Move the player
		if (Path.size() > 0)
		{
			MoveTo(dt, Path);
		}
		else
		{
			SetAtPathEnd(true);
		}
}
