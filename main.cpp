#include <iostream>
#include "booking.h"
#include "room.h"

/**           0  1  2  3  4  5  6  7  8  9
 *   room0 :        x  x  x
 *   room1 :
 *   room2 :
 **/

bool sortBookings( bp::Booking::List bookings, bp::Room::List rooms, int bn, int rn )
{
    bool status = false;

    if( rn >= rooms.size() )
    {
        status = true;
        bp::Room::print(rooms);
    }else
    {  
        for( int i=bn; i<bookings.size(); i++)
        {
            std::swap( bookings[bn], bookings[i] );
            if( ! rooms[rn].isOverlapping(bookings[i]) )
            {
                rooms[rn].bookings.push_back(bookings[i]);
                status = sortBookings( bookings, rooms, bn+1, rn ); 
            }
            rooms[rn].bookings.pop_back();
            std::swap( bookings[bn], bookings[i] );
        }

        

    }
    
    return status;
}


int main(int argc, char *argv[])
{
    bp::Room::List rooms = {bp::Room(0), bp::Room(1), bp::Room(2) };
    bp::Booking::List bookings = { bp::Booking(1, 0, 1, true)
                                 , bp::Booking(2, 0, 6, true) };

    rooms.at(0).bookings.push_back(bp::Booking(0, 3, 5, false));

    sortBookings( bookings, rooms, 0, 0 );

    return 0;
}
