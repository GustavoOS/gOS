int fibonacci(int sequence)
{
    int ultimate;
    int penultimate;
    int step;
    int fib;

    ultimate = 1;
    penultimate = 1;
    step = 2;

    if (sequence < 3)
        return 1;

    while (step < sequence)
    {
        fib = ultimate + penultimate;
        penultimate = ultimate;
        ultimate = fib;

        step = step + 1;
    }
    return fib;
}

int isEven(int n)
{
    int parity;
    int step;

    parity = 1;
    step = 1;

    while (step <= n)
    {
        if (parity == 1)
        {
            parity = 0;
        }
        else
        {
            parity = 1;
        }
        step = step + 1;
    }
    return parity;
}

int main(void)
{
    int ticket;

    ticket = input();
    ticket = fibonacci(ticket);
    ticket = isEven(ticket);

    if (ticket == 1)
    {
        // you won
        output(2798);
    }
    else
    {
        /* you lost */
        output(62224);
    }
}