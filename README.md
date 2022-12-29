

This project is showing that FilterBank and SlaveStartFilterBank is not needed when configuring CAN2 and that messages are still interrupting and being received.
You can connect a serial program to UART2 port to see the "MCU_ready" message when the board powers up and is running. The green LED will also turn on.

To turn on the Amber LED, send Standard ID 0x101 with byte0 as 0x01. DLC = 8.
To turn off the Amber LED, send Standar ID 0x101 with byte0 as 0x00. DLC = 8;


