#include <cassert>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
/*
struct TailCallOrAnswer;
typedef std::auto_ptr<TailCallOrAnswer> Ans_ptr;

void print_indent( int indent, const std::string& fn_name )
{
    for( int in = 0; in < indent; ++in )
    {
        std::cout << "  ";
    }
    std::cout << fn_name << std::endl;
}



struct FunctionTailCall
{
    Ans_ptr (*fn_)( long, long, int );
    long arg1_;
    long arg2_;
    int indent_;

    FunctionTailCall(
        Ans_ptr (*fn)( long, long, int ),
        long arg1,
        long arg2,
        int indent
    )
    : fn_( fn )
    , arg1_( arg1 )
    , arg2_( arg2 )
    , indent_( indent )
    {
    }

    FunctionTailCall( const FunctionTailCall& other )
    : fn_( other.fn_ )
    , arg1_( other.arg1_ )
    , arg2_( other.arg2_ )
    , indent_( other.indent_ )
    {
    }

    Ans_ptr operator()()
    {
        print_indent( indent_, "sumall_impl_tc" );
        return fn_( arg1_, arg2_, indent_ );
    }
};

typedef std::auto_ptr<FunctionTailCall> Tc_ptr;
typedef std::auto_ptr<long> long_ptr;

struct TailCallOrAnswer
{
    Tc_ptr tail_call_;
    long_ptr ret_val_;

    TailCallOrAnswer( Tc_ptr tail_call )
    : tail_call_( tail_call )
    , ret_val_( NULL )
    {
    }

    TailCallOrAnswer( long_ptr ret_val )
    : tail_call_( NULL )
    , ret_val_( ret_val )
    {
    }

    TailCallOrAnswer( const TailCallOrAnswer& other )
    : tail_call_( new FunctionTailCall( *(other.tail_call_) ) )
    , ret_val_( new long( *(other.ret_val_) ) )
    {
    }
};

Ans_ptr sumall_impl_tc( long acc, long i, int indent )
{
    if( i == 0 )
    {
        return Ans_ptr(
            new TailCallOrAnswer( long_ptr( new long( acc ) ) ) );
    }
    else
    {
        return Ans_ptr(
            new TailCallOrAnswer( Tc_ptr(
                new FunctionTailCall(
                    sumall_impl_tc, acc + i, i - 1, indent ) ) ) );
    }
}

long tail_call( Ans_ptr call )
{
    while( call->tail_call_.get() )
    {
        call = (*call->tail_call_)();
    }
    return *( call->ret_val_ );
}

long sumall_tc( long n )
{
    return tail_call( Ans_ptr(
        new TailCallOrAnswer(
            Tc_ptr( new FunctionTailCall( sumall_impl_tc, 1, n, 0 ) ) ) ) );
}

long sumall_impl( long acc, long i, int indent )
{
    print_indent( indent, "sumall_impl" );

    if( i == 0 )
    {
        return acc;
    }
    else
    {
        return sumall_impl( acc + i, i - 1, indent + 1 );
    }
}

long sumall( long n )
{
    return sumall_impl( 1, n, 0 );
}

*/

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
    }
    catch( AssertionFailure& e )
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

int main( int argc, char * const argv[] )
{
    if ( argc != 2 )
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
    }
    else if ( arg == "loop" )
    {
    }
    else if ( arg == "recursive" )
    {
    }
    else if ( arg == "tail_call" )
    {
    }

    return 0;
}

