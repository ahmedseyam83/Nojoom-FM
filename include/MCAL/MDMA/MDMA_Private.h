/*
 * MDMA_Private.h
 *
 *  Created on: 15 May 2024
 *      Author: User
 */

#ifndef MDMA_PRIVATE_H_
#define MDMA_PRIVATE_H_

#define DMA1_BASE           0x40026000
#define DMA2_BASE           0x40026400


/****************************************************************************/
/*						REGISTERS STRUCTURE									*/
/****************************************************************************/

typedef struct
{
  u32 CR;
  u32 NDTR;
  u32 PAR;
  u32 M0AR;
  u32 M1AR;
  u32 FCR;
} DMA_Stream_t;

typedef struct
{
  u32 LISR;
  u32 HISR;
  u32 LIFCR;
  u32 HIFCR;
  DMA_Stream_t DMA_STREAM[8];
} DMA_t;


#define DMA1                ((DMA_t *) DMA1_BASE)
#define DMA2                ((DMA_t *) DMA2_BASE)

/********************  Bits definition for DMA_SxCR register  *****************/
#define DMA_SxCR_CHSEL						 25
#define DMA_SxCR_MBURST						 23
#define DMA_SxCR_PBURST						 21
#define DMA_SxCR_CT							 19
#define DMA_SxCR_DBM						 18
#define DMA_SxCR_PL							 16
#define DMA_SxCR_PINCOS						 15
#define DMA_SxCR_MSIZE						 13
#define DMA_SxCR_PSIZE						 11
#define DMA_SxCR_MINC						 10
#define DMA_SxCR_PINC						 9
#define DMA_SxCR_CIRC						 8
#define DMA_SxCR_DIR                         6
#define DMA_SxCR_PFCTRL                      5
#define DMA_SxCR_TCIE                        4
#define DMA_SxCR_HTIE                        3
#define DMA_SxCR_TEIE                        2
#define DMA_SxCR_DMEIE                       1
#define DMA_SxCR_EN                          0

/********************  Bits definition for DMA_SxFCR register  ****************/
#define DMA_SxFCR_FEIE                       7
#define DMA_SxFCR_FS                         3
#define DMA_SxFCR_DMDIS                      2
#define DMA_SxFCR_FTH                        0


/********************  Bits definition for DMA_LISR register  *****************/
#define DMA_LISR_TCIF3                       27
#define DMA_LISR_HTIF3                       26
#define DMA_LISR_TEIF3                       25
#define DMA_LISR_DMEIF3                      24
#define DMA_LISR_FEIF3                       22
#define DMA_LISR_TCIF2                       21
#define DMA_LISR_HTIF2                       20
#define DMA_LISR_TEIF2                       19
#define DMA_LISR_DMEIF2                      18
#define DMA_LISR_FEIF2                       16
#define DMA_LISR_TCIF1                       11
#define DMA_LISR_HTIF1                       10
#define DMA_LISR_TEIF1                       9
#define DMA_LISR_DMEIF1                      8
#define DMA_LISR_FEIF1                       6
#define DMA_LISR_TCIF0                       5
#define DMA_LISR_HTIF0                       4
#define DMA_LISR_TEIF0                       3
#define DMA_LISR_DMEIF0                      2
#define DMA_LISR_FEIF0                       0

/********************  Bits definition for DMA_HISR register  *****************/
#define DMA_HISR_TCIF7                       27
#define DMA_HISR_HTIF7                       26
#define DMA_HISR_TEIF7                       25
#define DMA_HISR_DMEIF7                      24
#define DMA_HISR_FEIF7                       22
#define DMA_HISR_TCIF6                       21
#define DMA_HISR_HTIF6                       20
#define DMA_HISR_TEIF6                       19
#define DMA_HISR_DMEIF6                      18
#define DMA_HISR_FEIF6                       16
#define DMA_HISR_TCIF5                       11
#define DMA_HISR_HTIF5                       10
#define DMA_HISR_TEIF5                       9
#define DMA_HISR_DMEIF5                      8
#define DMA_HISR_FEIF5                       6
#define DMA_HISR_TCIF4                       5
#define DMA_HISR_HTIF4                       4
#define DMA_HISR_TEIF4                       3
#define DMA_HISR_DMEIF4                      2
#define DMA_HISR_FEIF4                       0

/********************  Bits definition for DMA_LIFCR register  ****************/
#define DMA_LIFCR_CTCIF3                     27
#define DMA_LIFCR_CHTIF3                     26
#define DMA_LIFCR_CTEIF3                     25
#define DMA_LIFCR_CDMEIF3                    24
#define DMA_LIFCR_CFEIF3                     22
#define DMA_LIFCR_CTCIF2                     21
#define DMA_LIFCR_CHTIF2                     20
#define DMA_LIFCR_CTEIF2                     19
#define DMA_LIFCR_CDMEIF2                    18
#define DMA_LIFCR_CFEIF2                     16
#define DMA_LIFCR_CTCIF1                     11
#define DMA_LIFCR_CHTIF1                     10
#define DMA_LIFCR_CTEIF1                     9
#define DMA_LIFCR_CDMEIF1                    8
#define DMA_LIFCR_CFEIF1                     6
#define DMA_LIFCR_CTCIF0                     5
#define DMA_LIFCR_CHTIF0                     4
#define DMA_LIFCR_CTEIF0                     3
#define DMA_LIFCR_CDMEIF0                    2
#define DMA_LIFCR_CFEIF0                     0

/********************  Bits definition for DMA_HIFCR  register  ****************/
#define DMA_HIFCR_CTCIF7                     27
#define DMA_HIFCR_CHTIF7                     26
#define DMA_HIFCR_CTEIF7                     25
#define DMA_HIFCR_CDMEIF7                    24
#define DMA_HIFCR_CFEIF7                     22
#define DMA_HIFCR_CTCIF6                     21
#define DMA_HIFCR_CHTIF6                     20
#define DMA_HIFCR_CTEIF6                     19
#define DMA_HIFCR_CDMEIF6                    18
#define DMA_HIFCR_CFEIF6                     16
#define DMA_HIFCR_CTCIF5                     11
#define DMA_HIFCR_CHTIF5                     10
#define DMA_HIFCR_CTEIF5                     9
#define DMA_HIFCR_CDMEIF5                    8
#define DMA_HIFCR_CFEIF5                     6
#define DMA_HIFCR_CTCIF4                     5
#define DMA_HIFCR_CHTIF4                     4
#define DMA_HIFCR_CTEIF4                     3
#define DMA_HIFCR_CDMEIF4                    2
#define DMA_HIFCR_CFEIF4                     0


/********************  Private Macros  ****************/

#define DMA_DISABLED    1
#define DMA_ENABLED 	2


#endif /* MDMA_PRIVATE_H_ */
