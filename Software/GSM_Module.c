#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>				//UART
#include <fcntl.h>				//UART
#include <termios.h>			//UART
#include <ugpio/ugpio.h>		//GPIO

int main (int argc, char **argv)
{
	int gpio = 0;
	int alarm = 0;
	int ver, val;
		

	if ((ver = gpio_is_requested(gpio)) < 0)
	{
		perror("WARNING! GPIO in use by another process.");
		return EXIT_FAILURE;
	}

	if (!ver) {
		printf("--------------- Sensor activation ---------------\n");
		if ((val = gpio_request(gpio, NULL)) < 0)
		{
			perror("WARNING! GPIO not available, the interface does not respond.");
			return EXIT_FAILURE;
		}
	}

	printf("--------------- Sensor initialization ---------------\n");
	if ((val = gpio_direction_input(gpio)) < 0)
	{
		perror("WARNING! Invalid GPIO value.");
	}
	

	printf("--------------- SENSOR ACTIVATED! Waiting on port '%d' ---------------\n",gpio);
	printf("\n#ARMED\n");

	while(1)
	{
		
		// read the gpio
		alarm = gpio_get_value(gpio);
		
		if(alarm == 0)
		{
			printf(".\n");
		}

		if(alarm == 1)
		{
			printf("\n\n--------------- ALARM ACTIVATED!!! ---------------\n");
		}
		// pause between each read
		sleep(1);

		if(alarm == 1)
		{

			int uart0 = -1;

			//----------UART INITIALIZATION----------

			uart0 = open("/dev/ttyS1", O_RDWR | O_NOCTTY | O_NDELAY); 

			if (uart0 == -1) 		
			{
				printf("WARNING! The device is unreachable. Verify connections and ascertain the device is not in use by another process.");
			}

			//----------UART CONFIGURATION----------
					
			struct termios settings;
			tcgetattr(uart0, &settings);
			settings.c_cflag = B115200 | CS8 | CLOCAL | CREAD;	
			settings.c_iflag = IGNPAR;
			settings.c_oflag = 0;
			settings.c_lflag = 0;
			tcflush(uart0, TCIFLUSH);
			tcsetattr(uart0, TCSANOW, &settings);

			
			unsigned char tx_buffer[50]; 	//Bits that will be trasmitted
			unsigned char *p_tx_buffer;		


			p_tx_buffer = &tx_buffer[0]; 	//AT comand to reactivate SIM800L from eventual standby
			*p_tx_buffer++ = 'A';
			*p_tx_buffer++ = 'T';
			*p_tx_buffer++ = '\n';
			
			printf("\n--------------- ATTIVAZIONE SEGNALATORE GSM! ---------------\n");

			if (uart0 != -1)
			{
				//Sending message
				int count = write(uart0, &tx_buffer[0], (p_tx_buffer - &tx_buffer[0]));

				if (count < 0)
				{
					printf("UART TX error\n");
				}
			}

			
				
			sleep(5);
			
			p_tx_buffer = &tx_buffer[0];	//Dialing number
			*p_tx_buffer++ = 'A';
			*p_tx_buffer++ = 'T';
			*p_tx_buffer++ = 'D';
			*p_tx_buffer++ = '1';
			*p_tx_buffer++ = '2';
			*p_tx_buffer++ = '3';
			*p_tx_buffer++ = '4';
			*p_tx_buffer++ = '5';
			*p_tx_buffer++ = '6';
			*p_tx_buffer++ = '7';
			*p_tx_buffer++ = '8';
			*p_tx_buffer++ = '9';
			*p_tx_buffer++ = ';';
			*p_tx_buffer++ = '\n';

			if (uart0 != -1)
			{	
				//Calling...
				int count = write(uart0, &tx_buffer[0],
							 (p_tx_buffer - &tx_buffer[0]));
				if (count < 0)
				{
					printf("UART TX error\n");
				}
			}

			int i = (p_tx_buffer - &tx_buffer[0])-2;			

			tx_buffer[i] = '\0';			

			tx_buffer[0] = '+';			
			tx_buffer[1] = '3';	
			tx_buffer[2] = '9';			
		
			printf("\n--------------- CALL TO %s IN PROGRESS! ---------------\n", tx_buffer);

			close(uart0);

			printf("\n--------------- SENSOR DEACTIVATED ---------------\n\n");

			return 0;

		}
	}
}
















