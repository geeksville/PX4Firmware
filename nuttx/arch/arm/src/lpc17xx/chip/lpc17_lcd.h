/************************************************************************************************
 * arch/arm/src/lpc17xx/chip/lpc17_lcd.h
 *
 *   Copyright (C) 2013 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
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
 ************************************************************************************************/

#ifndef __ARCH_ARM_SRC_LPC17XX_CHIP_LPC17_LCD_H
#define __ARCH_ARM_SRC_LPC17XX_CHIP_LPC17_LCD_H

/************************************************************************************************
 * Included Files
 ************************************************************************************************/

#include <nuttx/config.h>

#include "chip.h"
#include "chip/lpc17_memorymap.h"

/************************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************************/

/* Register offsets *****************************************************************/

#define LPC17_LCD_TIMH_OFFSET           (0x0000) /* Horizontal Timing Control register */
#define LPC17_LCD_TIMV_OFFSET           (0x0004) /* Vertical Timing Control register */
#define LPC17_LCD_POL_OFFSET            (0x0008) /* Clock & Signal Polarity Control register */
#define LPC17_LCD_LE_OFFSET             (0x000c) /* Line End Control register */
#define LPC17_LCD_UPBASE_OFFSET         (0x0010) /* Upper Panel Frame Base Address register */
#define LPC17_LCD_LPBASE_OFFSET         (0x0014) /* Lower Panel Frame Base Address register */
#define LPC17_LCD_CTRL_OFFSET           (0x0018) /* LCD Control register */
#define LPC17_LCD_INTMSK_OFFSET         (0x001c) /* Interrupt Mask register */
#define LPC17_LCD_INTRAW_OFFSET         (0x0020) /* Raw Interrupt Status register */
#define LPC17_LCD_INTSTAT_OFFSET        (0x0024) /* Masked Interrupt Status register */
#define LPC17_LCD_INTCLR_OFFSET         (0x0028) /* Interrupt Clear register */
#define LPC17_LCD_UPCURR_OFFSET         (0x002c) /* Upper Panel Current Address Value register */
#define LPC17_LCD_LPCURR_OFFSET         (0x0030) /* Lower Panel Current Address Value register */
#define LPC17_LCD_PAL0_OFFSET           (0x0200) /* 256x16bit Color Palette  registers */
#define LPC17_LCD_PAL1_OFFSET           (0x0200) /*  */
***
#define LPC17_LCD_PAL127_OFFSET         (0x03fc) /*  */

#define LPC17_LCD_CRSR_IMG0_OFFSET      (0x0800) /* Cursor Image registers */
#define LPC17_LCD_CRSR_IMG1_OFFSET      (0x0800) /* Cursor Image registers */
***
#define LPC17_LCD_CRSR_IMG255_OFFSET    (0x0bfc) /* Cursor Image registers */

#define LPC17_LCD_CRSR_CRTL_OFFSET      (0x0c00) /* Cursor Control register */
#define LPC17_LCD_CRSR_CFG_OFFSET       (0x0c04) /* Cursor Configuration register */
#define LPC17_LCD_CRSR_PAL0_OFFSET      (0x0c08) /* Cursor Palette register 0 */
#define LPC17_LCD_CRSR_PAL1_OFFSET      (0x0c0c) /* Cursor Palette register 1 */
#define LPC17_LCD_CRSR_XY_OFFSET        (0x0c10) /* Cursor XY Position register */
#define LPC17_LCD_CRSR_CLIP_OFFSET      (0x0c14) /* Cursor Clip Position register */
#define LPC17_LCD_CRSR_INTMSK_OFFSET    (0x0c20) /* Cursor Interrupt Mask regsiter */
#define LPC17_LCD_CRSR_INTCLR_OFFSET    (0x0c24) /* Cursor Interrupt Clear register */
#define LPC17_LCD_CRSR_INTRAW_OFFSET    (0x0c28) /* Cursor Raw Interrupt Status register */
#define LPC17_LCD_CRSR_INTSTAT_OFFSET   (0x0c2c) /* Cursor Masked Interrupt Status register */

