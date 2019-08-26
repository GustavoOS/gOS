int vet[100];
int length;

int findMin(void)
{

    int sentinel;
    int min;

    min = vet[0];
    sentinel = 0;

    while (sentinel < length)
    {
        if (vet[sentinel] < min)
            min = sentinel;
        sentinel = sentinel + 1;
    }
    return min;
}

int main(void)
{
    int i;
    int min;

    length = 100;

    i = 0;
    while (i < length)
    {
        vet[i] = length - i;
        i = i + 1;
    }
    min = findMin();
    output(min);
}