//- ------------------------------------------------------------------
//-    Copyright (c) James W. Grenning -- All Rights Reserved         
//-    For use by owners of Test-Driven Development for Embedded C,   
//-    and attendees of Renaissance Software Consulting, Co. training 
//-    classes.                                                       
//-                                                                   
//-    Available at http://pragprog.com/titles/jgade/                 
//-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3               
//-                                                                   
//-    Authorized users may use this source code in your own          
//-    projects, however the source code may not be used to           
//-    create training material, courses, books, articles, and        
//-    the like. We make no guarantees that this source code is       
//-    fit for any purpose.                                           
//-                                                                   
//-    www.renaissancesoftware.net james@renaissancesoftware.net      
//- ------------------------------------------------------------------


#include "CppUTest/TestHarness.h"

extern "C"
{
#include <stdio.h>
#include <memory.h>
#define ENDCHAR_BYTE 1
#define OVERFLOW_WRITE_CHECK_BYTE 1 
}

//START: testGroup
TEST_GROUP(sprintf)
{
    char *output;
    const char * expected;
    void setup()
    {
        expected = "";
        output = NULL;
    }
    void teardown()
    {
        free(output);
    }
    void expect(const char * s)
    {
        expected = s;
    }
    char *createOutputDynamically_alloc()
    {
        char *ptr;
        int len = strlen(expected) + ENDCHAR_BYTE + OVERFLOW_WRITE_CHECK_BYTE;
        ptr = (char *)calloc(len, sizeof(char));
        if(ptr != NULL)
        {
            memset(ptr,0xaa,len);
        }
        else
        {
            printf("Ptr not allocated by calloc!\n");
        }
        return ptr;
    }
    void given(int charsWritten)
    {
        LONGS_EQUAL(strlen(expected), charsWritten);
        STRCMP_EQUAL(expected, output);
        BYTES_EQUAL(0xaa, output[strlen(expected) + 1]);
    }
};
//END: testGroup

#if 1 //START: PersonalDevlopedTests
TEST(sprintf, InsertInteger)
{
    expect("The inserted number is 13!");
    output = createOutputDynamically_alloc();
    given(sprintf(output, "The inserted number is %d!",13));
}
TEST(sprintf, InsertFloat)
{
    expect("The inserted number is 24.07!");
    output = createOutputDynamically_alloc();
    given(sprintf(output, "The inserted number is %5.2f!",24.07));
}
#endif //END: PersonalDevlopedTests

#if 1 //START: RefactoredTests
TEST(sprintf, NoFormatOperations)
{
    expect("hey");
    output = createOutputDynamically_alloc();
    given(sprintf(output, "hey"));
}

TEST(sprintf, InsertString)
{
    expect("Hello World\n");
    output = createOutputDynamically_alloc();
    given(sprintf(output, "Hello %s\n", "World"));
}
//END: RefactoredTests

#else //START: Duplication
//START: FormatSpace
TEST(sprintf, NoFormatOperations)
{
    char output[5];
    memset(output, 0xaa, sizeof output);

    LONGS_EQUAL(3, sprintf(output, "hey"));
    STRCMP_EQUAL("hey", output);
    BYTES_EQUAL(0xaa, output[2]);
}
//END: FormatSpace

TEST(sprintf, InsertString)
{
    char output[20];
    memset(output, 0xaa, sizeof output);

    LONGS_EQUAL(12, sprintf(output, "%s\n", "Hello World"));
    STRCMP_EQUAL("Hello World\n", output);
    BYTES_EQUAL(0xaa, output[13]);
}
//END: Duplication
#endif

#if 0 //START: NoFormatOperations1
TEST(sprintf, NoFormatOperations)
{
    char output[5];
    LONGS_EQUAL(3, sprintf(output, "hey"));
    STRCMP_EQUAL("hey", output);
}
//END: NoFormatOperations1
#endif

#if 0 //START: NoFormatOperations2
TEST(sprintf, NoFormatOperations)
{
    char output[5] = "";
	
    LONGS_EQUAL(3, sprintf(output, "hey"));
    STRCMP_EQUAL("hey", output);
}
//END: NoFormatOperations2
#endif


#if 0 //START: oneString
TEST(sprintf, InsertString)
{
    char output[20] = "";

    LONGS_EQUAL(12, sprintf(output, "%s\n", "Hello World"));
    STRCMP_EQUAL("Hello World\n", output);
}
//END: oneString
#endif

#if 0 //START: failingTest
TEST(sprintf, NoFormatOperations)
{
    char output[5];
    LONGS_EQUAL(4, sprintf(output, "hey"));
    STRCMP_EQUAL("hey", output);
}
#endif //END: failingTest

