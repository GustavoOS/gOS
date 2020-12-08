int main(void)
{
    int i;
    int sum;

    i = 1;
    sum = 0;
    while (i <= 255)
    {
        sum = sum + i;
        i = i + 1;
    }
    output(i);
    if (sum == 32640)
        output(485); // 1E5
    else
        output(51914); // CACA

    return 0;
}
