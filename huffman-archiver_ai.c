#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMUM_TREE_NODES 512
#define MAXIMUM_CODE_LENGTH 256

// Узел дерева Хаффмана
typedef struct HuffmanNode {
    unsigned char character;
    int frequency;
    struct HuffmanNode *left_child;
    struct HuffmanNode *right_child;
} HuffmanNode;

// Очередь с приоритетами (Минимальная куча)
typedef struct {
    int current_size;
    HuffmanNode* nodes_array[MAXIMUM_TREE_NODES];
} MinimumPriorityQueue;

// Создание нового узла дерева
HuffmanNode* create_huffman_node(unsigned char character, int frequency) {
    HuffmanNode* new_node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    new_node->character = character;
    new_node->frequency = frequency;
    new_node->left_child = NULL;
    new_node->right_child = NULL;
    return new_node;
}

// Вспомогательная функция для обмена двух узлов в куче
void swap_huffman_nodes(HuffmanNode** first_node, HuffmanNode** second_node) {
    HuffmanNode* temporary_node = *first_node;
    *first_node = *second_node;
    *second_node = temporary_node;
}

// Восстановление свойств кучи вниз (Heapify)
void restore_minimum_heap_property(MinimumPriorityQueue* queue, int current_index) {
    int smallest_element_index = current_index;
    int left_child_index = 2 * current_index + 1;
    int right_child_index = 2 * current_index + 2;

    if (left_child_index < queue->current_size && 
        queue->nodes_array[left_child_index]->frequency < queue->nodes_array[smallest_element_index]->frequency) {
        smallest_element_index = left_child_index;
    }

    if (right_child_index < queue->current_size && 
        queue->nodes_array[right_child_index]->frequency < queue->nodes_array[smallest_element_index]->frequency) {
        smallest_element_index = right_child_index;
    }

    if (smallest_element_index != current_index) {
        swap_huffman_nodes(&queue->nodes_array[smallest_element_index], &queue->nodes_array[current_index]);
        restore_minimum_heap_property(queue, smallest_element_index);
    }
}

// Извлечение узла с минимальной частотой
HuffmanNode* extract_minimum_node(MinimumPriorityQueue* queue) {
    HuffmanNode* minimum_node = queue->nodes_array[0];
    queue->nodes_array[0] = queue->nodes_array[queue->current_size - 1];
    --queue->current_size;
    restore_minimum_heap_property(queue, 0);
    return minimum_node;
}

// Вставка нового узла в очередь с приоритетами
void insert_into_priority_queue(MinimumPriorityQueue* queue, HuffmanNode* node_to_insert) {
    ++queue->current_size;
    int current_index = queue->current_size - 1;
    
    while (current_index && node_to_insert->frequency < queue->nodes_array[(current_index - 1) / 2]->frequency) {
        queue->nodes_array[current_index] = queue->nodes_array[(current_index - 1) / 2];
        current_index = (current_index - 1) / 2;
    }
    queue->nodes_array[current_index] = node_to_insert;
}

// Проверка: является ли узел листом дерева (символом)
int is_leaf_node(HuffmanNode* node) {
    return !(node->left_child) && !(node->right_child);
}

// Рекурсивный обход дерева для генерации и вывода кодов
void print_huffman_codes(HuffmanNode* root_node, int code_bits_array[], int current_depth) {
    if (root_node->left_child) {
        code_bits_array[current_depth] = 0;
        print_huffman_codes(root_node->left_child, code_bits_array, current_depth + 1);
    }

    if (root_node->right_child) {
        code_bits_array[current_depth] = 1;
        print_huffman_codes(root_node->right_child, code_bits_array, current_depth + 1);
    }

    if (is_leaf_node(root_node)) {
        printf("'%c': ", root_node->character);
        for (int i = 0; i < current_depth; ++i) {
            printf("%d", code_bits_array[i]);
        }
        printf("\n");
    }
}

// Функция построения дерева Хаффмана
HuffmanNode* build_huffman_tree(unsigned char unique_characters[], int frequencies[], int total_elements) {
    MinimumPriorityQueue* queue = (MinimumPriorityQueue*)malloc(sizeof(MinimumPriorityQueue));
    queue->current_size = 0;

    // Шаг 1: Создаем листовые узлы для каждого символа и добавляем в очередь
    for (int i = 0; i < total_elements; ++i) {
        insert_into_priority_queue(queue, create_huffman_node(unique_characters[i], frequencies[i]));
    }

    // Шаг 2: Извлекаем по два узла с наименьшей частотой и объединяем их
    while (queue->current_size != 1) {
        HuffmanNode* left_child = extract_minimum_node(queue);
        HuffmanNode* right_child = extract_minimum_node(queue);

        // Внутренний узел дерева получает технический маркер '\0'
        int combined_frequency = left_child->frequency + right_child->frequency;
        HuffmanNode* parent_node = create_huffman_node('\0', combined_frequency);
        
        parent_node->left_child = left_child;
        parent_node->right_child = right_child;

        insert_into_priority_queue(queue, parent_node);
    }

    HuffmanNode* root_node = extract_minimum_node(queue);
    free(queue);
    return root_node;
}

// Освобождение памяти, выделенной под дерево
void free_huffman_tree(HuffmanNode* root_node) {
    if (!root_node) {
        return;
    }
    free_huffman_tree(root_node->left_child);
    free_huffman_tree(root_node->right_child);
    free(root_node);
}

int main(void) {
    const char* source_text = "beep boop beer!";
    printf("Исходная строка: \"%s\"\n\n", source_text);

    // Подсчет частот символов в тексте
    int character_frequencies_map[256] = {0};
    for (int i = 0; source_text[i] != '\0'; i++) {
        character_frequencies_map[(unsigned char)source_text[i]]++;
    }

    // Собираем массивы только для присутствующих в тексте символов
    unsigned char unique_characters[256];
    int frequencies[256];
    int unique_elements_count = 0;

    for (int i = 0; i < 256; i++) {
        if (character_frequencies_map[i] > 0) {
            unique_characters[unique_elements_count] = (unsigned char)i;
            frequencies[unique_elements_count] = character_frequencies_map[i];
            unique_elements_count++;
        }
    }

    // Построение дерева Хаффмана
    HuffmanNode* root_node = build_huffman_tree(unique_characters, frequencies, unique_elements_count);
    
    // Генерация и вывод префиксных кодов
    int code_bits_array[MAXIMUM_CODE_LENGTH];
    printf("Сгенерированные коды Хаффмана:\n");
    print_huffman_codes(root_node, code_bits_array, 0);

    // Освобождение памяти
    free_huffman_tree(root_node);
    
    return 0;
}
