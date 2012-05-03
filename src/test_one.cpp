#include <stdexcept>
#include <sstream>
#include <string>

struct AssertionFailure : public std::runtime_error
{
    explicit AssertionFailure( const std::string& what_arg )
    : std::runtime_error( what_arg )
    {
    }
};

std::string make_error(
    long expected, long actual, long arg, const std::string& function_name )
{
    std::ostringstream ss;
    ss  << "AssertionError: "
        << function_name << "( " << arg << " ) != "
        << expected << "  (Value returned: " << actual << ")";

    return ss.str();
}


void assert_equal(
    long expected, long actual, long arg, const std::string& function_name )
{
    if ( expected != actual )
    {
        throw AssertionFailure(
            make_error( expected, actual, arg, function_name ) );
    }
}

typedef long (*times_two_function)( long );

void test_one( times_two_function fn, const std::string& function_name )
{
    assert_equal(  0, fn(  0 ),  0, function_name );
    assert_equal(  2, fn(  1 ),  1, function_name );
    assert_equal(  4, fn(  2 ),  2, function_name );
    assert_equal( 20, fn( 10 ), 10, function_name );
    assert_equal( 26, fn( 13 ), 13, function_name );
}

