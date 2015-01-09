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
 * @file        Mutex-STL.cpp
 * @copyright   (c) 2015 - Jean-David Gadina - www.xs-labs.com
 * @abstract    Definition of the XS::Threading::Mutex class (STL implementation)
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
    class PIMPL::Object< Threading::Mutex >::IMPL
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
                if( this->_recursive )
                {
                    this->_mtx  = nullptr;
                    this->_rmtx = new std::recursive_mutex;
                }
                else
                {
                    this->_mtx  = new std::mutex;
                    this->_rmtx = nullptr;
                }
            }
            
            void DeleteMutex( void )
            {
                delete this->_mtx;
                delete this->_rmtx;
                
                this->_mtx  = nullptr;
                this->_rmtx = nullptr;
            }
            
            bool                   _recursive;
            std::mutex           * _mtx;
            std::recursive_mutex * _rmtx;
    };
    
    #ifdef __clang__
    #pragma clang diagnostic pop
    #endif
    
    template<>
    void PIMPL::Object< Threading::Mutex >::D::operator ()( PIMPL::Object< Threading::Mutex >::IMPL * p )
    {
        delete p;
    }

    template class PIMPL::Object< Threading::Mutex >;
    
    namespace Threading
    {
        Mutex::Mutex( bool recursive ): XS::PIMPL::Object< Mutex >( recursive )
        {}
        
        void Mutex::Lock( void )
        {
            if( this->impl->_recursive )
            {
                this->impl->_rmtx->lock();
            }
            else
            {
                this->impl->_mtx->lock();
            }
        }
        
        void Mutex::Unlock( void )
        {
            if( this->impl->_recursive )
            {
                this->impl->_rmtx->unlock();
            }
            else
            {
                this->impl->_mtx->unlock();
            }
        }
        
        bool Mutex::TryLock( void )
        {
            if( this->impl->_recursive )
            {
                return this->impl->_rmtx->try_lock();
            }
            
            return this->impl->_mtx->try_lock();
        }
    }
}
