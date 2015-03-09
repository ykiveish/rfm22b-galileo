// HardwareSPI.h
// Author: Mike McCauley (mikem@open.com.au)
// Copyright (C) 2011 Mike McCauley
// Contributed by Joanna Rutkowska
// $Id: RF22.h,v 1.22 2012/09/05 23:31:39 mikem Exp mikem $

#include "GenericSPI.h"

// These defs cause trouble on some versions of Arduino
#undef round
#undef double

#include <mraa.h>


/////////////////////////////////////////////////////////////////////
/// \class HardwareSPIClass HardwareSPI.h <HardwareSPI.h>
/// \brief Encapsulate the Arduino hardware SPI interface
///
/// This concrete subclass of GenericSPIClass ncapsulates the standard Arduino hardware SPI interface
class HardwareSPIClass : public GenericSPIClass 
{

public:

    /// Transfer a single octet to and from the SPI interface
    /// \param[in] data The octet to send
    /// \return The octet read from SPI while the data octet was sent
    uint8_t transfer(uint8_t data) 
    {
        // return SPI.transfer(data);
        return 1;
    }

    // SPI Configuration methods
    /// Enable SPI interrupts
    /// This can be used in an SPI slave to indicate when an SPI message has been received
    /// It will cause the SPI_STC_vect interrupt vectr to be executed
    void attachInterrupt() 
    {
        // return SPI.attachInterrupt();
    }

    /// Disable SPI interrupts
    /// This can be used to diable the SPI interrupt in slaves where that is supported.
    void detachInterrupt() 
    {
        // return SPI.detachInterrupt();
    }
    
    /// Initialise the SPI library
    /// Initializes the SPI bus by setting SCK, MOSI, and SS to outputs, pulling SCK and MOSI low, and SS high. 
    void begin() 
    {
        spi = mraa_spi_init(0);
    }

    /// Disables the SPI bus (leaving pin modes unchanged). 
    /// Call this after you have finished using the SPI interface
    void end() 
    {
        // return SPI.end();
    }

    /// Sets the bit order the SPI interface will use
    /// Sets the order of the bits shifted out of and into the SPI bus, either 
    /// LSBFIRST (least-significant bit first) or MSBFIRST (most-significant bit first). 
    /// \param[in] bitOrder Bit order to be used: LSBFIRST or MSBFIRST
    void setBitOrder(uint8_t bitOrder) 
    {
        if (bitOrder < 2)  {
            mraa_spi_lsbmode(spi, bitOrder);
        } else {
            mraa_spi_lsbmode(spi, 0);
        }
    }

    /// Sets the SPI data mode: that is, clock polarity and phase. 
    /// See the Wikipedia article on SPI for details. 
    /// \param[in] mode The mode to use: SPI_MODE0 SPI_MODE1 SPI_MODE2 SPI_MODE3 
    void setDataMode(uint8_t mode) 
    {
        switch (mode) {
            case 0:
                mraa_spi_mode (spi, MRAA_SPI_MODE0);
                break;
            case 1:
                mraa_spi_mode (spi, MRAA_SPI_MODE1);
                break;
            case 2:
                mraa_spi_mode (spi, MRAA_SPI_MODE2);
                break;
            case 3:
                mraa_spi_mode (spi, MRAA_SPI_MODE3);
                break;
            default:
                mraa_spi_mode (spi, MRAA_SPI_MODE0);
                break;
        }
    }

    /// Sets the SPI clock divider relative to the system clock. 
    /// On AVR based boards, the dividers available are 2, 4, 8, 16, 32, 64 or 128. 
    /// The default setting is SPI_CLOCK_DIV4, which sets the SPI clock to one-quarter 
    /// the frequency of the system clock (4 Mhz for the boards at 16 MHz). 
    /// \param[in] rate The data rate to use: one of SPI_CLOCK_
    void setClockDivider(uint8_t rate) 
    {
        /* SPI_CLOCK_DIV4 0x00
        SPI_CLOCK_DIV16 0x01
        SPI_CLOCK_DIV64 0x02
        SPI_CLOCK_DIV128 0x03
        SPI_CLOCK_DIV2 0x04
        SPI_CLOCK_DIV8 0x05
        SPI_CLOCK_DIV32 0x06 */
        
        switch (rate) {
            case 0x00:
                mraa_spi_frequency(spi, 4000000); // 4Mhz
                break;
            case 0x01:
                mraa_spi_frequency(spi, 1000000); // 1Mhz
                break;
            case 0x02:
                mraa_spi_frequency(spi, 250000); // 250Khz
                break;
            case 0x03:
                mraa_spi_frequency(spi, 125000); // 125Khz
                break;
            case 0x04:
                mraa_spi_frequency(spi, 8000000); // 8Mhz
                break;
            case 0x05:
                mraa_spi_frequency(spi, 2000000); // 2Mhz
                break;
            case 0x06:
                mraa_spi_frequency(spi, 500000); // 500Khz
                break;
            default:
                mraa_spi_frequency(spi, 1000000); // 4Mhz
                break;
        }
    }
    
    mraa_spi_context spi;
};
