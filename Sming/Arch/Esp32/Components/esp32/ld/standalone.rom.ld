/* linker script to bind symbols to their correct segments */

/*
MEMORY
{
  dport0_0_seg :                        org = 0x3FF00000, len = 0x10
  dram0_0_seg :                         org = 0x3FFE8000, len = 0x14000
  iram1_0_seg :                         org = 0x40100000, len = 0x8000
  irom0_0_seg :                         org = 0x4020a000, len = (1M - 0x0a000)
}

INCLUDE "common.ld"
*/