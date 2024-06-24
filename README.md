Arduino uno controlled Home & Green house system.

In this project we utilized multiple sensors to create a smart home
and a green house, and to control the sensors we used an Arduino
NANO. The smart home includes a temperature system that uses a
DHT sensor, a security system that uses a PIR sensor to detect
movement outside the house, a smart door that only allows entry
when the correct password is entered, and a smart lighting system
that can be controlled via a mobile application. Next to the smart
home, we created a smart garage that automatically opens and
closes as the situation requires, this system relies on 2 IR sensors
placed inside and outside of the garage. For the green house, we
used a DHT sensor to monitor the plant’s temperature and
humidity, an LDR sensor to monitor the light levels, and we also
used a soil moisture sensor to ensure that the moisture levels of the
soil are sufficient. If the soil moisture is low, the water pump starts
to pump water into the soil to increase it adequately. All information
about the plant is provided on the mobile application


Electric Components
- Arduino NANO, to control the sensors
Smart Home
- IR sensor (2), for the smart garage
- Keypad, to enter the password of the smart home
- LCD, to prompt the user to enter a password and informs them
if they entered the correct one
- Servo motor (2), to open and close the door of the smart home
and the garage
- 8-Bit shift register, to implement the lighting system without
taking too many pins for the Arduino
- PIR sensor, to detect movements outside the house
- Rain detector, to inform the user about the weather
Green House
- LDR sensor, to measure the light levels inside the green house
- Soil moisture sensor, to automatically water the plant using
the water pump when the moisture levels are low
- DHT sensor, to measure temperature and humidity
