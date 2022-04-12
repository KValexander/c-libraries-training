#include <stdio.h>
#include "main.h"

// Инициализация состояния жизни
void init_status_lives(GameState *game) {
	SDL_Color white = {255, 255, 255, 255};
	SDL_Surface *tmp = TTF_RenderText_Blended(game->font, "Game loading", white);
	game->label_w = tmp->w;
	game->label_h = tmp->h;
	game->textures.label = SDL_CreateTextureFromSurface(game->rndr, tmp);
	SDL_FreeSurface(tmp);
}

// Отрисовка состояния жизни
void draw_status_lives(GameState *game) {
	SDL_SetRenderDrawColor(game->rndr, 0, 0, 0, 255);
	SDL_RenderClear(game->rndr);

	SDL_SetRenderDrawColor(game->rndr, 255, 255, 255, 255);
	SDL_Rect text_rect = {320-game->label_w/2, 240-game->label_h/2, game->label_w, game->label_h};
	SDL_RenderCopy(game->rndr, game->textures.label, NULL, &text_rect);
}

// Отслеживание состояния жизни
void shutdown_status_lives(GameState *game) {
	SDL_DestroyTexture(game->textures.label);
	game->textures.label = NULL;
}