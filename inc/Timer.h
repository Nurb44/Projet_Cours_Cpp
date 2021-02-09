#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <iomanip>
#include <chrono>

class Timer
{
    public:
    Timer() : beg_(clock_::now()) {}
    void reset() { beg_ = clock_::now(); }
    double elapsed() const {
        return std::chrono::duration_cast<second_>
                (clock_::now() - beg_).count(); }
    std::string getString() const {
        double t = elapsed();
        std::string str = "Time to work: ";
        str += std::to_string(t);
        str += "s";
        return str;
    }

    private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
};

#endif