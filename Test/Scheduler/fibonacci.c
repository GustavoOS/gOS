int main(void)
{
    int num;
    int numA;
    int numB;
    int i;

    numA = 1;
    numB = 0;
    i = 0;
    while (i < 200)
    {
        num = numA + numB;
        numB = numA;
        numA = num;
        i = i + 1;
    }
    output(num);
}
