/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'nios2_gen2_0' in SOPC Builder design 'platform'
 * SOPC Builder design path: C:/intelFPGA_lite/Proyectos/P1-SistemasOperativos/ProcQsys/platform.sopcinfo
 *
 * Generated: Wed Sep 27 15:35:41 CST 2023
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x00004020
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1c
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x00004020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 0
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 0
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 0
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_ICACHE_SIZE 0
#define ALT_CPU_INST_ADDR_WIDTH 0xf
#define ALT_CPU_NAME "nios2_gen2_0"
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x00004000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x00004020
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0x1c
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x00004020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 0
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 0
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE_LOG2 0
#define NIOS2_ICACHE_SIZE 0
#define NIOS2_INST_ADDR_WIDTH 0xf
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x00004000


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_NIOS2_GEN2


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone V"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/null"
#define ALT_STDERR_BASE 0x0
#define ALT_STDERR_DEV null
#define ALT_STDERR_TYPE ""
#define ALT_STDIN "/dev/null"
#define ALT_STDIN_BASE 0x0
#define ALT_STDIN_DEV null
#define ALT_STDIN_TYPE ""
#define ALT_STDOUT "/dev/null"
#define ALT_STDOUT_BASE 0x0
#define ALT_STDOUT_DEV null
#define ALT_STDOUT_TYPE ""
#define ALT_SYSTEM_NAME "platform"


/*
 * buttons_0 configuration
 *
 */

#define ALT_MODULE_CLASS_buttons_0 altera_avalon_pio
#define BUTTONS_0_BASE 0x6000
#define BUTTONS_0_BIT_CLEARING_EDGE_REGISTER 0
#define BUTTONS_0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define BUTTONS_0_CAPTURE 1
#define BUTTONS_0_DATA_WIDTH 4
#define BUTTONS_0_DO_TEST_BENCH_WIRING 0
#define BUTTONS_0_DRIVEN_SIM_VALUE 0
#define BUTTONS_0_EDGE_TYPE "RISING"
#define BUTTONS_0_FREQ 50000000
#define BUTTONS_0_HAS_IN 1
#define BUTTONS_0_HAS_OUT 0
#define BUTTONS_0_HAS_TRI 0
#define BUTTONS_0_IRQ 0
#define BUTTONS_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define BUTTONS_0_IRQ_TYPE "EDGE"
#define BUTTONS_0_NAME "/dev/buttons_0"
#define BUTTONS_0_RESET_VALUE 0
#define BUTTONS_0_SPAN 16
#define BUTTONS_0_TYPE "altera_avalon_pio"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 4
#define ALT_SYS_CLK none
#define ALT_TIMESTAMP_CLK none


/*
 * key_select_0 configuration
 *
 */

#define ALT_MODULE_CLASS_key_select_0 altera_avalon_pio
#define KEY_SELECT_0_BASE 0x6010
#define KEY_SELECT_0_BIT_CLEARING_EDGE_REGISTER 0
#define KEY_SELECT_0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define KEY_SELECT_0_CAPTURE 0
#define KEY_SELECT_0_DATA_WIDTH 1
#define KEY_SELECT_0_DO_TEST_BENCH_WIRING 0
#define KEY_SELECT_0_DRIVEN_SIM_VALUE 0
#define KEY_SELECT_0_EDGE_TYPE "NONE"
#define KEY_SELECT_0_FREQ 50000000
#define KEY_SELECT_0_HAS_IN 1
#define KEY_SELECT_0_HAS_OUT 0
#define KEY_SELECT_0_HAS_TRI 0
#define KEY_SELECT_0_IRQ -1
#define KEY_SELECT_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define KEY_SELECT_0_IRQ_TYPE "NONE"
#define KEY_SELECT_0_NAME "/dev/key_select_0"
#define KEY_SELECT_0_RESET_VALUE 0
#define KEY_SELECT_0_SPAN 16
#define KEY_SELECT_0_TYPE "altera_avalon_pio"


/*
 * mode_0 configuration
 *
 */

