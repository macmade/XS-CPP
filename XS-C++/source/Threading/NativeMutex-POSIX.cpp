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
 * @copyright   (c) 2015 - Jean-David Gadina - www.xs-labs.com
 * @brief       Definition of the XS::Threading::NativeMutex class
 */

#include <XS-C++.hpp>
#include <XS/PIMPL/Object-IMPL.hpp>
#include <pthread.h>

namespace XS
{
    #ifdef __clang__
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wpadded"
    #endif
    
    template<>
    class PIMPL::Object< Threading::NativeMutex >::IMPL
    {
        public:
            
            IMPL( bool recursive ): _recursive( recursive )
            {
                this->CreateMutex();
            }
            
            IMPL( const IMPL & o ): _recursive( o._recursive )
            {
                 this->CreateMutex();
            }
            
            ~IMPL( void )
            {
                this->DeleteMutex();
            }
            
            void CreateMutex( void )
            {
                pthread_mutexattr_t attr;
                
                if( pthread_mutexattr_init( &attr ) != 0 )
                {
                    throw Exception( "Error initializing the mutex object" );
                }
                
                if( this->_recursive )
                {
                    if( pthread_mutexattr_settype( &attr, PTHREAD_MUTEX_RECURSIVE ) != 0 )
                    {
                        pthread_mutexattr_destroy( &attr );
                        
                        throw Exception( "Error initializing the mutex object" );
                    }
                }
                
                if( pthread_mutex_init( &( this->_mtx ), &attr ) != 0 )
                {
                    pthread_mutexattr_destroy( &attr );
                    
                    throw Exception( "Error initializing the mutex object" );
                }
                
                pthread_mutexattr_destroy( &attr );
            }
            
            void DeleteMutex( void )
            {
                pthread_mutex_destroy( &( this->_mtx ) );
            }
            
            bool            _recursive;
            pthread_mutex_t _mtx;
    };
    
    #ifdef __clang__
    #pragma clang diagnostic pop
    #endif
    
    namespace Threading
    {
        void NativeMutex::Lock( void )
        {
            pthread_mutex_lock( &( this->impl->_mtx ) );
        }
        
        void NativeMutex::Unlock( void )
        {
            pthread_mutex_unlock( &( this->impl->_mtx ) );
        }
        
        bool NativeMutex::TryLock( void )
        {
            return ( pthread_mutex_trylock( &( this->impl->_mtx ) ) == 0 ) ? true : false;
        }
    }
}
