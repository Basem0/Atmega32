/*
 * EXTI_prog.c
 *
 * Created: 1/31/2024 2:06:51 AM
 *  Author: ahmed
 */ 

#include "../Std_Types.h"
#include "EXTI_Private.h"
#include "EXTI_config.h"
#include "EXTI_int.h"

static Std_ReturnType INT0_level(EXTI_status state);
static Std_ReturnType INT1_level(EXTI_status state);
static Std_ReturnType INT2_level(EXTI_status state);

// Array to hold callback functions for each external interrupt
static volatile void (*EXTI_FUNS[3])() = {NULL,NULL,NULL};

/**
 * \brief Initializes external interrupts based on the provided configuration.
 * 
 * \param Copy_EXT_INTx Pointer to an array of EXTI_t structures containing the configuration for external interrupts.
 * \return Std_ReturnType E_OK if initialization is successful, E_NOT_OK otherwise.
 */
Std_ReturnType EXTI_Init(EXTI_t * Copy_EXT_INTx)
{
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == Copy_EXT_INTx)
    {
        ret = E_NOT_OK;
    }
    else
    {
        interrupt_INTx_src source_iter = 0;
        for (source_iter = 0; source_iter < 3 ; source_iter++)
        {
            if (Copy_EXT_INTx[source_iter].EXTI_State == ACTIVE)
            {
                // Register callback function for the interrupt
                ret = EXTI_CallBack(Copy_EXT_INTx[source_iter]);
                
                // Configure interrupt settings based on interrupt source
                switch(source_iter)
                {
                    case 0:
                        MCUCR &= 0xFC; // Clear previous settings
                        Ext_INT0_Enable();
                        ret = INT0_level(Copy_EXT_INTx[source_iter].EXTI_Level);
                        break;
                    case 1:
                        MCUCR &= 0xF3; // Clear previous settings
                        Ext_INT1_Enable();
                        INT1_level(Copy_EXT_INTx[source_iter].EXTI_Level);
                        break;
                    case 2:
                        MCUCSR &= 0xBF; // Clear previous settings
                        Ext_INT2_Enable();
                        INT2_level(Copy_EXT_INTx[source_iter].EXTI_Level);
                        break;
                }
            }
        }
		SREG |= (1<<7);
    }

    return ret;
}

/**
 * \brief Sets sensing mode for the specified external interrupt.
 * 
 * \param Copy_u8EXTI_ID ID of the external interrupt (0, 1, or 2).
 * \param Copy_u8SenseLevel Sensing level for the interrupt (RISING_EDGE, FALLING_EDGE, ANY_LOGIC, or LOW_LEVEL).
 * \return Std_ReturnType E_OK if setting the sensing mode is successful, E_NOT_OK otherwise.
 */
static Std_ReturnType EXTI_SetSenceMode(uint8 Copy_u8EXTI_ID , uint8 Copy_u8SenseLevel)
{
    Std_ReturnType ret = E_NOT_OK;

    if (Copy_u8EXTI_ID < 3)
    {
        if (Copy_u8EXTI_ID == 0)
        {
            MCUCR &= 0xFC; // Clear previous settings
            INT1_level(Copy_u8EXTI_ID);
        }
        else if (Copy_u8EXTI_ID == 1)
        {
            MCUCR &= 0xF3; // Clear previous settings
            INT1_level(Copy_u8EXTI_ID);
        }
        else if (Copy_u8EXTI_ID == 2)
        {
            MCUCSR &= 0xBF; // Clear previous settings
            INT2_level(Copy_u8EXTI_ID);
        }
    }

    return ret;
}

/**
 * \brief Enables the specified external interrupt.
 * 
 * \param source Interrupt source (INTERRUPT_EXTERNAL_INT0, INTERRUPT_EXTERNAL_INT1, or INTERRUPT_EXTERNAL_INT2).
 * \return Std_ReturnType E_OK if enabling the interrupt is successful, E_NOT_OK otherwise.
 */
Std_ReturnType EXTI_EnableINT(interrupt_INTx_src source)
{
    Std_ReturnType ret = E_OK;
    switch(source)
    {
        case INTERRUPT_EXTERNAL_INT0:
            Ext_INT0_Enable();
            break;
        case INTERRUPT_EXTERNAL_INT1:
            Ext_INT1_Enable();
            break;
        case INTERRUPT_EXTERNAL_INT2:
            Ext_INT2_Enable();
            break;
        default:
            ret = E_NOT_OK;
    }
    return ret;
}

