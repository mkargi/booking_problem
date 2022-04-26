#include <iostream>
#include "booking.h"
#include "room.h"

using namespace bp;

/**           0  1  2  3  4  5  6  7  8  9
 *   room0 :        x  x  x
 *   room1 :
 *   room2 :
 **/

bool sortBookings( Booking::List bookings, Booking::List openBookings, Room::List rooms, int bn, int rn )
{
    bool status = false;

    if( rn >= rooms.size() )
    {
        
        if( bookings.empty() )
        {
            Room::print(rooms);
            status = true;
        }else{
            //std::cout << "not valid" << std::endl;
        }
            
    }
    else if( bn >= bookings.size() )
    {
        //Booking::print(openBookings);
        //Room::print(rooms);
        status = sortBookings( openBookings, {}, rooms, 0, rn+1 );
    }
    else
    {  
        for( int i=bn; i<bookings.size(); i++)
        {
            //std::cout << "bn " << bn << " rn " << rn << std::endl;
            std::swap( bookings[bn], bookings[i] );
            bool isOverlapping = rooms[rn].isOverlapping(bookings[bn]);

            if( isOverlapping )
                openBookings.push_back(bookings[bn]);
            else
                rooms[rn].bookings.push_back(bookings[bn]);
            
            status = sortBookings( bookings, openBookings, rooms, bn+1, rn ); 

            // if( status == true)
            //     break;

            std::swap( bookings[bn], bookings[i] );
            if( isOverlapping )
                openBookings.pop_back();
            else
                rooms[rn].bookings.pop_back();
        }       

    }
    
    return status;
}


int main(int argc, char *argv[])
{
    Booking b0(0, 3, 5, 'X', false);
    Booking b1(2, 0, 6, 'B', true);

    auto status = b0.isOverlapping(b1);

    Room::List rooms = {Room(0), Room(1), Room(2) };
    Booking::List bookings = { Booking(1, 0, 2, 'A', true)
                             , Booking(2, 0, 6, 'B', true)
                             , Booking(3, 0, 0, 'C', true) };

    rooms.at(0).bookings.push_back(Booking(0, 3, 5, 'X', false));

    sortBookings( bookings, {}, rooms, 0, 0 );

    return 0;
}
