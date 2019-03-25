# Onion GSM Module

###### Modular GSM device, for embedded applications, realized with Onion Omega 2+ and SIM800L.
![Model](https://github.com/AlbertoZandara/Onion-GSM-Module/blob/master/Model.bmp) 
![Prototype](https://github.com/AlbertoZandara/Onion-GSM-Module/blob/master/Prototype.jpg) 

### Overview

This devices is a portable GSM prototype that can be used for different purpouse. The board allows to power an Onion Omega 2+ and a Simcom SIM800L thanks to two NCP3170A buck regulators. Moreover the device contains also different nets that permitts to Omega2+ to control the SIM800L. Besides has been also added a modular interface that allows to upgrade the device and add new functionalities.

### C program

In this repo there is also a short C program that has been realized as an example of module implementation. The source code allows to configure the system as a GSM allarm detector. Infact it uses the GPIO interface to detect an allarm signal ( thet can also be emitted by a relay connected to an antitheft siren) and send a call to a predefinite number as notification.

### Libraries and softwares used

For the hardware implementation of this project has been used the Cadence® suite. In the `/Hardware` directory you can find the .dsn design, the .opj schematic and the .brd layout.
Instead for the C program, that you can find in the `/Software` directory, different libraries have been used.
For UART (serial connection between Omega and SIM):
- `unistd.h`				
- `fcntl.h`			
- `termios.h`

For GPIO interactions:
- `ugpio/ugpio.h`

And a special thanks goes to @ mhei for the last one.
