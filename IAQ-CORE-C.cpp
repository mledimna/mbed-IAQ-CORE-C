#include "mbed.h"
#include "IAQ-CORE-C.h"

void IAQ_Core::Initialize(I2C* i2c){

    iaq_I2C = i2c;
    iaq_I2C->frequency(100000);
}

bool IAQ_Core::GetValues(IAQ_Data* data){

    char IAQ_Data[9];

    if(!iaq_I2C->read(IAQ_ADDR, IAQ_Data, 9)){

        data->prediction = IAQ_Data[0]*(uint16_t)pow((double)2, (double)8)+IAQ_Data[1];
        data->status = (uint8_t)IAQ_Data[2];
        data->resistance = IAQ_Data[4]*(uint16_t)pow((double)2, (double)16)+IAQ_Data[5]*(uint16_t)pow((double)2, (double)8)+IAQ_Data[6];
        data->tvoc = IAQ_Data[7]*(uint16_t)pow((double)2, (double)8)+IAQ_Data[8];
        
        return true;
    }
    else return false;
}

void IAQ_Core::PrintValues(IAQ_Data* data, Serial* comport){

    char buffer[15] = {'\0'};

    if(data->status==0x00) sprintf(buffer,"OK");
    else if(data->status==0x01) sprintf(buffer,"BUSY");
    else if(data->status==0x10) sprintf(buffer,"WARMUP");
    else if(data->status==0x80) sprintf(buffer,"ERROR");
    else sprintf(buffer,"UNKNOWN ERROR");

    comport->printf("IAQ Status : 0x%X(%s)\r\n",data->status,buffer);

    if(data->status==0x00){

        comport->printf("CO2 Prediction : %d ppm\r\n",data->prediction);
        comport->printf("IAQ Resistance : %d Ohm\r\n",data->resistance);
        comport->printf("TVOC : %d ppb\r\n\n",data->tvoc);
    }
}