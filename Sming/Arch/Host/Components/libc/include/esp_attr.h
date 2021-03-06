#pragma once
#include <c_types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ICACHE_FLASH_SECTION ".text"
#define ICACHE_RODATA_SECTION ".rodata"
#define ICACHE_RAM_SECTION ".data"

#define IRAM_ATTR
#define STORE_TYPEDEF_ATTR __attribute__((aligned(4), packed))
#define STORE_ATTR __attribute__((aligned(4)))
#define ICACHE_FLASH_ATTR

#define GDB_IRAM_ATTR

#ifdef __cplusplus
}
#endif
