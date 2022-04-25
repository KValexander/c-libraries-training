/* Include libraries */
#include <stdio.h>
#include <string.h>

/* Include libraries */
#include <raylib.h>

/* Include files */
#include "common.h"
#include "storage/character.h"


/* Create character */
Character create_character(char *name, MyTexture icon, MyTexture sprite, int count_animations, Animation animations[MAX_ANIMATIONS]) {

	/* Create character */ 
	Character character;

	/* Naming */ 
	strcpy(character.name, name);

	/* Textures */
	character.icon = icon;
	character.sprite = sprite;

	/* Animations */
	character.count_animations = count_animations;
	character.current_animation = 0;
	for(int i = 0; i < character.count_animations; i++)
		character.animations[i] = animations[i];

	/* Return character */
	return character;

}

/* Change animation */
void character_change_animation(Character *character, int change) {

	/* Checking for animation existence */ 
	if(change < 0 || change >= character->count_animations) return;

	/* Change current animation */ 
	character->current_animation = change;
	character->animations[character->current_animation].current_frame = 0;

} 

/* Character update */
void character_update(Character *character, Player *player, int time) {

	/* Change animation */
	if(player->is_change) {
		character_change_animation(character, player->state);
		player->is_change = 0;
	}

	/* Animation play */ 
	animation_play(&character->animations[character->current_animation], time);
}

/* Character draw */
void character_draw(Character *character, int x, int y) {

	/* Get display */
	Rect display = animation_display(&character->animations[character->current_animation]);

	/* Frame rendering */ 
	DrawTextureRec(
		character->sprite.texture,
		(Rectangle) { display.x, display.y, display.w, display.h },
		(Vector2) { x, y },
		WHITE
	);

}