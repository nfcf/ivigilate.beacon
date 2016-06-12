/**
 ** ############################################################################
 **
 ** @file  config.h
 ** @brief System Compile-Time Configuration File
 **
 ** Defines symbols and constants used to configure the firmware for a
 ** specific product and the installed accessory components. This file
 ** is closely related in general purpose to the constants and data
 ** structure(s) defined in parameters.{h,c}. The primary difference is
 ** that configuration options in this file are generally common to all
 ** instances of the product.
 **
 ** ---- IN GENERAL ----
 ** If an item comment says "SET THIS" you may change it
 ** If an item comment says "def value" or "def test," you shouldn't modify it
 **
 ** Copyright (c) 2015 EM Microelectronic-US Inc. All rights reserved.
 ** Developed by Glacier River Design, LLC 
 **
 ** ############################################################################
 ** EM Microelectronic-US Inc. License Agreement
 ** 
 ** Please read this License Agreement ("Agreement") carefully before 
 ** accessing, copying, using, incorporating, modifying or in any way providing 
 ** ("Using" or "Use") this source code.  By Using this source code, you: (i) 
 ** warrant and represent that you have obtained all authorizations and other 
 ** applicable consents required empowering you to enter into and (ii) agree to 
 ** be bound by the terms of this Agreement.  If you do not agree to this 
 ** Agreement, then you are not permitted to Use this source code, in whole or 
 ** in part.
 ** 
 ** Pursuant to the terms in the accompanying software license agreement and 
 ** Terms of Use located at: www.emdeveloper.com/emassets/emus_termsofuse.html 
 ** (the terms of each are incorporated herein by this reference) and subject to 
 ** the disclaimer and limitation of liability set forth below, EM  
 ** Microelectronic US Inc. ("EM"), grants strictly to you, without the right to 
 ** sublicense, a non-exclusive, non-transferable, revocable, worldwide license 
 ** to use the source code to modify the software program for the sole purpose 
 ** of developing object and executable versions that execute solely and 
 ** exclusively on devices manufactured by or for EM or your products that use 
 ** or incorporate devices manufactured by or for EM; provided that, you clearly 
 ** notify third parties regarding the source of such modifications or Use.
 ** 
 ** Without limiting any of the foregoing, the name "EM Microelectronic-US 
 ** Inc." or that of any of the EM Parties (as such term is defined below) must 
 ** not be Used to endorse or promote products derived from the source code 
 ** without prior written permission from an authorized representative of EM 
 ** Microelectronic US Inc.
 ** 
 ** THIS SOURCE CODE IS PROVIDED "AS IS" AND "WITH ALL FAULTS", WITHOUT ANY 
 ** SUPPORT OR ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED 
 ** TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 ** PURPOSE ARE DISCLAIMED.  ALSO, THERE IS NO WARRANTY OF NON-INFRINGEMENT, 
 ** TITLE OR QUIET ENJOYMENT.
 ** 
 ** IN NO EVENT SHALL EM MICROELECTRONIC US INC., ITS AFFILIATES, PARENT AND 
 ** ITS/THEIR RESPECTIVE LICENSORS, THIRD PARTY PROVIDERS, REPRESENTATIVES, 
 ** AGENTS AND ASSIGNS ("COLLECTIVLEY, "EM PARTIES") BE LIABLE FOR ANY DIRECT, 
 ** INDIRECT, INCIDENTAL, SPECIAL, PUNITIVE, EXEMPLARY, OR CONSEQUENTIAL 
 ** DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 ** SERVICES; LOSS OF USE, DATA, EQUIPMENT, SYSTEMS, SOFTWARE, TECHNOLOGY, 
 ** SERVICES, GOODS, CONTENT, MATERIALS OR PROFITS; BUSINESS INTERRUPTION OR 
 ** OTHER ECONOMIC LOSS OR ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT 
 ** LIMITED TO ANY DEFENSE THEREOF) HOWEVER CAUSED AND ON ANY THEORY OF 
 ** LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
 ** NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOURCE 
 ** CODE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  NOTWITHSTANDING 
 ** ANYTHING ELSE TO THE CONTRARY, IN NO EVENT WILL THE EM PARTIES' AGGREGATE 
 ** LIABILITY UNDER THIS AGREEMENT OR ARISING OUT OF YOUR USE OF THE SOURCE 
 ** CODE EXCEED ONE HUNDRED U.S. DOLLARS (U.S. $100).
 ** 
 ** Please refer to the accompanying software license agreement and Terms of 
 ** Use located at: www.emdeveloper.com/emassets/emus_termsofuse.html to better 
 ** understand all of your rights and obligations hereunder. 
 ** ############################################################################
 */
