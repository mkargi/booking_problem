#include <iostream>
#include <set>
#include "booking.h"
#include "room.h"

using namespace bp;



bool assignBookings( Booking::List bookings, Booking::List openBookings, Room::List rooms, int bn, int rn, std::set<Room::List>& output, bool stopByFirstMatch = false )
{
    bool status = false;

    if( rn >= rooms.size() )
    {
        if( bookings.empty() )
        {
            output.insert(rooms);
            status = true;
        }            
    }
    else if( bn >= bookings.size() )
    {
        status = assignBookings( openBookings, {}, rooms, 0, rn+1, output, stopByFirstMatch );
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
            
            status = assignBookings( bookings, openBookings, rooms, bn+1, rn, output, stopByFirstMatch ); 

            if( stopByFirstMatch == true && status == true)
                break;

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
    // define some rooms
    Room::List rooms = {Room(0), Room(1), Room(2), Room(3), Room(4) };
    
    // add fixed bookings, which cannot be shifted
    rooms.at(0).bookings.push_back(Booking(0, 3, 5, 'X', false));
    rooms.at(2).bookings.push_back(Booking(1, 0, 3, 'X', false));

    // define some bookings
    Booking::List bookings = { Booking(2, 1, 2, 'A', true)
                             , Booking(3, 0, 4, 'B', true)
                             , Booking(4, 0, 0, 'C', true)
                             , Booking(5, 1, 3, 'D', true)
                             , Booking(6, 5, 6, 'E', true)
                             , Booking(7, 7, 10, 'D', true)
                             , Booking(8, 3, 6, 'F', true)
                             , Booking(9, 0, 1, 'G', true)
                            };

    // assign bookings to rooms
    std::set<Room::List> output;
    assignBookings( bookings, {}, rooms, 0, 0, output, true );

    // print all possible solutions
    for( const auto& out : output )
        Room::print(out);

    return 0;
}