/* Register Addresses */

#define LPC17_LCD_TIMH                  (LPC17_LCD_BASE+LPC17_LCD_TIMH_OFFSET)
#define LPC17_LCD_TIMV                  (LPC17_LCD_BASE+LPC17_LCD_TIMV_OFFSET)
#define LPC17_LCD_POL                   (LPC17_LCD_BASE+LPC17_LCD_POL_OFFSET)
#define LPC17_LCD_LE_OFFSET             (LPC17_LCD_BASE+LPC17_LCD_LE_OFFSET)
#define LPC17_LCD_UPBASE_OFFSET         (LPC17_LCD_BASE+LPC17_LCD_UPBASE_OFFSET)
#define LPC17_LCD_LPBASE_OFFSET         (LPC17_LCD_BASE+LPC17_LCD_LPBASE_OFFSET)
#define LPC17_LCD_CTRL_OFFSET           (LPC17_LCD_BASE+LPC17_LCD_CTRL_OFFSET)
#define LPC17_LCD_INTMSK_OFFSET         (LPC17_LCD_BASE+LPC17_LCD_INTMSK_OFFSET)
#define LPC17_LCD_INTRAW_OFFSET         (LPC17_LCD_BASE+LPC17_LCD_INTRAW_OFFSET)
#define LPC17_LCD_INTSTAT_OFFSET        (LPC17_LCD_BASE+LPC17_LCD_INTSTAT_OFFSET)
#define LPC17_LCD_INTCLR_OFFSET         (LPC17_LCD_BASE+ LPC17_LCD_INTCLR_OFFSET)
#define LPC17_LCD_UPCURR_OFFSET         (LPC17_LCD_BASE+LPC17_LCD_UPCURR_OFFSET)
#define LPC17_LCD_LPCURR_OFFSET         (LPC17_LCD_BASE+LPC17_LCD_LPCURR_OFFSET)
***
#define LPC17_LCD_PAL0_OFFSET           (LPC17_LCD_BASE+LPC17_LCD_PAL0_OFFSET)
#define LPC17_LCD_PAL1_OFFSET           (LPC17_LCD_BASE+LPC17_LCD_PAL1_OFFSET)
#define LPC17_LCD_PAL127_OFFSET         (LPC17_LCD_BASE+LPC17_LCD_PAL127_OFFSET)
***
#define LPC17_LCD_CRSR_IMG0             (LPC17_LCD_BASE+LPC17_LCD_CRSR_IMG0_OFFSET)
#define LPC17_LCD_CRSR_IMG1             (LPC17_LCD_BASE+LPC17_LCD_CRSR_IMG1_OFFSET)
#define LPC17_LCD_CRSR_IMG255           (LPC17_LCD_BASE+LPC17_LCD_CRSR_IMG255_OFFSET)

#define LPC17_LCD_CRSR_CRTL             (LPC17_LCD_BASE+LPC17_LCD_CRSR_CRTL_OFFSET)
#define LPC17_LCD_CRSR_CFG              (LPC17_LCD_BASE+LPC17_LCD_CRSR_CFG_OFFSET)
#define LPC17_LCD_CRSR_PAL0             (LPC17_LCD_BASE+LPC17_LCD_CRSR_PAL0_OFFSET)
#define LPC17_LCD_CRSR_PAL1             (LPC17_LCD_BASE+LPC17_LCD_CRSR_PAL1_OFFSET)
#define LPC17_LCD_CRSR_XY               (LPC17_LCD_BASE+LPC17_LCD_CRSR_XY_OFFSET)
#define LPC17_LCD_CRSR_CLIP             (LPC17_LCD_BASE+LPC17_LCD_CRSR_CLIP_OFFSET)
#define LPC17_LCD_CRSR_INTMSK           (LPC17_LCD_BASE+LPC17_LCD_CRSR_INTMSK_OFFSET)
#define LPC17_LCD_CRSR_INTCLR           (LPC17_LCD_BASE+LPC17_LCD_CRSR_INTCLR_OFFSET)
#define LPC17_LCD_CRSR_INTRAW           (LPC17_LCD_BASE+LPC17_LCD_CRSR_INTRAW_OFFSET)
#define LPC17_LCD_CRSR_INTSTAT          (LPC17_LCD_BASE+LPC17_LCD_CRSR_INTSTAT_OFFSET)

