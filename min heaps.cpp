#include <iostream>
#include <vector>
#include <algorithm> // For std::swap

using namespace std;

// Structure to represent a sword
struct Sword {
    int attackPower;  // Sword's attack power
    int weight;       // Sword's weight

    // Constructor to initialize sword
    Sword(int attackPower, int weight) : attackPower(attackPower), weight(weight) {}
};

// MinHeap class to manage heap operations for swords
class MinHeap {
private:
    vector<Sword> heap; // Vector to store sword objects

    // Helper function to get the index of the parent node
    int parent(int i) {
        return (i - 1) / 2;
    }

    // Helper function to get the index of the left child
    int left(int i) {
        return 2 * i + 1;
    }

    // Helper function to get the index of the right child
    int right(int i) {
        return 2 * i + 2;
    }

    // Helper function to restore the heap property after insertion
    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)].attackPower > heap[i].attackPower) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    // Helper function to restore the heap property after deletion
    void heapifyDown(int i) {
        int smallest = i;
        int leftChild = left(i);
        int rightChild = right(i);

        // Check if left child exists and has smaller attack power
        if (leftChild < heap.size() && heap[leftChild].attackPower < heap[smallest].attackPower) {
            smallest = leftChild;
        }

        // Check if right child exists and has smaller attack power
        if (rightChild < heap.size() && heap[rightChild].attackPower < heap[smallest].attackPower) {
            smallest = rightChild;
        }

        // If the smallest is not the current node, swap and continue heapifying down
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    // Insert a new sword into the heap
    void insert(Sword sword) {
        heap.push_back(sword);  // Add the sword at the end
        heapifyUp(heap.size() - 1);  // Restore heap property
        cout << "Inserted sword with attack power " << sword.attackPower << " and weight " << sword.weight << "." << endl;
        displayHeap();
    }

    // Delete the root sword (the sword with the smallest attack power)
    void deleteRoot() {
        if (heap.size() == 0) {
            cout << "Heap is empty. Nothing to delete!" << endl;
            return;
        }

        cout << "Deleting root sword with attack power " << heap[0].attackPower << "..." << endl;
        heap[0] = heap[heap.size() - 1];  // Move the last sword to the root
        heap.pop_back();  // Remove the last sword
        heapifyDown(0);  // Restore heap property
        displayHeap();
    }

    // Convert an unsorted array of swords into a Min-Heap
    void heapifyArray(vector<Sword>& arr) {
        heap = arr;  // Copy the array into the heap
        for (int i = parent(heap.size() - 1); i >= 0; --i) {
            heapifyDown(i);  // Perform heapify down from the last non-leaf node
        }

        cout << "Array of swords heapified based on attack power:" << endl;
        displayHeap();
    }

    // Display the heap
    void displayHeap() {
        cout << "Heap: ";
        for (const auto& sword : heap) {
            cout << "(" << sword.attackPower << ", " << sword.weight << ") ";
        }
        cout << endl;
    }
};

int main() {
    MinHeap swordHeap;

    // Insert swords with attack power and weight
    swordHeap.insert(Sword(100, 10));  // Sword with attack power 100, weight 10
    swordHeap.insert(Sword(80, 8));    // Sword with attack power 80, weight 8
    swordHeap.insert(Sword(150, 15));  // Sword with attack power 150, weight 15
    swordHeap.insert(Sword(120, 12));  // Sword with attack power 120, weight 12
    swordHeap.insert(Sword(90, 9));    // Sword with attack power 90, weight 9

    // Delete the root (the sword with the smallest attack power)
    swordHeap.deleteRoot();

    // Heapify an array of unsorted swords
    vector<Sword> unsortedSwords = {Sword(110, 11), Sword(95, 7), Sword(130, 14), Sword(60, 6)};
    swordHeap.heapifyArray(unsortedSwords);

    return 0;
}
