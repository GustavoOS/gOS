int userInput;
int null;
int zero;
int one;
int two;

int slot(int number)
{
    return 18442 +
           (1432 * number);
}

void setupVariables(void)
{
    zero = 0;
    one = 1;
    null = zero - one;
    two = 2;
}

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
    fullWords = zero;
    copied = zero;
    slotStart = slotStart + two; // where program start
    while (copied < instructionCount)
    {
        word = readFromMemory(slotStart + fullWords);
        movePackedData(word, copied);
        fullWords = fullWords + one;
        copied = copied + two;
    }
}

int findProgramByName(int file)
{
    int index;
    index = zero;
    while (index < 10)
    {
        if (readFromMemory(slot(index)) == file)
            return index;

        index = index + one;
    }
    return null;
}

int execute(int file)
{
    int programIndex;

    programIndex = findProgramByName(file);
    if (programIndex == null)
        return zero;
    if (readFromMemory(18432 + programIndex) == 0)
        return zero;
    insertProcessIntoMemory(slot(programIndex));
    return file;
}

void listProcess(int condition) {} //TODO
int resume(int process) {}         //TODO
void kill(int process) {}          //TODO

int main(void)
{
    int run;
    setupVariables();
    run = zero;

    while (run < one)
    {
        userInput = input();

        if (userInput == zero)
            output(45141);
        if (userInput == one)
            run = execute(input());
        if (userInput == two)
            run = resume(input());
        if (userInput == 3)
            kill(input());
        if (userInput == 4)
            listProcess(2);
        if (userInput == 5)
            listProcess(3);
    }

    return zero;
}