# GOS
GOS is an Operating System written in C- made to operate ARMAria

## Menu Options

Message | Meaning
--- | ---
C0DE | Start or Resume process
FACA | Kill process
CAFE | List running processes
CADEAD0 | List blocked processes

### Menu Messages

Message | Meaning
--- | ---
CODEC | Confirmed C0DE
FACAC | Confirmed Kill request
CAFEC | Confirmed running process list
CADEADOC | Coonfirmed blocked process list

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
E010* | IO request was refused

## Debug Messages*

Message | Meaning
------- | ------------
E5EC + number | Execute program (number)
FACA + number | Killing process (number)
CESEC + number | Resume process (number)
SS + number | Save State of process (number)


> \* : Temporary Messages