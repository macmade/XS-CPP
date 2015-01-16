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
 * @brief       Declaration of the XS::Atomic functions
 */

#ifndef __XSCPP_ATOMIC_H__
#define __XSCPP_ATOMIC_H__

namespace XS
{
    namespace Atomic
    {
        /*!
         * @brief       Issues a memory barrier/fence
         * 
         * Currently, this function is implemented for the following
         * architectures:
         *     - ARMv7
         *     - ARM64
         *     - x86
         *     - x86-64
         */
        void MemoryBarrier( void );
        
        /*!
         * @brief       Atomically increments a 32 bits integer value
         * @param       value       The value to increment
         * @return      The incremented value
         */
        XS::Int32 Increment32( volatile XS::Int32 * value );
        
        /*!
         * @brief       Atomically increments a 32 bits integer value
         * @param       value       The value to increment
         * @return      The incremented value
         */
        XS::Int64 Increment64( volatile XS::Int64 * value );
        
        /*!
         * @brief       Atomically decrements a 64 bits integer value
         * @param       value       The value to decrement
         * @return      The decremented value
         */
        XS::Int32 Decrement32( volatile XS::Int32 * value );
        
        /*!
         * @brief       Atomically decrements a 64 bits integer value
         * @param       value       The value to decrement
         * @return      The decremented value
         */
        XS::Int64 Decrement64( volatile XS::Int64 * value );
        
        /*!
         * @brief       Atomically adds to a 32 bits value
         * @param       amount      The amount to add
         * @param       value       The 32 bits value to modify
         * @return      The new value
         */
        XS::Int32 Add32( XS::Int32 amount, volatile XS::Int32 * value );
        
        /*!
         * @brief       Atomically adds to a 64 bits value
         * @param       amount      The amount to add
         * @param       value       The 64 bits value to modify
         * @return      The new value
         */
        XS::Int64 Add64( XS::Int64 amount, volatile XS::Int64 * value );
        
        /*!
         * @brief       Performs an atomic compare and swap on 32 bits integer values
         * @param       oldValue    The value to compare to (old value)
         * @param       newValue    The value to swap (new value)
         * @param       value       A pointer to the 32 bits integer value to compare and swap
         * @return      True if the comparison was equal and the swap occured, otherwise false
         */
        bool CompareAndSwap32( XS::Int32 oldValue, XS::Int32 newValue, volatile XS::Int32 * value );
        
        /*!
         * @brief       Performs an atomic compare and swap on 64 bits integer values
         * @param       oldValue    The value to compare to (old value)
         * @param       newValue    The value to swap (new value)
         * @param       value       A pointer to the 64 bits integer value to compare and swap
         * @return      True if the comparison was equal and the swap occured, otherwise false
         */
        bool CompareAndSwap64( XS::Int64 oldValue, XS::Int64 newValue, volatile XS::Int64 * value );
        
        /*!
         * @brief       Performs an atomic compare and swap on pointer values
         * @param       oldValue    The value to compare to (old value)
         * @param       newValue    The value to swap (new value)
         * @param       value       A pointer to the pointer value to compare and swap
         * @return      True if the comparison was equal and the swap occured, otherwise false
         */
        bool CompareAndSwapPointer( void * oldValue, void * newValue, void * volatile * value );
    }
}

#endif /* __XSCPP_ATOMIC_H__ */
