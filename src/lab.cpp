#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <atomic>
#include <chrono>
#include <deque>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

// Returns a random food from the set listed below
// You should not ever change code in this function.
std::string get_random_food() 
{
    static const std::vector<std::string> RANDOM_WORDS {"fish", "steak", "icecream", "sushi", "pork", "KD", "eggs", "bread"};
    
    const size_t idx = std::round((1.0 * rand() / RAND_MAX) * (RANDOM_WORDS.size() - 1));
    return RANDOM_WORDS[idx];
}

void chef_thread(bool* kill, std::mutex* mutex, std::deque<std::string>* foodQ, const int threadNumber) 
{
    // Create a loop that checks "kill" to see if it is true, if it is, break the loop.
    // Within the loop, sleep for 500ms then push a random word onto the queue, then 
    // print "Cooked $threadNumber -> $food" 
    
}

void patron_thread(bool* kill, std::mutex* mutex, std::deque<std::string>* foodQ, const int threadNumber) {
    // Create a loop that checks "kill" to see if it is true, if it is then break the loop.
    // Within the loop, sleep for 500ms then eat as much food as you can from `foodQ`. 
    // For each food item, print "Eaten $threadNumber -> $food"
    
}

int main(int argc, char **argv) {
    /* do not remove me */
    srand(time(0));
    
    std::deque<std::string> foodQ;
    bool kill(false);
    
    // Create two loops, first loop creates 3 threads for "chef_thread" and passes
    // a pointer to `kill`, and `foodQ` and the thread thread number 
    // For the second loop, create two threads, passing the same parameters but using
    // patron_thread instead
    
    // Be sure to read the constructor documentation for std::thread ( http://bit.ly/1jX1nxq )
    // Also, make sure the threads that are created are stored within the vector of threads so
    // they can be joined and deleted later.
    
    // Add work below:
    
    std::cout << "Hello World!\n";

    return 0;
}
