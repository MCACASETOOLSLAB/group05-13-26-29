//------------------------------------------------------------------------
// Filename: 
//    roller-coaster-main.cpp
// PROGRAM DESCRIPTION
//     This program solves the Roller Coasters problem using semaphores
// ---------------------------------------------------------------------

#include <iostream>
#include <stdlib.h>

#include "roller-coaster.h"

// --------------------------------------------------------------------- 
//                        The main program                           
// ---------------------------------------------------------------------

int main(int argc, char *argv[]) 
{
     int Capacity,            // capacity of the car 
         No_of_rides,         // number of times the car rides 
         No_of_passengers;    // number of passengers in the park 
     int i;
     PassengerThread *Passenger[MAX_PASSENGERS];

     if (argc != 4) {         // get user input
          cout << "Use " << argv[0] 
               << " #-of-Passengers car-capacity #-of-rides" << endl;
          exit(0);
     }
     else {
          No_of_passengers = abs(atoi(argv[1]));
          Capacity = abs(atoi(argv[2]));
          No_of_rides   = abs(atoi(argv[3]));
     }
    
     if (Capacity > No_of_passengers) { 
          cout << "Please check your input, car capacity "
               << "must be less than the no. of passengers" << endl;
          exit(1);
     }
     if (No_of_passengers > MAX_PASSENGERS) {
          cout << "The number of passengers is too large. " 
               << "Reset to " << MAX_PASSENGERS << endl;
          No_of_passengers = MAX_PASSENGERS;
     }
     if (Capacity > MAX_CAPACITY) {
          cout << "Car capacity is too large.  " 
               << "Reset to " << MAX_CAPACITY << endl;
          Capacity = MAX_CAPACITY;
     }

     CarThread Car("Car", Capacity, No_of_rides); // create and run the car
     Car.Begin();

     for (i = 1; i <= No_of_passengers; i++) {    // create and run passengers
          Passenger[i] = new PassengerThread(i, Capacity);
          Passenger[i]->Begin();
     }
     Car.Join();    // only join with the car
     Exit();
     
     return 0;
}