#define ALT_MODULE_CLASS_mode_0 altera_avalon_pio
#define MODE_0_BASE 0x6020
#define MODE_0_BIT_CLEARING_EDGE_REGISTER 0
#define MODE_0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define MODE_0_CAPTURE 0
#define MODE_0_DATA_WIDTH 1
#define MODE_0_DO_TEST_BENCH_WIRING 0
#define MODE_0_DRIVEN_SIM_VALUE 0
#define MODE_0_EDGE_TYPE "NONE"
#define MODE_0_FREQ 50000000
#define MODE_0_HAS_IN 1
#define MODE_0_HAS_OUT 0
#define MODE_0_HAS_TRI 0
#define MODE_0_IRQ -1
#define MODE_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define MODE_0_IRQ_TYPE "NONE"
#define MODE_0_NAME "/dev/mode_0"
#define MODE_0_RESET_VALUE 0
#define MODE_0_SPAN 16
#define MODE_0_TYPE "altera_avalon_pio"


/*
 * ram_0 configuration
 *
 */

#define ALT_MODULE_CLASS_ram_0 altera_avalon_onchip_memory2
#define RAM_0_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define RAM_0_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define RAM_0_BASE 0x0
#define RAM_0_CONTENTS_INFO ""
#define RAM_0_DUAL_PORT 0
#define RAM_0_GUI_RAM_BLOCK_TYPE "AUTO"
#define RAM_0_INIT_CONTENTS_FILE "platform_ram_0"
#define RAM_0_INIT_MEM_CONTENT 1
#define RAM_0_INSTANCE_ID "NONE"
#define RAM_0_IRQ -1
#define RAM_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define RAM_0_NAME "/dev/ram_0"
#define RAM_0_NON_DEFAULT_INIT_FILE_ENABLED 0
#define RAM_0_RAM_BLOCK_TYPE "AUTO"
#define RAM_0_READ_DURING_WRITE_MODE "DONT_CARE"
#define RAM_0_SINGLE_CLOCK_OP 0
#define RAM_0_SIZE_MULTIPLE 1
#define RAM_0_SIZE_VALUE 8192
#define RAM_0_SPAN 8192
#define RAM_0_TYPE "altera_avalon_onchip_memory2"
#define RAM_0_WRITABLE 1


/*
 * ram_1 configuration
 *
 */

#define ALT_MODULE_CLASS_ram_1 altera_avalon_onchip_memory2
#define RAM_1_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define RAM_1_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define RAM_1_BASE 0x2000
#define RAM_1_CONTENTS_INFO ""
#define RAM_1_DUAL_PORT 0
#define RAM_1_GUI_RAM_BLOCK_TYPE "AUTO"
#define RAM_1_INIT_CONTENTS_FILE "platform_ram_1"
#define RAM_1_INIT_MEM_CONTENT 1
#define RAM_1_INSTANCE_ID "NONE"
#define RAM_1_IRQ -1
#define RAM_1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define RAM_1_NAME "/dev/ram_1"
#define RAM_1_NON_DEFAULT_INIT_FILE_ENABLED 0
#define RAM_1_RAM_BLOCK_TYPE "AUTO"
#define RAM_1_READ_DURING_WRITE_MODE "DONT_CARE"
#define RAM_1_SINGLE_CLOCK_OP 0
#define RAM_1_SIZE_MULTIPLE 1
#define RAM_1_SIZE_VALUE 8192
#define RAM_1_SPAN 8192
#define RAM_1_TYPE "altera_avalon_onchip_memory2"
#define RAM_1_WRITABLE 1


/*
 * rom_0 configuration
 *
 */