#ifndef _CONFIG_H
#define _CONFIG_H


// NOTE - This file uses subordinate configurations that are conditionally
//        included by this file. This file's subordinates depend on params.h
//        so it must be included prior to including this file.


/**
 *  @brief a union that can be accessed as 8, 16, or 32-bit.
 */
typedef unsigned long UINT32;
typedef signed   long SINT32;
typedef union
{
   UINT32 part32;
   struct
   {
      UINT16 val16_1;
      UINT16 val16_0;
   } part16;
   struct
   {
      UINT8  val8_3;
      UINT8  val8_2;
      UINT8  val8_1;
      UINT8  val8_0;
   } part8;
} UINTX;

/**
 * @def   SWAP_BYTES(x)
 * @brief Swap LSB and MSB of 16-bit values
 *
 * 16-bit conversion from big-endian to little-endian and vice-versa
 */
#define SWAP_BYTES(x) (((x) << 8 &0xff00) | ((x) >>8 &0xff))


/**
 * @brief PRODUCT CONFIGURATION
 *
 * Product configuration is managed via Ride7 project configurations. Each
 * Beacon design is associated with a single project configuration which is
 * selected in the Ride7 IDE by selecting the "Beacon" Application in the
 * project explorer and using the Project::Properties menu.
 *
 * Selecting a configuration as just described is equivalent to uncommenting
 * exactly one and only one of the following #defines:
 *
 * #define EM_PRODUCT_COINCELL
 * #define EM_PRODUCT_EMBC02  // COiN with accelerometer
 * #define EM_PRODUCT_EMBC03  // COiN with EM4325 RFID used as temperature sensor
 * #define EM_PRODUCT_PATCH
 * #define EM_PRODUCT_TINY
 * #define EM_PRODUCT_LOWCOST
 *
 */


// @brief Advertising Interval (for continuous operation when the 9301 is not shut down
// between advertisements). Defined in BT 4.0, Vol.2 (E) 7.8.5.
// Note, the values are byte reversed for correct transmission to the 9301
#define ADV_INTERVAL_MIN  SWAP_BYTES(0x00A0)
#define ADV_INTERVAL_MAX  SWAP_BYTES(0x00A0)


/**
 * @brief EM9301 Features & Firmware Capabilities
 */

// Individual 9301 Features
#define EM9301_UNKNOWN_BLUETOOTH_DEVICE  0x00
#define EM9301_KNOWN_BLUETOOTH_DEVICE    0x01  // True of all known die revs
#define EM9301_GAIN_OFFSET_REQUIRED      0x02  // Workaround for di10
#define EM9301_ONE_SHOT_CAL              0x04  // can reload cal constants
#define EM9301_SIGNALS_RF_ACTIVITY       0x08  // can use IRQ as an activity indicator
#define EM9301_RESERVED_CAPABILITY_BITS  0xE0

// Sets of features supported by various 9301 die revisions
#define EM9301_FEATSET_DI07   ( EM9301_KNOWN_BLUETOOTH_DEVICE )

#define EM9301_FEATSET_DI10   ( EM9301_KNOWN_BLUETOOTH_DEVICE | EM9301_GAIN_OFFSET_REQUIRED |\
                                EM9301_ONE_SHOT_CAL           | EM9301_SIGNALS_RF_ACTIVITY     )

#define EM9301_FEATSET_DI11   ( EM9301_KNOWN_BLUETOOTH_DEVICE |\
                                EM9301_ONE_SHOT_CAL           | EM9301_SIGNALS_RF_ACTIVITY    )


// NOTE, the product-specific file included below defines the symbol EM9301_FIRMWARE_CAPABILITIES in
// order to specifiy *at compile time* the capabilities that will be supported by the firmware. The
// following macros use this symbol. Out of the supported capabilities, those actually used *at run
// time* are controlled by macros that are defined in hci_9301.h which rely on the die rev that was
// actually reported by the 9301.


// @brief Conditional support for 9301 devices with one-shot autocal mode. After
// initial calibration, subsequent power on events re-use the previous calibration values.
// Future autocalibration is deferred until required by a temperature change exceeding 5
// degrees Celcius.
#define CAPABILITY_EM9301_ONESHOT_CAL (EM9301_FIRMWARE_CAPABILITIES & EM9301_ONE_SHOT_CAL)

// @brief 9301 devices that support RF Activity Signals on the SEL pin. Normally the
// 9301 is powered down between advertisements to prolong battery live. This allows
// us to start that shutdown at the earliest opportunity instead of using a timer
// with some attendant margin.
#define CAPABILITY_EM9301_SIGNALS_RF_ACTIVITY (EM9301_FIRMWARE_CAPABILITIES & EM9301_SIGNALS_RF_ACTIVITY)


