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
 * @file        XS-Atomic.cpp
 * @copyright   (c) 2015 - Jean-David Gadina - www.xs-labs.com
 * @abstract    Test case XS::Atomic
 */

using namespace testing;

TEST( XS_Atomic, Increment32 )
{
    XS::Int32 i = 0;
    
    ASSERT_EQ( 1, XS::Atomic::Increment32( &i ) );
    ASSERT_EQ( 1, i );
}

TEST( XS_Atomic, Increment64 )
{
    XS::Int64 i = 0;
    
    ASSERT_EQ( 1, XS::Atomic::Increment64( &i ) );
    ASSERT_EQ( 1, i );
}

TEST( XS_Atomic, Decrement32 )
{
    XS::Int32 i = 0;
    
    ASSERT_EQ( -1, XS::Atomic::Decrement32( &i ) );
    ASSERT_EQ( -1, i );
}

TEST( XS_Atomic, Decrement64 )
{
    XS::Int64 i = 0;
    
    ASSERT_EQ( -1, XS::Atomic::Decrement64( &i ) );
    ASSERT_EQ( -1, i );
}

TEST( XS_Atomic, Add32 )
{
    XS::Int32 i = 0;
    
    ASSERT_EQ( 1, XS::Atomic::Add32( 1, &i ) );
    ASSERT_EQ( 1, i );
}

TEST( XS_Atomic, Add64 )
{
    XS::Int64 i = 0;
    
    ASSERT_EQ( 1, XS::Atomic::Add64( 1, &i ) );
    ASSERT_EQ( 1, i );
}

TEST( XS_Atomic, CompareAndSwap32Success )
{
    XS::Int32 i = 0;
    
    ASSERT_TRUE( XS::Atomic::CompareAndSwap32( 0, 1, &i ) );
    ASSERT_EQ( 1, i );
}

TEST( XS_Atomic, CompareAndSwap32Failure )
{
    XS::Int32 i = 0;
    
    ASSERT_FALSE( XS::Atomic::CompareAndSwap32( 1, 2, &i ) );
    ASSERT_EQ( 0, i );
}

TEST( XS_Atomic, CompareAndSwap64Success )
{
    XS::Int64 i = 0;
    
    ASSERT_TRUE( XS::Atomic::CompareAndSwap64( 0, 1, &i ) );
    ASSERT_EQ( 1, i );
}

TEST( XS_Atomic, CompareAndSwap64Failure )
{
    XS::Int64 i = 0;
    
    ASSERT_FALSE( XS::Atomic::CompareAndSwap64( 1, 2, &i ) );
    ASSERT_EQ( 0, i );
}

TEST( XS_Atomic, CompareAndSwapPointerSuccess )
{
    int    i = 0;
    void * p = nullptr;
    
    ASSERT_TRUE( XS::Atomic::CompareAndSwapPointer( nullptr, &i, &p ) );
    ASSERT_EQ( &i, p );
}

TEST( XS_Atomic, CompareAndSwapPointerFailure )
{
    int    i = 0;
    void * p = nullptr;
    
    ASSERT_FALSE( XS::Atomic::CompareAndSwapPointer( &i, nullptr, &p ) );
    ASSERT_EQ( nullptr, p );
}
