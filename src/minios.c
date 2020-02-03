int registers;
int null;

void saveStack(void)
{
    int fileIndex;
    int stackIndex;
    int sp;

    fileIndex = 19859;
    stackIndex = 8192;
    sp = readFromMemory(registers + 3);

    while (sp < stackIndex)
    {
        writeIntoMemory(fileIndex, readFromMemory(stackIndex - 1));
        stackIndex = stackIndex - 1;
        fileIndex = fileIndex - 1;
    }
}

void loadStack(void)
{
    int fileIndex;
    int stackIndex;
    int sp;

    fileIndex = 19859;
    stackIndex = 8192;
    sp = readFromMemory(registers + 3);

    while (sp < stackIndex)
    {
        writeIntoMemory(stackIndex - 1, readFromMemory(fileIndex));
        stackIndex = stackIndex - 1;
        fileIndex = fileIndex - 1;
    }
}

void insertProgramIntoMemory(void)
{
    int instructionCount;
    int copied;
    int slotStart;
    int data;

    slotStart = 18444;
    instructionCount = readFromMemory(slotStart);
    slotStart = slotStart + 1; // where program starts
    copied = 0;
    while (copied < instructionCount)
    {
        data = readFromMemory(slotStart + (copied / 2));
        writeIntoMemory(copied, extractFirstHW(data));
        writeIntoMemory(copied + 1, extractSecondHW(data));
        copied = copied + 2;
    }
}

void continueProcess(int slotEnd)
{
    insertProgramIntoMemory();
    // Load registers
    writeIntoMemory(registers + 8, readFromMemory(slotEnd - 7)); // Acumulator
    writeIntoMemory(registers + 7, readFromMemory(slotEnd - 6)); // Temporary Register
    writeIntoMemory(registers + 6, readFromMemory(slotEnd - 5)); // Frame Pointer
    writeIntoMemory(registers + 5, readFromMemory(slotEnd - 4)); // Global Pointer
    writeIntoMemory(registers + 4, readFromMemory(slotEnd - 3)); // Return Address
    writeIntoMemory(registers + 3, readFromMemory(slotEnd - 2)); // SP
    writeIntoMemory(registers + 2, readFromMemory(slotEnd - 1)); // PC
    writeIntoMemory(registers + 1, readFromMemory(slotEnd));     // SpecReg

    loadStack();
}

void runNewProcess(void)
{
    insertProgramIntoMemory();
    //Set Registers
    writeIntoMemory(registers + 1, 0);    // SpecReg
    writeIntoMemory(registers + 2, 0);    // PC
    writeIntoMemory(registers + 3, 8191); // SP
    writeIntoMemory(registers + 8, 0);    // Acumulator
}

void takeUserAction(void)
{
    while (null == null)
    {

        output(49374); // C0DE
        if (input() != 0)
        {
            output(789996); // C0DEC
            runNewProcess();
            return;
        }

        output(51966); // CAFE
        if (input() != 0)
        {
            output(831468); // CAFEC
            continueProcess(19875);
            return;
        }
    }
}

int ioFlow(void)
{
    writeIntoMemory(registers + 2,
                    readFromMemory(registers + 2) + 1); // PC++
    return 0;
}

void saveState(void)
{
    int stackpointer;
    int minSP;
    stackpointer = readFromMemory(registers + 3);
    minSP = readFromMemory(18444) + 1;
    minSP = (minSP / 2) + 6777;

    if (stackpointer < minSP)
        return;

    writeIntoMemory(19868, readFromMemory(registers + 8)); // Acumulator
    writeIntoMemory(19869, readFromMemory(registers + 7)); // Temporary Register
    writeIntoMemory(19870, readFromMemory(registers + 6)); // Frame Pointer
    writeIntoMemory(19871, readFromMemory(registers + 5)); // Global Pointer
    writeIntoMemory(19872, readFromMemory(registers + 4)); // Return Address
    writeIntoMemory(19873, stackpointer);                  // SP
    writeIntoMemory(19874, readFromMemory(registers + 2)); // PC
    writeIntoMemory(19875, readFromMemory(registers + 1)); // SpecReg

    saveStack();
}

int dispatchSystemCalls(int systemCall)
{
    output(systemCall);
    if (systemCall == 1)
        return ioFlow();
    if (systemCall == 3)
        saveState();
    return null;
}

int main(void)
{
    int run;

    // Set Variables
    null = 0 - 1;
    run = dispatchSystemCalls(readFromMemory(registers));
    if (run == null)
        takeUserAction();

    output(49568);
    return 0;
}
