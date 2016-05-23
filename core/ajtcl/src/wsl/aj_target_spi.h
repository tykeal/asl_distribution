/**
 * @file Platform specific function declarations that must be defined per platform port
 */
/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Contributed by Qualcomm Connected Experiences, Inc.,
 *    with authorization from the AllSeen Alliance, Inc.
 *    
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *    
 *        http://www.apache.org/licenses/LICENSE-2.0
 *    
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *    
 *    Pursuant to Section 1 of the License, the work of authorship constituting
 *    a Work and any Contribution incorporated in the Work shall mean only that
 *    Contributor's code submissions authored by that Contributor.  Any rights
 *    granted under the License are conditioned upon acceptance of these
 *    clarifications.
 ******************************************************************************/

#ifndef AJ_BSP_H_
#define AJ_BSP_H_

#include <ajtcl/aj_target.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This file contains the layer between alljoyn and platform specific code.
 * All the functions in this header need to be implemented in the platform
 * folder for example 'due'.
 */

/*
 * This function should include any initialization that needs to be done
 * for the specific platform. (Clock, UART, SPI, GPIO etc.)
 */
void AJ_PlatformInit(void);

/**
 * Platform specific SPI write function. This function write 1 byte of data to the SPI
 * peripheral.
 *
 * @param spi_device    The SPI device to write to (on the FRDM platform this has no effect)
 * @param byte          Byte of data to write to SPI
 * @param pcs           Chip Select device your writing to (on the FRDM platform this has no effect)
 * @param cont          Signals whether or not to assert/de-assert chip select to end the transfer
 *
 * @return              SPI_OK on success, SPI_ERR upon error
 */
aj_spi_status AJ_SPI_WRITE(uint8_t* spi_device, uint8_t byte, uint8_t pcs, uint8_t cont);

/**
 * Platform specific SPI read function. Read 1 byte of data from the SPI peripheral
 *
 * @param spi_device    The SPI device to read from (on the FRDM platform this has no effect)
 * @param data          Pointer to a buffer to read into
 * @param pcs           Chip select device to read from (on the FRDM platform this has no effect)
 */
aj_spi_status AJ_SPI_READ(uint8_t* spi_device, uint8_t* data, uint8_t pcs);

/*
 * This function should be implemented on a specific platform to initialize
 * the SPI hardware
 */
void AJ_WSL_SPI_InitializeSPIController(void);
/*
 * This function should be implemented on a specific platform to shutdown
 * the SPI hardware
 */
void AJ_WSL_SPI_ShutdownSPIController(void);
/*
 * This function should be implemented on a specific platform as the
 * SPI interrupt handler
 */
void AJ_WSL_SPI_ISR(void);

void AJ_WSL_SPI_CHIP_SPI_ISR(uint32_t id, uint32_t mask);
AJ_Status AJ_WSL_SPI_DMATransfer(uint8_t* buffer, uint16_t len, uint8_t direction);

#ifdef __cplusplus
}
#endif

#endif /* AJ_BSP_H_ */
