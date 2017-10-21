/**
* @Author: Michał Kocon
* @Date:   10-01-2017
* @Last modified by:   Michał Kocon
* @Last modified time: 10-01-2017
*/



#ifndef HOPERF_STRUCTURES_HPP_
#define HOPERF_STRUCTURES_HPP_

namespace skik {
namespace hoperf {

/**
Represents logic level of pin
*/
enum class Level{
    LO,
    HI
};
/**
Represents pin mode
*/
enum class PinMode{
    IN,
    OUT
};

/**
*/
enum class PinType{
    CONFIG,
    SLEEP,
    STATUS,
    RESET
};

}
}

#endif //HOPERF_STRUCTURES_HPP_
