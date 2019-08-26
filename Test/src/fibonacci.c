int fibonacci(int sequence)
{
    int ultimate;
    int penultimate;
    int step;
    int fib;

    ultimate = 1;
    step = 3;

    if (sequence < 3)
        return 1;

    while (step <= sequence)
    {
        fib = ultimate + penultimate;
        penultimate = ultimate;
        ultimate = fib;

        step = step + 1;
    }
    return fib;
}

void main(void)
{
    int sequence;
    sequence = input();
    sequence = fibonacci(sequence);
    output(sequence);
}