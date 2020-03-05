#include "mbed.h"

#define IAQ_ADDR (0x5A<<1)

typedef struct{
    uint16_t prediction;
    uint8_t status;
    uint32_t resistance;
    uint16_t tvoc;
}IAQ_Data;

class IAQ_Core{

    public:
    /*Methods */
    void Initialize(I2C* i2c);
    bool GetValues(IAQ_Data* data);
    void PrintValues(IAQ_Data* data, Serial* comport);

    private:
    I2C *iaq_I2C;
};
