#include "Player.h"
#include "SDL_image.h"

//initialises the player variables and move controls
Player::Player(SDL_Renderer* renderTarget, string filePath, int x, int y, int framesX, int framesY)
	: Assets(renderTarget, filePath, x, y, framesX, framesY)
{

	m_isActive = false;
	m_useGravity = true;

	m_canJump = true;
	isJumping = false;

	keys[0] = SDL_SCANCODE_A; //left
	keys[1] = SDL_SCANCODE_D; //right
	keys[2] = SDL_SCANCODE_SPACE; //jump

	moveSpeed = 250.0f;

}


Player::~Player()
{
}

//updates the player called every frame
void Player::update(float delta, const Uint8* keyState)
{
	m_isActive = true;

	//gravity pulls the player down
	if (m_useGravity)
	{
		positionRect.y += m_gravity;
	}

	//move left
	if (keyState[keys[0]])
	{
		positionRect.x -= moveSpeed * delta;
		//change direction of the player sprite
		m_cropRect.y = m_frameHeight;
	}
	//move right
	else if (keyState[keys[1]])
	{
		positionRect.x += moveSpeed * delta;
		//chnge direction of the player sprite
		m_cropRect.y = m_frameHeight * 2;
	}
	else
		m_isActive = false; //player is not moving
	
	//jump
	if (keyState[keys[2]])
	{
		//jump if the player is not already jumping
		if (m_canJump)
		{
			m_timer = 0.2f; //time till player falls
			isJumping = true;
			m_canJump = false;
		}
	}

	//animation
	if (m_isActive)
	{
		m_frameCounter += delta;

		if (m_frameCounter >= 0.25f)
		{
			m_frameCounter = 0;
			m_cropRect.x += m_frameWidth;
			if (m_cropRect.x >= m_textureWidth)
				m_cropRect.x = 0;
		}
	}
	else
	{
		m_frameCounter = 0;
		m_cropRect.x = m_frameWidth;
	}

	jump(delta);
}

//check if the player is colliding with a platform
bool Player::platformCollisionCheck(Platform &platform)
{

	if (positionRect.x + positionRect.w < platform.positionRect.x || positionRect.x > platform.positionRect.x + platform.positionRect.w ||
		(positionRect.y + 30) + (positionRect.h - 30) < platform.positionRect.y || (positionRect.y + 30) > platform.positionRect.y + platform.positionRect.h)
	{
		//not colliding
		SDL_SetTextureColorMod(m_texture, 255, 255, 255);
		m_useGravity = true;
		m_canJump = false;
		m_isCollidingPlatform = false;
		return false;
	}
	else //collides
	{
		m_useGravity = false;
		m_isCollidingPlatform = true;
		m_canJump = true;
		if (!platform.getPlatformFalling())
			platform.setPlatformFalling();
		return true;
	}
}

//check if the player is colliding with an enemy
bool Player::enemyCollisionCheck(Enemy &enemy)
{
	if (positionRect.x + positionRect.w < enemy.positionRect.x || positionRect.x > enemy.positionRect.x + enemy.positionRect.w ||
		(positionRect.y + 30) + (positionRect.h - 30) < enemy.positionRect.y || (positionRect.y + 30) > enemy.positionRect.y + enemy.positionRect.h)
	{
		//not colliding
		SDL_SetTextureColorMod(m_texture, 255, 255, 255);
		
		return false;
	}
	else //collides
	{
		//send the player back to the beginning
		positionRect.x = 20;
		positionRect.y = 10;
		return true;
	}
}

bool Player::coinCollision(Pickups &coin, HUD &hud)
{
	if (positionRect.x + positionRect.w < coin.positionRect.x || positionRect.x > coin.positionRect.x + coin.positionRect.w ||
		positionRect.y + positionRect.h < coin.positionRect.y || positionRect.y > coin.positionRect.y + coin.positionRect.h)
	{
		//not colliding
		SDL_SetTextureColorMod(m_texture, 255, 255, 255);

		return false;
	}
	else //collides
	{
		hud.loseHealth(1);
		return true;
	}
}

void Player::jump(float deltaTime)
{
	//if the player has pressed the jump button
	if (isJumping)
	{
		//if the timer is greater thn 0
		if (m_timer > 0)
		{
			//turn gravity off
			m_useGravity = false;
			//move player up (jumping)
			positionRect.y -= m_jumpSpeed * deltaTime;
			//decrease the timer
			m_timer -= deltaTime;
		}
		else
			isJumping = false; //dont jump
	}
	
}

int Player::GetOriginX()
{
	return positionRect.x + m_originX;
}

int Player::GetOriginY()
{
	return positionRect.y + m_originY;
}

