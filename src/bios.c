int one;
int zero;
int hdStart;
int osAddress;

void insertOSIntoMemory(void)
{
    int osLength;
    int index;
    int srcAddr;
    int targetAddr;

    osLength = readFromMemory(hdStart);
    index = zero;
    srcAddr = hdStart + one;
    targetAddr = osAddress;
    while (index < osLength)
    {
        writeIntoMemory(targetAddr + index,
                        readFromMemory(srcAddr + index));
        index = index + one;
    }
    output(readFromMemory(osLength + osAddress - one));
}

int main(void)
{
    zero = 0;
    one = 1;
    osAddress = 2048;
    hdStart = 16384;
    insertOSIntoMemory();
    output(49568);
    return 0;
}
