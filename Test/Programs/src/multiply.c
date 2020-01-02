int main(void)
{
    int a;
    int b;
    a = 1600;
    b = 32;
    while (a > 1)
    {
        b = b + b;
        a = a - 1;
    }

    output(b);
    return 0;
}
