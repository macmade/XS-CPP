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
 * @header      XS-C++.h
 * @copyright   (c) 2015 - Jean-David Gadina - www.xs-labs.com
 * @abstract    XS-C++ main header file
 */

#ifndef __XSCPP__
#define __XSCPP__
#ifdef  __cplusplus

/*!
 * @define      XSCPP_HAS_CPP11
 * @abstract    Whether the compiler has ISO C++ 2011 support
 */
#if defined( __cplusplus ) && ( __cplusplus > 199711L || ( defined( _MSC_VER ) && _MSC_VER >= 1800 ) )
#define XSCPP_HAS_CPP11         1
#endif

/*!
 * @define      XSCPP_THREADING_USE_STL
 * @abstract    Whether to use the ISO C++ 2011 thread support library
 * @discussion  If not defined previously to 0 (before inclusion of this header
 *              file, this macro will be defined to 1, meaning the ISO C++ 2011
 *              thread support library will be used instead of native thread
 *              functions (eg. pthread on POSIX).
 */
#ifndef XSCPP_THREADING_USE_STL
#define XSCPP_THREADING_USE_STL    1
#endif

/* ISO C++ 2011 is required */
#ifndef XSCPP_HAS_CPP11
#error "The XS-Labs C++ Utility Library requires ISO C++ 2011"
#endif

/* Includes from the C++ STL */
#include <algorithm>
#include <memory>
#include <string>
#include <iostream>

/* Includes from XS-C++ */
#include <XS-C++/Macros.h>
#include <XS-C++/Types.h>
#include <XS-C++/Atomic.h>

#endif /* __cplusplus */
#endif /* __XSCPP__ */
