#include "stm_button.h"

void BT_Init(BT_Button* button, GPIO_TypeDef* GPIOx_, uint16_t pin_, uint32_t clickPeriod_)
{
	button->GPIOx = GPIOx_;
	button->pin = pin_;
	button->clickPeriod = clickPeriod_;

	button->lastPressTime = HAL_GetTick();
	button->periodCounter = 0;

	button->delta = 0;

	button->presses = 0;
}

BT_ClickResult BT_CB_EXTI(BT_Button* button, uint16_t triggerPin)
{
	// Make sure it's our pin that interrupted
	if (!(triggerPin == button->pin))
	{
		return BT_NO_CLICK;
	}

	if (button->presses >= 2)
	{
		button->presses = 0;
		return BT_DOUBLE_CLICK;
	}

	// If pressed (as opposed to released)
	if (!HAL_GPIO_ReadPin(button->GPIOx, button->pin))
	{
		button->presses++;
		button->periodCounter = 0;

		button->delta = 0;

		return BT_DOWN;
	}

	// If released (returned at press)
	if (button->delta < button->clickPeriod)
	{
		return BT_SHORT_CLICK;
	}
	else
	{
	  return BT_LONG_CLICK;
	}

	return BT_NO_CLICK;
}

int BT_CB_TIM(BT_Button* button, TIM_HandleTypeDef* htim)
{
//	uint32_t timePassed = __HAL_TIM_GET_AUTORELOAD(htim);
	uint32_t timePassed = 10;
	button->periodCounter += timePassed;
	button->delta += timePassed;

	if (button->periodCounter >= button->clickPeriod)
	{
		button->presses = 0;
		return 1;
	}

	return 0;
}
