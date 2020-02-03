int main(void)
{
    int osLength;
    int index;
    int osStart;
    int hdStart;

    osStart = 2048;
    hdStart = 16384;
    osLength = readFromMemory(hdStart);
    hdStart = hdStart + 1;
    index = 0;
    while (index < osLength)
    {
        writeIntoMemory(osStart + index,
                        readFromMemory(hdStart + index));
        index = index + 1;
    }
    output(readFromMemory(osLength + osStart - 1));
    output(49568);
    return 0;
}
