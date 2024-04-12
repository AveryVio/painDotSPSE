/**
  * TWI0 Generated Driver File
  *
  * @file twi0.c
  *
  * @ingroup twi0_client
  *
  * @brief This file contains the driver code for TWI0 module.
  *
  * @version TWI0 Driver Version 1.1.0
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

#include "../twi0.h"
#include <stdbool.h>
#include "../../system/utils/compiler.h"

/**
  Section: Driver Interface
 */
const struct I2C_CLIENT_INTERFACE I2C0_Client = {
    .Initialize = TWI0_Initialize,
    .Deinitialize = TWI0_Deinitialize,
    .WriteByte = TWI0_WriteByte,
    .ReadByte = TWI0_ReadByte,
    .TransferDirGet = TWI0_TransferDirGet,
    .LastByteAckStatusGet = TWI0_LastByteAckStatusGet,
    .ErrorGet = TWI0_ErrorGet,
    .CallbackRegister = TWI0_CallbackRegister,
    .Tasks = TWI0_Tasks
};

/**
 Section: Private functions declaration
 */
static void TWI0_EventHandler();
static void TWI0_ErrorEventHandler();
static bool TWI0_DefaultCallback(i2c_client_transfer_event_t event);

/**
 Section: Private Variable Definitions
 */
static volatile uint16_t twi0Addr;
static volatile i2c_client_error_t twi0ErrorState;
static bool(*TWI0_InterruptHandler)(i2c_client_transfer_event_t clientEvent) = NULL;

/**
 Section: Public functions
 */
void TWI0_Initialize(void)
{
    //FMPEN OFF; INPUTLVL I2C; SDAHOLD OFF; SDASETUP 4CYC; 
    TWI0.CTRLA = 0x0;
    
    //Debug Run
    TWI0.DBGCTRL = 0x0;
    
    //Client Address
    TWI0.SADDR = 0x0;
    
    //ADDREN disabled; ADDRMASK 0x0; 
    TWI0.SADDRMASK = 0x0;
    
    //APIEN false; DIEN false; ENABLE enabled; PIEN false; PMEN disabled; SMEN disabled; 
    TWI0.SCTRLA = 0x1;
    
    //ACKACT ACK; SCMD NOACT; 
    TWI0.SCTRLB = 0x0;
    
    //Client Data
    TWI0.SDATA = 0x0;
    
    //APIF disabled; BUSERR disabled; COLL disabled; DIF disabled; 
    TWI0.SSTATUS = 0x0;
    

    TWI0_CallbackRegister(TWI0_DefaultCallback);
}

void TWI0_Deinitialize(void)
{
    //FMPEN OFF; INPUTLVL I2C; SDAHOLD OFF; SDASETUP 4CYC; 
    TWI0.CTRLA = 0x00;
    
    //Debug Run
    TWI0.DBGCTRL = 0x00;
    
    //Client Address
    TWI0.SADDR = 0x00;
    
    //ADDREN disabled; ADDRMASK 0x0; 
    TWI0.SADDRMASK = 0x00;
    
    //APIEN false; DIEN false; ENABLE enabled; PIEN false; PMEN disabled; SMEN disabled; 
    TWI0.SCTRLA = 0x00;
    
    //ACKACT ACK; SCMD NOACT; 
    TWI0.SCTRLB = 0x00;
    
    //Client Data
    TWI0.SDATA = 0x00;
    
    //APIF disabled; BUSERR disabled; COLL disabled; DIF disabled; 
    TWI0.SSTATUS = 0x00;
    

    TWI0_CallbackRegister(TWI0_DefaultCallback);
}

void TWI0_WriteByte(uint8_t wrByte)
{
    TWI0.SDATA = wrByte;
}

uint8_t TWI0_ReadByte(void)
{
    return TWI0.SDATA;
}

uint16_t TWI0_ReadAddr(void)
{
    return (TWI0.SADDR >> 1);
}

i2c_client_error_t TWI0_ErrorGet(void)
{
    i2c_client_error_t error;
    error = twi0ErrorState;
    twi0ErrorState = I2C_CLIENT_ERROR_NONE;
    return error;
}

i2c_client_transfer_dir_t TWI0_TransferDirGet(void)
{
    return ((TWI0.SSTATUS & TWI_DIR_bm) ? I2C_CLIENT_TRANSFER_DIR_READ : I2C_CLIENT_TRANSFER_DIR_WRITE);
}

i2c_client_ack_status_t TWI0_LastByteAckStatusGet(void)
{
    return ((TWI0.SSTATUS & TWI_RXACK_bm)? I2C_CLIENT_ACK_STATUS_RECEIVED_NACK : I2C_CLIENT_ACK_STATUS_RECEIVED_ACK);
}

