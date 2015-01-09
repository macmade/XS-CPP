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
 
/* $Id$ */

/*!
 * @file        XS-PIMPL-Object.cpp
 * @copyright   (c) 2015 - Jean-David Gadina - www.xs-labs.com
 * @abstract    Test case XS::PIMPL::Object
 */

using namespace testing;

class Base: XS::PIMPL::Object< Base >
{
    public:
        
        Base( void ): _x( 0 ), _y( 0 )
        {}
        
        int GetX( void )
        {
            return this->_x;
        }
        
        int GetY( void )
        {
            return this->_y;
        }
        
        void SetX( int x )
        {
            this->_x = x;
        }
        
        void SetY( int y )
        {
            this->_y = y;
        }
        
    private:
        
        int _x;
        int _y;
};

TEST( XS_PIMPL_Object, BaseClassGetter )
{
    Base b;
    
    ASSERT_EQ( 0, b.GetX() );
    ASSERT_EQ( 0, b.GetY() );
}

TEST( XS_PIMPL_Object, BaseClassSetter )
{
    Base b;
    
    b.SetX( 1 );
    b.SetY( 2 );
    
    ASSERT_EQ( 1, b.GetX() );
    ASSERT_EQ( 2, b.GetY() );
}
