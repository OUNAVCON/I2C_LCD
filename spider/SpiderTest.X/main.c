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

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/utils/interrupt_avr8.h"

/*
    Main application
*/

void periodDcCapture(void);
void pwmOverflow(void);

volatile uint16_t period;
volatile uint16_t dutyCycle;
volatile uint8_t signalRx = 0;
volatile uint8_t overflowOccured = 0;

int main(void)
{
    volatile uint16_t signalCount = 0;
    volatile uint8_t direction = 0;
    volatile uint8_t delayCountState = 0; //0 - start looking for flag. 1 - Count met move to delay.
    volatile uint16_t delayCount = 0;
    /* Initializes MCU, drivers and middleware */
    SYSTEM_Initialize();
    TCA0_SetOVFIsrCallback(pwmOverflow);
    TCA0_EnableInterrupt();
    TCA0_ClearOverflowInterruptFlag();
    
    TCB0_SetCaptIsrCallback(periodDcCapture);
    TCB0_EnableInterrupt();
    TCB0_ClearInterruptFlag();
    Enable_global_interrupt();
    IO_PA1_SetLow();
    IO_PA2_SetHigh();
    
    TCA0.SINGLE.CMP0 = TCA0.SINGLE.PER>>1;

    //Enable Global Interrupt
    
    /* Replace with your application code */
    while (1){

        switch(delayCountState){
            case 0: //Let's look for a activation
                if ((signalRx > 0) &&
                        (dutyCycle > (TCA0.SINGLE.CMP0 - 10)) && //Duty Cycle must be within a +/- 10 count band
                        (dutyCycle < (TCA0.SINGLE.CMP0 + 10)) &&
                        (period > (TCA0.SINGLE.PER - 10)) && //Period must be within a +/- 10 count band
                        (period < (TCA0.SINGLE.PER + 10))) {
                    signalRx = 0;
                    signalCount++;
                }
                if (signalCount > 50) { //500 pulses at 1ms each is a 1/2 second window.
                    //Switch Direction on Motor
                    //Wait a while before starting to check TCB0 again.
                    switch (direction) {
                        case 0:
                            direction = 1;
                            IO_PA1_SetHigh();
                            IO_PA2_SetLow();
                            break;
                        case 1:
                            direction = 0;
                            IO_PA1_SetLow();
                            IO_PA2_SetHigh();
                            break;
                    }
                    signalCount = 0; // Maybe this should be decremented on overflow of TCA...That way the value will be decreasing while the motor moves away.
                    delayCountState = 1; //Let's start waiting till we move off the switch.
                }
                break;
            case 1://Motor has switched directions let's delay while we wait for the sensor to move away.
                if(overflowOccured == 1){
                    delayCount++;
                }
                if(delayCount > 5000){ //TCA0 overflow is 1ms interval.
                    delayCountState = 0;
                    delayCount = 0;
                    signalCount = 0;
                }
                break;
            default:
                break;
        }
        overflowOccured = 0;
    }
}

void periodDcCapture(void){
    period = TCB0.CNT;
    dutyCycle = TCB0.CCMP;
    signalRx = 1;
    TCB0_ClearInterruptFlag();
}


void pwmOverflow(void){
    overflowOccured = 1;
     TCA0_ClearOverflowInterruptFlag();
}
   
/**
    End of File
*/