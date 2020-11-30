int context[0];

int main(void)
{
    int i;
    i = 0;
    assignPointer(context, 6133);
    while (i < 10)
    {
        output(context[i]);
        i = i + 1;
    }
    context[2] = 3;
    output(49568); //C1A0
    return 0;
}
