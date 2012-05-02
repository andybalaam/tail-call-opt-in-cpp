#include <memory>

namespace tail_call_templ
{

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


template<typename RetT>
RetT trampoline_templ( std::auto_ptr< IAnswer<RetT> > answer )
{
    while( !answer->finished() )
    {
        answer = answer->tail_call()();
    }
    return answer->value();
}

}

long times_two_tail_call_templ( long n )
{
    return tail_call_templ::trampoline_templ(
        typename std::auto_ptr< tail_call_templ::IAnswer<long> >(
            new tail_call_templ::Answer2<long>(
                false,
                tail_call_templ::FnPlusArgs<long>(
                    tail_call_templ::times_two_tail_call_impl, 0, n ),
                0
            )
        )
    );
}

