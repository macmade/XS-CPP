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
 * @abstract    Test case XS::Threading::Semaphore
 */

#include <XS-C++.h>
#include <GoogleMock/GoogleMock.h>

using namespace testing;

TEST( XS_Threading_Semaphore, UnnamedBinaryTryWait )
{
    XS::Threading::Semaphore sem;
    
    ASSERT_TRUE( sem.TryWait() );
    ASSERT_FALSE( sem.TryWait() );
    
    sem.Signal();
}

TEST( XS_Threading_Semaphore, NamedBinaryTryWait )
{
    XS::Threading::Semaphore sem1( 1, "XSCPPTestSemaphore" );
    XS::Threading::Semaphore sem2( 1, "XSCPPTestSemaphore" );
    
    ASSERT_TRUE( sem1.TryWait() );
    ASSERT_FALSE( sem1.TryWait() );
    ASSERT_FALSE( sem2.TryWait() );
    
    sem1.Signal();
    
    ASSERT_TRUE( sem2.TryWait() );
    ASSERT_FALSE( sem2.TryWait() );
    ASSERT_FALSE( sem1.TryWait() );
    
    sem2.Signal();
}

TEST( XS_Threading_Semaphore, UnnamedTryWait )
{
    XS::Threading::Semaphore sem( 2 );
    
    ASSERT_TRUE( sem.TryWait() );
    ASSERT_TRUE( sem.TryWait() );
    ASSERT_FALSE( sem.TryWait() );
    
    sem.Signal();
    sem.Signal();
}

TEST( XS_Threading_Semaphore, UnnamedWaitSignal )
{
    XS::Threading::Semaphore sem( 1 );
    
    sem.Wait();
    
    ASSERT_FALSE( sem.TryWait() );
    
    sem.Signal();
    
    ASSERT_TRUE( sem.TryWait() );
    
    sem.Signal();
}

TEST( XS_Threading_Semaphore, UnnamedThrowOnInvalidCount )
{
    ASSERT_THROW( XS::Threading::Semaphore( 0 ), XS::Exception );
}

TEST( XS_Threading_Semaphore, IsNamed )
{
    XS::Threading::Semaphore sem1( 1, "XSCPPTestSemaphore" );
    XS::Threading::Semaphore sem2;
    
    ASSERT_TRUE( sem1.IsNamed() );
    ASSERT_FALSE( sem2.IsNamed() );
}

TEST( XS_Threading_Semaphore, GetName )
{
    XS::Threading::Semaphore sem1( 1, "XSCPPTestSemaphore" );
    XS::Threading::Semaphore sem2;
    
    ASSERT_EQ( sem1.GetName(), "XSCPPTestSemaphore" );
    ASSERT_EQ( sem2.GetName(), "" );
}
