int main(void)
{
    int remainingInstructions;
    int osStorage[0];
    int osRuntime[0];

    assignPointer(osRuntime, 3072);
    assignPointer(osStorage, 8193);
    remainingInstructions = readFromMemory(8192); // Size of OS
    while (remainingInstructions > 0)
    {
        osRuntime[0] = extractFirstHW(osStorage[0]);
        osRuntime[1] = extractSecondHW(osStorage[0]);
        assignPointer(osRuntime, readPointer(osRuntime) + 2);
        assignPointer(osStorage, readPointer(osStorage) + 1);
        remainingInstructions = remainingInstructions - 2;
    }
    output(readFromMemory(readFromMemory(8192) + 3071)); // Last OS instruction
    output(49568);                                       // C1A0
    return 0;
}
