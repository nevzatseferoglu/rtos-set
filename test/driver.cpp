// Nevzat Seferoglu
// 171044024
// CSE437 - HW1

#include <algorithm>
#include <iostream>
#include <thread>
#include <vector>
#include <cassert>
#include "MockEvent.h"
#include "../set.h"

using namespace Rtos;

/*
* Starts 1000 threads. Each thread apply same operation to set.
* Ensure that the last set view is consistent.
*/
void Test_WriteAndRemove() {
    std::cout << "--Begin Test_WriteAndRemove--"<< std::endl;
    ThreadSafeSet<int> testSet;
    std::vector<std::thread> threads;
    for ( int i = 0; i < 1000; i++ ) {
        threads.emplace_back(std::thread([&testSet]{
            for (int i = 0; i < 100; ++i) {
                testSet.insert(i);
            }
            for (int i = 0; i < 50; ++i) {
                testSet.remove(i);
            }
        }));
    }
    for (auto& thread : threads) {
        thread.join();
    }
    std::cout << testSet << std::endl;
    if ( testSet.size() == 50 ) {
        std::cout << "--End Test_WriteAndRemove, PASS--" << std::endl;
    } else {
        std::cout << "--End Test_WriteAndRemove, FAIL--" << std::endl;
    }
    std::cout << std::endl;
}

/* Test usage of CustomType */
void Test_CustomType() {
    std::cout << "--Begin Test_CustomType--"<< std::endl;
    MockEvent e0(0, "0_info");
    MockEvent e1(1, "1_info");
    MockEvent e2(2, "2_info");
    MockEvent e3(3, "3_info");
    MockEvent e4(4, "4_info");
    MockEvent e5(5, "5_info");
    MockEvent e6(6, "6_info");

    ThreadSafeSet<MockEvent> testSet;
    // inserting item in reverse order
    testSet.insert(e5);
    testSet.insert(e4);
    testSet.insert(e3);
    testSet.insert(e2);
    testSet.insert(e1);
    testSet.insert(e0);
    testSet.insert(std::move(e6));
    testSet.insert(MockEvent(7, "7_info"));
    std::cout << "size: " << testSet.size() << std::endl;
    if ( testSet.search(e2) ) {
        std::cout << e2 << " is in the set!" << std::endl;
    }
    testSet.iterate([](const MockEvent& e){
        std::cout << e << std::endl;  
    });
    std::cout << "Cleared!" << std::endl;
    testSet.clear();
    if ( testSet.size() == 0 ) {
        std::cout << "--End Test_CustomType PASS--" << std::endl;
    }
    std::cout << std::endl;
}

std::ostream& operator<<( std::ostream& os, MockEvent e)
{
    os << "time: " << e.mockTime_ << " info: " << e.mockInfo_;
    return os;
}

int main() {
    // test thread-safety with 1000 threads
    Test_WriteAndRemove();
    
    // test CustomType validity
    Test_CustomType();
    return 0;
}

