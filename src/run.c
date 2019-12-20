int one;
int two;

void movePackedData(int data, int targetAddress)
{
    writeIntoMemory(targetAddress, extractFirstHW(data));
    writeIntoMemory(targetAddress + one, extractSecondHW(data));
}

void insertProcessIntoMemory(int slotStart)
{
    int instructionCount;
    int copied;
    int fullWords;
    int word;

    instructionCount = readFromMemory(slotStart + one);
    fullWords = 0;
    copied = fullWords;
    slotStart = slotStart + two; // where program start
    while (copied < instructionCount)
    {
        word = readFromMemory(slotStart + fullWords);
        movePackedData(word, copied);
        fullWords = fullWords + one;
        copied = copied + two;
    }
}

int main(void)
{
    one = 1;
    two = 2;
    insertProcessIntoMemory(18442); //2058 + 16384
    output(49568); //ciao
    return 0;
}
