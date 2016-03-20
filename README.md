# KobeTurret
## Inspiration
We just wanted to work with Arduino and see what we could do with it. But as we progressed, we started thinking of the practical applications of the device. Initially though, it was an exercise in what we could do with an Arduino the possible applications came later on. 

## What it does
The Archr is a two-button device with an analog stick that can fire a projectile at a specific distance. It's purpose is to be placed in a stationary location and launch projectiles at a certain distance, max accurate distance is 40 ft. When the user puts in a desired distance, the device calculates the necessary angle needed to achieve that distance, adjust itself, and fire, similar to a turret.


## How we built it

The Archr was initially designed to use ultra sonic sensor to provide the device with distance values and would automatically launch the projectile once an object came into a specific distance. However, the sensor was not good enough to provide reliable distance values. Instead, we used a formula from raw test data to then calculate the angle needed to reach a specific distance. The raw data helped create the formula that would give us reliable distance and accuracy results. The nerf gun, servos, Arduino, joystick, breadboards, LED lights, and wiring were connected together using acrylic and screws.

## Challenges we ran into

The design revolved around the sonic sensor, but did not function because of its low quality. It ultimately gave unreliable distance values. As well, most of the device was built from scratch using acrylic scraps. This caused us to manually place screws in those scraps in order to mount the device along with the breadboard and Arduino. The manual assembly of the parts was time consuming more than difficult, such as placing the nerf gun in a stable position. We had created an automatic mode in which the gun sweeps horizontally until given the command to switch back to manual mode, in which a joystick controls the vertical and horizontal movements of the gun. 

## Accomplishments that I'm proud of

Lucas: Proud of actually putting the Archr together in less than 23 hours.
Jay: Proud of getting everything working and seeing the finished product. 
Jonathan: Proud to represent Cherry Hill East at this event. 
Mauricio: Proud of joining a team as a Journalist and getting to see my teammates work on the coding and construction of the device. 

## What I learned

Lucas: Things don't go as you plan them to.
Jay: Learned more about Arduino and working with the microcontroller.
Jonathan:  Learning more about Arduino and C throughout the event. 
Mauricio: Learned a few basics of coding and the wiring that went into creating the Archr. 

## What's next for The Archr

The Archr is a prototype to a stationary device that can have many functions, especially in the area of wildlife observation. Instead of a nerf gun, a camera could mounted along with wifi, GPS, and an upgraded sonic sensor. These could then be triggered to capture wildlife that crosses the camera. With the GPS and distance, we can know the exact location of the animal captured in footage. With multiple devices scattered throughout the forest and over time, a heat map can be created of the forest that can show where the highest and lowest levels of wildlife activity are.
