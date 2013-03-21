#include "game.h"
#include "common.h"
#include "string.h"
#include "adt/linklist.h"
#include "device/video.h"
#include "x86/x86.h"

#define VELOCITY 8

LINKLIST_IMPL(body, 10000)
LINKLIST_IMPL(food, 2)
LINKLIST_IMPL(key_press, 10000)

static body_t head = NULL;
static food_t food_head = NULL;
static key_press_t direction_head = NULL;
//static int hit = 0, miss = 0;

//int
//get_hit(void) {
//	return hit;
//}

//int
//get_miss(void) {
//	return miss;
//}

body_t
characters(void) {
	return head;
}

/* Create new food */
void
create_new_food(void) {
	food_head->x = rand() % (SCR_WIDTH / 8 - 2) * 8 + 8;
	food_head->y = rand() % (SCR_WIDTH / 8 - 2) * 8 + 8;
}

/* Make body get longer after getting the food */
void
body_get_longer(void) {
	body_t temp=NULL;
	if (head == NULL) {
		head = body_new();
		temp->x = rand() % (SCR_WIDTH / 8 - 2) * 8 + 8;
		temp->y = temp->x;	
	}
	else {
		body_t now = body_new();
		body_insert(NULL, head, now);
		temp = head;
		head = now;
	}
	head->x = food_head->x;
	head->y = food_head->y;
}
/* 逻辑时钟前进1单位 */
void
update_pos(void) {
	body_t it;
	for (it = head; it != NULL; ) {
		body_t next = it->_next;
		if(it->direction == 0)/* 根据速度更新位置 */
			it->x += VELOCITY;
		if(it->direction == 1)
			it->x -= VELOCITY;
		if(it->direction == 2)
			it->y += VELOCITY;
		if(it->direction == 3)
			it->y -= VELOCITY;
		if (it->x < 0 || it->x + 7.9 > SCR_HEIGHT) {
			//if (it->x < 0) hit ++; /* 从上部飞出屏幕 */
			//else miss ++; /* 从下部飞出屏幕 */
			//body_remove(it);
			//body_free(it);
			//if (it == head) head = next; /* 更新链表 */
			game_over();
		}
		it = next;
	}
}


void game_over(void)
{
	disable_interrupt();
	prepare_buffer(); /* 准备缓冲区 */
	draw_string("GAME OVER", 0, strlen(itoa(get_fps())) * 8, 14);
	display_buffer(); /* 绘制缓冲区 */
}
/* 更新按键 */
bool
update_keypress(void) {
	/*body_t it, target = NULL;
	float min = -100;

	disable_interrupt();
	
	for (it = head; it != NULL; it = it->_next) {
		assert(it->text >= 0 && it->text < 26);
		if (it->v > 0 && it->x > min && query_key(it->text)) {
			min = it->x;
			target = it;
		}
	}
	
	if (target != NULL) {
		release_key(target->text);
		target->v = -3;
		return TRUE;
	}
	enable_interrupt();

	return FALSE;*/

	body_t temp = NULL;
	key_press_t direction_temp = NULL;
	key_press_t now=NULL;
	int query;
	bool flag=FALSE;

	disable_interrupt();


	/*for (it = head; it != NULL; it = it->_next) {
		assert(it->text >= 0 && it->text < 26);
		if (it->v > 0 && it->x > min && query_key(it->text)) {
			min = it->x;
			target = it;
		}
	}*/
	query=query_key();
	if(head->x==food_head->x && head->y == food_head->y && query!=-1)
	{
		now->x=head->x;
		now->y=head->y;
		now->direction=query;
		key_press_insert(NULL, direction_head, now);
		food_remove(food_head);
		create_new_food();
	}

	for ( direction_temp=direction_head; direction_temp !=NULL; direction_temp=direction_temp->_next){
		flag = FALSE;
		for ( temp=head; temp !=NULL; temp=temp->_next) {
			if(temp->x==direction_temp->x && temp->y==direction_temp->y)
			{
				flag=TRUE;
				temp->direction = direction_temp->direction;
			}
		}
		if(flag == FALSE)
		{
			key_press_remove(direction_temp);
			direction_temp=direction_head;
			
		}
			

	}



	enable_interrupt();

	return FALSE;
}

