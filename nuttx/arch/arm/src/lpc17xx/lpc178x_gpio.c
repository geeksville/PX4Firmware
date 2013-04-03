/****************************************************************************
 * arch/arm/src/lpc17xx/lpc178x_gpio.c
 *
 *   Copyright (C) 2010-2011, 2013 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *           With LPC178x extensions from Rommel Marcelo
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <debug.h>

#include <arch/irq.h>

#include "up_arch.h"
#include "chip.h"
#include "lpc17_gpio.h"

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Default input pin configuration */

#define DEFAULT_INPUT (GPIO_INPUT|GPIO_PULLUP)

/****************************************************************************
 * Private Types
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

/****************************************************************************
 * Public Data
 ****************************************************************************/
/* These tables have global scope because they are also used in
 * lpc17_gpiodbg.c
 */

/* We have to remember the configured interrupt setting.. PINs are not
 * actually set up to interrupt until the interrupt is enabled.
 */

#ifdef CONFIG_GPIO_IRQ
uint64_t g_intedge0;
uint64_t g_intedge2;
#endif

/* FIO register base addresses */

const uint32_t g_fiobase[GPIO_NPORTS] =
{
  LPC17_FIO0_BASE,
  LPC17_FIO1_BASE,
  LPC17_FIO2_BASE,
  LPC17_FIO3_BASE,
  LPC17_FIO4_BASE
#if GPIO_NPORTS > 5
  , LPC17_FIO5_BASE
#endif
};

/* Port 0 and Port 2 can provide a single interrupt for any combination of
 * port pins
 */

