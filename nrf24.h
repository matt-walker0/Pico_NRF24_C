#ifndef nrf24_included
#define nrf24_included

#ifdef __cplusplus
extern "C" 
{
#endif

bool nrf24Init(uint8_t address[2][6], uint8_t spi_bus, uint8_t sck_pin, uint8_t tx_pin, uint8_t rx_pin, uint8_t ce_pin, uint8_t csn_pin);
void nrf24PayloadLength(uint8_t len);
void nrf24AckEnabled(bool enabled);
void nrf24NumberRetries(uint8_t count, uint8_t time_interval);
void nrf24SetupIRQ(uint8_t irq_pin, void (*irq_handler) (uint gpio, uint32_t event));
bool nrf24RxIRQ();
bool nrf24HasNewData();
bool nrf24SendData(uint8_t buffer[], uint8_t len);
void nrf24ReadData(uint8_t buffer[], uint8_t len);
void nrf24TestRadio();
void nrf24StartListening();
void nrf24StopListening();
void nrf24LowPWR();
void nrf24MaxPWR();


#ifdef __cplusplus
}
#endif

#endif
