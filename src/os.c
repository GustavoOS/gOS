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

    instructionCount = readFromMemory(slotStart + 1);
    fullWords = 0;
    copied = 0;
    slotStart = slotStart + 2; // where program start
    while (copied < instructionCount)
    {
        movePackedData(
            readFromMemory(slotStart + fullWords),
            copied);
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
    int listPosition;

    programIndex = findProgramByName(file);
    listPosition = 18432 + programIndex;
    if (programIndex == null)
        return 0;
    if (readFromMemory(listPosition) == 0)
        return 0;
    insertProcessIntoMemory(slot(programIndex));
    writeIntoMemory(listPosition, 2);                  // Mark slot as executing
    writeIntoMemory(18442, programIndex);              // In memory
    writeIntoMemory(18443, programIndex);              // The leading process
    writeIntoMemory(18444, readFromMemory(18444) + 1); //process ++

    return file;
}

void listProcess(int condition) {} //TODO
int resume(int process) {}         //TODO
void kill(int process) {}          //TODO

int main(void)
{
    int run;
    int userInput;
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