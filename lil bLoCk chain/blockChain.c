#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_DATA_SIZE 256

// Define a block structure
typedef struct Block {
    uint32_t index;
    uint32_t timestamp;
    uint8_t prev_hash[32];
    uint8_t hash[32];
    char data[BLOCK_DATA_SIZE];
} Block;

// Define the blockchain structure
typedef struct Blockchain {
    Block *chain[100]; // Fixed-size array for simplicity
    int height;
} Blockchain;

// Function to calculate SHA-256 hash (dummy implementation)
void calculate_hash(uint8_t hash[32], const char *data) {
    // This is a dummy implementation, should use a real hashing algorithm
    sprintf((char *)hash, "%s", data);
}

// Function to create a new block
Block *create_block(uint32_t index, const char *data, uint8_t prev_hash[32]) {
    Block *new_block = (Block *)malloc(sizeof(Block));
    if (!new_block) {
        perror("Unable to allocate memory for new block");
        return NULL;
    }

    new_block->index = index;
    new_block->timestamp = (uint32_t)time(NULL);
    memcpy(new_block->prev_hash, prev_hash, 32);
    calculate_hash(new_block->hash, data);
    strncpy(new_block->data, data, BLOCK_DATA_SIZE - 1);
    new_block->data[BLOCK_DATA_SIZE - 1] = '\0'; // Ensure null-terminated

    return new_block;
}

// Function to add a block to the blockchain
void add_block(Blockchain *blockchain, Block *new_block) {
    if (blockchain->height >= 100) {
        fprintf(stderr, "Blockchain height limit reached.\n");
        return;
    }

    blockchain->chain[blockchain->height++] = new_block;
}

// Function to print a block
void print_block(Block *block) {
    printf("Block #%u\n", block->index);
    printf("Timestamp: %u\n", block->timestamp);
    printf("Data: %s\n", block->data);
    printf("Hash: %s\n", block->hash);
    printf("Previous Hash: %s\n", block->prev_hash);
    printf("-----------------------------------\n");
}

// Function to print the entire blockchain
void print_blockchain(Blockchain *blockchain) {
    printf("Printing Blockchain:\n");
    for (int i = 0; i < blockchain->height; i++) {
        print_block(blockchain->chain[i]);
    }
}

int main() {
    Blockchain blockchain;
    blockchain.height = 0;

    // Create genesis block
    uint8_t genesis_prev_hash[32] = {0}; // Initial previous hash for genesis block
    Block *genesis_block = create_block(0, "Genesis Block", genesis_prev_hash);
    if (!genesis_block) {
        fprintf(stderr, "Failed to create genesis block.\n");
        return 1;
    }

    // Add genesis block to the blockchain
    add_block(&blockchain, genesis_block);

    // Create and add more blocks (for example)
    Block *block1 = create_block(1, "This is block 1", genesis_block->hash);
    add_block(&blockchain, block1);

    Block *block2 = create_block(2, "Another block here", block1->hash);
    add_block(&blockchain, block2);

    // Print the blockchain
    print_blockchain(&blockchain);

    // Clean up memory (not essential in this simple example)
    for (int i = 0; i < blockchain.height; i++) {
        free(blockchain.chain[i]);
    }

    return 0;
}
