// Nevzat Seferoglu
// 171044024
// CSE437 - HW1

#pragma once
#include <functional>
#include <mutex>
#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <type_traits>
#include <mutex>

namespace Rtos
{
    template<typename T>
    class ThreadSafeSet
    {
    public:
        // Initiates a set with default allocation.
        ThreadSafeSet()
        {
            allocated_ = 0;
            capacity_ = 10;
            uptr_ = std::make_unique<T[]>( capacity_ );
        }
        
        // Initiates a new set with given values.
        // Insert makes an lvalue insert.
        ThreadSafeSet( const std::initializer_list<T>& items )
            : ThreadSafeSet()
        {
            for ( auto item : items ) {
                insert(item);
            }
        }

        /* Insert(lvalue) the given element to set.
        * If the given item is already in the set, return false.
        * Otherwise, it inserts according the BST, then return true;
        */
        bool insert( const T& item )
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if ( in(item) == true ) {
                return false;
            }
            if ( !uptr_ ) {
                uptr_ = std::make_unique<T[]>( capacity_ );
            } else if (capacity_ == allocated_) {
                capacity_ *= 2;
                auto newPtr = std::make_unique<T[]>( capacity_ );
                std::copy(uptr_.get(), uptr_.get()+allocated_, newPtr.get());
                uptr_ = std::move(newPtr);
            }

            int index = std::lower_bound(uptr_.get(), uptr_.get() + 
                            allocated_, item) - uptr_.get();
            if ( allocated_ != 0 ) {
                for ( int i = allocated_ - 1; i >= index; i-- ) {
                    uptr_[i + 1] = uptr_[i];  
                }
            }
            uptr_[index] = item;
            allocated_++;
            return true;
        }
        
        /* Insert(rvalue) the given element to set.
        * If the given item is already in the set, return false.
        * Otherwise, it inserts according the BST, then return true;
        */
        bool insert( T&& item )
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if ( in(item) == true ) {
                return false;
            }
            if ( !uptr_ ) {
                uptr_ = std::make_unique<T[]>( capacity_ );
            } else if (capacity_ == allocated_) {
                capacity_ *= 2;
                auto newPtr = std::make_unique<T[]>( capacity_ );
                std::copy(uptr_.get(), uptr_.get()+allocated_, newPtr.get());
                uptr_ = std::move(newPtr);
            }
            int index = std::lower_bound(uptr_.get(), uptr_.get() + 
                            allocated_, std::move(item)) - uptr_.get();
            if ( allocated_ != 0 ) {
                for ( int i = allocated_ - 1; i >= index; i-- ) {
                    uptr_[i + 1] = uptr_[i];  
                }
            }
            uptr_[index] = std::move(item);
            allocated_++;
            return true;
        } 
        
        /* Returns the size of the set. */
        int size() const
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            return allocated_;
        }
        
        /* Search for given element in the set.
        * If the item is in the set, returns true.
        * Otherwise, it returns false.
        */
        bool search( const T& item ) const
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            return in(item);
        }

        /* Remove given item from the set.
        * If given item is not located in the set before, it returns false.
        * Otherwise, it return true.
        */
        bool remove( const T& item ) {
            std::lock_guard<std::mutex> lock(m_mutex);
            if ( in(item) == false ) {
                return false;
            }
            int index = std::lower_bound(uptr_.get(), uptr_.get() + 
                            allocated_, item) - uptr_.get();
            for ( int i = index; i < allocated_; i++ ) {
                uptr_[i] = uptr_[i+1];  
            }
            allocated_--;
            return true;
        }
        
        /* Clear set, deallocate underlying buffer */ 
        void clear() {
            std::lock_guard<std::mutex> lock(m_mutex);
            uptr_.reset();
            allocated_ = 0;
        }
        
        /* Iterate on set content by applying given function */
        template<typename F>
        void iterate(F&& func) {
            std::lock_guard<std::mutex> lock(m_mutex);
            for ( int i = 0; i < allocated_; i++ ) {
                func(uptr_[i]);
            }
        }
        
        template <typename U>
        friend std::ostream& operator<<( std::ostream&, const ThreadSafeSet<U>& );

    private:
        bool in( const T& item ) const
        {
            if ( !uptr_ ) {
                return false;
            }
            return std::binary_search(uptr_.get(), uptr_.get() + allocated_, item);
        }
        
        // lock
        mutable std::mutex m_mutex;

        // capacity of the set
        int capacity_ = 10;
        
        // allocation of the set
        int allocated_ = 0;

        // underlying buffer
        std::unique_ptr<T[]> uptr_;
    }; 

    template<typename T>
    std::ostream& operator<<( std::ostream& os, const ThreadSafeSet<T>& set )
    {
        std::lock_guard<std::mutex> lock(set.m_mutex);
        if ( !set.uptr_ ) {
            os << "There is no object!"; 
            return os;
        }
        os << "[ ";
        for ( int i = 0; i < set.allocated_; i++ ) {
            os << set.uptr_[i];
            if ( i != set.allocated_ - 1 ) {
                os << " ";
            }
        }
        os << " ]"; 
        return os;
    }
}
