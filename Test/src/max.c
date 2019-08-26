int vet[100];
int length;

int findMax(void)
{

    int sentinel;
    int max;

    max = vet[0];
    sentinel = 0;

    while (sentinel < length)
    {
        if (vet[sentinel] > max)
            max = sentinel;
        sentinel = sentinel + 1;
    }
    return max;
}

int main(void)
{
    int i;
    int max;

    length = 100;

    i = 0;
    while (i < length)
    {
        vet[i] = length - i;
        i = i + 1;
    }
    max = findMax();
    output(max);
}