/* Include libraries */
#include <stdio.h>
#include <math.h>

/* Include files */
#include "fighter.h"

/* Create fighter */
Fighter create_fighter(Rect draw_box, Rect attack_box, Color color, int damage, int health, int control) {

	/* Create fighter */
	Fighter fighter;

	/* Boxes */
	fighter.draw_box = draw_box;
	fighter.attack_box = attack_box;

	/* Health bar */
	fighter.health_bar = (HealthBar) {
		100, health / 100, (WIDTH / 2 - 50) / 100,
		(Rect) {
			(control) ? WIDTH / 2 + 25 : 25,
			25,
			WIDTH / 2 - 50,
			40
		}
	};

	/* Velocity */
	fighter.velocity.x = 0;
	fighter.velocity.y = 0;

	/* Color */
	fighter.color = color;

	/* Countdown */
	fighter.countdown_attack = 0;
	fighter.countdown_attacked = 0;

	/* Damage */
	fighter.damage = damage;

	/* Health */
	fighter.health = health;

	/* Control */ 
	/* 0 - first fighter | 1 - second fighter */ 
	fighter.control = control;
	
	/* Direction */ 
	/* 0 - right | 1 - left */ 
	fighter.direction = (control) ? 1 : 0;

	/* States */
	fighter.is_attacking = 0;
	fighter.is_attacked = 0;
	fighter.is_jump = 0;
	fighter.is_dead = 0;

	/* Return fighter */
	return fighter;
 
}

/* Fighter attack */
void fighter_attack(Fighter *fighter) {
	if(fighter->countdown_attack <= 0 && !fighter->is_attacking) {
		fighter->is_attacking = 1;
		fighter->countdown_attack = 10;
	}
}

/* Fighter jump */
void fighter_jump(Fighter *fighter) {
	if(!fighter->is_jump) {
		fighter->velocity.y = -10;
		fighter->is_jump = 1;
	} fighter->velocity.y -= .2f;
}

/* Fighter move right */
void fighter_move_right(Fighter *fighter) {
	fighter->direction = 0;
	fighter->velocity.x += .5f;
	if(fighter->velocity.x > 6)
		fighter->velocity.x = 6;
}

/* Fighter move left */ 
void fighter_move_left(Fighter *fighter) {
	fighter->direction = 1;
	fighter->velocity.x -= .5f;
	if(fighter->velocity.x < -6)
		fighter->velocity.x = -6;
}

/* Fighter idle */ 
void fighter_idle(Fighter *fighter) {
	fighter->velocity.x *= .8f;
	if(fabsf(fighter->velocity.x) < .1f)
		fighter->velocity.x = 0;
}

/* Fighter key down */
void fighter_key_down(Fighter *fighter) {

	/* First player */ 
	if(!fighter->control) {

		/* ATTACK */
		if(IsKeyDown(KEY_S))
			fighter_attack(fighter);

		/* JUMP */
		if(IsKeyDown(KEY_W))
			fighter_jump(fighter);

		/* MOVE RIGHT */
		if(IsKeyDown(KEY_D))
			fighter_move_right(fighter);

		/* MOVE LEFT */ 
		else if(IsKeyDown(KEY_A))
			fighter_move_left(fighter);
		
		/* IDLE */ 
		else fighter_idle(fighter);

	}

	/* Second player */
	else {

		/* ATTACK */
		if(IsKeyDown(KEY_DOWN))
			fighter_attack(fighter);

		/* JUMP */
		if(IsKeyDown(KEY_UP))
			fighter_jump(fighter);

		/* MOVE RIGHT */
		if(IsKeyDown(KEY_RIGHT))
			fighter_move_right(fighter);

		/* MOVE LEFT */ 
		else if(IsKeyDown(KEY_LEFT))
			fighter_move_left(fighter);
		
		/* IDLE */ 
		else fighter_idle(fighter);

	}

}

