
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

