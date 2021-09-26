#ifdef __cplusplus
extern "C" 
{
#endif

bool nrf24Init(uint8_t address[2][6], uint8_t spi_bus, uint8_t sck_pin, uint8_t tx_pin, uint8_t rx_pin, uint8_t ce_pin, uint8_t csn_pin);
bool nrf24HasNewData();
bool nrf24SendData(uint8_t buffer[5]);
void nrf24ReadData(uint8_t buffer[5]);
bool nrf24InterruptHandle();
void nrf24TestRadio();

#ifdef __cplusplus
}
#endif
