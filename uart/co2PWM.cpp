//program: co2PWM
//compile with:    g++ co2PWM.cpp -o co2PWM  -lwiringPi
//run with:        sudo ./co2UART
#include <iostream>
#include <wiringPi.h>
using namespace std;

const int PWM=2;

int getPWM()
{
	//wait for PWM start
	//cout << "Waiting for LOW:\n";
	while (digitalRead(PWM)== LOW);
	//wait for PWM end
	long startTime = micros();
	//cout << "Waiting for HIGH:\n";
	while (digitalRead(PWM) == HIGH);
	long duration = micros() - startTime;
	//from datasheet
	//CO2 ppm = 5000 * (Th - 2ms) / (Th + Tl - 4ms)
	//  given Tl + Th = 1004
	//        Tl = 1004 - Th
	//        = 5000 * (Th - 2ms) / (Th + 1004 - Th -4ms)
	//        = 5000 * (Th - 2ms) / 1000 = 2 * (Th - 2ms)
        long co2ppm = 5 * ((duration/1000) - 2);
	return co2ppm;
}
int main(void)
{
        wiringPiSetup();
        pinMode(PWM, INPUT);
       	cout << " CO2 PWM program is running .. \n";
	while (1)
	{
               cout << "\nco2 ppm = \t"<< getPWM();
               delay (5000);   //wait  30 sekunds
	}
	return 0;
}
