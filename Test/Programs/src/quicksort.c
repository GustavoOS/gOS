int vet[10];

void swap(int values[], int first, int second)
{

    int temp;

    temp = values[first];
    values[first] = values[second];
    values[second] = temp;
}

int partition(int values[], int began, int end)
{
    int pivot;
    int edge;
    int sentinel;

    pivot = values[end];
    edge = began - 1;
    sentinel = began;

    while (sentinel < end)
    {
        if (values[sentinel] < pivot)
        {
            edge = edge + 1;
            swap(values, edge, sentinel);
        }
        sentinel = sentinel + 1;
    }

    edge = edge + 1;

    if (pivot < values[edge])
        swap(values, edge, end);

    return edge;
}

void quicksort(int values[], int began, int end)
{
    int p;

    if (began >= end)
        return;

    p = partition(vet, began, end);
    quicksort(vet, began, p - 1);
    quicksort(vet, p + 1, end);
}

int main(void)
{
    int i;
    i = 0;
    while (i < 10)
    {
        vet[i] = input();
        i = i + 1;
    }
    quicksort(vet, 0, 9);
    i = 0;
    while (i < 10)
    {
        output(vet[i]);
        i = i + 1;
    }
}