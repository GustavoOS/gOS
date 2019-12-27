int userInput;
int null;

int slot(int number)
{
    return 18445 +
           (1432 * number);
}

void movePackedData(int data, int targetAddress)
{
    writeIntoMemory(targetAddress, extractFirstHW(data));
    writeIntoMemory(targetAddress + 1, extractSecondHW(data));
}

void insertProcessIntoMemory(int slotStart)
{
    int instructionCount;
    int copied;
    int fullWords;
    int word;

    instructionCount = readFromMemory(slotStart + 1);
    fullWords = 0;
    copied = 0;
    slotStart = slotStart + 2; // where program start
    while (copied < instructionCount)
    {
        word = readFromMemory(slotStart + fullWords);
        movePackedData(word, copied);
        fullWords = fullWords + 1;
        copied = copied + 2;
    }
}

int findProgramByName(int file)
{
    int index;
    index = 0;
    while (index < 10)
    {
        if (readFromMemory(slot(index)) == file)
            return index;

        index = index + 1;
    }
    return null;
}

int execute(int file)
{
    int programIndex;

    programIndex = findProgramByName(file);
    if (programIndex == null)
        return 0;
    if (readFromMemory(18432 + programIndex) == 0)
        return 0;
    insertProcessIntoMemory(slot(programIndex));
    return file;
}

void listProcess(int condition) {} //TODO
int resume(int process) {}         //TODO
void kill(int process) {}          //TODO

int main(void)
{
    int run;
    null = 0 - 1;
    run = 0;

    while (run < 1)
    {
        userInput = input();

        if (userInput == 0)
            output(45141);
        if (userInput == 1)
            run = execute(input());
        if (userInput == 2)
            run = resume(input());
        if (userInput == 3)
            kill(input());
        if (userInput == 4)
            listProcess(2);
        if (userInput == 5)
            listProcess(3);
    }

    return 0;
}