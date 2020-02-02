int registers;
int null;
int processInMemory;
int statusTable;

int getSlot(int file)
{
    return (file * 1432) + statusTable + 12;
}

void insertProgramIntoMemory(int file)
{
    int instructionCount;
    int copied;
    int slotStart;
    int data;

    slotStart = getSlot(file);
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
    writeIntoMemory(statusTable + 10, file); // In memory
}

void execute(int file)
{
    insertProgramIntoMemory(file);
    //Set Registers
    writeIntoMemory(registers + 1, 0);    // SpecReg
    writeIntoMemory(registers + 2, 0);    // PC
    writeIntoMemory(registers + 3, 8191); // SP
    writeIntoMemory(registers + 8, 0);    // Acumulator
}

int findNextProcess(int current, int condition)
{
    int next;
    next = current + 1;
    if (next > 9)
        next = 0;
    while (next != current)
    {
        if (readFromMemory(statusTable + next) == condition)
            return next;
        next = next + 1;
        if (next > 9)
            next = 0;
    }
    if (readFromMemory(statusTable + current) == condition)
        return current;
    return null;
}

void kill(int process)
{
    int state;
    if (process < 10)
    {
        if (processInMemory != null)
        {
            output(4207542272 + process); // Faca
            state = readFromMemory(statusTable + process);
            state = state / state; // Division by 0 is defined as 0 in the ALU
            writeIntoMemory(statusTable + process, state);
        }
    }
}

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

void saveState(int slot)
{
    int stackpointer;
    int minSP;
    stackpointer = readFromMemory(registers + 3);
    minSP = readFromMemory(slot) + 1;
    minSP = (minSP / 2) + 6777;

    if (stackpointer < minSP)
        return;
    slot = slot + 1431;

    writeIntoMemory(slot - 7, readFromMemory(registers + 8)); // Acumulator
    writeIntoMemory(slot - 6, readFromMemory(registers + 7)); // Temporary Register
    writeIntoMemory(slot - 5, readFromMemory(registers + 6)); // Frame Pointer
    writeIntoMemory(slot - 4, readFromMemory(registers + 5)); // Global Pointer
    writeIntoMemory(slot - 3, readFromMemory(registers + 4)); // Return Address
    writeIntoMemory(slot - 2, stackpointer);                  // SP
    writeIntoMemory(slot - 1, readFromMemory(registers + 2)); // PC
    writeIntoMemory(slot, readFromMemory(registers + 1));     // SpecReg

    saveStack();
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

void continueExecution(int pgm)
{
    int slotEnd;
    insertProgramIntoMemory(pgm);
    slotEnd = getSlot(pgm) + 1431;
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

int changeRunningProcess(void)
{
    int nextAvailableProgram;
    nextAvailableProgram = findNextProcess(processInMemory, 2);
    if (nextAvailableProgram == null)
        return null;
    continueExecution(nextAvailableProgram);
    return nextAvailableProgram;
}

int resume(void)
{
    int process;
    int stateSlot;
    process = input();
    if (process < 10)
    {
        stateSlot = statusTable + process;
        if (1 < readFromMemory(stateSlot))
        {
            writeIntoMemory(stateSlot, 2);
            continueExecution(process);
            writeIntoMemory(statusTable + 11, process); // The leading process
            return process;
        }
    }
    return null;
}

int ioFlow(void)
{
    writeIntoMemory(registers + 2,
                    readFromMemory(registers + 2) + 1); // PC++
    // if (processInMemory == readFromMemory(18443))
    //     return processInMemory;
    // writeIntoMemory(18432 + processInMemory, 3);
    return 0;
    // return changeRunningProcess();
}

void takeUserAction(void)
{
    int menu;
    menu = 0;
    while (menu == menu)
    {
        if (menu == 0)
        {
            output(49374); // C0DE
            if (input() != 0)
            {
                output(789996); // C0DEC
                execute(0);
                return;
            }
        }
        if (menu == 1)
        {
            output(51966); // CAFE
            if (input() != 0)
            {
                output(831468); // CAFEC
                continueExecution(19875);
                return;
            }
        }

        menu = menu + 1;
        if (menu > 1)
            menu = 0;
    }
}

int dispatchSystemCalls(int systemCall)
{
    output(systemCall);
    if (systemCall == 1)
        return ioFlow();
    if (systemCall == 3)
        saveState(0);
    return null;
}

int main(void)
{
    int run;

    // Set Variables
    null = 0 - 1;
    statusTable = 18432;
    processInMemory = readFromMemory(statusTable + 10);
    run = dispatchSystemCalls(readFromMemory(registers));
    if (run == null)
        takeUserAction();

    output(49568);
    return 0;
}