/**
 *  @brief Define the fields in advModes
 *
 *  When customizing beacons, use AdvParams.advModes to specify which packet types to
 *  enable and which state machine (what happens when the button is pushed) to use.
 *  The default state machine is CoinStandardModes[] defined in main.c.
 */
#define ADVMODES_EMBEACON           0x01    // bit flag - TRUE-->enable sensor data adverts
#define ADVMODES_IDDATA             0x02    // bit flag - TRUE-->enable iddata adverts
#define ADVMODES_ALTBEACON          0x04    // bit flag - TRUE-->enable AltBeacon adverts

#define ADVMODES_EDDY_URL           0x08    // bit flag - TRUE-->enable Eddystone 
#define ADVMODES_EDDY_TLM           0x10    // bit flag - TRUE-->enable Eddystone 
#define ADVMODES_EDDY_UID           0x20    // bit flag - TRUE-->enable Eddystone 
#define ADVMODES_RESERVED           0x80    // do not use

#define ADVMODES_BEACONS_MASK       (ADVMODES_EMBEACON|ADVMODES_ALTBEACON|ADVMODES_IDDATA|ADVMODES_EDDY_URL|ADVMODES_EDDY_TLM|ADVMODES_EDDY_UID)

                                            //
#define ADVMACHINES_MASK         0x03    // specifies state machine 0..3
#define ADVMACHINES_RESERVED     0x00    // reserved for future state machine definition
#define ADVMACHINES_CUSTOM       0x01    // Custom (simple on/off, fully customized by parameters)
#define ADVMACHINES_PRODUCT      0x02    // Product-Specific FSM (used for Proximity FSM on COiN)
#define ADVMACHINES_PROXIMITY    0x02    // **DEPRECATED** Refactored as ADV_STATE_PRODUCT for EMBC01
#define ADVMACHINES_USER_DEFN    0x03    // User-defined state machine. Requires change to 
                                         //   InitParams() & GetMode()
/**
 *  @brief Sensor Data Types
 *  Values for least-significant 4 bits of a 16-bit field to define
 *  the sensor-type (and related measurement units).
 */
/**                                                    EMBC01  02  03    */
#define SENSOR_FIELD_TYPE_LIGHT_SENSE        0x00  /**      -   -   -    */
#define SENSOR_FIELD_TYPE_FIRMWARE_REV       0x01  /**      y   y   y    */
#define SENSOR_FIELD_TYPE_AUTOCAL_RESULT     0x02  /**      y   y   y    */
#define SENSOR_FIELD_TYPE_SPARE0x3           0x03  /**      -   -   -    */
#define SENSOR_FIELD_TYPE_TEMPERATURE        0x04  /**      -   -   y    */
#define SENSOR_FIELD_TYPE_SPARE0x5           0x05  /**      -   -   -    */ 
#define SENSOR_FIELD_TYPE_SPARE0x6           0x06  /**      -   -   -    */ 
#define SENSOR_FIELD_TYPE_SPARE0x7           0x07  /**      -   -   -    */ 
#define SENSOR_FIELD_TYPE_SPARE0x8           0x08  /**      -   -   -    */ 
#define SENSOR_FIELD_TYPE_SPARE0x9           0x09  /**      -   -   -    */ 
#define SENSOR_FIELD_TYPE_SPARE0xA           0x0A  /**      -   -   -    */ 
#define SENSOR_FIELD_TYPE_ACCELERATION       0x0B  /**      -   y   -    */
#define SENSOR_FIELD_TYPE_SPARE0xC           0x0C  /**      -   -   -    */ 
#define SENSOR_FIELD_TYPE_SPARE0xD           0x0D  /**      -   -   -    */ 
#define SENSOR_FIELD_TYPE_SPARE0xE           0x0E  /**      -   -   -    */ 
#define SENSOR_FIELD_TYPE_SPARE0xF           0x0F  /**      -   -   -    */ 


#define LSB12(data)              (data & 0x0FFF)

#define SENSOR_LIGHT(lux)        ((SENSOR_FIELD_TYPE_LIGHT_SENSE    << 12) | LSB12(lux))
#define SENSOR_FW_REV()          ((SENSOR_FIELD_TYPE_FIRMWARE_REV   << 12) | ((UINT16)FirmwareVersion))
#define SENSOR_AUTOCAL(vco,mod)  ((SENSOR_FIELD_TYPE_AUTOCAL_RESULT << 12) | \
                                   ((vco << 8) & 0x0F00) | \
                                    (mod       & 0x00FF))
