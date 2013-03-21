#include "common.h"
#include "string.h"
#include "game.h"

/* a-z对应的键盘扫描码 */
/*static int letter_code[] = {
	30, 48, 46, 32, 18, 33, 34, 35, 23, 36,
	37, 38, 50, 49, 24, 25, 16, 19, 31, 
	20, 22, 47, 17, 45, 21, 44
};*/
/* 对应键按下的标志位 */
static int letter_pressed;

void
press_key(int scan_code) {
	
		if(scan_code == 37)
			letter_pressed = 0;
		else if(scan_code == 38)
			letter_pressed = 3;
		else if(scan_code == 50)
			letter_pressed = 1;
		else if(scan_code == 48)
			letter_pressed = 2;
		else
			letter_pressed = -1;
	

	//}
}

void
release_key(int index) {
	assert(0 <= index && index < 26);
	letter_pressed = -1;
}

bool
query_key() {
	//assert(0 <= index && index < 26);
	return letter_pressed;
}

/* key_code保存了上一次键盘事件中的扫描码 */
static volatile int key_code = 0;

int last_key_code(void) {
	return key_code;
}

void
keyboard_event(int code) {
	key_code = code;
	press_key(code);
}

