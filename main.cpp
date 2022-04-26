#include <iostream>
#include <set>
#include <map>
#include <algorithm>
#include "booking.h"
#include "room.h"

using namespace bp;

bool preCheck( Booking::List& bookings, int maxRooms )
{
    std::sort(bookings.begin(), bookings.end(), [](const Booking& b0, const Booking& b1){ return b0.start < b1.start; } );
    std::map<int, int> counter;

    for( const auto& booking : bookings )
        for( int i=booking.start; i<=booking.end; i++)
            counter[i]++;

    for( const auto& [key,val] : counter)
        if( val > maxRooms )
            return false;

    return true;
}

bool assignBookings( Booking::List bookings, Booking::List openBookings, Room::List rooms, int bn, int rn, std::set<Room::List>& output, bool stopByFirstMatch = false )
{
    static int counter = 0; 
    counter++;
    bool status = false;

    if( rn >= rooms.size() )
    {
        if( bookings.empty() )
        {
            output.insert(rooms);
            status = true;            
            std::cout << "counter " << counter << std::endl << std::flush;
        }            
    }
    else if( bn >= bookings.size() )
    {
        status = assignBookings( openBookings, {}, rooms, 0, rn+1, output, stopByFirstMatch );
    }
    else
    {  
        //std::cout << "rn: " << rn << " bn: " << bn << std::endl;
        for( int i=bn; i<bookings.size(); i++)
        {      
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
    rooms.at(2).bookings.push_back(Booking(1, 0, 4, 'X', false));

    // define some bookings
    Booking::List bookings = { Booking(2,   1,  2,  'A',    true)
                             , Booking(3,   0,  6,  'B',    true)
                             , Booking(4,   0,  0,  'C',    true)
                             , Booking(5,   1,  3,  'D',    true)
                             , Booking(6,   5,  7,  'E',    true)
                             , Booking(7,   6,  9,  'F',    true)
                             , Booking(8,   2,  4,  'G',    true)
                             , Booking(9,   0,  1,  'H',    true)
                             , Booking(10,  8, 10,  'I',    true)
                             , Booking(11,  5,  6,  'J',    true)
                             , Booking(12,  4,  5,  'K',    true)
                             , Booking(13,  6,  7,  'L',    true)
                             , Booking(14,  9, 12,  'M',    true)
                             , Booking(15,  7,  8,  'N',    true)
                             , Booking(16,  9, 12,  'O',    true)
                             , Booking(17,  7,  8,  'P',    true)
                             , Booking(18,  0,  0,  'Q',    true)
                             , Booking(19,  9,  15, 'Z',    true)
                            };

    // assign bookings to rooms
    std::set<Room::List> output;    
    if( preCheck( bookings, rooms.size() ) )
        assignBookings( bookings, {}, rooms, 0, 0, output, true );
    else
        std::cout << "too many bookings" << std::endl;

    // print all possible solutions
    for( const auto& out : output )
        Room::print(out);

    return 0;
}
