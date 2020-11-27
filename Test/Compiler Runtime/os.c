int context[0];

int main(void)
{
    int i;
    i = 0;
    assignPointer(context, 6134);
    while (i < 9)
    {
        output(context[i]);
        i = i + 1;
    }
    return 0;
}
