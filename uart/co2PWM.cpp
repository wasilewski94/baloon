#include <iostream>
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <sys/time.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <system_error>
#include <string>
#include <wiringPi.h>
#include <csignal>

#define _BSD_SOURCE

using namespace std;

const int PWM=2;
bool time_to_quit=false;

void sig_handler(int signo)
{
  cout << "It's time to quit.\n";
  time_to_quit=true;
}

void init()
{
  wiringPiSetup();
  pinMode(PWM, INPUT);
  cout << " CO2 PWM program is running .. \n"; 
}

string GetTimeStamp() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    string s = to_string(tv.tv_sec) + ";" + to_string(tv.tv_usec);
    return s;
}

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
	if (signal(SIGINT, sig_handler) == SIG_ERR)
	    printf("can't catch SIGINT\n");
	init();
	fstream plik;
	//string utime;
	
	plik.open( "pomiarCO2.txt", ios::in | ios::out );
	if( plik.good() == true )
	{
	    cout << "Otwieranie pliku zakonczone sukcesem!" << endl;
	} else {
	    cout << "Nie udalo sie otworzyc pliku!" << endl;
	    cerr << "Error: " << strerror(errno) << endl;
	}
	while(!time_to_quit)
	{
	 string s = to_string(getPWM());
	 s += ";" + GetTimeStamp(); 
	 cout << s << endl;
	 plik << s << '\n';
	   sleep(1);
	}
	plik.close();
	return 0;
}
