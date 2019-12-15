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
        srcAddr = srcAddr + index;
        targetAddr = targetAddr + index;
        moveData(srcAddr, targetAddr);
        index = index + 1;
    }
}

int main(void)
{
    setupVariables();
    insertOSIntoMemory();
    return 0;
}
