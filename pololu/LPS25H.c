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
	short int data_L, data_H, data_XL;
	int fd = wiringPiI2CSetup(0x5d);
	char init = 1;

	//Data rate: 25Hz and power on pressure sensor
	wiringPiI2CWriteReg8 (fd, 0x20, 0b11000000);

	data_L = wiringPiI2CReadReg8 (fd, 0x20);

	//Temperature average , pressure average 
	data_L = wiringPiI2CReadReg8 (fd, 0x10);
	wiringPiI2CWriteReg8 (fd, 0x10, (0x05 | data_L));

	//Check:
	data_H = wiringPiI2CReadReg8 (fd,0x10);
	if(data_H != (0x05 | data_L)){
		printf("Wpisanie sie nie powiodlo\n");
	}
	if(!init)
		return -1;
	//FIFO_CTRL: enabling averaging ()
	wiringPiI2CWriteReg8 (fd, 0x2E,0xC0);
	wiringPiI2CWriteReg8 (fd, 0x21,0x40); 
	

	while(1){
	//Temperature read
	data_L = wiringPiI2CReadReg8 (fd, 0x2B);
	data_H = wiringPiI2CReadReg8 (fd, 0x2C);


	double x = ( (double)((short int)((data_H << 8)| data_L)) / 480.00 )+42.50;
	printf("%luus ", getMicrotime());
    printf("Temp: \%lf C \n", x );
	//printf("Data_L: \%x \n", data_L);
	//printf("Data_H: \%x \n", data_H);

	 //Pressure read
	data_XL = wiringPiI2CReadReg8 (fd, 0x28);
    data_L = wiringPiI2CReadReg8 (fd, 0x29);
    data_H = wiringPiI2CReadReg8 (fd, 0x2A);

	x = (data_H << 16) | (data_L << 8) | (data_XL);
	x /= 4096;
	printf("%luus ", getMicrotime());
	printf("Pressure: \%lf hPa \n", x );
        //printf("Data_XL: \%x \n", data_XL);
        //printf("Data_L: \%x \n", data_L);
        //printf("Data_H: \%x \n", data_H);
    sleep(1);
	}

	}
