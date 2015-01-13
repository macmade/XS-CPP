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
 * @file        XS-CPP.mm
 * @copyright   (c) 2015 - Jean-David Gadina - www.xs-labs.com
 * @abstract    Unit tests for XS-C++ (using GMock)
 */

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wvariadic-macros"
#pragma clang diagnostic ignored "-Wgnu-statement-expression"
#endif

#import <XCTest/XCTest.h>
#import <objc/runtime.h>

#ifdef __clang__
#pragma clang diagnostic pop
#endif

using namespace testing;

static bool                              __inited = false;
static std::vector< const TestCase * > * __t      = nullptr;

static void __f( id self, SEL _cmd );
static void __f( id self, SEL _cmd )
{
    std::string        testCaseName;
    std::string        testInfoName;
    int                i;
    int                n;
    const TestInfo   * testInfo;
    const TestResult * testResult;
    
    /* Name of the GMock test case to analyze */
    testCaseName = std::string( [ NSStringFromClass( [ self class ] ) UTF8String ] );
    
    /* Name of the GMock test to analyze */
    testInfoName = std::string( [ [ NSStringFromSelector( _cmd ) substringFromIndex: 4 ] UTF8String ] );
    
    /* Process each stored GMock test case */
    for( const TestCase * testCase: *( __t ) )
    {
        if( std::string( testCase->name() ) != testCaseName )
        {
            /* Not the current test case */
            continue;
        }
        
        /* Number of tests in the test case */
        n = testCase->total_test_count();
        
        /* Process each test in the test case */
        for( i = 0; i < n; i++ )
        {
            testInfo = testCase->GetTestInfo( i );
            
            if( testInfo == nullptr )
            {
                continue;
            }
            
            if( std::string( testInfo->name() ) != testInfoName )
            {
                /* Not the current test */
                continue;
            }
            
            if( testInfo->should_run() == false )
            {
                /* Test is disabled */
                return;
            }
            
            testResult = testInfo->result();
            
            if( testResult == nullptr )
            {
                XCTAssertNotEqual( testResult, nullptr, "Invalid GMock test result" );
                
                return;
            }
            
            if( testResult->Passed() )
            {
                /* Test has passed */
                XCTAssertTrue( true );
                
                return;
            }
            
            /* Test has failed */
            {
                int        testPartResultCount;
                int        j;
                NSString * summary;
                
                /* Number of test part results */
                testPartResultCount = testResult->total_part_count();
                
                /* Process each test part result */
                for( j = 0; j < testPartResultCount; j++ )
                {
                    const TestPartResult & testPartResult = testResult->GetTestPartResult( j );
                    
                    if( testPartResult.type() != TestPartResult::kFatalFailure )
                    {
                        /* Successfull part */
                        continue;
                    }
                    
                    /* First line of the summary */
                    summary = [ NSString stringWithCString: testPartResult.summary() encoding: NSUTF8StringEncoding ];
                    summary = [ [ summary componentsSeparatedByString: @"\n" ] firstObject ];
                    
                    /* Fails the test */
                    XCTAssertTrue
                    (
                        false,
                        "Failed GMock test - %s.%s - %s\n"
                        "\n"
                        "--------------------------------------------------------------------------------\n"
                        "Test:        %s.%s\n"
                        "File name:   %s\n"
                        "Line number: %i\n"
                        "--------------------------------------------------------------------------------\n"
                        "%s\n"
                        "--------------------------------------------------------------------------------\n",
                        testCaseName.c_str(),
                        testInfoName.c_str(),
                        summary.UTF8String,
                        testCaseName.c_str(),
                        testInfoName.c_str(),
                        ( testPartResult.file_name() == nullptr ) ? "" : testPartResult.file_name(),
                        testPartResult.line_number(),
                        testPartResult.message()
                    );
                }
            }
            
            return;
        }
    }
    
    XCTAssertTrue( false, "Cannot determine GMock test from current selector" );
}

static void __dtor( void ) __attribute__( ( destructor ) );
static void __dtor( void )
{
    delete __t;
}

@interface XS_CPP: XCTestCase
{}

@end

@implementation XS_CPP

+ ( void )initialize
{
    if( self != [ XS_CPP self ] )
    {
        return;
    }
    
    /* Initializes GMock */
    {
        int          argc;
        const char * argv[ 1 ];
        
        argc      = 1;
        argv[ 0 ] = "XS-CPP-GMock";
        
        testing::InitGoogleMock( &argc, const_cast< char ** >( argv ) );
    }
    
    /*
     * Support for xctool
     * 
     * The xctool helper will use otest-query-osx to query all tests in
     * the bundle, expecting JSON output in stdout.
     * As the GMock output is not JSON, we don't run the tests in such a case.
     * The Objective-C classes for each GMock test cases will still be
     * created, and the tests correctly run when necessary.
     */
    if( [ [ [ NSProcessInfo processInfo ] processName ] isEqualToString: @"otest-query-osx" ] == NO )
    {
        /* Runs all GMock tests */
        {
            int res;
            
            res = RUN_ALL_TESTS();
            
            /* warn_unused_result */
            ( void )res;
        }
    }
    
    /* Stores all GMock test cases and creates XCTest methods for each one */
    {
        const TestCase * testCase;
        const TestInfo * testInfo;
        int              testCaseCount;
        int              testInfoCount;
        int              i;
        int              j;
        Class            cls;
        IMP              imp;
        SEL              sel;
        NSString       * testName;
        
        /* Storage for the GMock test cases */
        __t = new std::vector< const TestCase * >;
        
        /* Number of available GMock test cases */
        testCaseCount = UnitTest::GetInstance()->total_test_case_count();
        
        /* Process each test case */
        for( i = 0; i < testCaseCount; i++ )
        {
            testCase = UnitTest::GetInstance()->GetTestCase( i );
            
            if( testCase == nullptr )
            {
                continue;
            }
            
            /* Stores the test case */
            __t->push_back( testCase );
            
            /* Creates a new Objective-C class for the test case */
            cls = objc_allocateClassPair( objc_getClass( "XCTestCase" ), testCase->name(), 0 );
            
            /* Number of tests in the test case */
            testInfoCount = testCase->total_test_count();
            
            /* Process each test in the test case */
            for( j = 0; j < testInfoCount; j++ )
            {
                testInfo = testCase->GetTestInfo( j );
                
                if( testInfo == nullptr )
                {
                    continue;
                }
                
                /* XCTest method name and selector */
                testName = [ NSString stringWithFormat: @"test%s", testInfo->name() ];
                sel      = sel_registerName( testName.UTF8String );
                
                /* IMP for the generic XCTest method */
                imp = reinterpret_cast< IMP >( __f );
                
                /* Adds the XCTest method to the class, so Xcode will run it */
                class_addMethod( cls, sel, imp, "v@:" );
                
                /* We have tests from GMock */
                __inited = true;
            }
            
            /* Registers the new class with the Objective-C runtime */
            objc_registerClassPair( cls );
        }
    }
}

- ( void )testGMock
{
    XCTAssertTrue( __inited, "No GMock test" );
}

@end
