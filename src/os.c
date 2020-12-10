int null;
int nextProgram;

int context[0];
int statusTable[0];
int nameTable[0];
int slotPosition[0];
int file[0];
int stack[0];

void copyFromFileToStack(int numberOfItems)
{
    while (numberOfItems >= 0)
    {
        stack[numberOfItems] = file[numberOfItems];
        numberOfItems = numberOfItems - 1;
    }
}

void recoverState(void)
{
    int i;
    int slot;

    slot = slotPosition[nextProgram];
    assignPointer(file, slot + 2561);

    // Load Context
    i = 0;
    while (i < 10)
    {
        context[i] = file[i];
        i = i + 1;
    }

    // Load Stack
    assignPointer(file, slot + 1537);
    assignPointer(stack, context[3]);
    copyFromFileToStack(8191 - context[3]);

    // Load heap
    assignPointer(stack, 7168);
    i = context[9] - 7168;
    assignPointer(file, slot + 2560 - i);
    copyFromFileToStack(i);
}

void copyFromStackToFile(int numberOfItems)
{
    while (numberOfItems >= 0)
    {
        file[numberOfItems] = stack[numberOfItems];
        numberOfItems = numberOfItems - 1;
    }
}

void saveState(void)
{
    int i;
    int slot;

    slot = slotPosition[statusTable[10]];
    assignPointer(file, slot + 2561);

    // Save Context
    i = 0;
    while (i < 10)
    {
        file[i] = context[i];
        i = i + 1;
    }

    // Save Stack
    assignPointer(file, slot + 1537);
    assignPointer(stack, context[3]);
    copyFromStackToFile(8191 - context[3]);

    // Save heap
    assignPointer(stack, 7168);
    i = context[9] - 7168;
    assignPointer(file, slot + 2560 - i);
    copyFromStackToFile(i);
}

void insertProgramIntoMemory(void)
{
    int remainingInstructions;
    int slotStart;
    int program[0];

    slotStart = slotPosition[nextProgram];
    assignPointer(program, 0);
    assignPointer(file, slotStart + 1);
    remainingInstructions = readFromMemory(slotStart);
    while (remainingInstructions > 0)
    {
        program[0] = extractFirstHW(file[0]);
        program[1] = extractSecondHW(file[0]);
        assignPointer(program, readPointer(program) + 2);
        assignPointer(file, readPointer(file) + 1);
        remainingInstructions = remainingInstructions - 2;
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
    context[9] = 7168; // Heap

    statusTable[11] = nextProgram; // Leading process
    statusTable[nextProgram] = 2;  // Running
    statusTable[12] = statusTable[12] + 1;
}

void validateNextProgram(int candidate)
{
    if (candidate >= 0)
        if (statusTable[candidate] > 0)
            nextProgram = candidate;
}

void fastKill(int process)
{
    if (statusTable[process] > 1)
    {
        statusTable[12] = statusTable[12] - 1;
        statusTable[process] = 1;
    }
}

void kill(int process)
{
    if (process >= 0)
    {
        output(4207542272 + nameTable[process]); // Faca
        fastKill(process);
    }
}

int findProgramByName(int name)
{
    int index;
    index = 0;
    while (index < 10)
    {
        if (nameTable[index] == name)
            return index;
        index = index + 1;
    }
    return null;
}

void selectProgram(int name)
{
    while (nextProgram < 0)
    {
        output(name);
        validateNextProgram(findProgramByName(input()));
    }
}

void codeExecution(void)
{
    selectProgram(49374); // C0DE
    if (statusTable[nextProgram] < 2)
    {
        execute();
        return;
    }

    // continue execution
    if (statusTable[nextProgram] == 3) // IO Unlock
        statusTable[12] = statusTable + 1;

    statusTable[11] = nextProgram;
    if (statusTable[10] != nextProgram)
        insertProgramIntoMemory();
    recoverState();
}

void listProcessByCondition(int initial, int end, int condition)
{
    int result;
    int count;

    result = 0;
    count = 0;
    while (initial < end)
    {
        if (statusTable[initial] == condition)
        {
            count = count + 1;
            result = (result << 4) + initial;
        }
        initial = initial + 1;
    }

    output((count << 24) + result);
}

void takeUserAction(void)
{
    int option;
    while (nextProgram < 0)
    {
        output(1541);
        option = input();
        if (option == 0)
            codeExecution(); // C0DE
        if (option == 1)
        {
            selectProgram(64202); // FACA
            kill(nextProgram);
            nextProgram = null;
        }
        if (option == 2) // rename
        {
            selectProgram(3269); // CC5 or Change Call Sign
            option = nameTable[nextProgram] << 16;
            output(option);
            nameTable[nextProgram] = input();
            output(option + nameTable[nextProgram]);
            option = 2;
            nextProgram = null;
        }

        if (option == 3) // List Active
        {
            output(90); // 5A Show Active
            listProcessByCondition(0, 5, 2);
            listProcessByCondition(5, 10, 2);
        }

        if (option == 4) // List Blocked
        {
            output(91); // 5B Show Blocked
            listProcessByCondition(0, 5, 3);
            listProcessByCondition(5, 10, 4);
        }

        if (option == 5)
        {
            output(1477); // 5C5 Show Call Sign
            output(nameTable[input() % 10]);
        }
    }
}

void firstRun(void)
{
    int program;
    program = 0;
    while (program < 10)
    {
        fastKill(program);
        program = program + 1;
    }

    statusTable[10] = null;
    statusTable[11] = null;
    statusTable[12] = 0;
}

void findNextProcess(void)
{
    int nextCandidate;
    int i;
    i = 0;
    nextCandidate = (statusTable[10] + 1) % 10;
    while (statusTable[nextCandidate] != 2)
    {
        if (i == 10)
            return;
        nextCandidate = (nextCandidate + 1) % 10;
        i = i + 1;
    }
    nextProgram = nextCandidate;
}

void schedule(void)
{

    if (statusTable[12] == 1)
    {
        nextProgram = statusTable[10];
        return;
    }

    findNextProcess();
    saveState();
    insertProgramIntoMemory();
    recoverState();
}

void processIO(void)
{
    context[2] = context[2] + 1;
    if (statusTable[10] == statusTable[11])
    {
        nextProgram = statusTable[10]; // Continue execution
        return;
    }
    saveState();
    statusTable[statusTable[10]] = 3; // Block
    if (statusTable[12] > 1)
        schedule();
    statusTable[12] = statusTable[12] - 1; // Inactive process
}

void dispatchSystemCall(void)
{
    output(6029312 + context[0]); // SC + no of file

    if (context[0] == 4) // BIOS
    {
        firstRun();
        return;
    }

    if (context[0] == 2) // End Of Program
    {
        output(3599); // E0F
        kill(statusTable[10]);
        findNextProcess();
        if (nextProgram >= 0)
        {
            insertProgramIntoMemory();
            recoverState();
        }
        return;
    }

    if (context[0] == 1) // IO
    {
        processIO();
        return;
    }

    if (context[0] == 3) // User request
    {
        saveState();
        return;
    }

    if (context[0] == 0) // Scheduler
        schedule();
}

int main(void)
{
    // Set Variables
    null = 0 - 1;
    assignPointer(statusTable, 9729);
    assignPointer(slotPosition, 9742);
    assignPointer(context, 7157);
    assignPointer(nameTable, 9752);
    nextProgram = null;

    dispatchSystemCall();
    if (nextProgram < 0)
        takeUserAction();

    output(3248488448 + nameTable[nextProgram]); // CIAO + Program name
    return 0;
}
