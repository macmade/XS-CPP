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
 * @brief       Definition of the XS::Version class
 */

#include <XS-C++.h>
#include <XS/PIMPL/Object-IMPL.h>

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
            
            IMPL( const IMPL & o )
            {
                Threading::LockGuard lock( const_cast< Threading::Mutex * >( &( o._mtx ) ) );
                
                this->_major    = o._major;
                this->_minor    = o._minor;
                this->_build    = o._build;
                this->_revision = o._revision;
                this->_major    = o._major;
            }
            
            ~IMPL( void )
            {}
            
            unsigned int     _major;
            unsigned int     _minor;
            unsigned int     _build;
            unsigned int     _revision;
            Version::Status  _status;
            Threading::Mutex _mtx;
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
    
    std::string Version::ToString( void ) const
    {
        std::string  v;
        unsigned int major;
        unsigned int minor;
        unsigned int build;
        unsigned int revision;
        Status       status;
        
        major    = this->GetMajor();
        minor    = this->GetMinor();
        build    = this->GetBuild();
        revision = this->GetRevision();
        status   = this->GetStatus();
        
        v  = std::to_string( major )
           + "."
           + std::to_string( minor )
           + "."
           + std::to_string( build );
        
        switch( status )
        {
            case StatusAlpha:            v += "-a";  break;
            case StatusBeta:             v += "-b";  break;
            case StatusReleaseCandidate: v += "-rc"; break;
            
            case StatusFinal:
                
                if( revision > 0 )
                {
                    v += "-r";
                }
                
                break;
        }
        
        if( revision > 0 )
        {
            v += std::to_string( revision );
        }
        
        return v;
    }
    
    unsigned int Version::GetMajor( void ) const
    {
        Threading::LockGuard lock( &( this->impl->_mtx ) );
        
        return this->impl->_major;
    }
    
    unsigned int Version::GetMinor( void ) const
    {
        Threading::LockGuard lock( &( this->impl->_mtx ) );
        
        return this->impl->_minor;
    }
    
    unsigned int Version::GetBuild( void ) const
    {
        Threading::LockGuard lock( &( this->impl->_mtx ) );
        
        return this->impl->_build;
    }
    
    unsigned int Version::GetRevision( void ) const
    {
        Threading::LockGuard lock( &( this->impl->_mtx ) );
        
        return this->impl->_revision;
    }
    
    Version::Status Version::GetStatus( void ) const
    {
        Threading::LockGuard lock( &( this->impl->_mtx ) );
        
        return this->impl->_status;
    }
    
    void Version::SetMajor( unsigned int value )
    {
        Threading::LockGuard lock( &( this->impl->_mtx ) );
        
        this->impl->_major = value;
    }
    
    void Version::SetMinor( unsigned int value )
    {
        Threading::LockGuard lock( &( this->impl->_mtx ) );
        
        this->impl->_minor = value;
    }
    
    void Version::SetBuild( unsigned int value )
    {
        Threading::LockGuard lock( &( this->impl->_mtx ) );
        
        this->impl->_build = value;
    }
    
    void Version::SetRevision( unsigned int value )
    {
        Threading::LockGuard lock( &( this->impl->_mtx ) );
        
        this->impl->_revision = value;
    }
    
    void Version::SetStatus( Version::Status value )
    {
        Threading::LockGuard lock( &( this->impl->_mtx ) );
        
        this->impl->_status = value;
    }
}
