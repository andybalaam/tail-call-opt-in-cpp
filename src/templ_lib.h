#ifndef TEMPL_LIB_H
#define TEMPL_LIB_H

namespace tail_call_templ
{

template<typename RetT>
class IAnswer;

template<typename RetT>
class ICallable
{
public:
    typedef std::auto_ptr< IAnswer<RetT> > AnswerPtr;
    virtual AnswerPtr operator()() const = 0;
};

template<typename RetT>
class IAnswer
{
public:
    virtual const bool             finished()  const = 0;
    virtual const ICallable<RetT>& tail_call() const = 0;
    virtual const RetT             value()     const = 0;
};

template<typename RetT, typename Arg1T, typename Arg2T>
class FnPlusArgs2 : public ICallable<RetT>
{
private:
    typedef typename ICallable<RetT>::AnswerPtr AnswerPtr;
public:
    typedef AnswerPtr (*fn_type)( const Arg1T, const Arg2T );
private:
    const fn_type fn_;
    const Arg1T arg1_;
    const Arg2T arg2_;

public:
    FnPlusArgs2( const fn_type fn, const Arg1T arg1, const Arg2T arg2 )
    : fn_( fn )
    , arg1_( arg1 )
    , arg2_( arg2 )
    {
    }

    virtual AnswerPtr operator()() const
    {
        return fn_( arg1_, arg2_ );
    }

    static FnPlusArgs2<RetT, Arg1T, Arg2T> null()
    {
        return FnPlusArgs2<RetT, Arg1T, Arg2T>( NULL, 0, 0 );
    }

};


template<typename RetT, typename Arg1T, typename Arg2T>
class Answer2 : public IAnswer<RetT>
{
private:
    typedef FnPlusArgs2<RetT, Arg1T, Arg2T> FnArgs;
    typedef std::auto_ptr< IAnswer<RetT> > AnswerPtr;

    const bool finished_;
    const FnArgs tail_call_;
    const RetT value_;

private:
    Answer2( const bool finished, const FnArgs tail_call, const RetT value )
    : finished_( finished )
    , tail_call_( tail_call )
    , value_( value )
    {
    }

    static AnswerPtr newPtr(
        const bool finished, const FnArgs tail_call, const RetT value )
    {
        return AnswerPtr( new Answer2<RetT, Arg1T, Arg2T>(
            finished, tail_call, value ) );
    }
public:
    static AnswerPtr newFn(
        const typename FnArgs::fn_type fn,
        const Arg1T arg1,
        const Arg2T arg2,
        const RetT zero_val )
    {
        return newPtr( false, FnArgs( fn, arg1, arg2 ), zero_val );
    }

    static AnswerPtr newAns( const RetT value )
    {
        return newPtr( true, FnArgs::null(), value );
    }

    virtual const bool    finished()  const { return finished_; };
    virtual const FnArgs& tail_call() const { return tail_call_; };
    virtual const RetT    value()     const { return value_; };
};

template<typename RetT>
const RetT trampoline_templ( std::auto_ptr< IAnswer<RetT> > answer )
{
    while( !answer->finished() )
    {
        answer = answer->tail_call()();
    }
    return answer->value();
}

}

#endif //TEMPL_LIB_H

