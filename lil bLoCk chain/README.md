# Simple Blockchain Implementation in C

This project implements a basic blockchain data structure in C. The blockchain manages a series of blocks, where each block contains an index, timestamp, data, hash, and a reference to the previous block's hash.

## Files

- **blockchain.c**: Contains the implementation of the blockchain data structure and related functions.
- **README.md**: This file, providing an overview of the project.

## Compilation

To compile the program, ensure you have GCC (GNU Compiler Collection) installed on your system.

### Compilation Command

```bash
gcc -o blockchain blockchain.c
```

## Usage
1. Run the Program:
    - After compiling, execute the program by running:

```bash
./blockchain
```

2. Functionality:
    - Initialization: The blockchain initializes with a genesis block.
    - Adding Blocks: Blocks are added sequentially with calculated hashes.
    - Printing: The program prints the blockchain to the console,  displaying each block's details.