/* Register Bitfield Definitions */

/* LCD_TIMH - Horizontal Timing Register */

                                                /* Bits 0-1: Reserved */
#define LCD_TIMH_PPL_SHIFT              (2)     /* Bits 2-7: Pixels Per Line - 16-1024ppl */
#define LCD_TIMH_PPL_MASK               (0x3f << LCD_TIMH_PPL_SHIFT)
#define LCD_TIMH_HSW_SHIFT              (8)     /* Bits 8-15: Horizontal Sync Pulse Width */
#define LCD_TIMH_HWS_MASK               (0xff << LCD_TIMH_HSW_SHIFT)
#define LCD_TIMH_HFP_SHIFT              (16)    /* Bits 16-23: Horizontal Front Porch */
#define LCD_TIMH_HFP_MASK               (0xff << LCD_TIMH_HFP_SHIFT)
#define LCD_TIMH_HBP_SHIFT              (24)    /* Bits 24-31: Horizontal Back Porch */
#define LCD_TIMH_HBP_MASK               (0xff << LCD_TIMH_HBP_SHIFT)

/* LCD_TIMV - Vertical Timing Register */

#define LCD_TIMV_LPP_SHIFT              (0)     /* Bits 0-9: Lines Per Panel 1-1024 lpp*/
#define LCD_TIMV_LPP_MASK               (0x3ff << LCD_TIMV_LPP_SHIFT)
#define LCD_TIMV_VSW_SHIFT              (10)    /* Bits 10-15: Vertical Synch Pulse Width */
#define LCD_TIMV_VSW_MASK               (0x3f << LCD_TIMV_VSW_SHIFT)
#define LCD_TIMV_VFP_SHIFT              (16)    /* Bits 16-23: Vertical Front Porch */
#define LCD_TIMV_VFP_MASK               (0xff << LCD_TIMV_VFP_SHIFT)
#define LCD_TIMV_VBP_SHIFT              (24)    /* Bits 24-31: Vertical Back Porch */
#define LCD_TIMV_VBP_MASK               (0xff << LCD_TIMV_VBP_SHIFT)

/* LCD_POL - Clock and Signal Polarity Register */

#define LCD_POL_PCDLO_SHIFT             (0)     /* Bits 0-4: Lower 5 bits of panel clock divisor */
#define LCD_POL_PCDLO_MASK              (0x1f << LCD_POL_PCDLO_SHIFT)
#define LCD_POL_CLKSEL_SHIFT            (5)     /* Bit 5: Clock select- 0=CCLK, 1=LCD_CLKIN */
#define LCD_POL_CLKSEL_MASK             (1 << LCD_POL_CLKSEL_SHIFT)
#define LCD_POL_ACB_SHIFT               (6)     /* Bits 6-10: AC bias pin frequency */
#define LCD_POL_ACB_MASK                (0x1f << LCD_POL_ACB_SHIFT)
#define LCD_POL_IVS_SHIFT               (11)    /* Bit 11: Invert vertical sync */
#define LCD_POL_IVS_MASK                (1 << LCD_POL_IVS_SHIFT)
#define LCD_POL_IHS_SHIFT               (12)    /* Bit 12: Invert horizontal sync */
#define LCD_POL_IHS_MASK                (1 << LCD_POL_IHS_SHIFT)
#define LCD_POL_IPC_SHIFT               (13)    /* Bit 13: Invert panel clock */
#define LCD_POL_IPC_MASK                (1 << LCD_POL_IPC_SHIFT)
#define LCD_POL_IOE_SHIFT               (14)    /* Bit 14: Invert output enable */
#define LCD_POL_IOE_MASK                (1 << LCD_POL_IOE_SHIFT)
                                                /* Bit 15: Reserved */
