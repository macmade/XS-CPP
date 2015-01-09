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
 * @header      Version.h
 * @copyright   (c) 2015 - Jean-David Gadina - www.xs-labs.com
 * @abstract    Declaration of the XS::Version
 */

#ifndef __XSCPP_VERSION_H__
#define __XSCPP_VERSION_H__

namespace XS
{
    /*!
     * @class           XS::Version
     * @abstract        Version class
     */
    class Version: public XS::PIMPL::Object< Version >
    {
        public:
            
            using PIMPL::Object< Version >::impl;
            
            typedef enum
            {
                StatusAlpha             = 0,
                StatusBeta              = 1,
                StatusReleaseCandidate  = 2,
                StatusFinal             = 3
            }
            Status;
            
            Version( unsigned int major = 0, unsigned int minor = 0, unsigned int revision = 0, Status status = StatusFinal );
            unsigned int GetMajor( void ) const;
            unsigned int GetMinor( void ) const;
            unsigned int GetRevision( void ) const;
            Status GetStatus( void ) const;
            void SetMajor( unsigned int value );
            void SetMinor( unsigned int value );
            void SetRevision( unsigned int value );
            void SetStatus( Status value );
    };
}

#endif /* __XSCPP_VERSION_H__ */
