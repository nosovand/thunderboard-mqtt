#include <mbed.h>
#include "Si7021.h" // relative humidity and temperature sensor
#include <string>
 
UnbufferedSerial serial_port(USBTX, USBRX, 115200);
DigitalOut R_LED(LED0); // LED0 = PD8 ~ RED, LED1 = PD9 ~ GREEN
DigitalOut G_LED(LED1);

/* Turn on power supply to ENV sensor suite = Si7021, Si1133 and BMP280 */
DigitalOut env_en(PF9, 1);

Si7021* rhtSensor;

I2C env_i2c(PC4, PC5);
bool rhtsensor_en = true;
int32_t temperature;
uint32_t humidity;
int readyToWrite = 0;
unsigned char value[4];

void serial_isr()
{
    char c;
    if (serial_port.read(&c, 1))
    {                             // Read the data to clear the receive interrupt.
        serial_port.write(&c, 1); // Echo the input back to the terminal.
        if (c == 'r')
            R_LED = !R_LED;
        if (c == 'g')
            G_LED = !G_LED;
    }
}
 

class T
{
	Ticker t;
	volatile int count;
	

	void cblk()
	{
	
  rhtsensor_en = true;
  readyToWrite = 1;
	}

public:
	T(float cas):count(0)
	{
		t.attach (callback (this, &T::cblk), cas);
	}	

	unsigned char * status()
	{
		return value;
	}
};

int main()
{

   thread_sleep_for(100);
   //BMP280* pressureSensor = new BMP280(env_i2c);
    Si7021* rhtSensor = new Si7021(PC4, PC5);

    serial_port.attach(serial_isr, SerialBase::RxIrq);

    	T x(1.0);
    while(1) {
      G_LED = !G_LED;
      if(rhtsensor_en) {
       // serial_port.write("a", 1);
            rhtSensor->measure();
            //rhtSensor->measure();
            temperature = rhtSensor->get_temperature();
            humidity = rhtSensor->get_humidity();
            value[0] = temperature/1000;
            value[1] = abs(temperature%100);
            value[2] = humidity/1000;
            value[3] = humidity%100;
            serial_port.write(&value, 4);
            rhtsensor_en = false;
            //printf("test");
        }
    }
}