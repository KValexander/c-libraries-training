#include <stdio.h>
#include "main.h"

// GAMEOVER
void init_game_over(GameState *game) {
	char str[128] = "";
	SDL_Color white = {255, 255, 255, 255};
	SDL_Surface *surface = TTF_RenderText_Blended(game->font, "Game over", white);
	game->label_w2 = surface->w;
	game->label_h2 = surface->h;
	game->textures.label2 = SDL_CreateTextureFromSurface(game->rndr, surface);
	SDL_FreeSurface(surface);
}

// Инициализация состояния жизни
void init_status_lives(GameState *game) {
	char str[128] = "";
	sprintf(str, "x %d", (int)game->player.lives);

	SDL_Color white = {255, 255, 255, 255};
	SDL_Surface *surface = TTF_RenderText_Blended(game->font, str, white);
	game->label_w = surface->w;
	game->label_h = surface->h;
	game->textures.label = SDL_CreateTextureFromSurface(game->rndr, surface);
	SDL_FreeSurface(surface);
}

// Отрисовка состояния жизни
void draw_status_lives(GameState *game) {
	// Задний фон
	SDL_SetRenderDrawColor(game->rndr, 0, 0, 0, 255);
	SDL_RenderClear(game->rndr);
    
    // Персонаж
    SDL_Rect player_rect = {320 - game->player.w - 20, 240-game->player.h/2, game->player.w, game->player.h};
    SDL_RenderCopy(game->rndr, game->textures.player_frames[0], NULL, &player_rect); // отрисовка текстуры

    // Текст
	SDL_SetRenderDrawColor(game->rndr, 255, 255, 255, 255);
	SDL_Rect text_rect = {320, 240-game->label_h/2, game->label_w, game->label_h};
	SDL_RenderCopy(game->rndr, game->textures.label, NULL, &text_rect);
}

// Отрисовка экрана окончания игры
void draw_game_over(GameState *game) {
	// Задний фон
	SDL_SetRenderDrawColor(game->rndr, 0, 0, 0, 255);
	SDL_RenderClear(game->rndr);

	// Текст
	SDL_SetRenderDrawColor(game->rndr, 255, 255, 255, 255);
	SDL_Rect text_rect = {320-game->label_w2/2, 240-game->label_h2/2, game->label_w2, game->label_h2};
	SDL_RenderCopy(game->rndr, game->textures.label2, NULL, &text_rect);
}

// Сокрытие состояния жизни
void shutdown_status_lives(GameState *game) {
	SDL_DestroyTexture(game->textures.label);
	SDL_DestroyTexture(game->textures.label2);
	game->textures.label = NULL;
	game->textures.label2 = NULL;
}