/*Sensor Data Formatter
You have a raw 12-bit ADC value (uint16_t). Write a program that:

Converts it to voltage (0–3.3V): voltage = (float)adc_raw / 4095 * 3.3f
Converts voltage to temperature: temp = (voltage - 0.5f) * 100.0f
Stores raw value, voltage, and temp in a struct
Passes the struct to a function via pointer and prints all three fields inside that function*/

#include <stdio.h>
#include <stdint.h>

struct values{
    uint16_t adc_raw;
    float v;
    float t;
};

void sensor_values(struct values *ptr){
    printf("ADC value: %d\n", ptr->adc_raw);
    printf("Voltage: %f\n", ptr->v);
    printf("Temperature: %f\n", ptr->t);
}

int main(){

    uint16_t adc;
    float voltage, temp;
    struct values sensor;
    struct values *ptr = &sensor; 

    printf("Enter 16 bit ADC value: ");
    scanf("%hu", &adc);
    
    voltage = (float)adc / 4095 * 3.3f;
    temp = (voltage - 0.5f) * 100.0f;

    ptr->adc_raw = adc; //This is same as (*ptr).adc_raw=adc. "->" is  used as short form.
    ptr->v = voltage;
    ptr->t = temp;

    sensor_values(ptr);

    return 0;
}