/*******************************************************************************
 * Copyright (c) 2015, Jean-David Gadina - www.xs-labs.com
 * Distributed under the Boost Software License, Version 1.0.
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/

/*!
 * @file        Semaphore.cpp
 * @copyright   (c) 2015 - Jean-David Gadina - www.xs-labs.com
 * @brief       Definition of the XS::Threading::Semaphore class
 */

#include <XS-C++.h>
#include <XS-C++/PIMPL/Object-IMPL.h>

#ifdef __APPLE__
#include <mach/mach_init.h>
#include <mach/task.h>
#include <mach/semaphore.h>
#endif

namespace XS
{
    #ifdef __clang__
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wpadded"
    #endif
    
    template<>
    class PIMPL::Object< Threading::Semaphore >::IMPL
    {
        public:
            
            IMPL( unsigned int count ): _count( count )
            {
                this->CreateSemaphore();
            }
            
            IMPL( const IMPL & o ): _count( o._count )
            {
                ( void )o;
                
                this->CreateSemaphore();
            }
            
            ~IMPL( void )
            {
                this->DeleteSemaphore();
            }
            
            void CreateSemaphore( void )
            {
                if( semaphore_create( mach_task_self(), &( this->_semaphore ), SYNC_POLICY_FIFO, static_cast< int >( this->_count ) ) != KERN_SUCCESS )
                {
                    /* TODO: throw */
                    throw 0;
                }
            }
            
            void DeleteSemaphore( void )
            {
                semaphore_destroy( mach_task_self(), this->_semaphore );
            }
            
            unsigned int _count;
            semaphore_t  _semaphore;
    };
    
    #ifdef __clang__
    #pragma clang diagnostic pop
    #endif
    
    template<>
    void PIMPL::Object< Threading::Semaphore >::D::operator ()( PIMPL::Object< Threading::Semaphore >::IMPL * p )
    {
        delete p;
    }

    template class PIMPL::Object< Threading::Semaphore >;
    
    namespace Threading
    {
        Semaphore::Semaphore( unsigned int count ): XS::PIMPL::Object< Semaphore >( count )
        {
            if( count == 0 )
            {
                XS::Exception e( "Cannot initialize a semaphore with zero as count" );
                
                throw e;
            }
        }
        
        bool Semaphore::TryWait( void )
        {
            {
                mach_timespec_t ts;
                
                ts.tv_sec  = 0;
                ts.tv_nsec = 0;
                
                return ( semaphore_timedwait( this->impl->_semaphore, ts ) == KERN_SUCCESS ) ? true : false;
            }
        }
        
        void Semaphore::Signal( void )
        {
            semaphore_signal( this->impl->_semaphore );
        }
    }
}
