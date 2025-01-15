# Producer-Consumer Problem
## Overview

The Producer-Consumer Problem demonstrates a synchronization mechanism where multiple producer and consumer threads access a shared bounded buffer. The producers generate data and place it into the buffer, while the consumers remove and process the data. Proper synchronization ensures that the buffer does not overflow or underflow.

## Key Features

1. **Shared Circular Buffer**:

   - Fixed size (5 items).
   - Managed as a circular queue to efficiently handle item placement and retrieval.

2. **Synchronization Mechanisms**:

   - Semaphores to track empty and full buffer slots.
   - Mutex to ensure mutual exclusion during buffer operations.

3. **Thread Management**:

   - Multiple producer and consumer threads.
   - Threads alternate between producing/consuming items and sleeping for random durations.

## System Requirements

- **Operating System**: Windows (required for Windows threading API).
- **Compiler**: Any C compiler supporting Windows threads, such as MinGW or Visual Studio.

## Usage

### Compilation

Compile the program using a Windows-compatible C compiler. For example, with MinGW:

```sh
gcc producer_consumer.c -o producer_consumer -lwinpthread
```

### Execution

Run the executable with the following arguments:

```sh
producer_consumer <sleep time> <number of producers> <number of consumers>
```

- `<sleep time>`: Total duration (in seconds) before the program terminates.
- `<number of producers>`: Number of producer threads to create.
- `<number of consumers>`: Number of consumer threads to create.

### Example

```sh
producer_consumer 10 2 3
```

This runs the program for 10 seconds with 2 producer threads and 3 consumer threads.

## Code Structure

### `main()`

- Initializes the buffer and synchronization primitives.
- Creates the specified number of producer and consumer threads.
- Sleeps for the given duration and terminates the application.

### Buffer Functions

- `initialize_buffer()`: Initializes semaphores and mutex.
- `insert_item(buffer_item item)`: Inserts an item into the buffer.
- `remove_item(buffer_item *item)`: Removes an item from the buffer.

### Producer and Consumer Threads

- **Producer**: Generates random numbers and inserts them into the buffer.
- **Consumer**: Retrieves items from the buffer and "consumes" them.

## Output

The program outputs messages indicating actions taken by the producers and consumers:

- `Producer produced <item>`: A producer thread has added an item to the buffer.
- `Consumer consumed <item>`: A consumer thread has removed an item from the buffer.
- Error messages (if any synchronization or buffer operation fails).

## Notes

- The program uses Windows-specific APIs (e.g., `CreateSemaphore`, `CreateThread`, `WaitForSingleObject`), and hence is not portable to other operating systems without modification.
- Synchronization ensures thread-safe access to the shared buffer.

## License

This project is for educational purposes only and may not be redistributed without proper attribution.

---

Developed as part of the **Operating Systems course** at IUST, Winter 2024 by Dr. Mahmoud Shirazi.

