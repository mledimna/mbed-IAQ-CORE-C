# mbed-IAQ-CORE-C
This Library drives the [IAQ-CORE-C](https://ams.com/iaq-core-c) indoor air quality module.

# How to include this library to your project
- On [Mbed Studio](https://os.mbed.com/studio/) :
  - Go to View>Libraries (Or Ctrl+Shift+L)
  - On the "Libraries" panel click on the "+" icon
  - Enter the Git project address in the "Git or os.mbed.com URL" entry and press "Next"
  - Don't forget to include the library in your main.cpp
  
# main.cpp example
```C++
#include "mbed.h"
#include "IAQ-CORE-C.h"

/*IAQ */
I2C i2c3(PB_4,PA_8);
IAQ_Core iaq;

/*IAQ Data Structure */
IAQ_Data iaq_data;

/*Serial port */
Serial comport(USBTX, USBRX, 115200);

int main()
{
    /*Initialize IAQ Module */
    iaq.Initialize(&i2c3);

    while (true) {

        /*Store IAQ data in data structure*/
        /*Print IAQ data structure to Serial object */
        if(iaq.GetValues(&iaq_data)) iaq.PrintValues(&iaq_data, &comport);
        
        /*Sleep for 1 second */
        ThisThread::sleep_for(1000);
    }
}

```
