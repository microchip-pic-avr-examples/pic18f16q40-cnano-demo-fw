/**
  PWM1_16BIT Generated Driver File
 
  @Company
    Microchip Technology Inc.
 
  @File Name
    pwm1_16bit.c
 
  @Summary
    This is the generated driver implementation file for the PWM1_16BIT driver
 
  @Description
    This source file provides APIs for driver for PWM1_16BIT.
    Generation Information :
        Driver Version    :  <!--Use existing driver version-->
    The generated drivers are tested against the following:
        Compiler          :  XC8 v2.20
        MPLAB             :  MPLABX 5.30
*/

/*
Copyright (c) [2012-2020] Microchip Technology Inc.  

    All rights reserved.

    You are permitted to use the accompanying software and its derivatives 
    with Microchip products. See the Microchip license agreement accompanying 
    this software, if any, for additional info regarding your rights and 
    obligations.
    
    MICROCHIP SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT 
    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
    LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT 
    AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP OR ITS
    LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT 
    LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE 
    THEORY FOR ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT 
    LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
    OR OTHER SIMILAR COSTS. 
    
    To the fullest extend allowed by law, Microchip and its licensors 
    liability will not exceed the amount of fees, if any, that you paid 
    directly to Microchip to use this software. 
    
    THIRD PARTY SOFTWARE:  Notwithstanding anything to the contrary, any 
    third party software accompanying this software is subject to the terms 
    and conditions of the third party's license agreement.  To the extent 
    required by third party licenses covering such third party software, 
    the terms of such license will apply in lieu of the terms provided in 
    this notice or applicable license.  To the extent the terms of such 
    third party licenses prohibit any of the restrictions described here, 
    such restrictions will not apply to such third party software.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "../pwm1_16bit.h"

//Pointers to PWM1_16BIT interrupt handlers
//User can use them in application code to initialize with custom ISRs
static void (*PWM1_16BIT_Slice1Output1_InterruptHandler)(void);   //SaP1IF and hence PWMxIF is set
static void (*PWM1_16BIT_Slice1Output2_InterruptHandler)(void);   //SaP2IF and hence PWMxIF is set
static void (*PWM1_16BIT_Period_InterruptHandler)(void);          //PWMxPIF is set
static void PWM1_16BIT_Slice1Output1_DefaultInterruptHandler(void);
static void PWM1_16BIT_Slice1Output2_DefaultInterruptHandler(void);
static void PWM1_16BIT_Period_DefaultInterruptHandler(void);

void PWM1_16BIT_Initialize(void)
{
     PWM1ERS = 0x0;

     PWM1CLK = 0x2;

     PWM1LDS = 0x0;

     PWM1PRL = 0x0;

     PWM1PRH = 0x0;

     PWM1CPRE = 0x0;

     PWM1PIPOS = 0x0;

     PWM1GIR = 0x0;

     PWM1GIE = 0x0;

     PWM1S1CFG = 0x80;

     PWM1S1P1L = 0x0;

     PWM1S1P1H = 0x0;

     PWM1S1P2L = 0x0;

     PWM1S1P2H = 0x0;
    
    //Clear PWM1_16BIT period interrupt flag
    PIR4bits.PWM1PIF = 0;
    
    //Clear PWM1_16BIT interrupt flag
    PIR4bits.PWM1IF = 0;
    
    //Clear PWM1_16BIT slice 1, output 1 interrupt flag
    PWM1GIRbits.S1P1IF = 0;
    
    //Clear PWM1_16BIT slice 1, output 2 interrupt flag
    PWM1GIRbits.S1P2IF = 0;
    
    //PWM1_16BIT interrupt enable bit
    PIE4bits.PWM1IE = 0;
    
    //PWM1_16BIT period interrupt enable bit
    PIE4bits.PWM1PIE = 0;
    
    //Set default interrupt handlers
    PWM1_16BIT_Slice1Output1_SetInterruptHandler(PWM1_16BIT_Slice1Output1_DefaultInterruptHandler);
    PWM1_16BIT_Slice1Output2_SetInterruptHandler(PWM1_16BIT_Slice1Output2_DefaultInterruptHandler);
    PWM1_16BIT_Period_SetInterruptHandler(PWM1_16BIT_Period_DefaultInterruptHandler);

     PWM1CON = 0x80;
}

void PWM1_16BIT_Enable()
{
    PWM1CON |= _PWM1CON_EN_MASK;
}

void PWM1_16BIT_Disable()
{
    PWM1CON &= (~_PWM1CON_EN_MASK);
}

void PWM1_16BIT_WritePeriodRegister(uint16_t periodCount)
{
    PWM1PRL = (uint8_t)periodCount;
    PWM1PRH= (uint8_t)(periodCount >> 8);
}

void PWM1_16BIT_SetSlice1Output1DutyCycleRegister(uint16_t registerValue)
{    
    PWM1S1P1L = (uint8_t)(registerValue);
    PWM1S1P1H = (uint8_t)(registerValue >> 8);
}

void PWM1_16BIT_SetSlice1Output2DutyCycleRegister(uint16_t registerValue)
{        
    PWM1S1P2L = (uint8_t)(registerValue);
    PWM1S1P2H = (uint8_t)(registerValue >> 8);
}

void PWM1_16BIT_LoadBufferRegisters(void)
{
    //Load the period and duty cycle registers on the next period event
    PWM1CONbits.LD = 1;
}

void PWM1_16BIT_PWMI_ISR(void)
{
    PIR4bits.PWM1IF = 0;
    if((PWM1GIEbits.S1P1IE == 1) && (PWM1GIRbits.S1P1IF == 1))
    {
        PWM1GIRbits.S1P1IF = 0;
        if(PWM1_16BIT_Slice1Output1_InterruptHandler != NULL)
            PWM1_16BIT_Slice1Output1_InterruptHandler();
    }
    else if((PWM1GIEbits.S1P2IE == 1) && (PWM1GIRbits.S1P2IF == 1))
    {
        PWM1GIRbits.S1P2IF = 0;
        if(PWM1_16BIT_Slice1Output2_InterruptHandler != NULL)
            PWM1_16BIT_Slice1Output2_InterruptHandler();
    }
}

void PWM1_16BIT_PWMPI_ISR(void)
{
    PIR4bits.PWM1PIF = 0;
    if(PWM1_16BIT_Period_InterruptHandler != NULL)
        PWM1_16BIT_Period_InterruptHandler();
}

void PWM1_16BIT_Slice1Output1_SetInterruptHandler(void (* InterruptHandler)(void))
{
    PWM1_16BIT_Slice1Output1_InterruptHandler = InterruptHandler;
}

void PWM1_16BIT_Slice1Output2_SetInterruptHandler(void (* InterruptHandler)(void))
{
    PWM1_16BIT_Slice1Output2_InterruptHandler = InterruptHandler;
}

void PWM1_16BIT_Period_SetInterruptHandler(void (* InterruptHandler)(void))
{
    PWM1_16BIT_Period_InterruptHandler = InterruptHandler;
}

static void PWM1_16BIT_Slice1Output1_DefaultInterruptHandler(void)
{
    //Add your interrupt code here or
    //Use PWM1_16BIT_Slice1Output1_SetInterruptHandler() function to use Custom ISR
}

static void PWM1_16BIT_Slice1Output2_DefaultInterruptHandler(void)
{
    //Add your interrupt code here or
    //Use PWM1_16BIT_Slice1Output2_SetInterruptHandler() function to use Custom ISR
}

static void PWM1_16BIT_Period_DefaultInterruptHandler(void)
{
    //Add your interrupt code here or
    //Use PWM1_16BIT_Period_SetInterruptHandler() function to use Custom ISR
}