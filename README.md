# Arduino-Kiln-Controller
Basic Arduino kiln controller using Adafruit MAX31855 thermocouple amplifier board and library. Power switching using solid state relay. Change ramp rate and soak temp and soak hold time parameters within main program.

DISCLAIMER:
I am not a professional programmer. I made this program for my own personal use. This project (at least for me) involves dangerous amounts of power and heat. Enough to cause injury, desruction of property, death, and probably more undesirable things. USE THIS PROGRAM AND INFORMATION AT YOUR OWN RISK. I MAKE NO GUARANTEES OF ANY KIND AND ACCEPT NO LIABILITY.

Basic Hardware Used: Arduino Uno, Adafruit MAX31855, Solid State Relay, Kiln.

Software Used: Arduino IDE, old free version of MegunoLink

Description:
Program will read current temperature at start/reset and increase temperature at the ramp rate until the soak temperature is reached. It will then hold the soak temperature for the soak time. 

soakTemp, soakTime, and rampRate are defined in the first 3 lines of the program. Edit them as needed.

thermoDO, thermoCS, and thermoCLK are defined next. Edit these if connecting MAX31855 board to different pins.

relayPin and led are defined next. Edit these if you want to connect the relay or led to different pins.

The led and relayPin will be ON and OFF at the same time. led is only there to show you the relay's status. You can leave led disconnected. no need to edit the program. But, dont use the led pin for the MAX31855 board without changing pin numbers to match.

This program does not involve PID controll. It simply draws out a target temperature line (targetTemp) and turns the relay ON if the current temperature (currentTemp) is less than targetTemp. And OFF if more.

The program can be started/reset at any currentTemp and it will start the program from there and ramp up to the soakTemp. However, if the program is started/reset at or above the soakTemp, the program will start the soak time timer from zero and hold the soakTemp for the defined soakTime. In other words, the program does not remember how long its been soaking if the Arduino is reset and will start the soakTime from scratch.

Once the program completes (i.e. soakTime has passed) it will infinitely loop in a while loop where it will execute the heatOFF() function.

I Serial.print using a format that MegunoLink reads and plots to a graph. I use an old version of MegunoLink that was free. I think they are paid now, but I'm not sure. I use version 1.0.8.xxxxx of MegunoLink. 
