# Arduino-Kiln-Controller
Basic Arduino kiln controller using Adafruit's MAX31855 thermocouple amplifier board and library (you need to get their library from them). Power switching using solid state relay. Change the ramp rate and soak temp and soak hold time parameters within the main program.

DISCLAIMER:
I am not a professional programmer. I made this program for my own personal use. This project (at least mine) involves dangerous amounts of power and heat. Enough to cause injury, desruction of property, death, and probably more undesirable things. USE THIS PROGRAM AND INFORMATION AT YOUR OWN RISK. I MAKE NO GUARANTEES OF ANY KIND AND ACCEPT NO LIABILITY. EXPECT THIS PROGRAM TO FAIL, HEAT YOUR KILN TO A BRAZILLION DEGREES, AND BURN THE WHOLE WORLD TO A CRISP. BUT SERIOUSLY, DO NOT LEAVE YOUR KILN UNATTENDED FOR ANY REASON. PLEASE. BE. CAREFUL.

HARDWARE USED: Arduino Uno, Adafruit MAX31855, Solid State Relay, Kiln, LED.

SOFTWARE USED: Arduino IDE, MegunoLink v1.0.8.xxxxx.

DESCRIPTION:
Program will read current temperature at start/reset and increase temperature at ramp rate until soak temperature is reached. It will then hold soak temperature for soak time. 

soakTemp, soakTime, and rampRate are defined in first 3 lines of program. Edit as needed.

thermoDO, thermoCS, and thermoCLK are defined next. Edit if connecting MAX31855 to different pins.

relayPin and ledPin are defined next. Edit if you want to connect relay or led to different pins.

The ledPin and relayPin will be ON and OFF at the same time. The led is there to show you the relay's status. You can omit it without needing to edit the program.

This program does not involve PID controll. It simply calculates the target temperature (targetTemp) and turns the relay ON if the current temperature (currentTemp) is less than targetTemp. And OFF if more.

The program can be started/reset at any temperature. It will begin the program from there and ramp up to the soakTemp.

However, if the program is started/reset at or above the soakTemp, the program will start the soak time timer from zero and hold the soakTemp for the defined soakTime. In other words, the program does not remember how long its been soaking if the Arduino is reset and will start the soakTime from scratch.

Once the program completes (i.e. soakTime has passed) it will loop infinitely in a while loop where it will execute the heatOFF() function. At this point, disconnect power from the kiln first and then unplug the arduino.

Regarding MegunoLink:
I Serial.print using a format that MegunoLink reads and plots to a graph. I use an old version of MegunoLink that was free. I think they are all paid now, but I'm not sure. I use version 1.0.8.xxxxx of MegunoLink if you'd like to do your own research.
