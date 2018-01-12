#include <hal.h>
#include "leds.h"
#include <string.h>

static uint8_t rgb_led[4][3];

void set_led(unsigned int led_number, unsigned int value) {
	switch(led_number) {
		case 0: 
			if(value>1)  {
				palTogglePad(GPIOD, GPIOD_LED1);
			} else {
				value?palClearPad(GPIOD, GPIOD_LED1):palSetPad(GPIOD, GPIOD_LED1);
			}
			break;
		case 1:
			if(value>1) {
				palTogglePad(GPIOD, GPIOD_LED3);
			} else {
				value?palClearPad(GPIOD, GPIOD_LED3):palSetPad(GPIOD, GPIOD_LED3);
			}
			break;
		case 2:
			if(value>1) {
				palTogglePad(GPIOD, GPIOD_LED5);
			} else {
				value?palClearPad(GPIOD, GPIOD_LED5):palSetPad(GPIOD, GPIOD_LED5);
			}
			break;
		case 3:
			if(value>1) {
				palTogglePad(GPIOD, GPIOD_LED7);
			} else {
				value?palClearPad(GPIOD, GPIOD_LED7):palSetPad(GPIOD, GPIOD_LED7);
			}
			break;
		default:
			for(int i=0; i<4; i++) {
				set_led(i, value);
			}
	}
}

void set_rgb_led(unsigned int led_number, uint8_t red_val, uint8_t green_val, uint8_t blue_val) {
	rgb_led[led_number][RED] = red_val;
	rgb_led[led_number][GREEN] = green_val;
	rgb_led[led_number][BLUE] = blue_val;
}

void toggle_rgb_led(unsigned int led_number, uint8_t led, uint8_t intensity) {
	if(rgb_led[led_number][led] > 0) {
		rgb_led[led_number][led] = 0;
	} else {
		rgb_led[led_number][led] = intensity;
	}
}

/*! \brief turn on/off the body LED
 *
 * The e-puck has a green LED that illuminate his body. With this function,
 * you can change the state of this LED.
 * \param value 0 (off), 1 (on) otherwise change the state
 */
void set_body_led(unsigned int value)
{
	if(value>1)
		palTogglePad(GPIOB, GPIOB_LED_BODY);
	else
		value?palSetPad(GPIOB, GPIOB_LED_BODY):palClearPad(GPIOB, GPIOB_LED_BODY);
}

/*! \brief turn on/off the front LED
 *
 * The e-puck has a red LED in the front. With this function, you can
 * change the state of this LED.
 * \param value 0 (off), 1 (on) otherwise change the state
 */
void set_front_led(unsigned int value)
{
	if(value>1)
		palTogglePad(GPIOD, GPIOD_LED_FRONT);
	else
		value?palSetPad(GPIOD, GPIOD_LED_FRONT):palClearPad(GPIOD, GPIOD_LED_FRONT);
}

/*! \brief turn off the 8 LEDs
 *
 * The e-puck has 8 green LEDs. This function turn all off.
 * \warning this function doesn't turn off "body LED" and "front LED".
 */
void clear_leds(void)
{
	for(int i=0; i<4; i++) {
		set_led(i, 0);
	}
}

void get_all_rgb_state(uint8_t* values) {
	memcpy(values, rgb_led, 12);
}

