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
 * @brief       XS-C++ common macros
 */

#ifndef XSCPP_MACROS_H
#define XSCPP_MACROS_H

/*!
 * @brief   Checks whether a builtin function is supported
 * @param   The name of the builtin function
 * @return  0 - Compatibility with non-clang compilers.
 */
#ifndef __has_builtin
#define __has_builtin( _x_ )                0
#endif

/*!
 * @brief   Checks whether a feature is supported
 * @param   The name of the feature
 * @return  0 - Compatibility with non-clang compilers.
 */
#ifndef __has_feature
#define __has_feature( _x_ )                0
#endif

/*!
 * @brief   Checks whether an extension is supported
 * @param   The name of the extension
 * @return  Same as __has_feature - Compatibility with pre-3.0 compilers.
 */
#ifndef __has_extension
#define __has_extension                     __has_feature
#endif

/*!
 * @brief   Checks whether a C++ attribute is supported
 * @param   The name of the C++ attribute
 * @return  0 - Compatibility with non-clang compilers.
 */
#ifndef __has_cpp_attribute
#define __has_cpp_attribute( _x_ )          0
#endif

/*!
 * @brief   Checks whether an attribute is supported
 * @param   The name of the attribute
 * @return  0 - Compatibility with non-clang compilers.
 */
#ifndef __has_attribute
#define __has_attribute( _x_ )              0
#endif

/*!
 * @brief   Checks whether a MS attribute is supported
 * @param   The name of the MS attribute
 * @return  0 - Compatibility with non-clang compilers.
 */
#ifndef __has_declspec_attribute
#define __has_declspec_attribute( _x_ )     0
#endif

#endif /* XSCPP_MACROS_H */