#define LCD_POL_CPL_SHIFT               (16)    /* Bit 16-25: Clocks per line */
#define LCD_POL_CPL_MASK                (0x3ff << LCD_POL_CPL_SHIFT)
#define LCD_POL_BCD_SHIFT               (26)    /* Bit 26: Bypass pixel clock divider */
#define LCD_POL_BCD_MASK                (1 << LCD_POL_BCD_SHIFT)
#define LCD_POL_PCDHI_SHIFT             (27)    /* Bits 27-31: Upper 5 bits of panel clock divisor */
#define LCD_POL_PCDHI_MASK              (0x1f << LCD_POL_PCDHI_SHIFT)

/* LCD_LE - Line End Control Register */

#define LCD_LE_LED_SHIFT                (0)     /* Bits 0-6: Line End delay */
#define LCD_LE_LED_MASK                 (0x7f << LCD_LE_LED_SHIFT)
                                                /* Bits 7-15: Reserved */
#define LCD_LE_LEE_SHIFT                (16)    /* Bit16: LCD line end enable */
#define LCD_LE_LEE_MASK                 (1 << LCD_LE_LEE_SHIFT)
                                                /* Bit 17-31: Reserved */

/* LCD_UPBASE - Upper Panel Frame Base Address Register */
                                                /* Bits 0-2: Reserved */
#define LCD_UPBASE_LCDUPBASE_SHIFT      (3)     /* Bits 3-31: LCD upper panel base address */
#define LCD_UPBASE_LCDUPBASE_MASK       (0x1FFFFFFF << LCD_UPBASE_LCDUPBASE_SHIFT)

/* LCD_UPBASE - Lower Panel Frame Base Address Register */
                                                /* Bits 0-2: Reserved */
#define LCD_UPBASE_LCDLPBASE_SHIFT      (3)     /* Bits 3-31: LCD lower panel base address */
#define LCD_UPBASE_LCDLPBASE_MASK       (0x1FFFFFFF << LCD_UPBASE_LCDUPBASE_SHIFT)

/* LCD_CTRL - Controle Register */

#define LCD_CTRL_LCDEN_SHIFT            (0)     /* Bit 0: LCD enable control bit */
#define LCD_CTRL_LCDEN_MASK             (1 << LCD_CTRL_LCDEN_SHIFT)
#define LCD_CTRL_LCDBPP_SHIFT           (1)     /* Bits 1-3: LCD bits per pixel */
#define LCD_CTRL_LCDBPP_MASK            (7 << LCD_CTRL_LCDBPP_SHIFT)
#define LCD_CTRL_LCDBW_SHIFT            (4)     /* Bit 4: STN LCD monochrome/color selection */
#define LCD_CTRL_LCDBW_MASK             (1 << LCD_CTRL_LCDBW_SHIFT)
#define LCD_CTRL_LCDTFT_SHIFT           (5)     /* Bit 5: LCD TFT type selection */
#define LCD_CTRL_LCDTFT_MASK            (1 << LCD_CTRL_LCDTFT_SHIFT)
#define LCD_CTRL_LCDMONO8_SHIFT         (6)     /* Bit 6: Monochrome LCD interface bit */
#define LCD_CTRL_LCDMONO8_MASK          (1 << LCD_CTRL_LCDMONO8_SHIFT)
#define LCD_CTRL_LCDDUAL_SHIFT          (7)     /* Bit 7: Single or Dual LCD panel selection */
#define LCD_CTRL_LCDDUAL_MASK           (1 << LCD_CTRL_LCDDUAL_SHIFT)
#define LCD_CTRL_BGR_SHIFT              (8)     /* Bit 8: Color format */
#define LCD_CTRL_BGR_MASK               (1 << LCD_CTRL_BGR_SHIFT)
#define LCD_CTRL_BEBO_SHIFT             (9)     /* Bit 9:  Big-Endian Byte Order */
#define LCD_CTRL_BEBO_MASK              (1 << LCD_CTRL_BEBO_SHIFT)
#define LCD_CTRL_BEPO_SHIFT             (10)    /* Bit 10: Big-Endian Pixel Ordering */
#define LCD_CTRL_BEPO_MASK              (1 << LCD_CTRL_BEPO_SHIFT)
#define LCD_CTRL_LCDPWR_SHIFT           (11)    /* Bit 11: LCD Power enable */
#define LCD_CTRL_LCDPWR_MASK            (1 << LCD_CTRL_LCDPWR_SHIFT)
#define LCD_CTRL_LCDVCOMP_SHIFT         (12)    /* Bits 12-13: LCD Vertical compare interrupt */
#define LCD_CTRL_LCDVCOMP_MASK          (3 << LCD_CTRL_LCDVCOMP_SHIFT)
                                                /* Bits 14-15: Reserved */
