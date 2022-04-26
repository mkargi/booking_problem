#include <iostream>
#include <set>
#include "booking.h"
#include "room.h"

using namespace bp;



bool sortBookings( Booking::List bookings, Booking::List openBookings, Room::List rooms, int bn, int rn, std::set<Room::List>& output, bool stopByFirstMatch = false )
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
        status = sortBookings( openBookings, {}, rooms, 0, rn+1, output, stopByFirstMatch );
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
            
            status = sortBookings( bookings, openBookings, rooms, bn+1, rn, output, stopByFirstMatch ); 

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
    Booking b0(0, 3, 5, 'X', false);
    Booking b1(2, 0, 6, 'B', true);

    auto status = b0.isOverlapping(b1);

    Room::List rooms = {Room(0), Room(1), Room(2), Room(3) };
    Booking::List bookings = { Booking(2, 1, 2, 'A', true)
                             , Booking(3, 0, 6, 'B', true)
                             , Booking(4, 0, 0, 'C', true)
                             , Booking(5, 1, 2, 'D', true)
                             , Booking(6, 5, 6, 'E', true) };

    rooms.at(0).bookings.push_back(Booking(0, 3, 5, 'X', false));
    rooms.at(2).bookings.push_back(Booking(1, 0, 3, 'X', false));

    std::set<Room::List> output;
    sortBookings( bookings, {}, rooms, 0, 0, output, false );

    for( const auto& out : output )
    {
        Room::print(out);
    }

    return 0;
}
