int context[0];

int main(void)
{
    int i;
    i = 0;
    assignPointer(context, 6134);
    while (i < 10)
    {
        output(context[i]);
        i = i + 1;
    }
    context[2] = 3;
    return 0;
}
