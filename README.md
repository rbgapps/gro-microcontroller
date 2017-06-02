# gro-microcontroller
Code running on bot's microcontroller (Arduino Mega 2560).

Arduino Library Requirements:
Copy all the files from ArdionLibrary folder to your arduino libraries. 



ZigBee Firmware:
Zigbee Coordinator API -> version 21A7
Zigbee Router API -> version 23A7

On XCTU send a ND through the coordinator.
Expect Frame Type: 136 as response.

Coordinator Commands:
ND -> discover
TR -> Transmit Request -> Frame type, Command "Bulk 1 ".



