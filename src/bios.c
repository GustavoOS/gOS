int main(void)
{
    int osLength;
    int index;
    int data;
    int osStorage[0];
    int osRuntime[0];

    assignPointer(osRuntime, 3072);
    assignPointer(osStorage, 8193);
    osLength = readFromMemory(8192);
    index = 0;
    while (index < osLength)
    {
        data = osStorage[index / 2];
        osRuntime[index] = extractFirstHW(data);
        osRuntime[index + 1] = extractSecondHW(data);
        index = index + 2;
    }
    output(osRuntime[osLength - 1]);
    output(49568); // C1A0
    return 0;
}
