#include <wiringPiI2C.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/types.h>
#include <sys/time.h>


//timestamp
long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (uint64_t)1e6 + currentTime.tv_usec;
}

int main(){
	short int data_L, data_H, whoami, cmd, check;
	int fd = wiringPiI2CSetup(0x5f);
    if(!fd){
        printf("Nie udalo sie otworzyc pliku i2cdev-1: %d\n", fd);
    }
    printf("Otwieranie pliku i2cdev-1 przebieglo pomyslnie: %d\n", fd);
    
	char init = 1;
	//Whoami
	whoami = wiringPiI2CReadReg8 (fd, 0x0F);
    if(whoami != 0xBC){
        printf("Blad komunikacji z czujnikiem");
        exit(0);
    }
    else
        printf("Komunikacja z czujnikiem poprawna\n");
    
	//Temperature and humidity average 
	cmd = wiringPiI2CReadReg8 (fd, 0x10);
	wiringPiI2CWriteReg8 (fd, 0x10, (cmd | 0b00111111));
    
    //Check
    check = wiringPiI2CReadReg8 (fd, 0x10);
    if (check != (cmd | 0b00111111)){
        printf("Ustawienie usredniania sie nie powiodlo\n");
        exit(0);
    }
    else 
        printf("Ustawiono usrednianie\n");
    
	//Data rate: 12,5Hz and power on
	cmd = wiringPiI2CReadReg8 (fd, 0x20);
	wiringPiI2CWriteReg8 (fd, 0x20, (cmd | 0b10000011));
    
    //Check
    check = wiringPiI2CReadReg8 (fd, 0x20);
    if (check != (cmd | 0b10000011)){
        printf("Ustawienie czestotliwosci probkowania sie nie powiodlo\n");
        exit(0);
    }
    else 
        printf("Ustawiono czestotliwosc probkowania \n");
  
    
	while(1){
	//Temperature read
	data_L = wiringPiI2CReadReg8 (fd, 0x2A);
	data_H = wiringPiI2CReadReg8 (fd, 0x2B);

	double x = ( (double)((short int)((data_H << 8)| data_L)) / 480.00 )+20.00;
	printf("%luus ", getMicrotime());
    printf("Temp: \%lf C \n", x );
// 	printf("Data_L: \%x \n", data_L);
// 	printf("Data_H: \%x \n", data_H);

    //Humidity read
    data_L = wiringPiI2CReadReg8 (fd, 0x28);
    data_H = wiringPiI2CReadReg8 (fd, 0x29);

	x = (data_H << 8) | data_L;
	x /= 4096;
    x += 60;
	printf("%luus ", getMicrotime());
	printf("Humidity: \%lf % \n", x );
//     printf("Data_L: \%x \n", data_L);
//     printf("Data_H: \%x \n", data_H);
    
    sleep(1);
	}

	}
