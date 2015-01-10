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
 * @header      Exception.h
 * @copyright   (c) 2015 - Jean-David Gadina - www.xs-labs.com
 * @abstract    Declaration of the XS::Exception class
 */

#ifndef __XSCPP_EXCEPTION_H__
#define __XSCPP_EXCEPTION_H__

namespace XS
{
    /*!
     * @class           XS::Exception
     * @abstract        Exception class
     * @discussion      All exception thrown by XS-C++ are instances of
     *                  this class.
     */
    class Exception: public XS::PIMPL::Object< Exception >, public std::exception, public ToStringable
    {
        public:
            
            using PIMPL::Object< Exception >::impl;
            
            /*!
             * @function    Exception
             * @abstract    Class constructor
             * @param       reason  The exception's reason
             * @param       code    The exception's code, if any
             */
            Exception( std::string reason, int code = 0 );
            
            std::string GetReason( void ) const;
            int GetCode( void ) const;
            const char * what( void ) const noexcept;
            std::string ToString( void ) const;
    };
}

#endif /* __XSCPP_EXCEPTION_H__ */