const uint32_t g_intbase[GPIO_NPORTS] =
{
  LPC17_GPIOINT0_BASE,
  0,
  LPC17_GPIOINT2_BASE,
  0,
  0
#if GPIO_NPORTS > 5
  , 0
#endif
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: lpc17_configiocon
 *
 * Description:
 *   Set the LPC178x IOCON register
 *
 *   Type D: FUNC, MODE, HYS, INV, SLEW, OD             -
 *   Type A: FUNC, MODE, INV, ADMODE, FILTER, OD, DACEN -P0[12:13,23:26],P1[30:31]
 *   Type U: FUNC                                       -P0[29:31]
 *   Type I: FUNC, INV, HS, HIDRIVE                     -P0[27:28], P5[2:3]
 *   Type W: FUNC, MODE, HYS, INV, FILTER, SLEW, OD     -P0[7:9]
 *
 ****************************************************************************/

static int lpc17_configiocon(unsigned int port, unsigned int pin,
                             unsigned int value)
{
  uint32_t regaddr;
  uint32_t regval;
  uint32_t typemask = GPIO_IOCON_TYPE_D_MASK;

  /* Select the mask based on pin usage */

  switch (port)
    {
      case 0:
        switch (pin)
          {
            case 7:
            case 8:
            case 9:
              typemask = GPIO_IOCON_TYPE_W_MASK;
              break;

            case 12:
            case 13:
            case 23:
            case 24:
            case 25:
            case 26:
              typemask = GPIO_IOCON_TYPE_A_MASK;
              break;

            case 27:
            case 28:
              typemask = GPIO_IOCON_TYPE_I_MASK;
              break;

            case 29:
            case 30:
            case 31:
              typemask = GPIO_IOCON_TYPE_U_MASK;
              break;

            default:
                break;
          }
        break;

      case 1:
        switch (pin)
          {
            case 30:
            case 31:
              typemask = GPIO_IOCON_TYPE_A_MASK;
              break;

            default:
              break;
          }
        break;

      case 5:
        switch (pin)
          {
            case 2:
            case 3:
              typemask = GPIO_IOCON_TYPE_I_MASK;
              break;

            default:
              break;
          }
        break;

      default:
        break;
    }

  regaddr = LPC17_IOCON_P(port, pin);
  regval  = getreg32(regaddr);
  regval |= value;
  regval &= typemask;
  putreg32(regval, regaddr);

  return OK;
}

/****************************************************************************
 * Name: lpc17_setintedge
 *
 * Description:
 *  Remember the configured interrupt edge.  We can't actually enable the
 *  the edge interrupts until the called calls IRQ enabled function.
 *
 ****************************************************************************/

#ifdef CONFIG_GPIO_IRQ
static void lpc17_setintedge(unsigned int port, unsigned int pin,
                             unsigned int value)
{
  uint64_t *intedge;
  unsigned int shift;

  /* Which word to we use? */

  if (port == 0)
    {
      intedge = &g_intedge0;
    }
  else if (port == 2)
    {
      intedge  = &g_intedge2;
    }
  else
    {
      return;
    }

  /* Set the requested value in the PINSEL register */

  shift     = pin << 1;
  *intedge &= ~((uint64_t)3     << shift);
  *intedge |=  ((uint64_t)value << shift);
}
#endif /* CONFIG_GPIO_IRQ */

/****************************************************************************
 * Name: lpc17_configinput
 *
 * Description:
 *   Configure a GPIO inpue pin based on bit-encoded description of the pin.
 *
 ****************************************************************************/

static inline int lpc17_configinput(lpc17_pinset_t cfgset, unsigned int port, unsigned int pin)
{
  uint32_t regval;
  uint32_t fiobase;
  uint32_t intbase;
  uint32_t pinmask = (1 << pin);

  /* Set up FIO registers */

  fiobase = g_fiobase[port];

  /* Set as input */

  regval = getreg32(fiobase + LPC17_FIO_DIR_OFFSET);
  regval &= ~pinmask;
  putreg32(regval, fiobase + LPC17_FIO_DIR_OFFSET);

  /* Set up interrupt registers */

  intbase = g_intbase[port];
  if (intbase != 0)
    {
      /* Disable any rising edge interrupts */

      regval = getreg32(intbase + LPC17_GPIOINT_INTENR_OFFSET);
      regval &= ~pinmask;
      putreg32(regval, intbase + LPC17_GPIOINT_INTENR_OFFSET);

      /* Disable any falling edge interrupts */

      regval = getreg32(intbase + LPC17_GPIOINT_INTENF_OFFSET);
      regval &= ~pinmask;
      putreg32(regval, intbase + LPC17_GPIOINT_INTENF_OFFSET);

      /* Forget about any falling/rising edge interrupt enabled */

#ifdef CONFIG_GPIO_IRQ
      lpc17_setintedge(port, pin, 0);
#endif
    }

  /* Set up PINSEL registers */
  /* Configure the pin as a GPIO.  Clear opendrain, input inversion,
   * hysteris, slew.  Set analog pins as digital.
   */

  regval = IOCON_FUNC_GPIO;

  /* Set pull-up mode.  Isolate the field from the cfgset and move it
   * into the correct position in the register value.
   */

  regval |= (((cfgset & GPIO_PUMODE_MASK) >> GPIO_PUMODE_SHIFT) << IOCON_MODE_SHIFT);

  /* Select input polarity */

  if ((cfgset & GPIO_INVERT) != 0)
  {
    regval |= IOCON_INV_MASK;
  }

  /* Select hysteresis enable */

  if ((cfgset & GPIO_HYSTERESIS) != 0)
  {
    regval |= IOCON_HYS_MASK;
  }

  /* Set IOCON register */

  lpc17_configiocon(port, pin, regval);

  return OK;
}

/****************************************************************************
 * Name: lpc17_configinterrupt
 *
 * Description:
 *   Configure a GPIO interrupt pin based on bit-encoded description of the pin.
 *
 ****************************************************************************/

static inline int lpc17_configinterrupt(lpc17_pinset_t cfgset, unsigned int port,
                                        unsigned int pin)
{
  /* First, configure the port as a generic input so that we have a known
   * starting point and consistent behavior during the re-configuration.
   */

  (void)lpc17_configinput(cfgset, port, pin);

  /* Then just remember the rising/falling edge interrupt enabled */

  DEBUGASSERT(port == 0 || port == 2);
#ifdef CONFIG_GPIO_IRQ
  lpc17_setintedge(port, pin, (cfgset & GPIO_EDGE_MASK) >> GPIO_EDGE_SHIFT);
#endif
  return OK;
}

/****************************************************************************
 * Name: lpc17_configoutput
 *
 * Description:
 *   Configure a GPIO output pin based on bit-encoded description of the pin.
 *
 ****************************************************************************/

static inline int lpc17_configoutput(lpc17_pinset_t cfgset, unsigned int port,
                                     unsigned int pin)
{
  uint32_t fiobase;
  uint32_t regval;

  /* First, configure the port as a generic input so that we have a known
   * starting point and consistent behavior during the re-configuration.
   */

  (void)lpc17_configinput(DEFAULT_INPUT, port, pin);

  /* Now, reconfigure the pin as an output */

  fiobase = g_fiobase[port];
  regval  = getreg32(fiobase + LPC17_FIO_DIR_OFFSET);
  regval |= (1 << pin);
  putreg32(regval, fiobase + LPC17_FIO_DIR_OFFSET);

  /* Configure the pin as a GPIO.  Clear opendrain, input inversion,
   * hysteris, slew.  Set analog pins as digital.
   */

  regval = IOCON_FUNC_GPIO;

  /* Select open drain output */

  if ((cfgset & GPIO_OPEN_DRAIN) != 0)
    {
      regval |= IOCON_OD_MASK;
    }

  /* Select slew output */

  if ((cfgset & GPIO_SLEW) != 0)
    {
      regval |= IOCON_SLEW_MASK;
    }

  /* Set pull-up mode.  Isolate the field from the cfgset and move it
   * into the correct position in the register value.
   */

  regval |= (((cfgset & GPIO_PUMODE_MASK) >> GPIO_PUMODE_SHIFT) << IOCON_MODE_SHIFT);

  /* Set IOCON register */

  lpc17_configiocon(port, pin, regval);

  /* Set the initial value of the output */

  lpc17_gpiowrite(cfgset, ((cfgset & GPIO_VALUE) != GPIO_VALUE_ZERO));
  return OK;
}

/****************************************************************************
 * Name: lpc17_configalternate
 *
 * Description:
 *   Configure a GPIO alternate function pin based on bit-encoded description
 *   of the pin.
 *
 ****************************************************************************/

static int lpc17_configalternate(lpc17_pinset_t cfgset, unsigned int port,
                                 unsigned int pin, uint32_t alt)
{
  uint32_t regval;

  /* First, configure the port as an input so that we have a known
   * starting point and consistent behavior during the re-configuration.
   */

  (void)lpc17_configinput(DEFAULT_INPUT, port, pin);

  /* Select the alternate pin */

  regval = (alt & IOCON_FUNC_MASK);

  /* Select analog mode */

  if ((cfgset & GPIO_ADMODE) != 0)
  {
    regval |= IOCON_ADMODE_MASK;
  }

  /* Set pull-up mode.  Isolate the field from the cfgset and move it
   * into the correct position in the register value.
   */

  regval |= (((cfgset & GPIO_PUMODE_MASK) >> GPIO_PUMODE_SHIFT) << IOCON_MODE_SHIFT);

  /* Select open drain output */

  if ((cfgset & GPIO_OPEN_DRAIN) != 0)
    {
      regval |= IOCON_OD_MASK;
    }

  /* Set IOCON register */

  lpc17_configiocon(port, pin, regval);

  return OK;
}

/****************************************************************************
 * Global Functions
 ****************************************************************************/

/****************************************************************************
 * Name: lpc17_configgpio
 *
 * Description:
 *   Configure a GPIO pin based on bit-encoded description of the pin.
 *
 ****************************************************************************/

int lpc17_configgpio(lpc17_pinset_t cfgset)
{
  unsigned int port;
  unsigned int pin;
  int ret = -EINVAL;

  /* Verify that this hardware supports the select GPIO port */

  port = (cfgset & GPIO_PORT_MASK) >> GPIO_PORT_SHIFT;
  if (port < GPIO_NPORTS)
    {
      /* Get the pin number and select the port configuration register for that pin */

      pin = (cfgset & GPIO_PIN_MASK) >> GPIO_PIN_SHIFT;

      /* Handle according to pin function */

      switch (cfgset & GPIO_FUNC_MASK)
        {
        case GPIO_INPUT:   /* GPIO input pin */
          ret = lpc17_configinput(cfgset, port, pin);
          break;

        case GPIO_INTFE:   /* GPIO interrupt falling edge */
        case GPIO_INTRE:   /* GPIO interrupt rising edge */
        case GPIO_INTBOTH: /* GPIO interrupt both edges */
          ret = lpc17_configinterrupt(cfgset, port, pin);
          break;

        case GPIO_OUTPUT:  /* GPIO outpout pin */
          ret = lpc17_configoutput(cfgset, port, pin);
          break;

        case GPIO_ALT1:    /* Alternate function 1 */
          ret = lpc17_configalternate(cfgset, port, pin, IOCON_FUNC_ALT1);
          break;

        case GPIO_ALT2:    /* Alternate function 2 */
          ret = lpc17_configalternate(cfgset, port, pin, IOCON_FUNC_ALT2);
          break;

        case GPIO_ALT3:    /* Alternate function 3 */
          ret = lpc17_configalternate(cfgset, port, pin, IOCON_FUNC_ALT3);
          break;

        case GPIO_ALT4:    /* Alternate function 4 */
          ret = lpc17_configalternate(cfgset, port, pin, IOCON_FUNC_ALT4);
          break;

        case GPIO_ALT5:    /* Alternate function 5 */
          ret = lpc17_configalternate(cfgset, port, pin, IOCON_FUNC_ALT5);
          break;

        case GPIO_ALT6:    /* Alternate function 6 */
          ret = lpc17_configalternate(cfgset, port, pin, IOCON_FUNC_ALT6);
          break;

        case GPIO_ALT7:    /* Alternate function 7 */
          ret = lpc17_configalternate(cfgset, port, pin, IOCON_FUNC_ALT7);
          break;

        default:
          break;
        }
    }

  return ret;
}

/****************************************************************************
 * Name: lpc17_gpiowrite
 *
 * Description:
 *   Write one or zero to the selected GPIO pin
 *
 ****************************************************************************/

void lpc17_gpiowrite(lpc17_pinset_t pinset, bool value)
{
  uint32_t fiobase;
  uint32_t offset;
  unsigned int port;
  unsigned int pin;

  port = (pinset & GPIO_PORT_MASK) >> GPIO_PORT_SHIFT;
  if (port < GPIO_NPORTS)
    {
      /* Get the port base address */

      fiobase = g_fiobase[port];

      /* Get the pin number  */

      pin = (pinset & GPIO_PIN_MASK) >> GPIO_PIN_SHIFT;

      /* Set or clear the output on the pin */

      if (value)
        {
          offset = LPC17_FIO_SET_OFFSET;
        }
      else
        {
          offset = LPC17_FIO_CLR_OFFSET;
        }

      putreg32((1 << pin), fiobase + offset);
    }
}

/****************************************************************************
 * Name: lpc17_gpioread
 *
 * Description:
 *   Read one or zero from the selected GPIO pin
 *
 ****************************************************************************/

bool lpc17_gpioread(lpc17_pinset_t pinset)
{
  uint32_t fiobase;
  unsigned int port;
  unsigned int pin;

  port = (pinset & GPIO_PORT_MASK) >> GPIO_PORT_SHIFT;
  if (port < GPIO_NPORTS)
    {
      /* Get the port base address */

      fiobase = g_fiobase[port];

      /* Get the pin number and return the input state of that pin */

      pin = (pinset & GPIO_PIN_MASK) >> GPIO_PIN_SHIFT;
      return ((getreg32(fiobase + LPC17_FIO_PIN_OFFSET) & (1 << pin)) != 0);
    }

  return false;
}
