/*******************************************************************************
* File Name: front_wheels.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_front_wheels_H) /* Pins front_wheels_H */
#define CY_PINS_front_wheels_H

#include "cytypes.h"
#include "cyfitter.h"
#include "front_wheels_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} front_wheels_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   front_wheels_Read(void);
void    front_wheels_Write(uint8 value);
uint8   front_wheels_ReadDataReg(void);
#if defined(front_wheels__PC) || (CY_PSOC4_4200L) 
    void    front_wheels_SetDriveMode(uint8 mode);
#endif
void    front_wheels_SetInterruptMode(uint16 position, uint16 mode);
uint8   front_wheels_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void front_wheels_Sleep(void); 
void front_wheels_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(front_wheels__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define front_wheels_DRIVE_MODE_BITS        (3)
    #define front_wheels_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - front_wheels_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the front_wheels_SetDriveMode() function.
         *  @{
         */
        #define front_wheels_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define front_wheels_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define front_wheels_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define front_wheels_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define front_wheels_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define front_wheels_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define front_wheels_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define front_wheels_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define front_wheels_MASK               front_wheels__MASK
#define front_wheels_SHIFT              front_wheels__SHIFT
#define front_wheels_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in front_wheels_SetInterruptMode() function.
     *  @{
     */
        #define front_wheels_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define front_wheels_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define front_wheels_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define front_wheels_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(front_wheels__SIO)
    #define front_wheels_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(front_wheels__PC) && (CY_PSOC4_4200L)
    #define front_wheels_USBIO_ENABLE               ((uint32)0x80000000u)
    #define front_wheels_USBIO_DISABLE              ((uint32)(~front_wheels_USBIO_ENABLE))
    #define front_wheels_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define front_wheels_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define front_wheels_USBIO_ENTER_SLEEP          ((uint32)((1u << front_wheels_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << front_wheels_USBIO_SUSPEND_DEL_SHIFT)))
    #define front_wheels_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << front_wheels_USBIO_SUSPEND_SHIFT)))
    #define front_wheels_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << front_wheels_USBIO_SUSPEND_DEL_SHIFT)))
    #define front_wheels_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(front_wheels__PC)
    /* Port Configuration */
    #define front_wheels_PC                 (* (reg32 *) front_wheels__PC)
#endif
/* Pin State */
#define front_wheels_PS                     (* (reg32 *) front_wheels__PS)
/* Data Register */
#define front_wheels_DR                     (* (reg32 *) front_wheels__DR)
/* Input Buffer Disable Override */
#define front_wheels_INP_DIS                (* (reg32 *) front_wheels__PC2)

/* Interrupt configuration Registers */
#define front_wheels_INTCFG                 (* (reg32 *) front_wheels__INTCFG)
#define front_wheels_INTSTAT                (* (reg32 *) front_wheels__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define front_wheels_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(front_wheels__SIO)
    #define front_wheels_SIO_REG            (* (reg32 *) front_wheels__SIO)
#endif /* (front_wheels__SIO_CFG) */

/* USBIO registers */
#if !defined(front_wheels__PC) && (CY_PSOC4_4200L)
    #define front_wheels_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define front_wheels_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define front_wheels_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define front_wheels_DRIVE_MODE_SHIFT       (0x00u)
#define front_wheels_DRIVE_MODE_MASK        (0x07u << front_wheels_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins front_wheels_H */


/* [] END OF FILE */
