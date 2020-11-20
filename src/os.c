int null;
int nextProgram;

int context[0];
int statusTable[0];
int file[0];

int getSlot(int fileIndex)
{
    return (fileIndex * 1432) + 18444;
}

int file_stackOrigin(void)
{
    return ((file[0] + 1) / 2) + 1;
}

void insertProgramIntoMemory(void)
{
    int instructionCount;
    int copied;
    int slotStart;
    int data;
    int program[0];

    slotStart = getSlot(nextProgram);
    assignPointer(file, slotStart);
    assignPointer(program, 0);
    instructionCount = file[0];
    assignPointer(file, slotStart + 1);
    copied = 0;
    while (copied < instructionCount)
    {
        data = file[copied / 2];
        program[copied] = extractFirstHW(data);
        program[copied + 1] = extractSecondHW(data);
        copied = copied + 2;
    }
    statusTable[10] = nextProgram; // In memory
}

void execute(void)
{
    output(941760 + nextProgram); //E5EC
    insertProgramIntoMemory();
    //Set context
    context[1] = 0;    // SpecReg
    context[2] = 0;    // PC
    context[3] = 8191; // SP
    context[8] = 0;    // Acumulator

    statusTable[11] = nextProgram; // Leading process
    statusTable[nextProgram] = 2;  // Running
}

// int findNextProcess(int current, int condition)
// {
//     int next;
//     next = (current + 1) | 10;
//     while (next != current)
//     {
//         if (statusTable[next] == condition)
//             return next;
//         next = (next + 1) | 10;
//     }
//     if (statusTable[current] == condition)
//         return current;
//     return null;
// }

void validateNextProgram(int candidate)
{
    if (candidate > 9)
        return;
    if (statusTable[candidate] == 0)
        return;
    nextProgram = candidate;
}

void fastKill(int process)
{
    if (statusTable[process] > 1)
        statusTable[process] = 1;
}

void kill(int process)
{
    if (process < 10)
    {
        output(1027232 + process); // Faca
        fastKill(process);
    }
}

void saveStack(void)
{
    int remainingItems;
    int stack[0];

    remainingItems = 8192 - context[3];
    assignPointer(stack, context[3]);
    assignPointer(file, file_stackOrigin() + getSlot(statusTable[10]));

    while (remainingItems > 0)
    {
        file[remainingItems] = stack[remainingItems];
        remainingItems = remainingItems - 1;
    }
}

void saveState(void)
{
    int stackpointer;
    int slot;
    int minSP;
    slot = getSlot(statusTable[10]);
    output(1360 + statusTable[10]); // 55
    assignPointer(file, getSlot(statusTable[10]));
    stackpointer = context[3];
    minSP = file_stackOrigin() + 6777;
    if (stackpointer < minSP)
    {
        output(57344); // E000
        kill(statusTable[10]);
        return;
    }
    assignPointer(file, slot + 1423); // file += 1423
    file[0] = context[8];             // Acumulator
    file[1] = context[7];             // Temporary Register
    file[2] = context[6];             // Second Register
    file[3] = context[5];             // Frame Pointer
    file[4] = context[4];             // Global Pointer
    file[5] = context[3];             // SP
    file[6] = context[2];             // PC
    file[7] = context[1];             // SpecReg
    file[8] = context[0];             // SysCall

    saveStack();
}

void loadStack(void)
{
    int remainingItems;
    int stack[0];

    remainingItems = 8192 - context[3];
    assignPointer(stack, context[3]);
    assignPointer(file, file_stackOrigin() + getSlot(nextProgram));

    while (remainingItems > 0)
    {
        stack[remainingItems] = file[remainingItems];
        remainingItems = remainingItems - 1;
    }
}

void continueExecution(void)
{
    int slot;
    slot = getSlot(nextProgram);
    output(13524672 + nextProgram); // CESEC0
    insertProgramIntoMemory();
    assignPointer(file, slot + 1423);
    // Load context
    context[8] = file[0]; // Acumulator
    context[7] = file[1]; // Temporary Register
    context[6] = file[2]; // Second Register
    context[5] = file[3]; // Frame Pointer
    context[4] = file[4]; // Global Pointer
    context[3] = file[5]; // SP
    context[2] = file[6]; // PC
    context[1] = file[7]; // SpecReg

    assignPointer(file, slot);
    loadStack();
}

void callExecuter(void)
{
    if (statusTable[nextProgram] == 1)
    {
        execute();
        return;
    }
    statusTable[nextProgram] = 2;
    continueExecution();
    statusTable[11] = nextProgram; // The leading process
}

void processIORequest(void)
{
    context[2] = context[2] + 1; // PC++
    if (statusTable[10] == statusTable[11])
    {
        output(256 + statusTable[10]); // 10
        nextProgram = statusTable[10];
        return;
    }
    output(57360); // E010
    statusTable[statusTable[10]] = 3;
    saveState();
}

// void listProcesses(int condition)
// {
//     int result;
//     result = 0;
//     while (null == null)
//     {
//         result = findNextProcess(result, condition);
//         output(result);
//         if (input() != 0)
//             return;
//     }
// }

void takeUserAction(void)
{
    while (nextProgram == null)
    {

        output(49374); // C0DE
        if (input() != 0)
        {
            output(789996); // C0DEC
            validateNextProgram(input());
            if (nextProgram != null)
            {
                callExecuter();
                return;
            }
        }

        output(64202); // FACA
        if (input() != 0)
        {
            output(1027244); // FACAC
            kill(input());
        }

        // output(51966); // CAFE
        // if (input() != 0)
        // {
        //     output(831468); // CAFEC
        //     listProcesses(2);
        // }

        // output(212724432); // CADEAD0
        // if (input() != 0)
        // {
        //     output(3403590924); // CADEAD0C
        //     listProcesses(3);
        // }
    }
}

void firstRun(void)
{
    fastKill(0);
    fastKill(1);
    fastKill(2);
    fastKill(3);
    fastKill(4);
    fastKill(5);
    fastKill(6);
    fastKill(7);
    fastKill(8);
    fastKill(9);

    statusTable[10] = null;
}

void dispatchSystemCalls(int systemCall)
{
    output(systemCall);
    if (systemCall == 4)
    {
        firstRun();
        return;
    }
    if (systemCall == 2)
    {
        kill(statusTable[10]);
        return;
    }
    if (systemCall == 1)
    {
        processIORequest();
        return;
    }
    saveState();
}

int main(void)
{
    // Set Variables
    null = 0 - 1;
    assignPointer(statusTable, 18432);
    assignPointer(context, 6135);
    nextProgram = null;

    dispatchSystemCalls(context[0]);
    if (nextProgram == null)
        takeUserAction();

    output(3248488448 + nextProgram); // CIAO + Process
    return 0;
}
