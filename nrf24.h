#ifndef nrf24_included
#define nrf24_included

#ifdef __cplusplus
extern "C" 
{
#endif

bool NRF24_Init(uint8_t address[2][6], uint8_t spi_bus, uint8_t sck_pin, uint8_t tx_pin, uint8_t rx_pin, uint8_t ce_pin, uint8_t csn_pin);
void NRF24_PayloadLength(uint8_t len);
void NRF24_AckEnabled(bool enabled);
void NRF24_NumberRetries(uint8_t count, uint8_t time_interval);
void NRF24_SetupIRQ(uint8_t irq_pin, void (*irq_handler) (uint gpio, uint32_t event));
bool NRF24_RxIRQ();
bool NRF24_HasNewData();
bool NRF24_SendData(uint8_t buffer[], uint8_t len);
void NRF24_ReadData(uint8_t buffer[], uint8_t len);
void NRF24_TestRadio();
void NRF24_StartListening();
void NRF24_StopListening();
void NRF24_LowPWR();
void NRF24_MaxPWR();


#ifdef __cplusplus
}
#endif

#endif
