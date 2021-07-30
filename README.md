# **FT205EV**

### Introductory Information:
	The FT205EV Sensor is an ultrasonic wind sensor. It utilizes known properties of sound to measure wind speed,
	wind direction in relation to the onboard compass, and temperature. This project provides a method to mount the sensor, PCB and required external battery on a DJI Inspire. 
	File List:
	PCB (not including Arduino, Micro-SD card holder or Micro-SD card)
	STL files for 3D printing (PLA)
	.INO file for Arduino

	The PCB .zip file folder is an EasyEDA format. It contains all required files, and a BOM parts list. 
		Some soldering skills are required to assemble the PCB. Note that the led-resistor combos (POWER and DATA) are optional.
		The POWER area can remain empty; DATA requires a solder bridge over both resistor and led footprints. 

	The STL 3D printing files are optimized for a 2S 7.4V LiPo Battery. The sensor mount screws onto the sensor; and twists into the Inspire Camera lock. 
		The enclosure box hooks on the thorn of the gimble, and clicks into place. 

	The .INO file needs to be uploaded to the Arduino before use with the sensor. It utilizes <SPI.h>, <SD.h>, <Wire.h>, and "RTClib.h" libraries. 

### Sensor Overview:
	The FT205EV sensor requires a DC voltage across the range of 6-30 V. The PCB will handle voltage between 6-8V. 
	If a different power source (not the 7.4V LiPo) is desired, voltage regulation needs to be included. 
	The Sensor uses Serial ASCII communication. It has 3 protocol options: RS422, RS485 and UART. This system utilizes UART. 
	Any connection to a pc can be done with the included RS485 cable. The PC will require a serial interface. This project recommends TeraTerm. 
	TeraTerm requires some familiarity to serial communications to use. Power the RS485 cable with a benchtop power supply (within 6-30V) and plug the USB into the PC. 
	Open TeraTerm and select the USB COM port in the serial dropdown. The Sensor requires CR+LF line endings so open SETUP>TERMINAL in the TeraTerm window. Change the New-Line      options from CR to CR+LF. 
	Optionally check the Local Echo box to see user input. Before any communications are made; the sensor needs to be set into RS485 mode and the continuous update turned off. Do that using these commands:
		$01,CUD*//  
		$01,CI8*//
	After these commands are entered; the sensor should be able to communicate with the PC. Either open the ACU-VIS included software or send commands through TeraTerm to ensure connection. 
	Check the Sensor User Manual to see full list of commands. 
