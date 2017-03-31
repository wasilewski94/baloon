/*
 * blink.c:
 *      blinks the first LED
 *      Gordon Henderson, projects@drogon.net
 */
 
#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <unistd.h> 
int main (void)
{	
	char command[25];
  printf ("Raspberry Pi blink\n") ;
 
  if (wiringPiSetup () == -1)
    return 1 ;
 
  pinMode (1, INPUT) ;         // aka BCM_GPIO pin 17
 
  for (;;)
  {
	  int read=0;
    read=digitalRead (1);
    sprintf(command, "echo read: %d %s", read, read?"jupi!":"");	
    system(command);
    if(read){
	system("shutdown -P now");
	return 0;
    }
    sleep(1);
  }
  return 0 ;
}
