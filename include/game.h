#ifndef __GAME_H__
#define __GAME_H__

#include "common.h"
#include "adt/linklist.h"

/* 中断时调用的函数 */
void timer_event(void);
void keyboard_event(int scan_code);

/* 按键相关 */
void press_key(int scan_code);
void release_key(int ch);
bool query_key();
int last_key_code(void);

/* 定义body_t链表 */
LINKLIST_DEF(body)
	int8_t x, y;
	int8_t direction;
	/*int text;
	float v;*/	
LINKLIST_DEF_FI(body)

LINKLIST_DEF(food)
	int8_t x, y;
	int8_t direction;
	/*int text;
	float v;*/	
LINKLIST_DEF_FI(food)

LINKLIST_DEF(key_press)
	int8_t x, y;
	int8_t direction;
	/*int text;
	float v;*/	
LINKLIST_DEF_FI(key_press)

/* 主循环 */
void main_loop(void);

/* 游戏逻辑相关 */
void create_new_food(void);
void body_get_longer(void);
void update_pos(void);
bool update_keypress(void);
void game_over(void);
body_t characters(void);

/*int get_hit(void);
int get_miss(void);*/
int get_fps(void);
void set_fps(int fps);
//fly_t characters(void);

void redraw_screen(void);

/* 随机数 */
int rand(void);
void srand(int seed);

#endif