#define LCD_CTRL_WATERMARK_SHIFT        (16)    /* Bit 16: LCD DMA FIFO watermark level */
#define LCD_CTRL_WATERMARK_MASK         (1 << LCD_CTRL_WATERMARK_SHIFT)
                                                /* Bits 17-31: Reserved */

/* LCD_INTMSK - Interrupt Mask Register */
                                                /* Bits 0: Reserved */
#define LCD_INTMSK_FUFIM_SHIFT          (1)     /* Bit 1: FIFO underflow interrupt enable */
#define LCD_INTMSK_FUFIM_MASK           (1 << LCD_INTMSK_FUFIM_SHIFT)
#define LCD_INTMSK_LNBUIM_SHIFT         (2)     /* Bit 2: LCD next base address interrupt enable */
#define LCD_INTMSK_LNBUIM_MASK          (1 << LCD_INTMSK_LNBUIM_SHIFT)
#define LCD_INTMSK_VCOMPIM_SHIFT        (3)     /* Bit 3: Vertical compare interrupt enable */
#define LCD_INTMSK_VCOMPIM_MASK         (1 << LCD_INTMSK_VCOMPIM_SHIFT)
#define LCD_INTMSK_BERIM_SHIFT          (4)     /* Bit 4: AHB Master error interrupt enable */
#define LCD_INTMSK_BERIM_MASK           (1 << LCD_INTMSK_BERIM_SHIFT)
                                                /* Bits 5-31: Reserved */

/* LCD_INTRAW - Raw Interrupt Status Register */
                                                /* Bits 0: Reserved */
#define LCD_INTRAW_FUFRIS_SHIFT         (1)     /* Bit 1: FIFO Undeflow raw interrupt status */
#define LCD_INTRAW_FUFRIS_MASK          (1 << LCD_INTRAW_FUFRIS_SHIFT)
#define LCD_INTRAW_LNBURIS_SHIFT        (2)     /* Bit 2: LCD Next address base update intterupt */
#define LCD_INTRAW_LNBURIS_MASK         (1 << LCD_INTRAW_LNBURIS_SHIFT)
#define LCD_INTRAW_VCOMPRIS_SHIFT       (3)     /* Bit 3: Vertical compare interrupt status */
#define LCD_INTRAW_VCOMPRIS_MASK        (1 << LCD_INTRAW_VCOMPRIS_SHIFT)
#define LCD_INTRAW_BERRAW_SHIFT         (4)     /* Bit 4: AHB Master bus error interrupt status */
#define LCD_INTRAW_BERRAW_MASK          (1 << LCD_INTRAW_BERRAW_SHIFT)
                                                /* Bits 5-31: Reserved */

