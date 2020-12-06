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
