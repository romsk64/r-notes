// Huffman Archiver on C99.

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_TREE_NODES_COUNT 512
#define MAX_CODE_LENGTH 256


// node structure
struct HARCH_NODE {
    uint8_t m_char;
    int m_frequence;
    struct HARCH_NODE *m_leftChild;
    struct HARCH_NODE *m_rightChild;
};

struct HARCH_MINIMUM_PRIORITY_QUEUE {
    int m_currentSize;
    struct HARCH_NODE *m_nodesArray[MAX_TREE_NODES_COUNT];
};


// functions for working with node
struct HARCH_NODE *createNode(
    uint8_t character,
    int frequence
) {
    struct HARCH_NODE *newNode = (struct HARCH_NODE *)malloc(sizeof(struct HARCH_NODE));
    if (!newNode) return NULL;

    newNode->m_char = character;
    newNode->m_frequence = frequence;
    newNode->m_leftChild = NULL;
    newNode->m_rightChild = NULL;

    return newNode;
}

void swapNode(
    struct HARCH_NODE **firstNode,
    struct HARCH_NODE **secondNode
) {
    struct HARCH_NODE *tempNode = *firstNode;
    *firstNode = *secondNode;
    *secondNode = tempNode;
}

void restoreMinimumHeapProperty(
    struct HARCH_MINIMUM_PRIORITY_QUEUE *queue,
    int currentIndex
) {
    int smallestElementIndex = currentIndex;
    int leftChildIndex = (currentIndex * 2) + 1;
    int rightChildIndex = (currentIndex * 2) + 2;

    if (
        leftChildIndex < queue->m_currentSize &&
        queue->m_nodesArray[leftChildIndex]->m_frequence < queue->m_nodesArray[smallestElementIndex]->m_frequence
    ) {
        smallestElementIndex = leftChildIndex;
    }

    if (
        rightChildIndex < queue->m_currentSize &&
        queue->m_nodesArray[rightChildIndex]->m_frequence < queue->m_nodesArray[smallestElementIndex]->m_frequence
    ) {
        smallestElementIndex = rightChildIndex;
    }

    if (smallestElementIndex != currentIndex) {
        swapNode(&queue->m_nodesArray[smallestElementIndex], &queue->m_nodesArray[currentIndex]);
        restoreMinimumHeapProperty(queue, smallestElementIndex);
    }
}

struct HARCH_NODE *extractMinimumNode(
    struct HARCH_MINIMUM_PRIORITY_QUEUE *queue
) {
    struct HARCH_NODE *minimumNode = queue->m_nodesArray[0];
    queue->m_nodesArray[0] = queue->m_nodesArray[queue->m_currentSize - 1];
    (queue->m_currentSize)--;

    restoreMinimumHeapProperty(queue, 0);
    return minimumNode;
}

void insertIntoPropertyQueue(
    struct HARCH_MINIMUM_PRIORITY_QUEUE *queue,
    struct HARCH_NODE *nodeToInsert
) {
    (queue->m_currentSize)++;
    int currentIndex = queue->m_currentSize;

    while (
        currentIndex &&
        nodeToInsert->m_frequence < queue->m_nodesArray[(currentIndex - 1) / 2]->frequence
    ) {
        queue->m_nodesArray[currentIndex] = queue->m_nodesArray[(currentIndex - 1) / 2];
        currentIndex = (currentIndex - 1) / 2;
    }

    queue->m_nodesArray[currentIndex] = nodeToInsert;
}

bool isLeafNode(
    struct HARCH_NODE *node
) {
    return !(node->m_leftChild) && !(node->m_rightChild);
}

void


int main(int argc, char *argv[]) {
    return 0;
}
