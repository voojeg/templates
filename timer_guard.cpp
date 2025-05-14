#include <iostream>
#include <chrono>
#include <string>
#include <utility>

class TimerGuard {
public:
    TimerGuard(std::string message = "", std::ostream& out = std::cout) :
        start_(std::chrono::high_resolution_clock::now()), message_(std::move(message)), output_stream_(out)
    {
    }

    ~TimerGuard() {
        output_stream_ << message_ << " " <<
            std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_);
    }
    
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_;
    std::string message_;
    std::ostream& output_stream_;
};

