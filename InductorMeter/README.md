# Inductor Meter

This project for Arduino Uno to measure unknown inductors between 10 - 500 uH

You need to recalibrate your 1uF to get good results.
Or you can add a bigger size of capacitor like 2uH or more.

	double capacitance = 1.03; 

Do not use polarized capacitor.

It is not stable yet, but it give me a quite good reading.

![](https://github.com/zaher/arduino_projects/blob/master/InductorMeter/InductorMeter.svg)

####Based on 

http://reibot.org/2011/07/19/measuring-inductance/

http://soundation.blogspot.com/2012/07/arduino-inductance-meter.html

http://codinglab.blogspot.be/2013/02/measuring-inductances-using-arduino.html

http://forum.allaboutcircuits.com/threads/inductor-meter-on-arduino.118518/
	
But with some modifications, I made it as permanent oscilator instead of ring by adding a resisitor R3 then in my code I removed the delay before reading the pulses, with mesuring the lenght of full wave not half.

####Library

You need to install this library in your arduino IDE
 
	PinChangeInterrupt