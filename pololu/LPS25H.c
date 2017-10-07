
#include <wiringPiI2C.h>
#include <time.h>
#include <stdio.h>


void str_time(char *time_to_text, char width){
	
	const char time_format[] = "[%T  %d/%m/%y]";
	time_t actual_time;
	struct tm* time_info; 

	time(&actual_time);
	time_info = localtime(&actual_time);
	strftime(time_to_text, width, time_format, time_info);
	}


int main(){
	short int data_L, data_H, data_XL;
	int fd = wiringPiI2CSetup(0x5d);
	char init = 1;

	char time_to_text[21];

	//Data rate: 25Hz and power on pressure sensor
	wiringPiI2CWriteReg8 (fd, 0x20, 0b11000000);

	data_L = wiringPiI2CReadReg8 (fd, 0x20);
	//Check:
	if(data_L != 0b11000000){
		str_time(time_to_text,21);
		printf("%s ",time_to_text);
		printf("Wpisanie sie nie powiodlo\n");
	}

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
	str_time(time_to_text,21);
	printf("#%s ", time_to_text);
	printf("Temp: \%lf C \n", x );
	//printf("Data_L: \%x \n", data_L);
	//printf("Data_H: \%x \n", data_H);

	 //Pressure read
	data_XL = wiringPiI2CReadReg8 (fd, 0x28);
        data_L = wiringPiI2CReadReg8 (fd, 0x29);
        data_H = wiringPiI2CReadReg8 (fd, 0x2A);

	x = (data_H << 16) | (data_L << 8) | (data_XL);
	x /= 4096;
	
	str_time(time_to_text,21);
	printf("#%s ", time_to_text);
	printf("Pressure: \%lf hPa \n", x );
        //printf("Data_XL: \%x \n", data_XL);
        //printf("Data_L: \%x \n", data_L);
        //printf("Data_H: \%x \n", data_H);
	}

	}
