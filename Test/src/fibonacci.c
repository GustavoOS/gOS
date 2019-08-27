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

int main(void)
{
    int sequence;
    sequence = input();
    sequence = fibonacci(sequence);
    output(sequence);
}