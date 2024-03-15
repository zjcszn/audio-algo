/**
  @page X-CUBE-OPUS Opus evaluation and profiling software expansion for STM32Cube

  @verbatim
  ******************************************************************************
  * @file    OpusProfilingTool/readme.txt
  * @author  SRA
  * @brief   Getting started with the X-CUBE-OPUS audio codec evaluation and 
  *	     profiling software expansion for STM32Cube 
  ******************************************************************************
  *
  * Copyright (c) 2020 STMicroelectronics. All rights reserved.
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0094, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                               www.st.com/SLA0094
  *
  ******************************************************************************
   @endverbatim

@par Example Description

The X-CUBE-OPUS expansion software package for STM32Cube runs on different STM32
family and includes a firmware example that allows to easily configure and profile 
Opus encoder and decoder. 
The expansion is built on STM32Cube software technology to ease portability across 
different STM32 microcontrollers. The software comes with a sample implementation
of the drivers running on NUCLEO-F413ZH, NUCLEO-H743ZI, NUCLEO-F746ZG, NUCLEO-L552ZE-Q 
or P-NUCLEO-WB55 development board.
The package provides a python application to be used together with the STM32 example
to create a point to point bidirectional communication. The SW allows the user to 
choose each Opus settings, with an intuitive GUI, select different audio input file 
for profiling test and receive back results and encode/decode data.
The two nodes (host with python app and STM32) communicate through the ST-Link Virtual
COM port with a custom protocol.
The X-CUBE-OPUS expansion software package allows the user to evaluate Opus performance
depending on his target application, facilitating the choice of the correct STM32 and 
easily integrate the audio codec. 


@par Directory contents

  - inc/config.h			Header for opus codec configuration
  - inc/cube_hal.h			Include file for specific STM32
  - inc/opt_cmd_handlers.h		Header for opt_cmd_handlers.c module
  - inc/opus_interface.h		Header for opus_interface.c module  
  - inc/stcmdp_manager.h		Header for stcmdp_manager.c module
  - inc/stcmdp_opt_command.h		This file contains opt commands code
  - inc/stm32f7xx_hal_conf.h		HAL configuration file
  - inc/stm32xx_it.h			Header for stm32xx_it.c module
  - inc/uart_protocol_interface.h	Header for uart_protocol_interface.c module

  - src/main.c				This software provides an example application
					to demonstrate and profile Opus encoding and decoding
  - src/opt_cmd_handlers.c		This file provides a set of firmware functions
					to handle OPT custom commands
  - src/opus_interface.c		this file contains a set of API to easily use Opus
  - src/stcmdp_manager.c		STCmdP Protocol manager
  - src/stm32xx_it.c			Main Interrupt Service Routines
  - src/syscalls.c			System Workbench Minimal System calls 
  - src/system_stm32f7xx.c		CMSIS Cortex-M Device Peripheral Access Layer System Source File
  - src/uart_protocol_interface.c	This file contains the functions used for received 
					and send message via UART and to configure it


@par Hardware and Software environment

  - This example runs on STM32F413ZH, STM32F746ZG, STM32H743ZI, STM32L552ZE,
	STM32WB55RG devices.
  - This example has been tested with STMicroelectronics NUCLEO-F413ZH, NUCLEO-F746ZG, 
	NUCLEO-H743ZI, NUCLEO-L552ZE-Q and P-NUCLEO-WB55.
	It can be easily tailored to any other supported device and development board.
  - This example must be used in conjuction with OPT SW Control available in Utilities folder    


@par How to use it?

This package contains projects for 3 IDE: IAR, Keil and STM32CubeIDE
In order to make the program work, you must do the following:
 - WARNING: before opening the project with any toolchain be sure your folder
   installation path is not too in-depth since the toolchain may report errors
   after building.

For IAR:
 - Open IAR toolchain (this firmware has been successfully tested with
   Embedded Workbench v8.50.5).
 - Open the IAR project file EWARM\Project.eww
 - Rebuild all files and load your image into target memory.
 - Run the example.

For Keil
 - Open Keil uVision5 toolchain (this firmware has been 
   successfully tested with MDK-ARM Professional Version: 5.31).
 - Open the µVision project file MDK-ARM\Project.uvprojx
 - Rebuild all files and load your image into target memory.
 - Run the example.

For CubeIDE:
 - Open CubeIDE (this firmware has been successfully tested with CubeIDE Version 1.4).
 - Set the default workspace proposed by the IDE (please be sure that there are not spaces in the workspace path).
 - Press "File" -> "Import" -> "Existing Projects into Workspace"; press "Browse" in the "Select root directory" and choose the path where the CubeIDE project is located
 - Rebuild all files.
	
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
