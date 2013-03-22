#include "game.h"
#include "common.h"
#include "string.h"
#include "adt/linklist.h"
#include "device/video.h"
#include "x86/x86.h"
#define VELOCITY 8

LINKLIST_IMPL(body, 10000)
LINKLIST_IMPL(food, 10000)
LINKLIST_IMPL(keypress, 100)

static body_t head = NULL;
static food_t food_head = NULL;
static keypress_t keypress_head = NULL;


body_t
snakebody(void) {
	return head;
}

food_t
getfood(void) {
	return food_head;
}

keypress_t
getkey(void) {
	return keypress_head;
}

/* 在屏幕上创建一个新的字母 */


void
create_new_food(void) {
	food_t it;
	it=food_new();
	it->x = rand() % SCR_HEIGHT;
	it->y = rand() % SCR_WIDTH;
	it->x = it->x - it->x % 8;
	it->y = it->y - it->y % 8;
	it->direction=0;
	food_head=it;
}

/* Make body get longer after getting the food */
void
body_get_longer(void) {
	if (head == NULL) {
		head = body_new();
		head->x = (SCR_HEIGHT / 16 ) * 8;
		head->y = (SCR_WIDTH / 16 ) * 8;
	}
	else {
		body_t now = body_new();
		if(head->direction == 0)
		{
			now->x=head->x;now->r_x=head->r_x;
			now->y=head->y-8;now->r_y=head->r_y-8;
		}
		else if(head->direction == 1)
		{
			now->x=head->x;now->r_x=head->r_x;
			now->y=head->y+8;now->r_y=head->r_y+8;
		}
		else if(head->direction == 2)
		{
			now->x=head->x-8;now->r_x=head->r_x-8;
			now->y=head->y;now->r_y=head->r_y;
		}
		else if(head->direction == 3)
		{
			now->x=head->x+8;now->r_x=head->r_x+8;
			now->y=head->y;now->r_y=head->r_y;
		}
		now->direction = head->direction;
		body_insert(NULL, head, now);
		head = now;
	}
	release_key();
	
}

/* 逻辑时钟前进1单位 */
void
update_pos(void) {
	body_t it = head;
	if (head == NULL) body_get_longer();
	if (food_head == NULL) create_new_food();
	if(head->r_x==food_head->x && head->r_y == food_head->y )
	{
		body_get_longer();
		food_free(food_head);
		food_head = NULL;
		
	}

	for (it = head; it->_next != NULL; it = it->_next);
	for (; it != head; it = it->_prev)
	{
		it->r_x = it->_prev->r_x;
		it->r_y = it->_prev->r_y; 
	}

	if(head->direction == 0 )
			{head->y -= VELOCITY;head->r_x=(int)head->x-(int)head->x%8;head->r_y=(int)head->y-(int)head->y%8;}
	if(head->direction == 1 )
			{head->y += VELOCITY;head->r_x=(int)head->x-(int)head->x%8;head->r_y=(int)head->y-(int)head->y%8;}
	if(head->direction == 2 )
			{head->x -= VELOCITY;head->r_x=(int)head->x-(int)head->x%8;head->r_y=(int)head->y-(int)head->y%8;}
	if(head->direction == 3 )
			{head->x += VELOCITY;head->r_x=(int)head->x-(int)head->x%8;head->r_y=(int)head->y-(int)head->y%8;}


	for (it = head; it != NULL; it = it->_next) {
		if (it->r_x < 0 || it->r_x + 7.9 > SCR_HEIGHT || it->r_y < 0 || it->r_y + 7.9 > SCR_WIDTH ) {
			game_over();
		}		
	}


	release_key();
}


void game_over(void)
{
	release_key();
	disable_interrupt();
	prepare_buffer();
	draw_string("GAME OVER", 0, strlen(itoa(get_fps())) * 8, 14);
	display_buffer();
}


/* 更新按键 */
bool
update_keypress(void) {
	keypress_t now=NULL;
	int query;

	disable_interrupt();
	query=query_key();
	if(query!=-1)
	{
		if(keypress_head==NULL){
			keypress_head=keypress_new();
			keypress_head->x=head->r_x;
			keypress_head->y=head->r_y;
			keypress_head->direction=query;
		}
		else {
			now = keypress_new();
			now->x=head->r_x;
			now->y=head->r_y;
			now->direction=query;
			keypress_insert(NULL, keypress_head, now);
			keypress_head=now;
		}
		head->direction = query;

	}
	release_key();

	enable_interrupt();
	return FALSE;
}

