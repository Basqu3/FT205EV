3d anemometer Project

Due June 22nd

Resources:
Email contact: Phil.Richardson@fttechnologies.com
Thesis on wind-flow: https://www.ri.cmu.edu/wp-content/uploads/2020/08/Jay_MSR_Thesis-2.pdf
	Uses the FT205EV mounted on a 400mm pole above the drone. 
	Gives formula to calculate real wind speed from raw drone mounted data
	See 4.2.4 - 4.3.1
Article on arduino ASCII: https://forum.arduino.cc/t/sending-data-from-serial-moniter-and-saving-it-on-the-sd-card/575120/18
Article on telemetry integration: https://poseidon01.ssrn.com/delivery.php?ID=064009119124119124107092115069119126031031005037095033119000104125086120095004082077009121016122105097101109075004009009018113026076045089042089118000107126004123088001075028120088093097007064102127112124102127017118079125085025126121102097090068097115&EXT=pdf&INDEX=TRUE
Docs for requesting serial Ascii from pixhawk: https://www.mathworks.com/help/supportpkg/px4/ref/serialreceive.html

	
FT205EV lightweight wind sensor
ACU-VIS software 


Sensor Communication -> ASCII
	PC direct connect for testing uses RS485 half-duplex mode (See docs)
	RS422 is full-duplex, 4 wire, best for multiple sensors
	RS485 is half-duplex, 2 wire, possible option
	UART allow 1 sensor, used with short cable lengths: Top option as of now
	Listener ID is unique for each sensor; current: <01> 

Sensor Comms Final:
	UART from pi to sensor
	pi stores/sends to pixhawk
	timing issues?

Serial Address:
	run ls -l usb or ls -l /dev to find serial ports
	python serial model can open comms through port
	use baud 9600
	write the UTF-8 code to the sensor and read return
	write to file or telemetry
	Processing on data done after?
	Sensor filtration may help/ may hurt

TeraTerm -> com software: remember to change terminal to cr+lf
must be set in RS485 and CU must be off.
Baud rate: 9600
Relevant commands:
	$01,CUD*//  Cont. update
	$01,CI8*//  RS485 instead of UART
	$01,WV?*//  Query the sensor for polar weather data
	$01,DF?*//  Check weather data sensors (polar/NMEA)



Requirements for mounting on RPA:
6-30VDC up to 0.2A  -> nominal is 24VDC at .03A
Arduino takes 5V input

Required Voltages:
	6-30 for sensor
	5V for pi
	What kind of battery? what voltage does it give?
	Step up to 12V, then down to 5? 
	
Pole mount would allow for sensor to avoid wash, maybe consider bottom mounted rotors. 	Given height from paper is 40cm/400mm. Longest cord is 600mm
	consider weight and balance issues; might also cause problems with UART 
	FINAL: side mount provides least wind interferance. need to constant subtract for given wind rate. best to mount and remeasure 


Procedure for FT205EV:
BOM:
	FT205EV Sensor and included wires
	PC and downloaded Serial Interface (i.e. TeraTerm)
	3D printed parts and mount
	20-24 Gauge wire. Use whatever you have
	Matching connector sets plus electrical equiptment (sodering set/connectors/multimeter etc.)
	2S LiPo Battery or 9V batteries (or any battery pack that can provide >7 volts throughout discharge cycle of battery)

Technicals:
	The FT205EV anamometer requires a power source of 6-30 VDC.

Testing the sensor:
	The sensor comes with a RS485 to USB connection cable. You will need to download a Serial Interface; I used TeraTerm. 
	Details depend on the chosen Serial Interface, however ensure that messages are appended with <cr><nl> (/r/n). For TeraTerm this can be set by going to Setup->Terminal 
	and then New Line from CR to CR+LF
	Also check on the local echo button if you want to see the commands you type (reccomended)	

	The sensor should now respond to send commands. 
	The format for sent commands is $<Sensor ID>,<Command>*<checksum>
	Sensor ID is defaulted at 01
	See manual for all the sensor commands. Most are 3/4 symbols
	Checksum is only required if secure communications are vital. If not, // replaces the checksum
	Example: $01,WV?*//  will query the wind speed
	
	If the sensor is not responding to sent commands, it may not be in the correct communication modes.
	Send the following commands:
	$01,CUD*//  will turn off the cont. update feature of the sensor
	$01,CI8*//  will switch to RS485 communications

	The sensor should be responsive after sending those commands
	If not contact .....................

Using the sensor:
	After the sensor is firmly secured in the mount; certain setting need to be updated to utalize an arduino for data-collection.
	Connect the sensor to the computer as described in Testing the Sensor. Send $01,CIU*// to turn the sensor to UART comms mode. 
	The sensor is wired to protect against accidental switch of data and power, however take care to label wires. 

	

SD Card Pins:
	CS	Chip Select
	DI	Master Out/Slave In (MOSI)
	DO	Master In/Slave Out (MISO)
	SCK=CLK Clock input for syncing data transfer

Raspberry Pi Alternative:
	Download .py file
	Auto-run file with a systemd .service file