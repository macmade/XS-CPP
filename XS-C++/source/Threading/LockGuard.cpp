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
 * @file        LockGuard.cpp
 * @copyright   (c) 2015 - Jean-David Gadina - www.xs-labs.com
 * @abstract    Definition of the XS::Threading::LockGuard class
 */

#include <XS-C++.h>
#include <XS-C++/PIMPL/Object-IMPL.h>

namespace XS
{
    #ifdef __clang__
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wpadded"
    #endif
    
    template<>
    class PIMPL::Object< Threading::LockGuard >::IMPL
    {
        public:
            
            IMPL( Threading::Lockable * lock ): _lock( lock )
            {
                this->_lock->Lock();
            }
            
            IMPL( const IMPL & o ): _lock( o._lock )
            {
                this->_lock->Lock();
            }
            
            ~IMPL( void )
            {
                this->_lock->Unlock();
            }
            
            Threading::Lockable * _lock;
    };
    
    #ifdef __clang__
    #pragma clang diagnostic pop
    #endif
    
    template<>
    void PIMPL::Object< Threading::LockGuard >::D::operator ()( PIMPL::Object< Threading::LockGuard >::IMPL * p )
    {
        delete p;
    }

    template class PIMPL::Object< Threading::LockGuard >;
    
    namespace Threading
    {
        LockGuard::LockGuard( Lockable * lock ): XS::PIMPL::Object< LockGuard >( lock )
        {}
    }
}
