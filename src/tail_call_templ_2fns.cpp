#include <memory>

#include "templ_lib.h"

namespace tail_call_templ
{

// Extensions to templ_lib for 3-argument functions


template<typename RetT, typename Arg1T, typename Arg2T, typename Arg3T>
class FnPlusArgs3 : public ICallable<RetT>
{
private:
    typedef typename ICallable<RetT>::AnswerPtr AnswerPtr;
public:
    typedef AnswerPtr (*fn_type)( const Arg1T, const Arg2T, const Arg3T );
private:
    const fn_type fn_;
    const Arg1T arg1_;
    const Arg2T arg2_;
    const Arg3T arg3_;

public:
    FnPlusArgs3(
        const fn_type fn, const Arg1T arg1, const Arg2T arg2, const Arg3T arg3 )
    : fn_( fn )
    , arg1_( arg1 )
    , arg2_( arg2 )
    , arg3_( arg3 )
    {
    }

    virtual AnswerPtr operator()() const
    {
        return fn_( arg1_, arg2_, arg3_ );
    }

    static FnPlusArgs3<RetT, Arg1T, Arg2T, Arg3T> null()
    {
        return FnPlusArgs3<RetT, Arg1T, Arg2T, Arg3T>( NULL, 0, 0, 0 );
    }

};



template<typename RetT, typename Arg1T, typename Arg2T, typename Arg3T>
class Answer3 : public IAnswer<RetT>
{
private:
    typedef FnPlusArgs3<RetT, Arg1T, Arg2T, Arg3T> FnArgs;
    typedef std::auto_ptr< IAnswer<RetT> > AnswerPtr;

    const bool finished_;
    const FnArgs tail_call_;
    const RetT value_;

private:
    Answer3( const bool finished, const FnArgs tail_call, const RetT value )
    : finished_( finished )
    , tail_call_( tail_call )
    , value_( value )
    {
    }

    static AnswerPtr newPtr(
        const bool finished, const FnArgs tail_call, const RetT value )
    {
        return AnswerPtr( new Answer3<RetT, Arg1T, Arg2T, Arg3T>(
            finished, tail_call, value ) );
    }
public:
    static AnswerPtr newFn(
        const typename FnArgs::fn_type fn,
        const Arg1T arg1,
        const Arg2T arg2,
        const Arg3T arg3,
        const RetT zero_val )
    {
        return newPtr( false, FnArgs( fn, arg1, arg2, arg3 ), zero_val );
    }

    static AnswerPtr newAns( const RetT value )
    {
        return newPtr( true, FnArgs::null(), value );
    }

    virtual const bool    finished()  const { return finished_; };
    virtual const FnArgs& tail_call() const { return tail_call_; };
    virtual const RetT    value()     const { return value_; };
};



/**
 * Forward-declaration.
 */
std::auto_ptr< IAnswer<long> > times_two_tail_call_impl_2fns(
    const long acc, const long i );

/**
 * Extra function added to demonstrate that this code works with 2 functions
 * calling each other recursively, instead of a single function, even when
 * those functions take different arguments.
 */
std::auto_ptr< IAnswer<long> > times_two_tail_call_impl_2fns_log(
    const std::string extra_arg, const long acc, const long i )
{
    std::cout << extra_arg;

    return Answer2<long, long, long>::newFn(
        times_two_tail_call_impl_2fns, acc, i, 0 );
}

/**
 * The function that does the real work, but calls
 * times_two_tail_call_impl_log, which calls this again recursively.
 */
std::auto_ptr< IAnswer<long> > times_two_tail_call_impl_2fns(
    const long acc, const long i )
{
    typedef Answer2<long, long, long> AnswerType;

    if( i == 0 )
    {
        return AnswerType::newAns( acc );
    }
    else
    {
        // Note we pass an extra string argument here
        return Answer3<long, std::string, long, long>::newFn(
            times_two_tail_call_impl_2fns_log, ".", acc + 2, i - 1, 0 );
    }
}


const long times_two_tail_call_templ_2fns_ns( const long n )
{
    typedef Answer2<long, long, long> AnswerType;

    return trampoline_templ(
        AnswerType::newFn( times_two_tail_call_impl_2fns, 0, n, 0 )
    );
}

}

long times_two_tail_call_templ_2fns( long n )
{
    return tail_call_templ::times_two_tail_call_templ_2fns_ns( n );
}

