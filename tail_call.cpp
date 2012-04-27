#include <cassert>
#include <iostream>
#include <memory>
#include <string>

struct TailCallOrAnswer;

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
    std::auto_ptr<TailCallOrAnswer> (*fn_)( long, long, int );
    long arg1_;
    long arg2_;
    int indent_;

    FunctionTailCall(
        std::auto_ptr<TailCallOrAnswer> (*fn)( long, long, int ),
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

    std::auto_ptr<TailCallOrAnswer> operator()()
    {
        print_indent( indent_, "fact_impl_tc" );
        return fn_( arg1_, arg2_, indent_ );
    }
};

struct TailCallOrAnswer
{
    std::auto_ptr<FunctionTailCall> tail_call_;
    std::auto_ptr<long> ret_val_;

    TailCallOrAnswer( std::auto_ptr<FunctionTailCall> tail_call )
    : tail_call_( tail_call )
    , ret_val_( NULL )
    {
    }

    TailCallOrAnswer( std::auto_ptr<long> ret_val )
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

std::auto_ptr<TailCallOrAnswer> fact_impl_tc( long acc, long i, int indent )
{
    if( i == 0 )
    {
        return std::auto_ptr<TailCallOrAnswer>(
            new TailCallOrAnswer( std::auto_ptr<long>( new long( acc ) ) ) );
    }
    else
    {
        return std::auto_ptr<TailCallOrAnswer>(
            new TailCallOrAnswer( std::auto_ptr<FunctionTailCall>(
                new FunctionTailCall(
                    fact_impl_tc, acc + i, i - 1, indent ) ) ) );
    }
}

long tail_call( std::auto_ptr<TailCallOrAnswer> call )
{
    while( call->tail_call_.get() )
    {
        call = (*call->tail_call_)();
    }
    return *( call->ret_val_ );
}

long fact_tc( long n )
{
    return tail_call( std::auto_ptr<TailCallOrAnswer>(
        new TailCallOrAnswer(
            std::auto_ptr<FunctionTailCall>(
                new FunctionTailCall( fact_impl_tc, 1, n, 0 ) ) ) ) );
}

long fact_impl( long acc, long i, int indent )
{
    print_indent( indent, "fact_impl" );

    if( i == 0 )
    {
        return acc;
    }
    else
    {
        return fact_impl( acc + i, i - 1, indent + 1 );
    }
}

long fact( long n )
{
    return fact_impl( 1, n, 0 );
}

int main()
{
    std::cout << fact_tc( 300 ) << std::endl;
    std::cout << fact( 300 ) << std::endl;
}

