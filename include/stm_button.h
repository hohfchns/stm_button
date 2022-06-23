#ifndef INC_STM_BUTTON_H_
#define INC_STM_BUTTON_H_

#include "main.h"
#include "stm_mclock.h"

typedef enum BT_ClickResult {
	BT_NO_CLICK = 0,
	BT_SHORT_CLICK,
	BT_LONG_CLICK,
	BT_DOUBLE_CLICK,
	BT_DOWN,
	BT_INVALID_CLICK
} BT_ClickResult;

typedef struct BT_Button {
	GPIO_TypeDef* GPIOx;
	uint16_t pin;

	uint32_t lastPressTime;
	uint32_t clickPeriod;
	uint32_t periodCounter;

	MCL_Clock clock;

	uint32_t delta;

	uint8_t presses;
} BT_Button;


void BT_Init(BT_Button* button, GPIO_TypeDef* GPIOx_, uint16_t pin_, uint32_t clickPeriod_, uint32_t timPeriod_);

BT_ClickResult BT_CB_EXTI(BT_Button* button, uint16_t triggerPin);

int BT_CB_TIM(BT_Button* button, TIM_HandleTypeDef* htim);


#endif /* VENDOR_STM_BUTTON_INCLUDE_STM_BUTTON_H_ */
