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
 * @file        Version.cpp
 * @copyright   (c) 2015 - Jean-David Gadina - www.xs-labs.com
 * @abstract    Definition of the XS::Version class
 */

#include <XS-C++.h>
#include <XS-C++/PIMPL/Object-IMPL.h>

namespace XS
{
    #ifdef __clang__
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wpadded"
    #endif
    
    template<>
    class PIMPL::Object< Version >::IMPL
    {
        public:
            
            IMPL( unsigned int major, unsigned int minor, unsigned int build, unsigned int revision, Version::Status status ): _major( major ), _minor( minor ), _build( build ), _revision( revision ), _status( status )
            {}
            
            /* TODO: Thread-safety */
            IMPL( const IMPL & o ): _major( o._major ), _minor( o._minor ), _build( o._build ), _revision( o._revision ), _status( o._status )
            {}
            
            ~IMPL( void )
            {}
            
            unsigned int    _major;
            unsigned int    _minor;
            unsigned int    _build;
            unsigned int    _revision;
            Version::Status _status;
    };
    
    #ifdef __clang__
    #pragma clang diagnostic pop
    #endif
    
    template<>
    void PIMPL::Object< Version >::D::operator ()( PIMPL::Object< Version >::IMPL * p )
    {
        delete p;
    }

    template class PIMPL::Object< Version >;
    
    Version::Version( unsigned int major, unsigned int minor, unsigned int build, unsigned int revision, Status status ): XS::PIMPL::Object< Version >( major, minor, build, revision, status )
    {}
    
    unsigned int Version::GetMajor( void ) const
    {
        return this->impl->_major;
    }
    
    unsigned int Version::GetMinor( void ) const
    {
        return this->impl->_minor;
    }
    
    unsigned int Version::GetBuild( void ) const
    {
        return this->impl->_build;
    }
    
    unsigned int Version::GetRevision( void ) const
    {
        return this->impl->_revision;
    }
    
    Version::Status Version::GetStatus( void ) const
    {
        return this->impl->_status;
    }
    
    /* TODO: Thread-safety */
    void Version::SetMajor( unsigned int value )
    {
        this->impl->_major = value;
    }
    
    /* TODO: Thread-safety */
    void Version::SetMinor( unsigned int value )
    {
        this->impl->_minor = value;
    }
    
    /* TODO: Thread-safety */
    void Version::SetBuild( unsigned int value )
    {
        this->impl->_build = value;
    }
    
    /* TODO: Thread-safety */
    void Version::SetRevision( unsigned int value )
    {
        this->impl->_revision = value;
    }
    
    /* TODO: Thread-safety */
    void Version::SetStatus( Version::Status value )
    {
        this->impl->_status = value;
    }
}
