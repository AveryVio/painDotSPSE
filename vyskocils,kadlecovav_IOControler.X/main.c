 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2023] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"

uint16_t JoystickX;
uint16_t JoystickY;
uint8_t buttons = 0;

char getButton(char buttonNum){
    return (buttons >> buttonNum) & 1;
}
void setButton(char buttonNum){
    buttons = buttons | (1 >> buttonNum);
}
void clearButton(char buttonNum){
    buttons = buttons | ~(1 >> buttonNum);
}

void readButtons(){
    (IO_PC5_GetValue() == 1)? setButton(0): clearButton(0);
    (IO_PC6_GetValue() == 1)? setButton(1): clearButton(1);
    (IO_PC7_GetValue() == 1)? setButton(2): clearButton(2);
    (IO_PD0_GetValue() == 1)? setButton(3): clearButton(3);
    (IO_PE0_GetValue() == 1)? setButton(4): clearButton(4);
}

void readJoysticks(){
    ADC0_StartConversion(ADC_MUXPOS_AIN1_gc);
    while(!ADC0_IsConversionDone());
    JoystickX = ADC0_GetConversionResult();

    ADC0_StartConversion(ADC_MUXPOS_AIN2_gc);
    while(!ADC0_IsConversionDone());
    JoystickY = ADC0_GetConversionResult();
}

int main(void){
    SYSTEM_Initialize();
    while(1){
        TWI0_Tasks(void);
    }    
}