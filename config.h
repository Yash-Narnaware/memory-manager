#ifndef CONFIG_H
#define CONFIG_H

// Fixed section starting addresses
#define TEXT_SECTION_START 0x00400000
#define DATA_SECTION_START 0x00600000
#define STACK_SECTION_START 0x00700000
#define SHARED_LIB_SECTION_START 0x00800000
#define HEAP_SECTION_START 0x00900000

#define PAGE_SIZE 4096  //4KB
#define MEMORY_SIZE 4294967296 //4GB in bytes

// Virtual memory size in bytes (16MB)
//#define VIRTUAL_MEMORY_SIZE 16384 * 1024

// Virtual memory size in bytes (4GB)
#define VIRTUAL_MEMORY_SIZE 4294967296

#define FILENAME "../tracefiles/tracefile_4KB_4GB_4GB.txt"

// #define FILENAME "../tracefiles/generated_traces.txt"


// #define PAGE_SIZE 1024  //1KB
// #define MEMORY_SIZE 17179869184 //16GB in bytes

// // Virtual memory size in bytes (16MB)
// //#define VIRTUAL_MEMORY_SIZE 16384 * 1024

// // Virtual memory size in bytes (8GB)
// #define VIRTUAL_MEMORY_SIZE 8589934592

// #define FILENAME "../tracefiles/tracefile_1KB_8GB_16GB.txt"


// #define PAGE_SIZE 2048  //2KB
// #define MEMORY_SIZE 8589934592 //8GB in bytes

// // Virtual memory size in bytes (16MB)
// //#define VIRTUAL_MEMORY_SIZE 16384 * 1024

// // Virtual memory size in bytes (4GB)
// #define VIRTUAL_MEMORY_SIZE 4294967296

// #define FILENAME "../tracefiles/tracefile_2KB_4GB_8GB.txt"

// #define FILENAME "../tracefiles/generated_tracces.txt"

#endif // CONFIG_H