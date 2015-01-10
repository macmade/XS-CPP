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
 * @abstract    Declaration of the XS::Version class
 */

#ifndef __XSCPP_VERSION_H__
#define __XSCPP_VERSION_H__

namespace XS
{
    /*!
     * @class           XS::Version
     * @abstract        Version class
     * @discussion      This class is thread-safe
     */
    class Version: public XS::PIMPL::Object< Version >, public XS::ToStringable
    {
        public:
            
            using PIMPL::Object< Version >::impl;
            
            /*!
             * @typedef     XS::Version::Status
             * @abstract    Predefined version statuses
             */
            typedef enum
            {
                StatusAlpha             = 0, /*! Alpha status (-a) */
                StatusBeta              = 1, /*! Beta status (-b) */
                StatusReleaseCandidate  = 2, /*! Release candidate status (-rc) */
                StatusFinal             = 3  /*! Final status (-r) */
            }
            Status;
            
            /*!
             * @function    Version
             * @abstract    Class constructor
             * @param       major       The version's major number
             * @param       minor       The version's minor number
             * @param       build       The version's build number
             * @param       revision    The version's revision number
             * @param       status      The version's status
             */
            Version( unsigned int major = 0, unsigned int minor = 0, unsigned int build = 0, unsigned int revision = 0, Status status = StatusFinal );
            
            /*!
             * @function    operator std::string
             * @abstract    Type-casting to std::string
             * @see         ToString
             */
            operator std::string( void ) const;
            
            /*!
             * @function    ToString
             * @abstract    Gets a string representation of the version
             * @return      A string representation of the object
             * @discussion  This method will return a string representation in
             *              the following form:
             *              [major].[minor].[build]-[status][revision]
             *              eg: 1.2.3-rc4
             *              Note that for version objects with a "final" status,
             *              the status/revision part will be ommited if the
             *              revision number is zero.
             */
            std::string ToString( void ) const;
            
            /*!
             * @function    GetMajor
             * @abstract    Gets the version's major number
             * @return      The version's major number
             */
            unsigned int GetMajor( void ) const;
            
            /*!
             * @function    GetMinor
             * @abstract    Gets the version's minor number
             * @return      The version's minor number
             */
            unsigned int GetMinor( void ) const;
            
            /*!
             * @function    GetBuild
             * @abstract    Gets the version's build number
             * @return      The version's build number
             */
            unsigned int GetBuild( void ) const;
            
            /*!
             * @function    GetRevision
             * @abstract    Gets the version's revision number
             * @return      The version's revision number
             */
            unsigned int GetRevision( void ) const;
            
            /*!
             * @function    GetStatus
             * @abstract    Gets the version's status
             * @return      The version's status
             */
            Status GetStatus( void ) const;
            
            /*!
             * @function    SetMajor
             * @abstract    Sets the version's major number
             * @param       value   The major number to set
             */
            void SetMajor( unsigned int value );
            
            /*!
             * @function    SetMinor
             * @abstract    Sets the version's minor number
             * @param       value   The minor number to set
             */
            void SetMinor( unsigned int value );
            
            /*!
             * @function    SetBuild
             * @abstract    Sets the version's build number
             * @param       value   The build number to set
             */
            void SetBuild( unsigned int value );
            
            /*!
             * @function    SetRevision
             * @abstract    Sets the version's revision number
             * @param       value   The revision number to set
             */
            void SetRevision( unsigned int value );
            
            /*!
             * @function    SetStatus
             * @abstract    Sets the version's status
             * @param       value   The status to set
             */
            void SetStatus( Status value );
    };
}

#endif /* __XSCPP_VERSION_H__ */
