int registers;
int null;
int processInMemory;

int readFromRegister(int reg)
{
    return readFromMemory(registers + reg);
}

void writeIntoRegister(int reg, int value)
{
    writeIntoMemory(registers + reg, value);
}

int getSlot(int file)
{
    return 18444 + (file * 1432);
}

void insertProcessIntoMemory(int file)
{
    int instructionCount;
    int copied;
    int fullWords;
    int slotStart;
    int data;

    slotStart = getSlot(file);
    instructionCount = readFromMemory(slotStart);
    slotStart = slotStart + 1; // where program start
    while (copied < instructionCount)
    {
        data = readFromMemory(slotStart + fullWords);
        writeIntoMemory(copied, extractFirstHW(data));
        writeIntoMemory(copied + 1, extractSecondHW(data));
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
    writeIntoMemory(listPosition, 2); // Mark slot as executing
    writeIntoMemory(18443, file);     // The leading process

    //Set Registers
    writeIntoRegister(1, 0);    // SpecReg
    writeIntoRegister(2, 0);    // PC
    writeIntoRegister(3, 8191); // SP
    return file;
}

int findNextProcess(int current, int condition)
{
    int next;
    next = current + 1;
    if (next > 9)
        next = 0;
    while (next != current)
    {
        if (readFromMemory(18432 + next) == condition)
            return next;
        next = next + 1;
        if (next > 9)
            next = 0;
    }
    if (readFromMemory(18432 + current) == condition)
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
            state = readFromMemory(18432 + process);
            state = state / state; // Division by 0 is defined as 0 in the ALU
            writeIntoMemory(18432 + process, state);
        }
    }
}

void saveState(void)
{
    int codeSize;
    int stackpointer;
    int slot;
    int regStart;
    stackpointer = readFromRegister(3);
    slot = getSlot(processInMemory);
    codeSize = readFromMemory(slot);
    codeSize = (codeSize + 1) / 2;
    if (stackpointer - codeSize > 6770) // If Stack Fits
    {
        regStart = getSlot(processInMemory + 1) - 1;

        // Save Registers
        writeIntoMemory(regStart, readFromRegister(1));     // SpecReg
        writeIntoMemory(regStart - 1, readFromRegister(2)); // PC
        writeIntoMemory(regStart - 2, stackpointer);        // SP
        writeIntoMemory(regStart - 3, readFromRegister(4)); // Return Address
        writeIntoMemory(regStart - 4, readFromRegister(5)); // Global Pointer
        writeIntoMemory(regStart - 5, readFromRegister(6)); // Frame Pointer
        writeIntoMemory(regStart - 6, readFromRegister(7)); // Temporary Register
        writeIntoMemory(regStart - 7, readFromRegister(8)); // Acumulator

        // Save Stack
        slot = slot + codeSize + 1;
        while (stackpointer < 8192)
        {
            writeIntoMemory(slot, readFromMemory(stackpointer));
            stackpointer = stackpointer + 1;
            slot = slot + 1;
        }
    }
    else
        kill(processInMemory);
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
    writeIntoRegister(1, readFromMemory(regStart));     // SpecReg
    writeIntoRegister(2, readFromMemory(regStart - 1)); // PC
    writeIntoRegister(3, stackpointer);                 // SP
    writeIntoRegister(4, readFromMemory(regStart - 3)); // Return Address
    writeIntoRegister(5, readFromMemory(regStart - 4)); // Global Pointer
    writeIntoRegister(6, readFromMemory(regStart - 5)); // Frame Pointer
    writeIntoRegister(7, readFromMemory(regStart - 6)); // Temporary Register
    writeIntoRegister(8, readFromMemory(regStart - 7)); // Acumulator

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

void continueExecution(int nextProgram)
{
    insertProcessIntoMemory(nextProgram);
    recoverState(nextProgram);
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


int resume(int process)
{
    if (process != null)
    {
        if (readFromMemory(18432 + process) > 1)
        {
            output(51966); // Cafe
            writeIntoMemory(18432 + process, 2);
            continueExecution(process);
            writeIntoMemory(18443, process); // The leading process
            return process;
        }
    }
    return null;
}

int ioFlow(void)
{
    output(16);
    writeIntoRegister(2, readFromRegister(2) + 1); // PC++ to avoid loop
    if (processInMemory == readFromMemory(18443))
        return processInMemory;
    writeIntoMemory(18432 + processInMemory, 3);
    return changeRunningProcess();
}

int main(void)
{
    int run;
    int userInput;
    int systemCall;
    int showing;
    null = 0 - 1;
    run = null;
    systemCall = readFromRegister(0);
    processInMemory = readFromMemory(18442);
    showing = processInMemory;
    output(systemCall);

    if (systemCall == 0)
        run = changeRunningProcess();
    if (systemCall == 1)
        run = ioFlow();
    if (systemCall == 2) // End Process
        kill(processInMemory);
    if (systemCall == 3) // User Preemption
        saveState();

    while (run == null)
    {
        output(0);
        userInput = input();

        if (userInput == 0)
        {
            output(49374); // Code
            run = execute(input());
        }
        if (userInput == 1)
        {
            output(2826); // B0A
            showing = findNextProcess(showing, 2);
            output(showing);
        }
        if (userInput == 2)
        {
            output(212724432); // CADEADO
            showing = findNextProcess(showing, 3);
            output(showing);
        }
        if (userInput == 3)
        {
            // CAFE
            run = resume(showing);
        }
        if (userInput == 4)
        {
            kill(showing);
        }
    }

    output(3248488448 + run); // CIAO + Process
    return 0;
}
