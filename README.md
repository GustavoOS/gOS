# GOS
GOS is an Operating System written in C- made to operate ARMAria

## System Calls

Value | Meaning
------- | ---------
0 | Watchdog has interrupted execution
1 | Process has requested IO usage
2 | Process has terminated
3 | User wants to submit a command
4 | BIOS has terminated


## File States
State | Meaning
------ | -------
0 | Empty
1 | Exists
2 | Executing
3 | Blocked

## Commands
Number  |  Command  |  Display
--------  |  ------  | -------
0  |  Execute or continue program  | C0DE
1  |  Kill proccess  | FACA
2  |  Change Call Sign (Rename)  | CC5
3  |  Show Active Processes  |  54
4  |  Show Blocked Processes  | 5B
5  |  Show Call Sign of PID  |  5C5
6  |  Create file  | CF
7  |  Delete file  | DE1
