int main(void)
{
    int osLength;
    int index;

    osLength = readFromMemory(16384);
    index = 0;
    while (index < osLength)
    {
        writeIntoMemory(2048 + index,
                        readFromMemory(16385 + index));
        index = index + 1;
    }
    output(readFromMemory(osLength + 2047));
    output(49568);
    return 0;
}
