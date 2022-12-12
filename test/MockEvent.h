// Nevzat Seferoglu
// 171044024
// CSE437 - HW1

#pragma once
#include <cstddef>
#include <memory>
#include <string>
#include <iostream>
#include <cstring>


/* It is mock class that keeps an event time and info in it.
* It is used for testing purposes.
*/
class MockEvent
{
public:
    MockEvent() = default;

    MockEvent( int mockTime, const char* mockInfo )
        : mockTime_(mockTime)
    {
        mockInfo_ = new char [strlen(mockInfo) + 1];
        strcpy(mockInfo_, mockInfo);
        mockInfo_[strlen(mockInfo)] = '\0';
    }

    MockEvent( const MockEvent& event )
    {
        if ( this != &event ) {
            mockTime_ = event.mockTime_;
            mockInfo_ = new char [strlen(event.mockInfo_) + 1];
            strcpy(mockInfo_, event.mockInfo_);
            mockInfo_[strlen(event.mockInfo_)] = '\0';
        }
    }

    MockEvent( MockEvent&& event )
    {
        if ( this != &event ) {
            mockTime_ = event.mockTime_;
            mockInfo_ = event.mockInfo_;
            event.mockInfo_ = nullptr;
            event.mockTime_ = -1;
        }
    }

    MockEvent &operator=( const MockEvent& event ) {
        if ( this != &event ) {
            delete mockInfo_;
            mockTime_ = event.mockTime_;
            mockInfo_ = new char [strlen(event.mockInfo_) + 1];
            strcpy(mockInfo_, event.mockInfo_);
            mockInfo_[strlen(event.mockInfo_)] = '\0';
        }
        return *this;
    }

    MockEvent &operator=( MockEvent&& event ) {
        if ( this != &event ) {
            this -> mockTime_ = -1;
            delete this -> mockInfo_;
            mockTime_ = event.mockTime_;
            mockInfo_ = event.mockInfo_;
            event.mockInfo_ = nullptr;
            event.mockTime_ = -1;
        }
        return *this;
    }
     
    bool operator==( const MockEvent& event ) const
    {
        if ( strcmp(event.mockInfo_, mockInfo_) == 0 && event.mockTime_ == mockTime_ ) {
            return true;
        }
        return false;
    }

    bool operator<( const MockEvent& event ) const
    {
        return mockTime_ < event.mockTime_;
    }
    
    int Time() {
        return mockTime_;     
    }

    friend std::ostream& operator<<( std::ostream&, MockEvent );
    
    ~MockEvent() {
        delete mockInfo_;
        mockTime_ = -1;
    } 
private:
    int mockTime_ = -1;
    char* mockInfo_ = nullptr; 
};