#define SENSOR_SPARE0x3(data)    ((SENSOR_FIELD_TYPE_SPARE0x3    << 12) | LSB12(data))
#define SENSOR_TEMPERATURE(temp) ((SENSOR_FIELD_TYPE_TEMPERATURE    << 12) | ((UINT16)temp >> 4))
#define SENSOR_ACCELERATION(g)   ((SENSOR_FIELD_TYPE_ACCELERATION   << 12) | (g))


#if MCU_HASDCDC
#define OPERATIONAL_VOLTAGE_LIMIT  0x09            // Just sleep if battery below 0.9 volts
#else
#define OPERATIONAL_VOLTAGE_LIMIT  0x20            // Just sleep if battery below 2.5 volts
#endif

/**
 * @brief Event Data Types
 *
 * Values for the most-significant 4 bits of a 16-bit field to define the type
 * of event count that appears in the packet.
 */
/**                                                    EMBC01  02  03    */
#define EVENT_FIELD_TYPE_BUTTON_PRESS        0x00  /**      y   y   y    */
#define EVENT_FIELD_TYPE_LOW_BATTERY         0x01  /**      y   y   y    */
#define EVENT_FIELD_TYPE_RF_VCO_CAL          0x02  /**      y   y   y    */
#define EVENT_FIELD_TYPE_LOW_TEMPERATURE     0x03  /**      -   -   y    */
#define EVENT_FIELD_TYPE_HIGH_TEMPERATURE    0x04  /**      -   -   y    */
#define EVENT_FIELD_TYPE_LOW_PRESSURE        0x05  /**      -   -   -    */
#define EVENT_FIELD_TYPE_HIGH_PRESSURE       0x06  /**      -   -   -    */
#define EVENT_FIELD_TYPE_LOW_HUMIDITY        0x07  /**      -   -   -    */
#define EVENT_FIELD_TYPE_HIGH_HUMIDITY       0x08  /**      -   -   -    */
#define EVENT_FIELD_TYPE_CLOSE_MAGNET        0x09  /**      -   -   -    */
#define EVENT_FIELD_TYPE_FAR_MAGNET          0x0A  /**      -   -   -    */
#define EVENT_FIELD_TYPE_ANY_MOVEMENT        0x0B  /**      -   y   -    */
#define EVENT_FIELD_TYPE_TAP                 0x0C  /**      -   y   -    */
#define EVENT_FIELD_TYPE_FALL                0x0D  /**      -   y   -    */
#define EVENT_FIELD_TYPE_ALARM               0x0E  /**      -   -   -    */
#define EVENT_FIELD_TYPE_BUZZER              0x0F  /**      -   -   -    */

// @brief Advertising Interval (for continuous operation when the 9301 is not shut down
// between advertisements). Defined in BT 4.0, Vol.2 (E) 7.8.5.
// Note, the values are byte reversed for correct transmission to the 9301
#define ADV_INTERVAL_MIN  SWAP_BYTES(0x00A0)
#define ADV_INTERVAL_MAX  SWAP_BYTES(0x00A0)


/**
 * @brief Product-Specific Configuration Items
 */

#if defined (EM_PRODUCT_COINCELL)
#include "config-coincell.h"
#define  EM_PRODUCT_MODEL_ID    "01"
#elif defined (EM_PRODUCT_EMBC02)
#include "config-EMBC02.h"
#define  EM_PRODUCT_MODEL_ID    "02"
#elif defined (EM_PRODUCT_EMBC03)
#include "config-EMBC03.h"
#define  EM_PRODUCT_MODEL_ID    "03"
#elif defined (EM_PRODUCT_TINY)
#include "config-tiny-lowcost.h"
#define  EM_PRODUCT_MODEL_ID    "TY"
#elif defined (EM_PRODUCT_LOWCOST)
#include "config-tiny-lowcost.h"
#define  EM_PRODUCT_MODEL_ID    "LC"
#else
#error not one of EM_PRODUCT_{COINCELL,EMBC02,EMBC03,TINY,LOWCOST}
#endif


/**
 * CONFIGURATION ERROR CHECKING
 *
 * Detect missing and over-specified options.
 */

#if (COINSTANDARD && (!CAPABILITY_EMBEACON || !CAPABILITY_IDDATA_BEACON))
#error COINSTANDARD must include emBeacon and iddata beacon compiled
#endif
#if CLOCKRC_2MHZ  && CLOCKRC_15MHZ
#error only one of CLOCKRC_2MHZ  & CLOCKRC_15MHZ can be defined
#endif
#if !(CLOCKRC_2MHZ  || CLOCKRC_15MHZ)
#error one of CLOCKRC_2MHZ  & CLOCKRC_15MHZ must be defined
#endif

#endif  // _CONFIG_H
