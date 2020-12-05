int main(void)
{
    int osLength;
    int index;
    int osStorage[0];
    int osRuntime[0];

    assignPointer(osRuntime, 3072);
    assignPointer(osStorage, 8193);
    osLength = readFromMemory(8192);
    index = 0;
    while (index < osLength)
    {
        osRuntime[index] = osStorage[index];
        index = index + 1;
    }
    output(osRuntime[osLength - 1]);
    output(49568); // C1A0
    return 0;
}
