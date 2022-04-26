#ifndef BOOKING_H_
#define BOOKING_H_

#include <vector>

namespace bp
{
    class Booking
    {
        public:
        using List = std::vector<Booking>;

        static void print(const Booking::List& bookings)
        {
            for (const auto& booking : bookings)
            {
                std::cout << "booking " << booking.id << ":";
                std::cout << " start=" << booking.start << ",";
                std::cout << " end=" << booking.end << ",";
                std::cout << " symbol=" << booking.symbol << ",";
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }

        public:
            Booking(int id, int start, int end, char symbol, bool is_moveable)
                : id(id), start(start), end(end), symbol(symbol), is_moveable(is_moveable)
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
            char symbol;
    };
}

#endif /* BOOKING_H_ */