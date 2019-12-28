int registers;
int null;

int getSlot(int file)
{
    return 18445 + (file * 1432);
}

void movePackedData(int data, int targetAddress)
{
    writeIntoMemory(targetAddress, extractFirstHW(data));
    writeIntoMemory(targetAddress + 1, extractSecondHW(data));
}

void insertProcessIntoMemory(int file)
{
    int instructionCount;
    int copied;
    int fullWords;
    int slotStart;

    slotStart = getSlot(file);
    instructionCount = extractSecondHW(readFromMemory(slotStart));
    fullWords = 0;
    copied = 0;
    slotStart = slotStart + 1; // where program start
    while (copied < instructionCount)
    {
        movePackedData(
            readFromMemory(slotStart + fullWords),
            copied);
        fullWords = fullWords + 1;
        copied = copied + 2;
    }
    writeIntoMemory(18442, file); // In memory
}

int execute(int file)
{
    int listPosition;

    if (file > 9)
        return null;

    listPosition = 18432 + file;
    if (readFromMemory(listPosition) == 0)
        return null;

    insertProcessIntoMemory(file);

    // Update Process List
    writeIntoMemory(listPosition, 2);                  // Mark slot as executing
    writeIntoMemory(18443, file);                      // The leading process
    writeIntoMemory(18444, readFromMemory(18444) + 1); // ProcessCount ++

    //Set Registers
    writeIntoMemory(registers, 0);        // SystemCall
    writeIntoMemory(registers + 1, 0);    // SpecReg
    writeIntoMemory(registers + 2, 0);    // PC
    writeIntoMemory(registers + 3, 8191); // SP
    return file;
}

int findNextProcess(int condition)
{
    int next;
    int current;

    current = readFromMemory(18442);
    next = current + 1;

    while (next != current)
    {
        if (next > 9)
            next = 0;
        if (readFromMemory(18432 + next) == condition)
            return next;
        next = next + 1;
    }
    return current;
}

int saveState(int program)
{
    int codeSize;
    int stackpointer;
    int slot;
    int regStart;
    int maxSP;
    stackpointer = readFromMemory(registers + 3);
    slot = getSlot(program);
    codeSize = extractSecondHW(readFromMemory(slot));
    codeSize = (codeSize + 1) / 2;
    if (stackpointer - codeSize < 6769)
        return null; // Stack doesn't fit

    regStart = getSlot(program + 1) - 1;

    // Save Registers
    writeIntoMemory(regStart, readFromMemory(registers + 1));     // SpecReg
    writeIntoMemory(regStart - 1, readFromMemory(registers + 2)); // PC
    writeIntoMemory(regStart - 2, stackpointer);                  // SP
    writeIntoMemory(regStart - 3, readFromMemory(registers + 4)); // Swap
    writeIntoMemory(regStart - 4, readFromMemory(registers + 5)); // Return Address
    writeIntoMemory(regStart - 5, readFromMemory(registers + 6)); // Global Pointer
    writeIntoMemory(regStart - 6, readFromMemory(registers + 7)); // Frame Pointer
    writeIntoMemory(regStart - 7, readFromMemory(registers + 8)); // Temporary Register
    writeIntoMemory(regStart - 8, readFromMemory(registers + 9)); // Acumulator

    // Save Stack
    slot = slot + codeSize + 1;
    maxSP = 8192;
    while (stackpointer < maxSP)
    {
        writeIntoMemory(slot, readFromMemory(stackpointer));
        stackpointer = stackpointer + 1;
        slot = slot + 1;
    }
    return 0;
}

void recoverState(int file)
{
    int regStart;
    int stackpointer;
    int maxSP;
    int codeSize;
    regStart = getSlot(file + 1) - 1;
    stackpointer = readFromMemory(regStart - 2);
    maxSP = 8192;
    //Save registers
    writeIntoMemory(registers + 1, readFromMemory(regStart));     // SpecReg
    writeIntoMemory(registers + 2, readFromMemory(regStart - 1)); // PC
    writeIntoMemory(registers + 3, stackpointer);                 // SP
    writeIntoMemory(registers + 4, readFromMemory(regStart - 3)); // Swap
    writeIntoMemory(registers + 5, readFromMemory(regStart - 4)); // Return Address
    writeIntoMemory(registers + 6, readFromMemory(regStart - 5)); // Global Pointer
    writeIntoMemory(registers + 7, readFromMemory(regStart - 6)); // Frame Pointer
    writeIntoMemory(registers + 8, readFromMemory(regStart - 7)); // Temporary Register
    writeIntoMemory(registers + 9, readFromMemory(regStart - 8)); // Acumulator

    regStart = getSlot(file);
    codeSize = extractSecondHW(readFromMemory(regStart));
    codeSize = (codeSize + 1) / 2;
    regStart = regStart + codeSize + 1;
    while (stackpointer < maxSP)
    {
        writeIntoMemory(stackpointer, readFromMemory(regStart));
        stackpointer = stackpointer + 1;
        regStart = regStart + 1;
    }
}

void kill(int process)
{
    int state;
    state = readFromMemory(18432 + process);
    writeIntoMemory(18432 + process, 1);
    if (state > 1)
        writeIntoMemory(18444, readFromMemory(18444) - 1);
}

int changeRunningProcess(void)
{
    int numberOfRunningPrograms;
    int programInMemory;
    int nextAvailableProgram;
    numberOfRunningPrograms = readFromMemory(18444);
    if (numberOfRunningPrograms == 0)
        return null;
    programInMemory = readFromMemory(18442);
    nextAvailableProgram = findNextProcess(2);
    if (nextAvailableProgram == programInMemory)
        return programInMemory;

    if (saveState(programInMemory) == null)
        kill(programInMemory);
    insertProcessIntoMemory(nextAvailableProgram);
    recoverState(nextAvailableProgram);
    return nextAvailableProgram;
}

void listProcess(int condition) {} //TODO
int resume(int process) {}         //TODO
void ioFlow(void) {}               //TODO

int main(void)
{
    int run;
    int userInput;
    int systemCall;
    null = 0 - 1;
    run = null;
    systemCall = readFromMemory(registers);
    if (systemCall == 0)
        run = changeRunningProcess();
    if (systemCall == 1)
        ioFlow();
    if (systemCall == 2)
        kill(readFromMemory(18442));

    while (run == null)
    {
        userInput = input();

        if (userInput == 0)
            output(45141); // gOS
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