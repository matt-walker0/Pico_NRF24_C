#include <stdio.h>
#include "pico/stdlib.h"
#include <RF24.h>      
#include "nrf24.h"


// NRF24 C WRAPPER: Used to call NRF24 common operations from C.
// Expects to be in a project with RF24 included in target_link_libraries, defined in CMakeLists.txt


RF24 radio; // Instantiate an object for the RF24 transceiver.
SPI spi; // Instantiate SPI to pass none default pins.


// Return TRUE if setup correctly.
// Defaults: 250KBPS, dynamic payloads, and listening mode.
bool NRF24_Init(spi_inst_t *spi_bus, uint8_t sck_pin, uint8_t tx_pin, uint8_t rx_pin, uint8_t ce_pin, uint8_t csn_pin) {
    spi.begin(spi_bus, sck_pin, tx_pin, rx_pin);

    if(radio.begin(&spi, ce_pin, csn_pin) == false) {     // Setup and configure rf radio
        return(false);
    }
    radio.setDataRate(RF24_250KBPS);        // Slow == more signal 
    radio.enableDynamicPayloads();          // Dynamic payloads are way to go.
    radio.startListening();    
    return(true);
}

// Writing pipe wrapper.
void NRF24_OpenWritingPipe(uint64_t addr) {
    radio.openWritingPipe(addr);
}

// Reading pipe wrapper.
void NRF24_OpenReadingPipe(uint8_t pipe_num, uint64_t addr) {
    radio.openReadingPipe(pipe_num, addr);
}

// Set payload size upto 32 bytes. Applies to non-dynamic length payloads.
void NRF24_SetStaticPayloadSize(uint8_t len) {
    radio.setPayloadSize(len);               
}

// Grab static size for payloads.
uint8_t NRF24_GetStaticPayloadSize() {
    return(radio.getPayloadSize());               
}

// Enable/Disable dynamic payload sizes.
void NRF24_DynPayloadEnabled(bool enabled) {
    if(enabled) {
        radio.enableDynamicPayloads();
    }
    else {
        radio.disableDynamicPayloads();
    }
}

// Returns size of message in buffer to be read.
uint8_t NRF24_GetDynamicPayloadSize() {
    return(radio.getDynamicPayloadSize());
}

// True for acknowledgement packets.
void NRF24_AckEnabled(uint8_t pipe_num, bool enabled) {
    radio.setAutoAck(pipe_num, enabled);
}

// Toggle ACK payload ON. (global for all pipes?)
void NRF24_AckPayloadEnabled(bool enabled) {
    if(enabled) {
        radio.enableAckPayload();
    }
    else {
        radio.disableAckPayload();
    }
}

// Write buffer to specified pipe number.
// Returns true if messaged placed in FIFO (to be sent as acknowledgement)
bool NRF24_WriteAckPayload(uint8_t pipe, uint8_t buff[], uint8_t buff_len) {
    return(radio.writeAckPayload(pipe, buff, buff_len));
}

// Time intervals (x*250us... 1=250us, 2=500us...) of retries and number of attempts.
void NRF24_NumberRetries(uint8_t time_interval, uint8_t count) {
    radio.setRetries(time_interval, count);               
}

// Returns true if RX is available
bool NRF24_HasNewData() {
    return(radio.available());
}

// Assumes stop-listen prior to run. Return true if ack_rec
bool NRF24_SendData(uint8_t buffer[], uint8_t len) {
    return(radio.write(buffer, len));
}

// Modifies buffer with RX data, only to be called if buffer contains waiting message.
// If buff is greater than payload size either parts of next message will be added,
// or last byte will be padded until end of buffer.
// More detail here: https://nrf24.github.io/RF24/classRF24.html#a8e2eacacfba96426c192066f04054c5b
void NRF24_ReadData(uint8_t buffer[], uint8_t len) {
    radio.read(buffer, len);
}

// Start listening
void NRF24_StartListening() {
    radio.startListening();
}

// Stop listening
void NRF24_StopListening() {
    radio.stopListening();
}

// Radio to low power, useful when next to each other
void NRF24_LowPWR() {
    radio.setPALevel(RF24_PA_LOW);
}

// Radio to max power
void NRF24_MaxPWR() {
    radio.setPALevel(RF24_PA_MAX);
}

// Prints to details of radio
void NRF24_TestRadio() {
    radio.printDetails(); // Dump the configuration of the rf unit for debugging
}
