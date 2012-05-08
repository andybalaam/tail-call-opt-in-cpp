#include <memory>

#include "templ_lib.h"

namespace tail_call_templ
{

std::auto_ptr< IAnswer<long> > times_two_tail_call_impl(
    const long acc, const long i )
{
    typedef Answer2<long, long, long> AnswerType;

    if( i == 0 )
    {
        return AnswerType::newAns( acc );
    }
    else
    {
        return AnswerType::newFn(
            times_two_tail_call_impl, acc + 2, i - 1, 0 );
    }
}


const long times_two_tail_call_templ_ns( const long n )
{
    typedef Answer2<long, long, long> AnswerType;

    return trampoline_templ(
        AnswerType::newFn( times_two_tail_call_impl, 0, n, 0 )
    );
}

}

long times_two_tail_call_templ( long n )
{
    return tail_call_templ::times_two_tail_call_templ_ns( n );
}

