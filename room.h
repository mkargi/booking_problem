#ifndef ROOM_H_
#define ROOM_H_

#include <vector>
#include "booking.h"
#include <numeric>

namespace bp
{
    class Room
    {
        public:
        using List = std::vector<Room>;

        static void print(const Room::List& rooms)
        {
            for (const auto& room : rooms)
            {
                std::cout << "room" << room.id << ":";
                char c[30];
                std::fill(c, c + 30, '-');
                for (const auto& booking : room.bookings)
                {
                    for( int i=booking.start; i<=booking.end; ++i )
                    {
                        c[i] = booking.symbol;
                    }
                }
                std::cout << c << "";
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }


        public:
        Room(int id, const Booking::List& bookings = {})
            : id(id), bookings( bookings )
        {}

        bool isOverlapping( const Booking& booking ) const
        {
            bool status = false;
            for( const auto& b : bookings )
            {
                if( b.isOverlapping(booking) )
                {
                    status = true;
                    break;
                }
            }
            return status;
        }

        bool operator<(const Room& rhs) const
        {
            int hash0 = id + std::accumulate(bookings.begin(), bookings.end(), 0, [](int sum, const Booking& booking) {
                return sum + booking.id;
            });

            int hash1 = rhs.id + std::accumulate(rhs.bookings.begin(), rhs.bookings.end(), 0, [](int sum, const Booking& booking) {
                return sum + booking.id;
            });
            return  hash0 < hash1;
        }


        public:
        int id;
        Booking::List bookings;
    };
}

#endif /* ROOM_H_ */