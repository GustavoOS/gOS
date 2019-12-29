int hdStart;
int osAddress;

void insertOSIntoMemory(void)
{
    int osLength;
    int index;
    int srcAddr;
    int targetAddr;

    osLength = readFromMemory(hdStart);
    index = 0;
    srcAddr = hdStart + 1;
    targetAddr = osAddress;
    while (index < osLength)
    {
        writeIntoMemory(targetAddr + index,
                        readFromMemory(srcAddr + index));
        index = index + 1;
    }
    output(readFromMemory(osLength + osAddress - 1));
}

int main(void)
{
    osAddress = 2048;
    hdStart = 16384;
    insertOSIntoMemory();
    output(49568);
    return 0;
}