#define ALT_MODULE_CLASS_rom_0 altera_avalon_onchip_memory2
#define ROM_0_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ROM_0_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ROM_0_BASE 0x4000
#define ROM_0_CONTENTS_INFO ""
#define ROM_0_DUAL_PORT 0
#define ROM_0_GUI_RAM_BLOCK_TYPE "AUTO"
#define ROM_0_INIT_CONTENTS_FILE "platform_rom_0"
#define ROM_0_INIT_MEM_CONTENT 1
#define ROM_0_INSTANCE_ID "NONE"
#define ROM_0_IRQ -1
#define ROM_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ROM_0_NAME "/dev/rom_0"
#define ROM_0_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ROM_0_RAM_BLOCK_TYPE "AUTO"
#define ROM_0_READ_DURING_WRITE_MODE "DONT_CARE"
#define ROM_0_SINGLE_CLOCK_OP 0
#define ROM_0_SIZE_MULTIPLE 1
#define ROM_0_SIZE_VALUE 8192
#define ROM_0_SPAN 8192
#define ROM_0_TYPE "altera_avalon_onchip_memory2"
#define ROM_0_WRITABLE 0


/*
 * sdram configuration
 *
 */

#define ALT_MODULE_CLASS_sdram altera_avalon_new_sdram_controller
#define SDRAM_BASE 0x8000000
#define SDRAM_CAS_LATENCY 3
#define SDRAM_CONTENTS_INFO
#define SDRAM_INIT_NOP_DELAY 0.0
#define SDRAM_INIT_REFRESH_COMMANDS 2
#define SDRAM_IRQ -1
#define SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_IS_INITIALIZED 1
#define SDRAM_NAME "/dev/sdram"
#define SDRAM_POWERUP_DELAY 100.0
#define SDRAM_REFRESH_PERIOD 7.8125
#define SDRAM_REGISTER_DATA_IN 1
#define SDRAM_SDRAM_ADDR_WIDTH 0x19
#define SDRAM_SDRAM_BANK_WIDTH 2
#define SDRAM_SDRAM_COL_WIDTH 10
#define SDRAM_SDRAM_DATA_WIDTH 16
#define SDRAM_SDRAM_NUM_BANKS 4
#define SDRAM_SDRAM_NUM_CHIPSELECTS 1
#define SDRAM_SDRAM_ROW_WIDTH 13
#define SDRAM_SHARED_DATA 0
#define SDRAM_SIM_MODEL_BASE 0
#define SDRAM_SPAN 67108864
#define SDRAM_STARVATION_INDICATOR 0
#define SDRAM_TRISTATE_BRIDGE_SLAVE ""
#define SDRAM_TYPE "altera_avalon_new_sdram_controller"
#define SDRAM_T_AC 5.4
#define SDRAM_T_MRD 3
#define SDRAM_T_RCD 15.0
#define SDRAM_T_RFC 70.0
#define SDRAM_T_RP 15.0
#define SDRAM_T_WR 14.0


/*
 * seg7_0 configuration
 *
 */

#define ALT_MODULE_CLASS_seg7_0 altera_avalon_pio
#define SEG7_0_BASE 0x6030
#define SEG7_0_BIT_CLEARING_EDGE_REGISTER 0
#define SEG7_0_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SEG7_0_CAPTURE 0
#define SEG7_0_DATA_WIDTH 7
#define SEG7_0_DO_TEST_BENCH_WIRING 0
#define SEG7_0_DRIVEN_SIM_VALUE 0
#define SEG7_0_EDGE_TYPE "NONE"
#define SEG7_0_FREQ 50000000
#define SEG7_0_HAS_IN 0
#define SEG7_0_HAS_OUT 1
#define SEG7_0_HAS_TRI 0
#define SEG7_0_IRQ -1
#define SEG7_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SEG7_0_IRQ_TYPE "NONE"
#define SEG7_0_NAME "/dev/seg7_0"
#define SEG7_0_RESET_VALUE 0
#define SEG7_0_SPAN 16
#define SEG7_0_TYPE "altera_avalon_pio"


/*
 * seg7_1 configuration
 *
 */

