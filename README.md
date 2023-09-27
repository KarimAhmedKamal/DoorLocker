# DoorLocker
Door-Locker system as a practical application of AVR peripherals

A Door Locker system which asks the user to enter the password stored on eeprom using a Keypad and gives him two options : 1- open the door using the servo motor. 2- Change the stored password.
It is divided into two parts : Master and Slave. The master is connected to slave using UART communication protocol.
The Master AVR has the control of keypad, LCD and Communicate with Slave using UART.
The Slave AVR has a connection of eeprom which carries the password. Also, it has the control of the door and the buzzer which works after 3 wrong password entries.
