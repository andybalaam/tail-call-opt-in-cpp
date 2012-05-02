#include <cassert>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>

template<typename RetT>
struct IAnswer;

template<typename RetT>
struct FnPlusArgs
{
    typedef std::auto_ptr< IAnswer<RetT> > AnswerPtr;
    typedef AnswerPtr (*fn_type)( long, long );

    fn_type fn_;
    long arg1_;
    long arg2_;

    FnPlusArgs(
        fn_type fn,
        long arg1,
        long arg2
    )
    : fn_( fn )
    , arg1_( arg1 )
    , arg2_( arg2 )
    {
    }

    AnswerPtr operator()()
    {
        return fn_( arg1_, arg2_ );
    }
};

template<typename RetT>
struct IAnswer
{
    virtual bool finished() = 0;
    virtual FnPlusArgs<RetT>& tail_call() = 0;
    virtual RetT value() = 0;
};


template<typename RetT>
struct Answer2 : public IAnswer<RetT>
{
    bool finished_;
    FnPlusArgs<RetT> tail_call_;
    RetT value_;

    Answer2( bool finished, FnPlusArgs<RetT> tail_call, RetT value )
    : finished_( finished )
    , tail_call_( tail_call )
    , value_( value )
    {
    }

    virtual bool finished() { return finished_; };
    virtual FnPlusArgs<RetT>& tail_call() { return tail_call_; };
    virtual RetT value() { return value_; };
};

template<typename RetT>
RetT trampoline_tmpl( std::auto_ptr< IAnswer<RetT> > answer )
{
    while( !answer->finished() )
    {
        answer = answer->tail_call()();
    }
    return answer->value();
}


std::auto_ptr< IAnswer<long> > times_two_tail_call_impl( long acc, long i )
{
    if( i == 0 )
    {
        return std::auto_ptr< IAnswer<long> >(
            new Answer2<long>( true, FnPlusArgs<long>( NULL, 0, 0 ), acc )
        );
    }
    else
    {
        return std::auto_ptr< IAnswer<long> >(
            new Answer2<long>(
                false,
                FnPlusArgs<long>( times_two_tail_call_impl, acc + 2, i - 1 ),
                0
            )
        );
    }
}

long times_two_tail_call_templ( long n )
{
    return trampoline_tmpl(
        typename std::auto_ptr< IAnswer<long> >(
            new Answer2<long>(
                false,
                FnPlusArgs<long>( times_two_tail_call_impl, 0, n ),
                0
            )
        )
    );
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

int test()
{
    try
    {
        test_one( times_two_tail_call_templ, "times_two_tail_call_templ"  );
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
    test();

    if ( argc < 2 )
    {
        std::cerr
            << "You must specify number of iterations"
            << std::endl;
    
        return 1;
    }
    
    long arg = 0;
    std::istringstream ss( argv[1] );
    ss >> arg;
    
    times_two_tail_call_templ( arg );
    
    return 0;
}

