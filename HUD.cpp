#include "HUD.h"


HUD::HUD(SDL_Renderer* renderTarget, int x, int y)
{
	font = TTF_OpenFont("Assets/DejaVuSans.ttf", 20);

	if (font == NULL)
	{
		printf("%s", TTF_GetError());
	}

	m_Score.str(string());

	m_Score << "Score: " << m_startScore;

	colour = { 144, 77, 255, 255 };
	textSurface = TTF_RenderText_Solid(font, m_Score.str().c_str(), colour);
	text = SDL_CreateTextureFromSurface(renderTarget, textSurface);
	textRect.x = x;
	textRect.y = y;

	

	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);



}


HUD::~HUD()
{
	SDL_DestroyTexture(text);
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);
	text = nullptr;
	textSurface = nullptr;
	font = nullptr;

}

void HUD::loseHealth(int updateScore)
{
	printf("loase life\n");
	m_startScore += updateScore;

	printf("Score %d", m_startScore);

	m_Score.str(string());

	m_Score << "Score: " << m_startScore;

}

void HUD::Update(SDL_Renderer* renderTarget)
{
	textSurface = TTF_RenderText_Solid(font, m_Score.str().c_str(), colour);
	text = SDL_CreateTextureFromSurface(renderTarget, textSurface);
}

void HUD::Draw(SDL_Renderer* renderTarget)
{
	SDL_RenderCopy(renderTarget, text, NULL, &textRect);
}

void HUD::GetNumHealth(int &score)
{
	score = m_startScore;
}
