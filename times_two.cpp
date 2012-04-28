#include <cassert>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>

struct Answer;
typedef Answer (*impl_fn_type)( long, long );

struct FnPlusArgs
{
    impl_fn_type fn_;
    long arg1_;
    long arg2_;

    FnPlusArgs(
        impl_fn_type fn,
        long arg1,
        long arg2
    );

    Answer operator()();
};

impl_fn_type null_fn = NULL;
FnPlusArgs null_fn_plus_args( null_fn, 0, 0 );

struct Answer
{
    bool finished_;
    FnPlusArgs tail_call_;
    long value_;

    Answer( bool finished, FnPlusArgs tail_call, long value );
};


FnPlusArgs::FnPlusArgs(
    impl_fn_type fn,
    long arg1,
    long arg2
)
: fn_( fn )
, arg1_( arg1 )
, arg2_( arg2 )
{
}

Answer FnPlusArgs::operator()()
{
    return fn_( arg1_, arg2_ );
}


Answer::Answer( bool finished, FnPlusArgs tail_call, long value )
: finished_( finished )
, tail_call_( tail_call )
, value_( value )
{
}

long tail_call( Answer answer )
{
    while( !answer.finished_ )
    {
        answer = answer.tail_call_();
    }
    return answer.value_;
}


Answer times_two_tail_call_impl( long acc, long i )
{
    if( i == 0 )
    {
        return Answer( true, null_fn_plus_args, acc );
    }
    else
    {
        return Answer(
            false,
            FnPlusArgs( times_two_tail_call_impl, acc + 2, i - 1 ),
            0
        );
    }
}

long times_two_tail_call( long n )
{
    return tail_call( Answer(
        false,
        FnPlusArgs( times_two_tail_call_impl, 0, n ),
        0 ) );
}

long times_two_recursive_impl( long total, long counter )
{
    if( counter == 0 )
    {
        return total;
    }
    else
    {
        return times_two_recursive_impl( total + 2, counter - 1 );
    }
}

long times_two_recursive( long value )
{
    return times_two_recursive_impl( 0, value );
}

long times_two_loop( long value )
{
    long ret = 0;
    for( long i = 0; i < value; ++i )
    {
        ret += 2;
    }
    return ret;
}

long times_two_hardware( long value )
{
    return value * 2;
}


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

int test_all()
{
    try
    {
        test_one( times_two_hardware,  "times_two_hardware"  );
        test_one( times_two_loop,      "times_two_loop"      );
        test_one( times_two_recursive, "times_two_recursive" );
        test_one( times_two_tail_call, "times_two_tail_call" );
    }
    catch( AssertionFailure& e )
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

void call_one( times_two_function fn, int argc, char * const argv[] )
{
    long arg = 0;
    if ( argc >= 3 )
    {
        std::istringstream ss( argv[2] );
        ss >> arg;
    }

    fn( arg );
}

int main( int argc, char * const argv[] )
{
    if ( argc < 2 )
    {
        std::cerr
            << "You must specify one of: "
            << "test, hardware, loop, recursive, tail_call"
            << std::endl;

        return 1;
    }

    std::string arg( argv[1] );
    if ( arg == "test" )
    {
        return test_all();
    }
    else if ( arg == "hardware" )
    {
        call_one( times_two_hardware, argc, argv );
    }
    else if ( arg == "loop" )
    {
        call_one( times_two_loop, argc, argv );
    }
    else if ( arg == "recursive" )
    {
        call_one( times_two_recursive, argc, argv );
    }
    else if ( arg == "tail_call" )
    {
        call_one( times_two_tail_call, argc, argv );
    }
    else
    {
        std::cerr
            << "You must specify one of: "
            << "test, hardware, loop, recursive, tail_call"
            << std::endl;
        return 1;
    }

    return 0;
}

