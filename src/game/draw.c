#include "game.h"
#include "string.h"
#include "device/video.h"

/* 绘制屏幕上的内容。
 * 注意程序在绘图之前调用了prepare_buffer，结束前调用了display_buffer。
 * prepare_buffer会准备一个空白的绘图缓冲区，display_buffer则会将缓冲区绘制到屏幕上，
 * draw_pixel或draw_string绘制的内容将保存在缓冲区内(暂时不会显示在屏幕上)，调用
 * display_buffer后才会显示。
*/
void
redraw_screen() {
	body_t it;
	food_t food_temp;
	int i=0;
	
	prepare_buffer(); /* 准备缓冲区 */

	/* 绘制每个字符 */
	for (it = snakebody(); it != NULL; it = it->_next,i++) {
		if(i==0) draw_string("@", it->r_x, it->r_y, 13);
		else draw_string("O", it->r_x, it->r_y, 15);
	}

	draw_string(itoa(i), 0, 200, 15);
	draw_string("Body length:", 0, strlen("Body length:") * 8, 15);

	food_temp = getfood();
	if(food_temp!=NULL) draw_string("*", food_temp->x, food_temp->y, 10);

	draw_string(itoa(get_fps()), 0, 0, 14);
	draw_string("FPS", 0, strlen(itoa(get_fps())) * 8, 14);

	display_buffer(); /* 绘制缓冲区 */
}

