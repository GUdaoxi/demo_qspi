#include "lptim16.h"

void LPTIM16_Start(void)
{
    FL_LPTIM16_Enable(LPTIM16);
}


void LPTIM_IRQHandler(void)
{
    if (FL_LPTIM16_IsActiveFlag_Update(LPTIM16) != 0U)
    {
        FL_LPTIM16_ClearFlag_Update(LPTIM16);
        /* Add Your TIMER IRQ Handler HERE！*/
    }

}

void MUX20_IRQHandler(void)
{
    LPTIM_IRQHandler();
}

void LPTIM16_TIMER_Init(void)
{
    FL_LPTIM16_InitTypeDef lptim16 = {0};
    FL_NVIC_ConfigTypeDef nvic = {0};

    FL_LPTIM16_StructInit(&lptim16);

    lptim16.mode = FL_LPTIM16_OPERATION_MODE_NORMAL;
    lptim16.clockSource = FL_CMU_LPTIM16_CLK_SOURCE_APBCLK;
    lptim16.prescalerClockSource = FL_LPTIM16_CLK_SOURCE_INTERNAL;
    lptim16.prescaler = FL_LPTIM16_PSC_DIV8;
    lptim16.autoReload = 1000 - 1;
    lptim16.onePulseMode = FL_LPTIM16_ONE_PULSE_MODE_CONTINUOUS;
    (void)FL_LPTIM16_Init(LPTIM16, &lptim16);

    nvic.preemptPriority = 2;
    FL_NVIC_Init(&nvic, MUX20_IRQn);

    FL_LPTIM16_ClearFlag_Update(LPTIM16);
    FL_LPTIM16_EnableIT_Update(LPTIM16);
}

