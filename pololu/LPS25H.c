
#include <wiringPiI2C.h>
#include <stdio.h>

int main(){
	short int data_L, data_H, data_XL;
	int fd = wiringPiI2CSetup(0x5d);

	if(fd == 0)
		printf("Inicjalizacja sie nie powiodla\n");
	else{
		printf("Inicjalizacja sie powiodla\n");

		//Data rate: 25Hz and power on pressure sensor
		wiringPiI2CWriteReg8 (fd, 0x20, 0b11000000);

		//Checking:
		data_L = wiringPiI2CReadReg8 (fd, 0x20);
		if(data_L==0b11000000)
			printf("Wpisanie sie powiodlo\n");

		//Temperature average 64
		data_L = wiringPiI2CReadReg8 (fd, 0x20);
		wiringPiI2CWriteReg8 (fd, 0x10, (0b000011 | data_L));


		//Temperature read
		data_L = wiringPiI2CReadReg8 (fd, 0x2B);
		data_H = wiringPiI2CReadReg8 (fd, 0x2C);


		double x = ( (double)((short int)((data_H << 8)| data_L)) / 480.00 )+42.50;
		printf("Temp: \%lf C \n", x );
		printf("Data_L: \%x \n", data_L);
		printf("Data_H: \%x \n", data_H);

		 //Pressure read
		data_XL = wiringPiI2CReadReg8 (fd, 0x28);
                data_L = wiringPiI2CReadReg8 (fd, 0x29);
                data_H = wiringPiI2CReadReg8 (fd, 0x2A);

		x = (data_H << 16) | (data_L << 8) | (data_XL);
		x /= 4096;

		printf("\nPressure: \%lf hPa \n", x );
                printf("Data_XL: \%x \n", data_XL);
                printf("Data_L: \%x \n", data_L);
                printf("Data_H: \%x \n", data_H);

		}

}
