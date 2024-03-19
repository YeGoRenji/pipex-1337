# Pipex Project

This project, named "pipex" is a C program designed to simulate the behavior of the shell command `< file1 cmd1 | cmd2 > file2` using inter-process communication (IPC) mechanisms. It consists of both a mandatory part and a bonus part, providing a comprehensive exploration of IPC concepts and pipe handling in Unix-like systems.

## Inter-Process Communication (IPC)

Inter-process communication (IPC) is a mechanism that allows processes to exchange data and synchronize their actions. In Unix-based systems, IPC is achieved through various methods, including pipes, shared memory, message queues, and sockets. 

- **Pipes:** One of the most common IPC mechanisms in Unix is pipes, which allow one process to send data to another process. Pipes can be unidirectional (one-way) or bidirectional (two-way), enabling efficient communication between processes.

- **Shared Memory:** Shared memory allows multiple processes to access the same region of memory, enabling them to share data directly without the need for copying. This method is efficient for large data transfers but requires synchronization mechanisms to avoid conflicts.

- **Message Queues:** Message queues provide a way for processes to exchange messages asynchronously. Messages are stored in a queue and can be read by the recipient process when ready. Message queues are suitable for communication between unrelated processes.

- **Sockets:** Sockets are used for communication between processes running on different machines or on the same machine. They provide a network interface for IPC, enabling processes to send and receive data over a network.

## Mandatory Part

### Compilation

To compile the mandatory part of the project, use the following command:

```bash
make
```

### Usage

The mandatory part of "pipex" demonstrates IPC using pipes. It takes four arguments:

```bash
./pipex file1 cmd1 cmd2 file2
```

- `file1` is the input file.
- `cmd1` is the first shell command with its parameters.
- `cmd2` is the second shell command with its parameters.
- `file2` is the output file.

### Example

```bash
./pipex infile "ls -l" "wc -l" outfile
```

This command simulates the shell command `< infile ls -l | wc -l > outfile`.

## Bonus Part

### Compilation

To compile the bonus part of the project, which includes additional IPC features, use the following command:

```bash
make bonus
```

### Usage

The bonus part extends the functionality of "pipex" with multiple pipes and the "here_doc" feature. It supports commands like:

```bash
./pipex infile "cat" "grep -v 'pattern'" "sort -r" outfile
```

This command simulates the shell command `cat infile | grep -v 'pattern' | sort -r > outfile`.

For here_doc :
```bash
./pipex here_doc LIMITER cmd cmd1 file
```
This command simulates the shell command `cmd << LIMITER | cmd1 >> file`.
