int registers;
int null;

// void printRegisters(void)
// {
//     output(readFromMemory(6135));
//     output(readFromMemory(6136));
//     output(readFromMemory(6137));
//     output(readFromMemory(6138));
//     output(readFromMemory(6139));
//     output(readFromMemory(6140));
//     output(readFromMemory(6141));
//     output(readFromMemory(6142));
// }

// void printStack(void)
// {
//     int sp;

//     sp = readFromMemory(6137);
//     while (sp < 8192)
//     {
//         output(sp);
//         output(readFromMemory(sp));
//         sp = sp + 1;
//     }
// }

void saveStack(void)
{
    int fileIndex;
    int stackIndex;
    int sp;
    int item;

    fileIndex = 19859;
    stackIndex = 8191;
    sp = readFromMemory(6137);

    while (sp < (stackIndex + 1))
    {
        item = readFromMemory(stackIndex);
        writeIntoMemory(fileIndex, item);
        stackIndex = stackIndex - 1;
        fileIndex = fileIndex - 1;
    }
}

void loadStack(void)
{
    int fileIndex;
    int stackIndex;
    int sp;
    int item;

    fileIndex = 19859;
    stackIndex = 8191;
    sp = readFromMemory(6137);

    while (sp < (stackIndex + 1))
    {
        item = readFromMemory(fileIndex);
        writeIntoMemory(stackIndex, item);
        stackIndex = stackIndex - 1;
        fileIndex = fileIndex - 1;
    }
}

void insertProgramIntoMemory(void)
{
    int instructionCount;
    int copied;
    int fullWords;
    int slotStart;
    int data;

    slotStart = 18444;
    instructionCount = readFromMemory(slotStart);
    slotStart = slotStart + 1; // where program start
    copied = 0;
    fullWords = 0;
    while (copied < instructionCount)
    {
        data = readFromMemory(slotStart + fullWords);
        writeIntoMemory(copied, extractFirstHW(data));
        writeIntoMemory(copied + 1, extractSecondHW(data));
        fullWords = fullWords + 1;
        copied = copied + 2;
    }
}

void continueProcess(void)
{
    int stackpointer;
    int stackIndex;
    stackpointer = readFromMemory(19873);

    insertProgramIntoMemory();
    // Save registers
    writeIntoMemory(registers + 8, readFromMemory(19868)); // Acumulator
    writeIntoMemory(registers + 7, readFromMemory(19869)); // Temporary Register
    writeIntoMemory(registers + 6, readFromMemory(19870)); // Frame Pointer
    writeIntoMemory(registers + 5, readFromMemory(19871)); // Global Pointer
    writeIntoMemory(registers + 4, readFromMemory(19872)); // Return Address
    writeIntoMemory(registers + 3, stackpointer);          // SP
    writeIntoMemory(registers + 2, readFromMemory(19874)); // PC
    writeIntoMemory(registers + 1, readFromMemory(19875)); // SpecReg

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
    int userInput;
    int menu;
    menu = 0;
    while (menu == menu)
    {
        if (menu == 0)
        {
            output(49374);
            userInput = input();
            if (userInput != 0)
            {
                output(789996);
                runNewProcess();
                return;
            }
        }
        if (menu == 1)
        {
            output(51966);
            userInput = input();
            if (userInput != 0)
            {
                output(831468);
                continueProcess();
                return;
            }
        }

        menu = menu + 1;
        if (menu > 1)
            menu = 0;
    }
}

int ioFlow(void)
{
    writeIntoMemory(registers + 2, readFromMemory(registers + 2) + 1); // PC++ to avoid loop
    return 0;
}

void saveState(void)
{
    int codeSize;
    int stackpointer;
    int savedStackItemAddr;
    stackpointer = readFromMemory(registers + 3);
    codeSize = readFromMemory(18444);
    codeSize = (codeSize + 1) / 2;

    if (stackpointer < 6776 + codeSize)
        return;
    // printRegisters();
    // Save Registers
    writeIntoMemory(19868, readFromMemory(registers + 8)); // Acumulator
    writeIntoMemory(19869, readFromMemory(registers + 7)); // Temporary Register
    writeIntoMemory(19870, readFromMemory(registers + 6)); // Frame Pointer
    writeIntoMemory(19871, readFromMemory(registers + 5)); // Global Pointer
    writeIntoMemory(19872, readFromMemory(registers + 4)); // Return Address
    writeIntoMemory(19873, stackpointer);                  // SP
    writeIntoMemory(19874, readFromMemory(registers + 2)); // PC
    writeIntoMemory(19875, readFromMemory(registers + 1)); // SpecReg

    // printStack();
    // // Save Stack
    // savedStackItemAddr = 18445 + codeSize;
    // while (stackpointer < 8191)
    // {
    //     writeIntoMemory(savedStackItemAddr, readFromMemory(stackpointer));
    //     stackpointer = stackpointer + 1;
    //     savedStackItemAddr = savedStackItemAddr + 1;
    // }
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
