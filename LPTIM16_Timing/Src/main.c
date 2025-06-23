#include "main.h"
#include "fm33fh0xx_fl.h"
#include "lptim16.h"

int main(void)
{   
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    /* SHOULD BE KEPT!!! */
    MF_Clock_Init();
    
    /* Configure the system clock */
    /* SHOULD BE KEPT!!! */
    MF_SystemClock_Config();
    
    /* Initialize FL Driver Library */
    /* SHOULD BE KEPT!!! */
    FL_Init();
    
    /* Initialize all configured peripherals */
    /* SHOULD BE KEPT!!! */
    MF_Config_Init();
    
        /* Initial the LPTIM16 Timing */
    LPTIM16_TIMER_Init();
    
      /* Start the LPTIM16 */
    LPTIM16_Start();
        
    FL_DelayMs(100);
    
    while(1)
    {     
         IWDT_Clr();    
    }
}


