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
 * @brief       Definition of XS::Atomic::Increment64
 */

#include <XS-C++.h>

#if defined( _WIN32 )

#include <Windows.h>
#include <Winnt.h>

#elif defined( __APPLE__ )

#include <libkern/OSAtomic.h>

#else

#error "XS::Atomic::Increment64 is not implemented for the current platform"

#endif

namespace XS
{
    namespace Atomic
    {
        XS::Int64 Increment64( volatile XS::Int64 * value )
        {
            #if defined( _WIN32 )
            
            return static_cast< XS::Int64 >( InterlockedIncrement64( static_cast< volatile LONGLONG * >( value ) ) );
            
            #elif defined( __APPLE__ )
            
            return static_cast< XS::Int64 >( OSAtomicIncrement64( static_cast< volatile int64_t * >( value ) ) );
            
            #elif defined( __clang__ ) && __has_builtin( __sync_add_and_fetch )
            
            return __sync_add_and_fetch( value, 1 );
            
            #else
            
            #error "XS::Atomic::Increment64 is not implemented for the current platform"
            
            #endif
        }
    }
}
