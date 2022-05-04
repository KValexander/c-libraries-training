/* Include libraries */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Include files */
#include "game.h"

/* Game init */
void game_init(Game *game) {

	/* Window initialization */
	InitWindow(WIDTH, HEIGHT, "Simple fighting");
	/* Set target FPS */
	SetTargetFPS(FPS);

	/* Randomizer initialization */
	srand(time(0));

	/* Create fighters */
	create_fighters(game);

}

/* Create fighters */
void create_fighters(Game *game) {

	/* Draw box */
	Rect draw_box = {
		25, HEIGHT - 150,
		50, 150
	};

	/* Attack box */
	Rect attack_box = {
		0, 0,
		50, 50
	};

	/* Create first fighter */
	game->fighters[0] = create_fighter(
		draw_box, attack_box,
		MAROON, 20, 100, 0
	);

	/* Create second fighter */
	draw_box.x = WIDTH - 100;
	game->fighters[1] = create_fighter(
		draw_box, attack_box,
		DARKBLUE, 20, 100, 1
	);

}


/* Game update */
void game_update(Game *game) {
	game->frame; // time

	/* Fighters update */
	for(int i = 0; i < NUM_FIGHTERS; i++)
		fighter_update(&game->fighters[i]);

}

/* Check collision */
int collide_2d(float x1, float y1, float x2, float y2, float w1, float h1, float w2, float h2) {
    return (!((x1 > (x2+w2)) || (x2 > (x1+w1)) || (y1 > (y2+h2)) || (y2 > (y1+h1))));
}

/* Game collisions */
void game_collisions(Game *game) {

	/* Fighters collision */ 
	for(int i = 0; i < NUM_FIGHTERS; i++) {
		fighter_collision(&game->fighters[i]);

		/* Attacks collision */
		if(game->fighters[i].is_attacking && !game->fighters[!i].is_attacked)
			if(collide_2d(
				game->fighters[i].draw_box.x,
				game->fighters[i].draw_box.y,
				game->fighters[!i].attack_box.x,
				game->fighters[!i].attack_box.y,
				game->fighters[i].draw_box.w,
				game->fighters[i].draw_box.h,
				game->fighters[!i].attack_box.w,
				game->fighters[!i].attack_box.h
			)) fighter_take_damage(&game->fighters[!i], game->fighters[i].damage);

	}

}


/* Game render */
void game_render(Game *game) {
	ClearBackground(BLACK); // background

	/* Fighters draw */
	for(int i = 0; i < NUM_FIGHTERS; i++) {
		fighter_draw(&game->fighters[i]);
	}

}


/* Game loop */
void game_loop(Game *game) {

	/* Game loop */ 
	while(!WindowShouldClose()) {

		/* Game update */
		game_update(game);

		/* Game collisions */
		game_collisions(game);

		/* Rendering */
		BeginDrawing(); // start draw

			game_render(game); // drawing
		
		EndDrawing(); // end draw

	}

}

/* Game deinitialization */
void game_deinit(Game *game) {

	/* Close window */
	CloseWindow();

}