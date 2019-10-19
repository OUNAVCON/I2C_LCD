/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "../include/pin_manager.h"
static void (*PORTA_IO_PA2_InterruptHandler)(void);
static void (*PORTA_IO_PA1_InterruptHandler)(void);
static void (*PORTA_IO_PA6_InterruptHandler)(void);
static void (*PORTA_PA7_InterruptHandler)(void);

void PORT_Initialize(void);

void PIN_MANAGER_Initialize()
{
    PORT_Initialize();

    /* DIR Registers Initialization */
    PORTA.DIR = 0x86;

    /* OUT Registers Initialization */
    PORTA.OUT = 0x00;

    /* PINxCTRL registers Initialization */
    PORTA.PIN0CTRL = 0x00;
    PORTA.PIN1CTRL = 0x00;
    PORTA.PIN2CTRL = 0x00;
    PORTA.PIN3CTRL = 0x00;
    PORTA.PIN4CTRL = 0x00;
    PORTA.PIN5CTRL = 0x00;
    PORTA.PIN6CTRL = 0x00;
    PORTA.PIN7CTRL = 0x00;

    /* PORTMUX Initialization */
    PORTMUX.CTRLA = 0x00;
    PORTMUX.CTRLB = 0x00;
    PORTMUX.CTRLC = 0x01;
    PORTMUX.CTRLD = 0x00;

    // register default ISC callback functions at runtime; use these methods to register a custom function
    PORTA_IO_PA2_SetInterruptHandler(PORTA_IO_PA2_DefaultInterruptHandler);
    PORTA_IO_PA1_SetInterruptHandler(PORTA_IO_PA1_DefaultInterruptHandler);
    PORTA_IO_PA6_SetInterruptHandler(PORTA_IO_PA6_DefaultInterruptHandler);
    PORTA_PA7_SetInterruptHandler(PORTA_PA7_DefaultInterruptHandler);
}

void PORT_Initialize(void)
{
    /* On AVR devices all peripherals are enable from power on reset, this
     * disables all peripherals to save power. Driver shall enable
     * peripheral if used */

    /* Set all pins to low power mode */
    for (uint8_t i = 0; i < 8; i++) {
        *((uint8_t *)&PORTA + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
    }
    
}

/**
  Allows selecting an interrupt handler for PORTA_IO_PA2 at application runtime
*/
void PORTA_IO_PA2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTA_IO_PA2_InterruptHandler = interruptHandler;
}

void PORTA_IO_PA2_DefaultInterruptHandler(void)
{
    // add your PORTA_IO_PA2 interrupt custom code
    // or set custom function using PORTA_IO_PA2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTA_IO_PA1 at application runtime
*/
void PORTA_IO_PA1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTA_IO_PA1_InterruptHandler = interruptHandler;
}

void PORTA_IO_PA1_DefaultInterruptHandler(void)
{
    // add your PORTA_IO_PA1 interrupt custom code
    // or set custom function using PORTA_IO_PA1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTA_IO_PA6 at application runtime
*/
void PORTA_IO_PA6_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTA_IO_PA6_InterruptHandler = interruptHandler;
}

void PORTA_IO_PA6_DefaultInterruptHandler(void)
{
    // add your PORTA_IO_PA6 interrupt custom code
    // or set custom function using PORTA_IO_PA6_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PORTA_PA7 at application runtime
*/
void PORTA_PA7_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PORTA_PA7_InterruptHandler = interruptHandler;
}

void PORTA_PA7_DefaultInterruptHandler(void)
{
    // add your PORTA_PA7 interrupt custom code
    // or set custom function using PORTA_PA7_SetInterruptHandler()
}
