#include <iostream>
#include <string>

#include "hardware.cpp"
#include "loop.cpp"
#include "recursive.cpp"
#include "tail_call.cpp"
#include "tail_call_templ.cpp"

#include "test_one.cpp"

int test_all()
{
    try
    {
        test_one( times_two_hardware,        "times_two_hardware"        );
        test_one( times_two_loop,            "times_two_loop"            );
        test_one( times_two_recursive,       "times_two_recursive"       );
        test_one( times_two_tail_call,       "times_two_tail_call"       );
        test_one( times_two_tail_call_templ, "times_two_tail_call_templ" );
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
    else if ( arg == "tail_call_templ" )
    {
        call_one( times_two_tail_call_templ, argc, argv );
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

