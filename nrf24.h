#ifdef __cplusplus
extern "C" 
{
#endif

bool nrf24Init(uint8_t address[][6], uint8_t SPI_BUS, uint8_t SCK_PIN, uint8_t TX_PIN, uint8_t RX_PIN, uint8_t CE_PIN, uint8_t CSN_PIN);
bool nrf24SendData(uint8_t buffer[5]);
bool nrf24ReadData(uint8_t buffer[5]);
bool nrf24InterruptHandle();
void nrf24TestRadio();

#ifdef __cplusplus
}
#endif
