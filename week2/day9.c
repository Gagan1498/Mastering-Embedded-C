/*Day 4 Program — Multi-Device Bus Config Register
You're configuring a communication bus that supports multiple devices. The register is 16 bits wide (uint16_t):
Bits 15-14: Reserved
Bits 13-12: BusSpeed    (00=100kHz, 01=400kHz, 10=1MHz,  11=3.4MHz)
Bits 11-9:  DeviceAddr  (000-111, 3 bits, device address 0-7)
Bits 8-6:   RetryCount  (000-111, 3 bits, number of retries 0-7)
Bits 5-4:   Voltage     (00=1.8V, 01=3.3V, 10=5V)
Bits 3-2:   Protocol    (00=I2C,  01=SPI,  10=UART)
Bits 1-0:   Mode        (00=off,  01=read, 10=write, 11=read-write)
Write a program that:

Defines a typedef enum with masks and positions for all fields
Starts with register 0x0000
Sets Mode to read-write (0b11)
Sets Protocol to SPI (0b01)
Sets Voltage to 3.3V (0b01)
Sets RetryCount to 5 (0b101)
Sets DeviceAddr to 3 (0b011)
Sets BusSpeed to 1MHz (0b10)
Changes Mode from read-write to read-only (0b01) without touching other fields
Reads back and prints every field separately by unpacking
Prints full register in binary and hex after every write

Rules:

uint16_t register this time — update print_binary to handle 16 bits
Clear-then-set pattern for every write
Unpack pattern for every read
No bit field structs — manual masking and shifting only*/

#include <stdio.h>
#include <stdint.h>

typedef enum{
    BusSpeed = 0b11 << 12,   //(00=100kHz, 01=400kHz, 10=1MHz,  11=3.4MHz)
    DeviceAddr = 0b111 << 9,  //(000-111, 3 bits, device address 0-7)
    RetryCount = 0b111 << 6,  //(000-111, 3 bits, number of retries 0-7)
    Voltage = 0b11 << 4,   //(00=1.8V, 01=3.3V, 10=5V)
    Protocol = 0b11 << 2,   //(00=I2C,  01=SPI,  10=UART)
    Mode = 0b11       //(00=off,  01=read, 10=write, 11=read-write)
}Config_reg;

void print_binary(uint16_t reg_bits){
    for(int i=15; i>=0; i--){
        printf("%d", (reg_bits >> i) & 1);
    }
}

int main(){

    uint16_t reg_bits = 0x0;

    reg_bits |= Mode;
    printf("After Mode=read-write: HEX=0x%04x, BIN=", reg_bits);
    print_binary(reg_bits);
    printf("\n");
    
    reg_bits &= ~Protocol;
    reg_bits |= (01 << 2);
    printf("After Protocol=SPI: HEX=0x%04x, BIN=", reg_bits);
    print_binary(reg_bits);
    printf("\n");

    reg_bits &= ~Voltage;
    reg_bits |= (01 << 4);
    printf("After Voltage=3.3V: HEX=0x%04x, BIN=", reg_bits);
    print_binary(reg_bits);
    printf("\n");

    reg_bits &= ~RetryCount;
    reg_bits |= (101 << 6);
    printf("After RetryCount=5: HEX=0x%04x, BIN=", reg_bits);
    print_binary(reg_bits);
    printf("\n");

    reg_bits &= ~DeviceAddr;
    reg_bits |= (011 << 9);
    printf("After DeviceAddr=3: HEX=0x%04x, BIN=", reg_bits);
    print_binary(reg_bits);
    printf("\n");

    reg_bits &= ~BusSpeed;
    reg_bits |= (10 << 11);
    printf("After DeviceAddr=3: HEX=0x%04x, BIN=", reg_bits);
    print_binary(reg_bits);
    printf("\n");

    return 0;
}