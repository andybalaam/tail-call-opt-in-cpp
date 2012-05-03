
namespace tail_call
{

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


long trampoline( Answer answer )
{
    while( !answer.finished_ )
    {
        answer = answer.tail_call_();
    }
    return answer.value_;
}

}

long times_two_tail_call( long n )
{
    return tail_call::trampoline( tail_call::Answer(
        false,
        tail_call::FnPlusArgs( tail_call::times_two_tail_call_impl, 0, n ),
        0 ) );
}

