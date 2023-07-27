/*
 * File:   application.c
 * Author: C16783
 *
 * Created on August 26, 2020, 9:24 AM
 */

#include <xc.h>
#include "application.h"
//#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/system/system.h"

void IntroSplashMessage(void) {
    printf("PIC18F16Q40 Curiosity Nano Demo \r\n");
    printf("Please refer to included readme.md for more information \r\n");
    printf("-------------------------------------------------------- \r\n");
}

void TempIndicator_Init(void) {
    gain = (FLASH_Read(DIA_TSHR1 + 1) << 8) + FLASH_Read(DIA_TSHR1);
    offset = (FLASH_Read(DIA_TSHR3 + 1) << 8) + FLASH_Read(DIA_TSHR3);
}

void TempIndicator_Calc(void) {
    adcc_meas = ADCC_GetConversionResult();
    tempC = (int24_t) adcc_meas * gain;
    tempC = tempC / 256;
    tempC = tempC + offset;
    tempC = tempC / 10;
    printf("Temp Sensor Result %d \r\n", tempC);
}