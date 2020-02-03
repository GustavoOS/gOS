# GOS
GOS is an Operating System written in C- made to operate ARMAria

## Menu Options

Message | Meaning
--- | ---
C0DE | Start or Resume process
FACA | Kill process
CAFE | List running processes
CADEAD0 | List blocked processes

## System Calls

Value | Meaning
------- | ---------
0 | Watchdog has interrupted execution
1 | Process has requested IO usage
2 | Process has terminated
3 | User wants to submit a command
4 | BIOS has terminated

## Error Codes

Message | Meaning
------- | ------------
E000 | Stack Overflow