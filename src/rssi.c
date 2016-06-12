/**
 ** ############################################################################
 **
 ** @file    rssi.c
 ** @brief   routines for handling the rssi power calibrations
 **
 ** Copyright (c) 2015 EM Microelectronic-US Inc. All rights reserved.
 ** Developed by Glacier River Design, LLC.
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
#include "Types.h"
#include "Macro.h"
#include "config.h"
#include "params.h"
#include "hci.h"
#include "hci_9301.h"
#include "beacon.h"
#include "rssi.h"
/*
 * @brief: Table of RSSI Values
 *
 * measured radiated power at 1 meter
 * really a signed integer 0xB0 =-80 0xC5=-59
 * value 
 */
static const UINT8 di07_RSSI[EM_RF_POWER_LEVEL_MAX_INDEX+1] = {0xB0,0xB3,0xB6,0xB9,0xBC,0xBF,0xC2,0xC5};
static const UINT8 di10_RSSI[EM_RF_POWER_LEVEL_MAX_INDEX+1] = {0xB0,0xB3,0xB6,0xB9,0xBF,0xC1,0xC3,0xC5};

/**
  * @brief meeasured ERP using the Apple Spec
 **/
//const UINT8 di07_measuredPower[EM_RF_POWER_LEVEL_MAX_INDEX+1] = {0xB0,0xB3,0xB6,0xB9,0xBC,0xBF,0xC2,0xC5};
//const UINT8 di10_measuredPower[EM_RF_POWER_LEVEL_MAX_INDEX+1] = {0xB0,0xB3,0xB6,0xB9,0xBF,0xC1,0xC3,0xC5};


UINT8* GetRssiTable()
{
   UINT8* value;
     if (EM9301_Rev == EM9301_REV_DI07)
      {
         value = (UINT8*)di07_RSSI;
      }
      else
      {
         // Other devices can default to this until we have more measured data
         value = (UINT8*)di10_RSSI;
      }
   return value;
}
UINT8 GetRssi(UINT8 powerIndex)
{
      if (powerIndex > EM_RF_POWER_LEVEL_MAX_INDEX)
      {
         powerIndex = EM_RF_POWER_LEVEL_MAX_INDEX;
      }
      return GetRssiTable()[powerIndex];
}
