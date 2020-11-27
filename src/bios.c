int main(void)
{
    int osLength;
    int index;
    int osStorage[0];
    int osRuntime[0];

    assignPointer(osRuntime, 2048);
    assignPointer(osStorage, 16385);
    osLength = readFromMemory(16384);
    index = 0;
    while (index < osLength)
    {
        osRuntime[index] = osStorage[index];
        index = index + 1;
    }
    output(osRuntime[osLength - 1]);
    output(49568);
    return 0;
}
