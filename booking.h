#ifndef BOOKING_H_
#define BOOKING_H_

#include <vector>

namespace bp
{
    class Booking
    {
        public:
        using List = std::vector<Booking>;

        public:
            Booking(int id, int start, int end, bool is_moveable)
                : id(id), start(start), end(end), is_moveable(is_moveable)
            {}  

            bool isOverlapping( const Booking& booking ) const
            {
                bool status = false;
                if( (start >= booking.start && start <= booking.end) ||
                    (end >= booking.start && end <= booking.end) ||
                    (start <= booking.start && end >= booking.end) )
                {
                    status = true;
                }
                return status;
            }

        public:
            int id;
            int start;
            int end;
            bool is_moveable; 

    };
}

#endif /* BOOKING_H_ */