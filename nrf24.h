#ifndef nrf24_pico_c_header
#define nrf24_pico_c_header

#ifdef __cplusplus
extern "C" 
{
#endif

// Return TRUE if setup correctly
// Defaults: 250KBPS, auto-ack enabled, dynamic payloads enabled.
bool NRF24_Init(spi_inst* spi_bus, uint8_t sck_pin, uint8_t tx_pin, uint8_t rx_pin, uint8_t ce_pin, uint8_t csn_pin);

// Writing pipe wrapper.
void NRF24_OpenWritingPipe(uint8_t addr[6]);

// Reading pipe wrapper.
void NRF24_OpenReadingPipe(uint8_t pipe_num, uint8_t addr[6]);

// Set payload size upto 32 bytes. Applies to non-dynamic length payloads.
void NRF24_SetStaticPayloadSize(uint8_t len);

// Grab static size for payloads.
int NRF24_GetStaticPayloadSize();

// Enable/Disable dynamic payload sizes.
void NRF24_DynamicPayloads(bool enabled);

// Returns size of message in buffer to be read.
int NRF24_GetDynamicPayloadSize();

// True for acknowledgement packets.
void NRF24_AckEnabled(uint8_t pipe_num, bool enabled);

// Number of retries and time intervals between attempts. (multiples of 250us)
void NRF24_NumberRetries(uint8_t time_interval, uint8_t count);

// Returns true if RX is available
bool NRF24_HasNewData();

// Assumes stop-listen prior to run. Return true if ack_rec
bool NRF24_SendData(uint8_t buffer[], uint8_t len);

// Modifies buffer with RX data, only to be called if buffer contains waiting message.
// If buff is greater than payload size either parts of next message will be added,
// or last byte will be padded until end of buffer.
// More detail here: https://nrf24.github.io/RF24/classRF24.html#a8e2eacacfba96426c192066f04054c5b
void NRF24_ReadData(uint8_t buffer[], uint8_t len);

// Start listening
void NRF24_StartListening();

// Stop listening
void NRF24_StopListening();

// Radio to low power, useful when next to each other
void NRF24_LowPWR();

// Radio to max power
void NRF24_MaxPWR();

// Prints to details of radio
void NRF24_TestRadio();



#ifdef __cplusplus
}
#endif

#endif