/**
 * \brief Disables the specified external interrupt.
 * 
 * \param source Interrupt source (INTERRUPT_EXTERNAL_INT0, INTERRUPT_EXTERNAL_INT1, or INTERRUPT_EXTERNAL_INT2).
 * \return Std_ReturnType E_OK if disabling the interrupt is successful, E_NOT_OK otherwise.
 */
Std_ReturnType EXTI_DisableINT(interrupt_INTx_src source)
{
    Std_ReturnType ret = E_OK;
    switch(source)
    {
        case INTERRUPT_EXTERNAL_INT0:
            Ext_INT0_Disable();
            break;
        case INTERRUPT_EXTERNAL_INT1:
            Ext_INT1_Disable();
            break;
        case INTERRUPT_EXTERNAL_INT2:
            Ext_INT2_Disable();
            break;
        default:
            ret = E_NOT_OK;
    }
    return ret;
}

/**
 * \brief Registers a callback function for the specified external interrupt.
 * 
 * \param Copy_EXT_INTx EXTI_t structure containing the configuration for the external interrupt.
 * \return Std_ReturnType E_OK if registering the callback function is successful, E_NOT_OK otherwise.
 */
Std_ReturnType EXTI_CallBack(EXTI_t Copy_EXT_INTx)
{
    Std_ReturnType ret = E_NOT_OK;
    if(Copy_EXT_INTx.EXT_InterruptHandler == NULL)
    {
        ret = E_NOT_OK;
    }
    else
    {
        EXTI_FUNS[Copy_EXT_INTx.source] = Copy_EXT_INTx.EXT_InterruptHandler;
        ret = E_OK;
    }
    return ret;
}

/**
 * \brief Interrupt service routine for external interrupt 0.
 */
ISR(VECT_INT0)
{
    if (NULL == EXTI_FUNS[0]){/*Nothing*/}
    else
    {
        EXTI_FUNS[0]();
    }
}

/**
 * \brief Interrupt service routine for external interrupt 1.
 */
ISR(VECT_INT1)
{
    if (NULL == EXTI_FUNS[1]){/*Nothing*/}
    else
    {
        EXTI_FUNS[1]();
    }
}

/**
 * \brief Interrupt service routine for external interrupt 2.
 */
ISR(VECT_INT2)
{
    if (NULL == EXTI_FUNS[2]){/*Nothing*/}
    else
    {
        EXTI_FUNS[2]();
    }
}

/**
 * \brief Sets the triggering level for external interrupt 0.
 * 
 * \param state Triggering level for the interrupt (RISING_EDGE, FALLING_EDGE, ANY_LOGIC, or LOW_LEVEL).
 * \return Std_ReturnType E_OK if setting the triggering level is successful, E_NOT_OK otherwise.
 */
static Std_ReturnType INT0_level(EXTI_status state)
{
    Std_ReturnType ret = E_OK;
    switch(state)
    {
        case RISING_EDGE:
            MCUCR |= 0x03;
            break;
        case FALLING_EDGE:
            MCUCR |= 0x02;
            break;
        case ANY_LOGIC:
            MCUCR |= 0x01;
            break;
        case LOW_LEVEL:
            MCUCR |= 0x00;
            break;
        default:
            ret = E_NOT_OK;
    }
    return ret;
}

/**
 * \brief Sets the triggering level for external interrupt 1.
 * 
 * \param state Triggering level for the interrupt (RISING_EDGE, FALLING_EDGE, ANY_LOGIC, or LOW_LEVEL).
 * \return Std_ReturnType E_OK if setting the triggering level is successful, E_NOT_OK otherwise.
 */
static Std_ReturnType INT1_level(EXTI_status state)
{
    Std_ReturnType ret = E_OK;
    switch(state)
    {
        case RISING_EDGE:
            MCUCR |= 0x0C;
            break;
        case FALLING_EDGE:
            MCUCR |= 0x08;
            break;
        case ANY_LOGIC:
            MCUCR |= 0x04;
            break;
        case LOW_LEVEL:
            MCUCR |= 0x00;
            break;
        default:
            ret = E_NOT_OK;
    }
    return ret;
}

/**
 * \brief Sets the triggering level for external interrupt 2.
 * 
 * \param state Triggering level for the interrupt (RISING_EDGE or FALLING_EDGE).
 * \return Std_ReturnType E_OK if setting the triggering level is successful, E_NOT_OK otherwise.
 */
static Std_ReturnType INT2_level(EXTI_status state)
{
    Std_ReturnType ret = E_OK;
    switch(state)
    {
        case RISING_EDGE:
            MCUCR |= 0x40;
            break;
        case FALLING_EDGE:
            MCUCR |= 0x00;
            break;
        default:
            ret = E_NOT_OK;
    }
    return ret;
}
