#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>


// Struct Definitions for Task 02 

// Unpacked struct (compiler inserts padding)
typedef struct {
    uint8_t  status_code;   // 1 byte  
    
    uint32_t timestamp;     // 4 bytes 
    
    uint8_t  sensor_id;     // 1 byte  
    
    uint16_t raw_adc_val;   // 2 bytes 
    
} SensorPacket_Unpacked;


// Optimized struct (reordered from largest to smallest)
typedef struct {
    uint32_t timestamp;     // 4 bytes 
    
    uint16_t raw_adc_val;   // 2 bytes 
    
    uint8_t  status_code;   // 1 byte  
    
    uint8_t  sensor_id;     // 1 byte  
    
} SensorPacket_Optimized;

// Packed struct (zero padding bytes) 
typedef struct __attribute__((packed)) {
    uint8_t  status_code;   // 1 byte  
    
    uint32_t timestamp;     // 4 bytes 
    
    uint8_t  sensor_id;     // 1 byte  
    
    uint16_t raw_adc_val;   // 2 bytes 
    
} SensorPacket_Packed;


// Helper Functions for Tasks 03 & 04


// Task 03: Hex dump helper
void print_hex_dump(const char *label, const void *ptr, size_t size) {
    const uint8_t *bytes = (const uint8_t *)ptr;
    printf("%-25s [%zu B]: ", label, size);
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", bytes[i]);
    }
    printf("\n");
}

// Task 04: Endianness check 

bool is_little_endian(void) {
    uint16_t test_val = 0x0102;
    uint8_t *first_byte = (uint8_t *)&test_val;
    return (*first_byte == 0x02);
}

// Task 04: Byte swapper 16-bit 

uint16_t swap_uint16(uint16_t val) {
    return (uint16_t)((val >> 8) | (val << 8));
}

// Task 04: Byte swapper 32-bit
uint32_t swap_uint32(uint32_t val) {
    return ((val >> 24) & 0x000000FF) |
           ((val >> 8)  & 0x0000FF00) |
           ((val << 8)  & 0x00FF0000) |
           ((val << 24) & 0xFF000000);
}


// Main Entry Point


int main(void) {
    printf("=========================================================\n");
    printf("    DAY 03 PRACTICAL LAB: MEMORY ALIGNMENT & ENDIANNESS   \n");
    printf("=========================================================\n\n");

    
    // Task 01: Fixed-Width Primitive Type Sizes                              
    uint8_t  unsigned_one_byte  = 0;
    uint16_t unsigned_two_byte  = 0;
    uint32_t unsigned_four_byte = 0;
    uint64_t unsigned_eight_byte= 0;

    int8_t   signed_one_byte   = 0;
    int16_t  signed_two_byte   = 0;
    int32_t  signed_four_byte  = 0;
    int64_t  signed_eight_byte = 0;

    printf("--- Task 01: Primitive Type Sizes ---\n");
    printf("Size of uint8_t is   = %zu byte(s)\n", sizeof(unsigned_one_byte));
    printf("Size of int8_t is    = %zu byte(s)\n", sizeof(signed_one_byte));

    printf("Size of uint16_t is  = %zu byte(s)\n", sizeof(unsigned_two_byte));
    printf("Size of int16_t is   = %zu byte(s)\n", sizeof(signed_two_byte));

    printf("Size of uint32_t is  = %zu byte(s)\n", sizeof(unsigned_four_byte));
    printf("Size of int32_t is   = %zu byte(s)\n", sizeof(signed_four_byte));

    printf("Size of uint64_t is  = %zu byte(s)\n", sizeof(unsigned_eight_byte));
    printf("Size of int64_t is   = %zu byte(s)\n", sizeof(signed_eight_byte));

    printf("Size of uintptr_t is = %zu byte(s)\n\n", sizeof(uintptr_t));

    
    // Task 02: Struct Memory Alignment & Padding                             
    printf("--- Task 02: Struct Alignment & Padding ---\n");
    printf("Size of SensorPacket_Unpacked  = %zu bytes (Includes padding)\n", sizeof(SensorPacket_Unpacked));
    printf("Size of SensorPacket_Optimized = %zu bytes (Reordered members)\n", sizeof(SensorPacket_Optimized));
    printf("Size of SensorPacket_Packed    = %zu bytes (__attribute__((packed)))\n\n", sizeof(SensorPacket_Packed));

    
    // Task 03: Memory Byte Hex Dump Inspection                                
    printf("--- Task 03: Memory Hex Dump Inspection ---\n");
    SensorPacket_Unpacked unpacked_pkt = { .status_code = 0xAA, .timestamp = 0x12345678, .sensor_id = 0x55, .raw_adc_val = 0x03FF };
    SensorPacket_Packed   packed_pkt   = { .status_code = 0xAA, .timestamp = 0x12345678, .sensor_id = 0x55, .raw_adc_val = 0x03FF };

    print_hex_dump("Unpacked Struct Dump", &unpacked_pkt, sizeof(unpacked_pkt));
    print_hex_dump("Packed Struct Dump  ", &packed_pkt, sizeof(packed_pkt));
    printf("\n");
    
    // Task 04: Endianness Detection & Byte Swapping                          
    printf("--- Task 04: Endianness Detection & Byte Swapping ---\n");
    bool little = is_little_endian();
    printf("System Endianness: %s\n", little ? "LITTLE-ENDIAN (LSB at lowest address)" : "BIG-ENDIAN (MSB at lowest address)");

    uint32_t orig_32 = 0x12345678;
    uint32_t swapped_32 = swap_uint32(orig_32);
    printf("Original 32-bit: 0x%08X\n", orig_32);
    printf("Swapped 32-bit:  0x%08X\n\n", swapped_32);

    
    // Task 05: Unsigned Integer Overflow Wrapping                            
    printf("--- Task 05: Unsigned Integer Overflow Wrapping ---\n");
    uint8_t count = 255;
    printf("Initial uint8_t max value: %u (0x%02X)\n", count, count);
    count++;
    printf("After overflow (255 + 1):  %u (0x%02X)\n", count, count);
    count--;
    printf("After underflow (0 - 1):   %u (0x%02X)\n\n", count, count);

    return 0;
}