int one;
int zero;
int hdStart;
int osAddress;

void setupVariables(void)
{
    zero = 0;
    one = 1;
    osAddress = 2048;
    hdStart = 16384;
}

void moveData(int srcAddr, int targetAddr)
{
    int data;
    data = readFromMemory(srcAddr);
    writeIntoMemory(targetAddr, data);
}

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
        moveData(srcAddr + index, targetAddr + index);
        index = index + one;
    }
    output(readFromMemory(osLength + osAddress - one));
}

int main(void)
{
    setupVariables();
    insertOSIntoMemory();
    output(49568);
    return 0;
}
