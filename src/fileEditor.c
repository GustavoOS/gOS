void assignPointer(int a[], int value) {}
int readFroMemory(int address) {}
int extractFirstHW(int data) {}
int extractSecondHW(int data) {}

int file[0];
int statusTable[0];
int slotPosition[0];
int null;

int fileIndex;
int instructionIndex;
int fileSize;

int readInstruction(void)
{
    if ((instructionIndex % 2) == 0)
        return extractFirstHW(file[fileIndex]);

    return extractSecondHW(file[fileIndex]);
}

void editFile(int id)
{
    int option;
    int instr;
    int newInstr;
    instructionIndex = 0;
    fileIndex = 1;
    assignPointer(file, slotPosition[id]);
    option = null;
    while (option != 0)
    {
        instr = readInstruction();
        output((instructionIndex << 16) + instr);
        if (option == 1) // advance
        {
            fileIndex = fileIndex + (instructionIndex % 2);
            if (fileIndex > fileSize)
                fileIndex = fileSize;
            instructionIndex = instructionIndex + 1) % fileSize;
        }
        if (option == 2) // retreat
        {
            //TODO changeinstructionIndex = (instructionIndex - 1) % fileSize;
            //TODO change fileIndex = fileIndex - (instructionIndex % 2);
            if (fileIndex > fileSize)
                fileIndex = fileSize;
        }
        if (option == 3) //change instruction
        {
            newInstr = input();
            instr = file[fileIndex];
            if ((instructionIndex % 2) == 0)
            {
                newInstr = newInstr << 16;
                instr = extractSecondHW(instr);
            }
            else
                instr = instr << 16;
            file[fileIndex] = instr + newInstr;
            if (fileIndex >= file[0])
                file[0] = fileIndex + 1;
        }
    }
}

int main(void)
{

    int option;
    // Set Variables
    null = 0 - 1;
    assignPointer(statusTable, 9729);
    assignPointer(slotPosition, 9742);
    option = null;
    fileSize = 1536;

    while (option != 0)
    {
        output(61726); // F11E
        option = input();

        if (option == 1) // EDIT FILE
        {
            output(237); // ED
            editFile(input());
        }
    }
}