/* LCD_INTSTAT - Masked Interrupt Status Register */
                                                /* Bits 0: Reserved */
#define LCD_INTSTAT_FUFMIS_SHIFT        (1)     /* Bit 1: FIFO Undeflow raw interrupt status */
#define LCD_INTSTAT_FUFMIS_MASK         (1 << LCD_INTSTAT_FUFMIS_SHIFT)
#define LCD_INTSTAT_LNBUMIS_SHIFT       (2)     /* Bit 2: LCD Next address base update intterupt */
#define LCD_INTSTAT_LNBUMIS_MASK        (1 << LCD_INTSTAT_LNBUMIS_SHIFT)
#define LCD_INTSTAT_VCOMPMIS_SHIFT      (3)     /* Bit 3: Vertical compare interrupt status */
#define LCD_INTSTAT_VCOMPMIS_MASK       (1 << LCD_INTSTAT_VCOMPMIS_SHIFT)
#define LCD_INTSTAT_BERMIS_SHIFT        (4)     /* Bit 4: AHB Master bus error interrupt status */
#define LCD_INTSTAT_BERMIS_MASK         (1 << LCD_INTSTAT_BERMIS_SHIFT)
                                                /* Bits 15-31: Reserved */
/* LCD_INTCLR - Interrupt Clear Register */
                                                /* Bits 0: Reserved */
#define LCD_INTCLR_FUFIC_SHIFT          (1)     /* Bit 1: FIFO Undeflow raw interrupt clear */
#define LCD_INTCLR_FUFIC_MASK           (1 << LCD_INTCLR_FUFIC_SHIFT)
#define LCD_INTCLR_LNBUIC_SHIFT         (2)     /* Bit 2: LCD Next address base update intterupt */
#define LCD_INTCLR_LNBUIC_MASK          (1 << LCD_INTCLR_LNBUIC_SHIFT)
#define LCD_INTCLR_VCOMPIC_SHIFT        (3)     /* Bit 3: Vertical compare interrupt clear */
#define LCD_INTCLR_VCOMPIC_MASK         (1 << LCD_INTCLR_VCOMPIC_SHIFT)
#define LCD_INTCLR_BERIC_SHIFT          (4)     /* Bit 4: AHB Master bus error interrupt clear */
#define LCD_INTCLR_BERIC_MASK           (1 << LCD_INTCLR_BERIC_SHIFT)
                                               /* Bits 15-31: Reserved */

/* Upper and Lower Panel Address register has no bitfields */
 /*
 *   Upper Panel Current Address register (LCDUPCURR)
 *   Lower Panel Current Address register (LCDLPCURR)
 */

/* LCD_PAL - Color Palette Register */

#define LCD_PAL_R04_0_SHIFT             (0)     /* Bits 0-4: Red palette data */
#define LCD_PAL_R04_0_MASK              (0x1f << LCD_PAL_R04_0_SHIFT)
#define LCD_PAL_G04_0_SHIFT             (5)     /* Bits 5-9: Green palette data */
#define LCD_PAL_G04_0_MASK              (0x1f << LCD_PAL_G04_0_SHIFT)
#define LCD_PAL_B04_0_SHIFT             (10)    /* Bits 10-14: Blue paletted data */
#define LCD_PAL_B04_0_MASK              (0x1f << LCD_PAL_B04_0_SHIFT)
#define LCD_PAL_I0_SHIFT                (15)    /* Bit 15: Intensity/Unused bit */
#define LCD_PAL_I0_MASK                 (1 << LCD_PAL_I0_SHIFT)
#define LCD_PAL_R14_0_SHIFT             (16)    /* Bit 16-20: Reda palette data */
#define LCD_PAL_R14_0_MASK              (0x1f << LCD_PAL_R14_0_SHIFT)
#define LCD_PAL_G14_0_SHIFT             (21)    /* Bit 21-25: Green palette data */
#define LCD_PAL_G14_0_MASK              (0x1f << LCD_PAL_G14_0_SHIFT)
#define LCD_PAL_B14_0_SHIFT             (26)    /* Bit 26-30: Blue palette data */
#define LCD_PAL_B14_0_MASK              (0x1f << LCD_PAL_B14_0_SHIFT)
#define LCD_PAL_I1_SHIFT                (31)    /* Bit 31: Intensity/Unused bit */
#define LCD_PAL_I1_MASK                 (1 << LCD_PAL_I1_SHIFT)

