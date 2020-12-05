int null;
int nextProgram;

int context[0];
int statusTable[0];
int slotPosition[0];
int file[0];

void insertProgramIntoMemory(void)
{
    int instructionCount;
    int copied;
    int slotStart;
    int data;
    int program[0];

    slotStart = slotPosition[nextProgram];
    assignPointer(program, 0);
    assignPointer(file, slotStart + 1);
    instructionCount = readFromMemory(slotStart);
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

void saveHeap(void)
{
    int lastRemainingItemIndex;
    int heap[0];
    int endOfStack;

    lastRemainingItemIndex = context[9] - 7168;
    assignPointer(heap, context[9]);
    assignPointer(file, slotPosition[statusTable[10]] + 1537);

    endOfStack = 1023;

    while (lastRemainingItemIndex >= 0)
    {
        file[endOfStack - lastRemainingItemIndex] = heap[lastRemainingItemIndex];
        lastRemainingItemIndex = lastRemainingItemIndex - 1;
    }
}

void saveStack(void)
{
    int lastRemainingItemIndex;
    int stack[0];

    lastRemainingItemIndex = 8192 - context[3];
    assignPointer(stack, context[3]);
    assignPointer(file, slotPosition[statusTable[10]] + 1537);

    while (lastRemainingItemIndex >= 0)
    {
        file[lastRemainingItemIndex] = stack[lastRemainingItemIndex];
        lastRemainingItemIndex = lastRemainingItemIndex - 1;
    }
    saveHeap();
}

void saveState(void)
{
    output(1360 + statusTable[10]); // 55
    assignPointer(file, slotPosition[statusTable[10]] + 2561);
    file[0] = context[0]; // SysCall
    file[1] = context[1]; // SpecReg
    file[2] = context[2]; // PC
    file[3] = context[3]; // SP
    file[4] = context[4]; // Global Pointer
    file[5] = context[5]; // Frame Pointer
    file[6] = context[6]; // Second Register
    file[7] = context[7]; // Temporary Register
    file[8] = context[8]; // Acumulator
    file[9] = context[9]; // Heap Array Register
    saveStack();
}

void loadStack(void)
{
    int remainingItems;
    int stack[0];

    remainingItems = 8192 - context[3];
    assignPointer(stack, context[3]);
    assignPointer(file, file_stackOrigin() + slotPosition[nextProgram]);

    while (remainingItems > 0)
    {
        stack[remainingItems] = file[remainingItems];
        remainingItems = remainingItems - 1;
    }
}

void continueExecution(void)
{
    int slot;
    slot = slotPosition[nextProgram];
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
        // BIOS
        firstRun();
        return;
    }
    if (systemCall == 2)
    {
        // End of Program
        kill(statusTable[10]);
        return;
    }
    if (systemCall == 1)
    {
        // IO Request
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
    assignPointer(slotPosition, 9740);
    assignPointer(context, 6135);
    nextProgram = null;

    dispatchSystemCalls(context[0]);
    if (nextProgram == null)
        takeUserAction();

    output(3248488448 + nextProgram); // CIAO + Process
    return 0;
}
