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
 * @file        XS-Version.cpp
 * @copyright   (c) 2015 - Jean-David Gadina - www.xs-labs.com
 * @abstract    Test case XS::Version
 */

using namespace testing;

TEST( XS_Version, Major )
{
    XS::Version v1;
    XS::Version v2( 1 );
    
    ASSERT_EQ( 0, static_cast< int >( v1.GetMajor() ) );
    ASSERT_EQ( 1, static_cast< int >( v2.GetMajor() ) );
    
    v1.SetMajor( 1 );
    
    ASSERT_EQ( 1, static_cast< int >( v1.GetMajor() ) );
}

TEST( XS_Version, Minor )
{
    XS::Version v1;
    XS::Version v2( 0, 1 );
    
    ASSERT_EQ( 0, static_cast< int >( v1.GetMinor() ) );
    ASSERT_EQ( 1, static_cast< int >( v2.GetMinor() ) );
    
    v1.SetMinor( 1 );
    
    ASSERT_EQ( 1, static_cast< int >( v1.GetMinor() ) );
}

TEST( XS_Version, Build )
{
    XS::Version v1;
    XS::Version v2( 0, 1, 2 );
    
    ASSERT_EQ( 0, static_cast< int >( v1.GetBuild() ) );
    ASSERT_EQ( 2, static_cast< int >( v2.GetBuild() ) );
    
    v1.SetBuild( 1 );
    
    ASSERT_EQ( 1, static_cast< int >( v1.GetBuild() ) );
}

TEST( XS_Version, Revision )
{
    XS::Version v1;
    XS::Version v2( 0, 1, 2, 3 );
    
    ASSERT_EQ( 0, static_cast< int >( v1.GetRevision() ) );
    ASSERT_EQ( 3, static_cast< int >( v2.GetRevision() ) );
    
    v1.SetRevision( 1 );
    
    ASSERT_EQ( 1, static_cast< int >( v1.GetRevision() ) );
}

TEST( XS_Version, Status )
{
    XS::Version v1;
    XS::Version v2( 0, 1, 2, 3, XS::Version::StatusAlpha );
    
    ASSERT_EQ( XS::Version::StatusFinal, static_cast< int >( v1.GetStatus() ) );
    ASSERT_EQ( XS::Version::StatusAlpha, static_cast< int >( v2.GetStatus() ) );
    
    v1.SetStatus( XS::Version::StatusAlpha );
    
    ASSERT_EQ( XS::Version::StatusAlpha, static_cast< int >( v1.GetStatus() ) );
}