/* LCD_CRSR_IMG - Cursor Image Register - has no bitfields */
/* The 256 words of the cursor image register defines the appearance
 * of either one 64x64 cursor, or 4 32x32 cursors.
 */

/* LCD CRSR_CTRL - Cursor Control Register */

#define LCD_CRSR_CTRL_CRSON_SHIFT       (0)     /* Bit 0: Cursor enable */
#define LCD_CRSR_CTRL_CRSON_MASK        (1 << LCD_CRSR_CTRL_CRSON_SHIFT)
                                                /* Bit 1-3: Reserved */
#define LCD_CRSR_CTRL_CRSRNUM1_0_SHIFT  (4)     /* Bit 4-5: Cursor image number */
#define LCD_CRSR_CTRL_CRSRNUM1_0_MASK   (3 << LCD_CRSR_CTRL_CRSRNUM1_0_SHIFT)
                                                /* Bit 6-31: Reserved */
/* If the selected cursor is 32x32 */

#define LCD_CURSOR0                     (0)
#define LCD_CURSOR1                     (1)
#define LCD_CURSOR2                     (2)
#define LCD_CURSOR3                     (3)

/* LCD CRSR_CFG - Cursor Configuration Register */

#define LCD_CRSR_CFG_CRSRSIZE_SHIFT     (0)     /* Bit 0: Cursor size selection */
#define LCD_CRSR_CFG_CRSRSIZE_MASK      (1 << LCD_CRSR_CFG_CRSRSIZE_SHIFT)
#define LCD_CRSR_CFG_FRAMESYNC_SHIFT    (1)     /* Bit 1: Cursor frame sync type */
#define LCD_CRSR_CFG_FRAMESYNC_MASK     (1 << LCD_CRSR_CFG_FRAMESYNC_SHIFT)
                                                /* Bit 2-31: Reserved */
#define LCD_CURSOR_SIZE32               (0)     /* 32x32 */
#define LCD_CURSOR_SIZE64               (1)     /* 64x64 */
#define LCD_CURSOR_FRAMEASYNC           (0)     /* Cursor coordinates are asynchronous */
#define LCD_CURSOR_FRAMESYNC            (1)     /* coordinates are synchronize to framesync pulse */

/* LCD CRSR_PAL0 - Cursor Palette Register 0 */

#define LCD_CRSR_PAL0_RED_SHIFT         (0)     /* Bits 0-7: Red color componnent */
#define LCD_CRSR_PAL0_RED_MASK          (0xff << LCD_CRSR_PAL0_RED_SHIFT)
#define LCD_CRSR_PAL0_GREEN_SHIFT       (8)     /* Bits 8-15: Green color component */
#define LCD_CRSR_PAL0_GREEN_MASK        (0xff << LCD_CRSR_PAL0_GREEN_SHIFT)
#define LCD_CRSR_PAL0_BLUE_SHIFT        (16)    /* Bits 16-23: Blue color component */
#define LCD_CRSR_PAL0_BLUE_MASK         (0xff << LCD_CRSR_PAL0_BLUE_SHIFT)
                                                /* Bit 24-31: Reserved */
/* LCD CRSR_PAL1 - Cursor Palette Register 1 */

