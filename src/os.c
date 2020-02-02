int registers;
int null;
int processInMemory;
int statusTable;
int nextProgram;

int getSlot(int file)
{
    return (file * 1432) + statusTable + 12;
}

void insertProgramIntoMemory(void)
{
    int instructionCount;
    int copied;
    int slotStart;
    int data;

    if (processInMemory == nextProgram)
        return;

    slotStart = getSlot(nextProgram);
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
    writeIntoMemory(statusTable + 10, nextProgram); // In memory
}

void execute(void)
{
    insertProgramIntoMemory();
    //Set Registers
    writeIntoMemory(registers + 1, 0);    // SpecReg
    writeIntoMemory(registers + 2, 0);    // PC
    writeIntoMemory(registers + 3, 8191); // SP
    writeIntoMemory(registers + 8, 0);    // Acumulator

    writeIntoMemory(statusTable + 11, nextProgram); // Leading process
    writeIntoMemory(statusTable + nextProgram, 2);  // Running
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

void validateNextProgram(int candidate)
{
    if (candidate > 9)
        return;
    if (readFromMemory(statusTable + candidate) == 0)
        return;
    nextProgram = candidate;
}

void kill(int process, int isVerbose)
{
    validateNextProgram(process);
    if (nextProgram == null)
        return;
    if (isVerbose == 1)
        output(4207542272 + process); // Faca
    writeIntoMemory(statusTable + process, 1);
    nextProgram = null;
}

void saveStack(int fileIndex)
{
    int stackIndex;
    int sp;

    stackIndex = 8192;
    sp = readFromMemory(registers + 3);

    while (sp < stackIndex)
    {
        writeIntoMemory(fileIndex, readFromMemory(stackIndex - 1));
        stackIndex = stackIndex - 1;
        fileIndex = fileIndex - 1;
    }
}

void saveState(void)
{
    int stackpointer;
    int minSP;
    int slot;
    slot = getSlot(processInMemory);
    stackpointer = readFromMemory(registers + 3);
    minSP = readFromMemory(slot) + 1;
    minSP = (minSP / 2) + 6777;

    if (stackpointer < minSP)
    {
        kill(processInMemory, 1);
        return;
    }

    slot = slot + 1431;

    writeIntoMemory(slot - 7, readFromMemory(registers + 8)); // Acumulator
    writeIntoMemory(slot - 6, readFromMemory(registers + 7)); // Temporary Register
    writeIntoMemory(slot - 5, readFromMemory(registers + 6)); // Frame Pointer
    writeIntoMemory(slot - 4, readFromMemory(registers + 5)); // Global Pointer
    writeIntoMemory(slot - 3, readFromMemory(registers + 4)); // Return Address
    writeIntoMemory(slot - 2, stackpointer);                  // SP
    writeIntoMemory(slot - 1, readFromMemory(registers + 2)); // PC
    writeIntoMemory(slot, readFromMemory(registers + 1));     // SpecReg

    saveStack(slot - 16);
}

void loadStack(int fileIndex)
{
    int stackIndex;
    int sp;

    stackIndex = 8192;
    sp = readFromMemory(registers + 3);

    while (sp < stackIndex)
    {
        writeIntoMemory(stackIndex - 1, readFromMemory(fileIndex));
        stackIndex = stackIndex - 1;
        fileIndex = fileIndex - 1;
    }
}

void continueExecution(void)
{
    int slotEnd;
    insertProgramIntoMemory();
    slotEnd = getSlot(nextProgram) + 1431;
    // Load registers
    writeIntoMemory(registers + 8, readFromMemory(slotEnd - 7)); // Acumulator
    writeIntoMemory(registers + 7, readFromMemory(slotEnd - 6)); // Temporary Register
    writeIntoMemory(registers + 6, readFromMemory(slotEnd - 5)); // Frame Pointer
    writeIntoMemory(registers + 5, readFromMemory(slotEnd - 4)); // Global Pointer
    writeIntoMemory(registers + 4, readFromMemory(slotEnd - 3)); // Return Address
    writeIntoMemory(registers + 3, readFromMemory(slotEnd - 2)); // SP
    writeIntoMemory(registers + 2, readFromMemory(slotEnd - 1)); // PC
    writeIntoMemory(registers + 1, readFromMemory(slotEnd));     // SpecReg

    loadStack(slotEnd - 16);
}

void scheduleNextProcess(void)
{
    saveState();
    validateNextProgram(findNextProcess(processInMemory, 2));
    if (nextProgram == null)
        return;
    continueExecution();
}

void resume(void)
{
    writeIntoMemory(statusTable + nextProgram, 2);
    continueExecution();
    writeIntoMemory(statusTable + 11, nextProgram); // The leading process
}

void processIORequest(void)
{
    writeIntoMemory(registers + 2,
                    readFromMemory(registers + 2) + 1); // PC++
    if (processInMemory == readFromMemory(statusTable + 11))
    {
        nextProgram = processInMemory;
        return;
    }
    writeIntoMemory(statusTable + processInMemory, 3); // Block
    scheduleNextProcess();
}

void iteractWithProcess(int process)
{
    int option;
    if (process == null)
        return;
    option = 0;
    while (null == null)
    {
        if (option == 0)
        {
            output(49152 + process); // C0 + process: Continue execution
            if (input() != 0)
            {
                nextProgram = process;
                resume();
                return;
            }
        }

        if (option == 1)
        {
            output(64202);
            if (input() != 0)
            {
                kill(process, 1);
                return;
            }
        }
        if (option == 2)
        {
            output(983146);
            if (input() != 0)
                return;
        }

        option = option + 1;
        if (option > 2)
            option = 0;
    }
}

void listProcesses(int condition)
{
    int result;
    if (processInMemory == null)
        return;
    result = processInMemory;
    while (null == null)
    {
        result = findNextProcess(result, condition);
        output(result);
        if (input() != 0)
        {
            iteractWithProcess(result);
            return;
        }
    }
}

void takeUserAction(void)
{
    int menu;
    menu = 0;
    while (nextProgram == null)
    {
        if (menu == 0)
        {
            output(49374); // C0DE
            if (input() != 0)
            {
                output(789996); // C0DEC
                validateNextProgram(input());
                if (nextProgram != null)
                    execute();
            }
        }
        if (menu == 1)
        {
            output(51966); // CAFE
            if (input() != 0)
            {
                output(831468); // CAFEC
                validateNextProgram(0);
                if (nextProgram != null)
                    listProcesses(2);
            }
        }

        if (menu == 2)
        {
            output(212724432); // CADEAD0
            if (input() != 0)
            {
                output(3403590924); // CADEAD0C
                validateNextProgram(0);
                if (nextProgram != null)
                    listProcesses(3);
            }
        }

        menu = menu + 1;
        if (menu > 2)
            menu = 0;
    }
}

void firstRun(void)
{
    int process;
    process = 0;
    while (process < 10)
    {
        kill(process, 0);
        process = process + 1;
    }
    processInMemory = null;
}

void dispatchSystemCalls(int systemCall)
{
    output(systemCall);
    if (systemCall == 0)
        scheduleNextProcess();
    if (systemCall == 1)
        processIORequest();
    if (systemCall == 2)
        kill(processInMemory, 1);
    if (systemCall == 3)
        saveState();
    if (systemCall == 4)
        firstRun();
}

int main(void)
{
    // Set Variables
    null = 0 - 1;
    statusTable = 18432;
    processInMemory = readFromMemory(statusTable + 10);
    nextProgram = null;

    dispatchSystemCalls(readFromMemory(registers));
    if (nextProgram == null)
        takeUserAction();

    output(3248488448 + nextProgram); // CIAO + Process
    return 0;
}
