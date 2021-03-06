#ifndef __GAME_H__
#define __GAME_H__

#include "common.h"
#include "adt/linklist.h"

/* 中断时调用的函数 */
void timer_event(void);
void keyboard_event(int scan_code);

/* 按键相关 */
void press_key(int scan_code);
void release_key();
int query_key();
int last_key_code(void);

/* 定义fly_t链表 */

LINKLIST_DEF(body)
	float x, y;
	int r_x, r_y;
	int ro_x, ro_y;
	int direction;
LINKLIST_DEF_FI(body)

LINKLIST_DEF(food)
	int x, y;
	int direction;
LINKLIST_DEF_FI(food)

LINKLIST_DEF(keypress)
	int x, y;
	int direction;
LINKLIST_DEF_FI(keypress)

/* 主循环 */
void main_loop(void);

/* 游戏逻辑相关 */
void create_new_food(void);
void update_pos(void);
bool update_keypress(void);
void game_over(void);

int get_hit(void);
int get_miss(void);
int get_fps(void);
void set_fps(int fps);
body_t snakebody(void);
food_t getfood(void);
keypress_t getkey(void);

void redraw_screen(void);

/* 随机数 */
int rand(void);
void srand(int seed);

#endif