#define LCD_CRSR_PAL1_RED_SHIFT         (0)     /* Bits 0-7: Red color componnent */
#define LCD_CRSR_PAL1_RED_MASK          (0xff << LCD_CRSR_PAL1_RED_SHIFT)
#define LCD_CRSR_PAL1_GREEN_SHIFT       (8)     /* Bits 8-15: Green color component */
#define LCD_CRSR_PAL1_GREEN_MASK        (0xff << LCD_CRSR_PAL1_GREEN_SHIFT)
#define LCD_CRSR_PAL1_BLUE_SHIFT        (16)    /* Bits 16-23: Blue color component */
#define LCD_CRSR_PAL1_BLUE_MASK         (0xff << LCD_CRSR_PAL1_BLUE_SHIFT)
                                                /* Bit 24-31: Reserved */

/* LCD CRSR_XY - Cursor XY Position Register */

#define LCD_CRSR_CRSRX_SHIFT            (0)     /* Bits 0-9: X ordinate */
#define LCD_CRSR_CRSRX_MASK             (0x3ff << LCD_CRSR_CRSRX_SHIFT)
                                                /* Bit 10-15: Reserved */
#define LCD_CRSR_CRSRY_SHIFT            (16)    /* Bits 16-25: Y ordinate */
#define LCD_CRSR_CRSRY_MASK             (0x3ff << LCD_CRSR_CRSRY_SHIFT)
                                                /* Bit 26-31: Reserved */

/* LCD CRSR_CLIP - Cursor Clip Position Register */

#define LCD_CRSR_CRSRCLIPX_SHIFT        (0)     /* Bits 0-5: X clip position */
#define LCD_CRSR_CRSRCLIPX_MASK         (0x3f << LCD_CRSR_CRSRCLIPX_SHIFT)
                                                /* Bit 6-7: Reserved */
#define LCD_CRSR_CRSRCLIPY_SHIFT        (8)     /* Bits 8-13: Reserved */
#define LCD_CRSR_CRSRCLIPY_MASK         (0x3f << LCD_CRSR_CRSRCLIPY_SHIFT)
                                                /* Bit 14-31: Reserved */

/* LCD CRSR_INTMSK - Cursor Interrrupt Mask Register */

#define LCD_CRSR_INTMSK_CRSRIM_SHIFT    (0)     /* Bit 0: Cursor interrupt mask */
#define LCD_CRSR_INTMSK_CRSRIM_MASK     (1 << LCD_CRSR_INTMSK_CRSRIM_SHIFT)
                                                /* Bit 1-31: Reserved */

/* LCD CRSR_INTCLR - Cursor Interrrupt Clear Register */

#define LCD_CRSR_INTCLR_CRSRIC_SHIFT    (0)     /* Bit 0: Cursor interrupt clear */
#define LCD_CRSR_INTCLR_CRSRIC_MASK     (1 << LCD_CRSR_INTCLR_CRSRIC_SHIFT)
                                                /* Bit 1-31: Reserved */

/* LCD CRSR_INTRAW - Cursor Raw Interrrupt Status Register */

#define LCD_CRSR_INTRAW_CRSRRIS_SHIFT   (0)     /* Bit 0: Cursor raw interrupt status */
#define LCD_CRSR_INTRAW_CRSRRIS_MASK    (1 << LCD_CRSR_INTRAW_CRSRRIS_SHIFT)
                                                /* Bit 1-31: Reserved */

/* LCD CRSR_INTSTAT - Mask Interrrupt Status Register */

#define LCD_CRSR_INTSTAT_CRSRMIS_SHIFT  (0)     /* Bit 0: Cursor mask interrupt status */
#define LCD_CRSR_INTSTAT_CRSRMIS_MASK   (1 << LCD_CRSR_INTSTAT_CRSRMIS_SHIFT)
                                                /* Bit 1-31: Reserved */

/************************************************************************************************
 * Public Types
 ************************************************************************************************/

/************************************************************************************************
 * Public Data
 ************************************************************************************************/

/************************************************************************************************
 * Public Functions
 ************************************************************************************************/

#endif /* __ARCH_ARM_SRC_LPC17XX_CHIP_LPC17_LCD_H */
