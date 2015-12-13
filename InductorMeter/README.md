# Inductor Meter

This project for Arduino Uno to measure unknown inductors between 50 - 500 uH

You need to recalibrate your 1uF to get good results.
Or you can add a bigger size of capacitor like 2uH or more.

	double capacitance = 1.035E-6; 

Do not use polarized capacitor.

#Based on 

http://reibot.org/2011/07/19/measuring-inductance/
http://soundation.blogspot.com/2012/07/arduino-inductance-meter.html
	
But with some modifications, I made it as permanent oscilator instead of ring, so i removed the delay before read the freq, also I size the lenght of full wave not half.

