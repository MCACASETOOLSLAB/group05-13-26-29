group05-13-26-29
================

This project is choosen to understand various concepts of operating system.


ROLLER COASTER PROBLEM 

Suppose there are n passengers and one roller coaster car. The passengers repeatedly wait to ride in the car,
which can hold maximum C passengers,
where C < n. However, the car can go around the track only when it is full.
After finishes a ride, each passenger wanders around the amusement park before returning to the roller coaster for another ride.
Due to safety reasons, the car only rides T times and then shot-off.

Suppose the car and each passenger are represented by a thread.Now we write a program using semaphores only,
that can simulate this system and fulfill the following requirements:

1) The car always rides with exactly C passengers
2) No passengers will jump off the car while the car is running
3) No passengers will jump on the car while the car is running
4) No passengers will request another ride before they can get off the car.