/* Fighter update */
void fighter_update(Fighter *fighter) {
	
	/* If the fighter is not dead */ 
	if(!fighter->is_dead) {
		
		/* Countdown attack */
		if(fighter->countdown_attack > 0)
			fighter->countdown_attack--;

		/* Attack countdown */
		if(fighter->countdown_attack <= 0 && fighter->is_attacking) {
			fighter->is_attacking = 0;
			fighter->countdown_attack = 20;
		}

		/* Countdown attacked */
		if(fighter->countdown_attacked > 0)
			fighter->countdown_attacked--;

		/* Attacked countdown */
		if(fighter->countdown_attacked <= 0 && fighter->is_attacked)
			fighter->is_attacked = 0;

		/* Fighter key down */
		fighter_key_down(fighter);

		/* Fighter move */
		fighter->draw_box.x += fighter->velocity.x;
		fighter->draw_box.y += fighter->velocity.y;

		/* Update attack_box */
		if(fighter->direction)
			fighter->attack_box.x = fighter->draw_box.x - fighter->attack_box.w;
		else fighter->attack_box.x =  fighter->draw_box.x + fighter->draw_box.w;
		fighter->attack_box.y = fighter->draw_box.y;

		/* Gravity update */
		fighter->velocity.y += GRAVITY;

	}

	/* Health bar update */
	fighter->health_bar.percents = fighter->health / fighter->health_bar.dist;

}

/* Fighter take damage */
void fighter_take_damage(Fighter *fighter, int damage) {
	fighter->is_attacked = 1;
	fighter->countdown_attacked = 30;
	fighter->health -= damage;
	if(fighter->health <= 0)
		fighter_dead(fighter);
} 

/* Fighter stop move */
void fighter_stop_move(Fighter *fighter, int x) {
	fighter->velocity.x = 0;
	fighter->draw_box.x = x;
}

/* Fighter stop falling */
void fighter_stop_falling(Fighter *fighter, int y) {
	fighter->velocity.y = 0;
	fighter->draw_box.y = y;
	fighter->is_jump = 0;
}

/* Fighter collision */
void fighter_collision(Fighter *fighter) {
	if(fighter->is_dead) return;

	/* LEFT SIDE */ 
	if(fighter->draw_box.x <= 0)
		fighter_stop_move(fighter, 0);

	/* RIGHT SIDE */
	else if(fighter->draw_box.x + fighter->draw_box.w >= WIDTH)
		fighter_stop_move(fighter, WIDTH - fighter->draw_box.w);

	/* DOWN SIDE */
	if(fighter->draw_box.y + fighter->draw_box.h >= HEIGHT)
		fighter_stop_falling(fighter, HEIGHT - fighter->draw_box.h);
}

/* Fighter dead */
void fighter_dead(Fighter *fighter) {
	fighter->is_dead = 1;
}

/* Fighter draw */
void fighter_draw(Fighter *fighter) {

	/* If the fighter is not dead */ 
	if(!fighter->is_dead) {

		/* Draw draw box */
		DrawRectangle(
			fighter->draw_box.x,
			fighter->draw_box.y,
			fighter->draw_box.w,
			fighter->draw_box.h,
			fighter->color
		);

		/* Draw attack box */
		if(fighter->is_attacking)
			DrawRectangle(
				fighter->attack_box.x,
				fighter->attack_box.y,
				fighter->attack_box.w,
				fighter->attack_box.h,
				GREEN
				// (fighter->is_attacking) ? LIGHTGRAY : GRAY
			);

	}

	/* Draw health bar */
	/* Draw background */ 
	DrawRectangle(
		fighter->health_bar.bar.x - 5,
		fighter->health_bar.bar.y - 5,
		fighter->health_bar.bar.w + 10,
		fighter->health_bar.bar.h + 10,
		LIGHTGRAY
	);
	/* Draw midground */ 
	DrawRectangle(
		fighter->health_bar.bar.x,
		fighter->health_bar.bar.y,
		fighter->health_bar.bar.w,
		fighter->health_bar.bar.h,
		WHITE
	);
	/* Draw foreground */ 
	DrawRectangle(
		fighter->health_bar.bar.x,
		fighter->health_bar.bar.y,
		fighter->health_bar.percents * fighter->health_bar.unit,
		fighter->health_bar.bar.h,
		fighter->color
	);

}