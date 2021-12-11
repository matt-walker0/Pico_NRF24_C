#include <stdio.h>
#include "pico/stdlib.h"
#include <RF24.h>         // rf24 radio object
#include "nrf24.h"
#include "hardware/gpio.h"

// NRF24 C WRAPPER: Used to call nrf24 common operations from C.
// Expects to be in a project with RF24 included in target_link_libraries. Defined in main CMakeLists.txt


RF24 radio; // instantiate an object for the nrf24L01 transceiver


// Return true if setup correctly
bool nrf24Init(uint8_t address[2][6], uint8_t spi_bus, uint8_t sck_pin, uint8_t tx_pin, uint8_t rx_pin, uint8_t ce_pin, uint8_t csn_pin) {
    printf("%d %d %d %d %d %d ", spi_bus, sck_pin,  tx_pin, rx_pin, ce_pin, csn_pin);
    if(spi_bus == 0) {
        spi.begin(spi0, sck_pin, tx_pin, rx_pin);        // Setup SPI bus
    }
    else if(spi_bus == 1) {
        spi.begin(spi1, sck_pin, tx_pin, rx_pin);        // Setup SPI bus
    }
    else { return (false); } // Unknown SPI bus

    if(radio.begin(&spi, ce_pin, csn_pin) == false) {     // Setup and configure rf radio
        return(false);
    }
    radio.setDataRate(RF24_250KBPS);        // Slow == more signal 
    radio.setAutoAck(1);                    // Ensure ACK is enabled
    radio.openWritingPipe(address[1]);      // Both radios listen on the same pipes by default, and switch when writing
    radio.openReadingPipe(1,address[0]);
    radio.startListening();    
    return(true);
}

// Set payload size (no. bytes)
void nrf24PayloadLength(uint8_t len) {
    radio.setPayloadSize(len);                // Here we are sending 1-byte payloads to test the call-response speed
}

// Change num. retries allowed and time interval multiples of 250us
void nrf24NumberRetries(uint8_t count, uint8_t time_interval) {
    radio.setRetries(time_interval, count);               
}

// Allows for function to be inserted for call on IRQ falling
void nrf24SetupIRQ(uint8_t irq_pin, void (*irq_handler)(uint gpio, uint32_t event) ) {
    radio.maskIRQ(1,1,0);
    gpio_set_irq_enabled_with_callback(irq_pin, GPIO_IRQ_EDGE_FALL, true, irq_handler);
}

// Returns true if RX is available
bool nrf24HasNewData() {
     if(radio.available() == true) {  // if there is data in the RX FIFO
        return(true);
     }
    return(false);
}

// Assumes stop-listen prior to run. Return true if ack_rec
bool nrf24SendData(uint8_t buffer[], uint8_t len) {
    bool ack_rec = radio.write(buffer, len);
    return ack_rec;
}

// Modifies buffer with RX data, ignore_ground stops 0 ID messages from pickup.
// True returned if read data, false if ground or something
void nrf24ReadData(uint8_t buffer[], uint8_t len) {
    if(radio.available() == true) {  // if there is data in the RX FIFO
        radio.read(buffer, len); // this clears the RX FIFO      
    } 
}


// Returns true if new RX data available (other IRQ's can lead to race conditions)
bool nrf24RxIRQ() {
    bool tx_ok, tx_fail, rx_ready;      
    radio.whatHappened(tx_ok, tx_fail, rx_ready); // get values for IRQ masks 

    if(rx_ready == true) { // new rx data
        return(true);
    }
    return(false);
}

// Start listening
void nrf24StartListening() {
    radio.startListening();
}

// Stop listening
void nrf24StopListening() {
    radio.stopListening();
}

// Radio to low power, useful when next to each other
void nrf24LowPWR() {
    radio.setPALevel(RF24_PA_LOW);
}

// Radio to max power
void nrf24MaxPWR() {
    radio.setPALevel(RF24_PA_MAX);
}

// Prints to details of radio
void nrf24TestRadio() {
    radio.printDetails(); // Dump the configuration of the rf unit for debugging
}