void TWI0_CallbackRegister(bool(*callback)(i2c_client_transfer_event_t clientEvent))
{
    if (callback != NULL)
    {
        TWI0_InterruptHandler = callback;
    }
}

static void TWI0_ErrorEventHandler(void)
{
    if (TWI0.SSTATUS & TWI_COLL_bm) {
        twi0ErrorState = I2C_CLIENT_ERROR_BUS_ERROR;
        TWI0_InterruptHandler(I2C_CLIENT_TRANSFER_EVENT_ERROR);
    }
    else if(TWI0.SSTATUS & TWI_BUSERR_bm)
    {
        twi0ErrorState = I2C_CLIENT_ERROR_COLLISION;
        TWI0_InterruptHandler(I2C_CLIENT_TRANSFER_EVENT_ERROR);
    }
}

static void TWI0_EventHandler(void)
{
    //Handling Stop Interrupt
    if((TWI0.SSTATUS & TWI_APIF_bm) && (!(TWI0.SSTATUS & TWI_AP_bm)))
    {
        TWI0_InterruptHandler(I2C_CLIENT_TRANSFER_EVENT_STOP_BIT_RECEIVED);
        TWI0.SCTRLB = TWI_SCMD_COMPTRANS_gc;
        TWI0.SSTATUS |=(TWI_AP_bm | TWI_APIF_bm | TWI_DIF_bm);
    }
    //Handling Address Interrupt
    else if((TWI0.SSTATUS & TWI_APIF_bm) && (TWI0.SSTATUS & TWI_AP_bm))
    {
        /* Received I2C address must be read out */
        twi0Addr = TWI0_ReadAddr();

        /* Clear Software Error State */
        twi0ErrorState = I2C_CLIENT_ERROR_NONE;

        /* Notify that a address match event has occurred */
        if (TWI0_InterruptHandler(I2C_CLIENT_TRANSFER_EVENT_ADDR_MATCH) == true)
        {
            /* TWI host wants to read */
            if (!(TWI0.SSTATUS & TWI_DIR_bm))
            {
                
                    /* In the callback, client must write to transmit register by calling I2Cx_WriteByte() */
                    if (TWI0_InterruptHandler(I2C_CLIENT_TRANSFER_EVENT_TX_READY) == false)
                    {
                        TWI0.SCTRLB = TWI_ACKACT_NACK_gc | TWI_SCMD_COMPTRANS_gc; /* Send NACK */
                    }
                
            }

            TWI0.SCTRLB = TWI_ACKACT_ACK_gc | TWI_SCMD_RESPONSE_gc; /* Send ACK */
        }
        else
        {
            TWI0.SCTRLB = TWI_ACKACT_NACK_gc | TWI_SCMD_COMPTRANS_gc; /* Send NACK */
        }
    }
    
    else if (TWI0.SSTATUS & TWI_DIF_bm)
    {
        /* Host reads from client, client transmits */
        if(TWI0.SSTATUS & TWI_DIR_bm)
        {

                /* TWI Host wants to read. In the callback, client must write to transmit register */
                if (TWI0_InterruptHandler(I2C_CLIENT_TRANSFER_EVENT_TX_READY) == false)
                {
                    TWI0.SCTRLB = TWI_ACKACT_NACK_gc | TWI_SCMD_COMPTRANS_gc; /* Send NACK */
                } 
                else 
                {
                    TWI0.SCTRLB = TWI_ACKACT_ACK_gc | TWI_SCMD_RESPONSE_gc;
                }
                
        } else { 
                       
                /* TWI Host wants to write. In the callback, client must read data by calling I2Cx_ReadByte()  */
                if (TWI0_InterruptHandler(I2C_CLIENT_TRANSFER_EVENT_RX_READY) == true)
                {
                    TWI0.SCTRLB = TWI_ACKACT_ACK_gc | TWI_SCMD_RESPONSE_gc; /* Send ACK */
                }
                else
                {
                    TWI0.SCTRLB = TWI_ACKACT_NACK_gc | TWI_SCMD_COMPTRANS_gc; /* Send NACK */
                }
        }   
    }    
}

void TWI0_Tasks(void)
{
    if((TWI0.SSTATUS & TWI_COLL_bm) || (TWI0.SSTATUS & TWI_BUSERR_bm))
    {
        TWI0_ErrorEventHandler();
    }
    
    if((TWI0.SSTATUS & TWI_DIF_bm) || ((TWI0.SSTATUS & TWI_APIF_bm) && (TWI0.SSTATUS & TWI_AP_bm)) || 
           ((TWI0.SSTATUS & TWI_APIF_bm) && (!(TWI0.SSTATUS & TWI_AP_bm))) )
    {
        TWI0_EventHandler();        
    }
}

static bool TWI0_DefaultCallback(i2c_client_transfer_event_t event)
{
    /* User has to register callback. Refer example code */
    return false;
}

