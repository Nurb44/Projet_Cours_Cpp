#include <iostream>
#include <stdlib.h>
#include <chrono>
#include "..\inc\Command.h"
#include "..\inc\Data.h"
#include "..\inc\Knn.h"
#include "..\inc\ClassificationReport.h"

using namespace std;

class Timer
{
public:
    Timer() : beg_(clock_::now()) {}
    void reset() { beg_ = clock_::now(); }
    double elapsed() const {
        return std::chrono::duration_cast<second_>
                (clock_::now() - beg_).count(); }

private:
    typedef std::chrono::high_resolution_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> beg_;
};

int main()
{
    // Enter command line
    string trainingDataPath, testDataPath;
    int k;
    Command app = Command();

    while(app.process())
    {
        // Start timer
        Timer tmr;

        // Process

        // Stop and display timer
        double t = tmr.elapsed();
        cout << "Time to work: " << t << endl;
    }
    return 0;
}
