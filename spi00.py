import spidev

spi= spidev.SpiDev()
spi.open(bus,device)
to_send=[0x00,0x00,0x00]
spi.xfer(to_send)