#define ALT_MODULE_CLASS_seg7_1 altera_avalon_pio
#define SEG7_1_BASE 0x6040
#define SEG7_1_BIT_CLEARING_EDGE_REGISTER 0
#define SEG7_1_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SEG7_1_CAPTURE 0
#define SEG7_1_DATA_WIDTH 7
#define SEG7_1_DO_TEST_BENCH_WIRING 0
#define SEG7_1_DRIVEN_SIM_VALUE 0
#define SEG7_1_EDGE_TYPE "NONE"
#define SEG7_1_FREQ 50000000
#define SEG7_1_HAS_IN 0
#define SEG7_1_HAS_OUT 1
#define SEG7_1_HAS_TRI 0
#define SEG7_1_IRQ -1
#define SEG7_1_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SEG7_1_IRQ_TYPE "NONE"
#define SEG7_1_NAME "/dev/seg7_1"
#define SEG7_1_RESET_VALUE 0
#define SEG7_1_SPAN 16
#define SEG7_1_TYPE "altera_avalon_pio"


/*
 * seg7_2 configuration
 *
 */

#define ALT_MODULE_CLASS_seg7_2 altera_avalon_pio
#define SEG7_2_BASE 0x6050
#define SEG7_2_BIT_CLEARING_EDGE_REGISTER 0
#define SEG7_2_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SEG7_2_CAPTURE 0
#define SEG7_2_DATA_WIDTH 7
#define SEG7_2_DO_TEST_BENCH_WIRING 0
#define SEG7_2_DRIVEN_SIM_VALUE 0
#define SEG7_2_EDGE_TYPE "NONE"
#define SEG7_2_FREQ 50000000
#define SEG7_2_HAS_IN 0
#define SEG7_2_HAS_OUT 1
#define SEG7_2_HAS_TRI 0
#define SEG7_2_IRQ -1
#define SEG7_2_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SEG7_2_IRQ_TYPE "NONE"
#define SEG7_2_NAME "/dev/seg7_2"
#define SEG7_2_RESET_VALUE 0
#define SEG7_2_SPAN 16
#define SEG7_2_TYPE "altera_avalon_pio"


/*
 * seg7_3 configuration
 *
 */

#define ALT_MODULE_CLASS_seg7_3 altera_avalon_pio
#define SEG7_3_BASE 0x6060
#define SEG7_3_BIT_CLEARING_EDGE_REGISTER 0
#define SEG7_3_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SEG7_3_CAPTURE 0
#define SEG7_3_DATA_WIDTH 7
#define SEG7_3_DO_TEST_BENCH_WIRING 0
#define SEG7_3_DRIVEN_SIM_VALUE 0
#define SEG7_3_EDGE_TYPE "NONE"
#define SEG7_3_FREQ 50000000
#define SEG7_3_HAS_IN 0
#define SEG7_3_HAS_OUT 1
#define SEG7_3_HAS_TRI 0
#define SEG7_3_IRQ -1
#define SEG7_3_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SEG7_3_IRQ_TYPE "NONE"
#define SEG7_3_NAME "/dev/seg7_3"
#define SEG7_3_RESET_VALUE 0
#define SEG7_3_SPAN 16
#define SEG7_3_TYPE "altera_avalon_pio"


/*
 * start configuration
 *
 */

#define ALT_MODULE_CLASS_start altera_avalon_pio
#define START_BASE 0x6070
#define START_BIT_CLEARING_EDGE_REGISTER 0
#define START_BIT_MODIFYING_OUTPUT_REGISTER 0
#define START_CAPTURE 0
#define START_DATA_WIDTH 1
#define START_DO_TEST_BENCH_WIRING 0
#define START_DRIVEN_SIM_VALUE 0
#define START_EDGE_TYPE "NONE"
#define START_FREQ 50000000
#define START_HAS_IN 1
#define START_HAS_OUT 0
#define START_HAS_TRI 0
#define START_IRQ -1
#define START_IRQ_INTERRUPT_CONTROLLER_ID -1
#define START_IRQ_TYPE "NONE"
#define START_NAME "/dev/start"
#define START_RESET_VALUE 0
#define START_SPAN 16
#define START_TYPE "altera_avalon_pio"

#endif /* __SYSTEM_H_ */
