#include <iostream>
#include <future>
#include <chrono>
#include <string>
#define CLEAR_SCREEN() std::cout << "\x1B[2J"
#define CURSOR_HOME()  std::cout << "\x1B[H"

// your existing function
int readInValue(int minVal, int maxVal){
   bool success = false;
   int temp;
   while(!success){
        std::string line;
        std::cout << " \n";
        std::cin >> line;
        try{
            temp = std::stoi(line);
            if(temp < minVal || temp > maxVal){
                throw std::out_of_range("out of range");
            }
            temp = std::stoi(line);
            success = true;
        }
        catch(const std::invalid_argument&){
            std::cerr<< "Error: Invalid Argument\n";
        }
        catch(const std::out_of_range&){
            std::cerr << "Error: Out of range\n";
        }
    }
    return temp;
}

// reads an int between [minVal..maxVal], but gives up after timeoutSeconds
// throws std::runtime_error on timeout
int readWithCountdown(int minVal, int maxVal, int timeoutSeconds) {
    // 1) Launch the blocking input in another thread
    minVal = 0;
    maxVal = 9999999;
    auto inputTask = std::async(std::launch::async, [=]() {
        return readInValue(minVal, maxVal);
    });

    // 2) Compute our deadline
    auto deadline = std::chrono::steady_clock::now() 
                  + std::chrono::seconds(timeoutSeconds);

    // 3) Loop until either input arrives or we hit the deadline
    while (true) {
        // 3a) Check if the user has entered something yet
        if (inputTask.wait_for(std::chrono::milliseconds(0)) 
                    == std::future_status::ready) {
            return inputTask.get();  // SUCCESS: we have the value
        }

        // 3b) Otherwise, update the countdown display
        auto now = std::chrono::steady_clock::now();
        int remaining = std::chrono::duration_cast<std::chrono::seconds>(
                            deadline - now).count();

        if (remaining < 0) {
            throw std::runtime_error("Input timed out");
        }

        // move cursor back to top, redraw UI + countdown
        CLEAR_SCREEN();
        CURSOR_HOME();
        std::cout << "---------------------------------- Newbie Farmer ----------------------------------------\n";
        // … your other UI code here …
        std::cout << "Time left to choose (secs): " 
                  << remaining << "  \n"
                  << "Enter something: " << std::flush;

        // sleep a bit so we don’t hammer the CPU
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

int main() {
    try {
        int temp = readWithCountdown(0, 3, 10);  // 10‐second timeout
        std::cout << "\nYou entered: " << temp << "\n";
        // ... handle temp as before ...
    }
    catch (const std::runtime_error& e) {
        std::cout << "\nNo input in time, moving on...\n";
    }
    return 0;
}