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
 * @header      NativeMutex.h
 * @copyright   (c) 2015 - Jean-David Gadina - www.xs-labs.com
 * @abstract    Declaration of the XS::Threading::NativeMutex class
 */

#ifndef __XSCPP_THREADING_NATIVE_MUTEX_H__
#define __XSCPP_THREADING_NATIVE_MUTEX_H__

namespace XS
{
    namespace Threading
    {
        /*!
         * @class           XS::Threading::NativeMutex
         * @abstract        Mutex class
         */
        class NativeMutex: public XS::PIMPL::Object< NativeMutex >, public Lockable
        {
            public:
                
                using PIMPL::Object< NativeMutex >::impl;
                
                /*!
                 * @function    NativeMutex
                 * @abstract    Class constructor
                 * @param       recursive   Whether to create a recursive mutex or not
                 * @discussion  If the mutex if created as recursive (default),
                 *              it may be successfully locked multiple times by
                 *              the same thread.
                 *              If the mutex isn't recursive, a dead-lock will
                 *              occur if it is locked twice from the same
                 *              thread.
                 *              Note that if a recursive mutex is locked
                 *              multiple times by a thread, each call to the
                 *              'Lock' method shall be balanced by a call to
                 *              the 'Unlock' method.
                 *              
                 */
                NativeMutex( bool recursive = true );
                
                /*!
                 * @function    NativeMutex
                 * @abstract    Class copy constructor
                 * @param       o   Another mutex to be used as data source for the initialization
                 * @discussion  Deleted - Not copy-constructible
                 */
                NativeMutex( const NativeMutex & o ) = delete;
                
                /*!
                 * @function    operator =
                 * @abstract    Assignment operator
                 * @param       o   Another mutex to use as data source
                 * @discussion  Deleted - Not copy-assignable
                 */
                NativeMutex & operator =( NativeMutex o ) = delete;
                
                /*!
                 * @function    Lock
                 * @abstract    Locks the mutex
                 */
                void Lock( void );
                
                /*!
                 * @function    Unlock
                 * @abstract    Unlocks the mutex
                 */
                void Unlock( void );
                
                /*!
                 * @function    TryLock
                 * @abstract    Tries to lock the mutex
                 * @return      True if the mutex was successfully locked, otherwise false
                 * @discussion  This method will return 'true' if called
                 *              multiple times from the same thread.
                 *              Note that each call to this method still needs
                 *              to be balanced by a call to the 'unlock' method.
                 */
                bool TryLock( void );
        };
    }
}

#endif /* __XSCPP_THREADING_NATIVE_MUTEX_H__ */
