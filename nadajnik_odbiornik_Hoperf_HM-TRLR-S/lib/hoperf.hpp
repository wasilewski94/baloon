/**
* @Author: Michał Kocon
* @Date:   09-01-2017
* @Last modified by:   Michał Kocon
* @Last modified time: 11-01-2017
*/



#ifndef HOPERF_HPP_
#define HOPERF_HPP_

#include <stdint.h>
#include "hoperf_driver.hpp"
#include "hoperf_structures.hpp"

namespace skik {
namespace hoperf {

struct Command{
    /**
    Sets UART baud rate
    param 0~9
    0--1200bps 1--2400bps 2--4800bps 3--9600bps 4--14400bps 5--19200bps 6--38400bps 7--56000bps 8--57600bps 9--115200bps
    */
    static constexpr const char* kBaudRate = "SPR";
    /**
    UART check mode
    param 0~2
    0--none 1--even 2--old
    */
    static constexpr const char* kSerialPortCheck = "SPC";
    /**
    Sets output power
    param 0~7
    0—20dbm 1—17dbm 2—15dbm 3—10dbm 5—8dbm 6—5dbm 7—2dbm
    */
    static constexpr const char* kTransmitPower = "POWER";
    /**
    Channel selection
    param 0~F
    ch_num--ch_num channel
    */
    static constexpr const char* kChannelSelect = "CS";
    /**
    Sync word
    param less than 16 characters
    */
    static constexpr const char* kSyncWord = "SYNW";
    /**
    Sync word length
    param 0~8
    */
    static constexpr const char* kSyncWordLength = "SYNL";
    /**
    FSK node function setPinMode
    param n,m
    n 0~1
    mode 0~1
    */
    static constexpr const char* kFskNode = "NODE";
    /**
    Set node ID
    param 0~255
    */
    static constexpr const char* kNodeId = "NID";
    /**
    Enable/disable CRC in LoRa
    param 0~1
    */
    /**
    Set LoRa bandwidth
    param 6~9
    */
    static constexpr const char* kLoRaBandwidth = "LRSBW";
    /**
    Set LoRa spread factor
    param 7~C
    7—SF=7 8—SF=8 9—SF=9 A—SF=10 B—SF=11 C—SF=12
    */
    static constexpr const char* kLoRaSpreadFactor = "LRSF";

    /**
    Set LoRa forward error correction
    param 0~3
    */
    static constexpr const char* kLoRaErrorCorrection = "LRCR";

    /**
    Set LoRa frequency hopping
    param 0~1
    */
    static constexpr const char* kLoRaHopping = "LRHF";

    /**
    Set LoRa data packet length in bytes
    param 1~127
    */
    static constexpr const char* kLoRaFrameSize = "LRPL";

    /**
    Set LoRa frequency hopping period
    */
    static constexpr const char* kLoRaHoppingPeriod = "LRHPV";
    /**
    LoRa frequency step value
    param 0~65535
    */
    static constexpr const char* kLoRaFrequencyStep = "LRFSV";

    /**
    Set modulation mode
    param 0~3
    0-LoRa Mode 1-OOK Mode 2-FSK Mode 3-GFSK Mode
    In the OOK mode，baudrate no more than 9600 bps
    */
    static constexpr const char* kModulation = "MODE";

    /**
    Set frequency band
    param 0~3
    0--434MHZ Band 1--470MHZ Band 2--868MHZ Band 3--915MHZ Band
    */
    static constexpr const char* kBand = "BAND";

    /**
    Test Command
    */
    static constexpr const char* kTest = "AT";

    /**
    Writre configuration to built-in memory.
    WRITE TIMES ARE LIMITED. USE AT YOUR OWN RISK!
    */
    static constexpr const char* kWriteConfigurationToBuiltInFlashMemory = "AT&W";
};


class RadioModule{
public:
    RadioModule(DriverInterface& driver, size_t uart_baud_rate = 9600);
    //~RadioModule();
    void writeCommand(const char* command, const char* param) const;
    bool testModule();
    void writeData(const uint8_t data) const;
    void writeData(const char data) const;
    void writeData(const uint8_t* data, size_t length) const;
    void writeData(const char* data) const;
    void readData(uint8_t* dest, size_t length) const;
    void readData(char* dest, size_t length) const;
    void reset() const;
private:
    DriverInterface& driver_;
    bool is_sleeping_;
};

}
}



#endif //
