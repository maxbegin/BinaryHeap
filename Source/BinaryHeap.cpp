// BinaryHeap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream> 
#include<climits> 
#include <assert.h> 
using namespace std;


class BinaryHeap
{
public:
    BinaryHeap(int size)
        : m_Capactity(size)
        , m_Count(0)
    {
        m_Data = new int[size];
    }

    int GetParent(int i) { return (i - 1) / 2; }
    int GetLeft(int i) { return (2 * i + 1); }
    int GetRight(int i) { return (2 * i + 2); }

    int ExtactMin();
    int GetMin() { return m_Data[0]; }
    void DeleteAtIndex(int i);
    void InsertValue(int value);

private:
    
    void Heapify(int);

    void swap(int *x, int *y)
    {
        int temp = *x;
        *x = *y;
        *y = temp;
    }

    BinaryHeap() = delete;

    int m_Capactity = 0;
    int m_Count = 0;
    int* m_Data;
};

void BinaryHeap::InsertValue(int value)
{
    if (m_Capactity == m_Count)
    {
        // heap full
        return;
    }

    // Add Value at end
    int index = m_Count;
    m_Count++;
    m_Data[index] = value;

    // swap with parent until current value no longer bigger than parent or we reach the root
    int parentIndex = GetParent(index);
    while (index != 0 && m_Data[parentIndex] > m_Data[index])
    {
        swap(&m_Data[index], &m_Data[parentIndex]);

        index = parentIndex;
        parentIndex = GetParent(index);
    }
}

int BinaryHeap::ExtactMin()
{
    if (m_Count == 0)
    {
        return INT_MAX;
    }

    if (m_Count == 1)
    {
        m_Count = 0;
        return m_Data[0];
    }

    int root = m_Data[0];
    m_Data[0] = m_Data[m_Count - 1];
    m_Count--;
    Heapify(0);

    return root;
}

void BinaryHeap::Heapify(int index)
{
    int leftIndex = GetLeft(index);
    int rightIndex = GetRight(index);

    int smallestIndex = index;
    if (leftIndex < m_Count && m_Data[leftIndex] < m_Data[smallestIndex])
        smallestIndex = leftIndex;

    if (rightIndex < m_Count && m_Data[rightIndex] < m_Data[smallestIndex])
        smallestIndex = rightIndex;

    if (smallestIndex != index)
    {
        swap(&m_Data[index], &m_Data[smallestIndex]);
        Heapify(smallestIndex);
    }
}

int main()
{
    BinaryHeap heap(10);
    heap.InsertValue(40);
    heap.InsertValue(5);
    heap.InsertValue(0);
    heap.InsertValue(20);
    heap.InsertValue(25);
    heap.InsertValue(15);
    heap.InsertValue(10);

    bool isMinValid = heap.GetMin() == 0;
    assert(heap.ExtactMin() == 0);
    assert(heap.ExtactMin() == 5);
    assert(heap.ExtactMin() == 10);
    assert(heap.ExtactMin() == 15);
    assert(heap.ExtactMin() == 20);
    assert(heap.ExtactMin() == 25);
    assert(heap.ExtactMin() == 40);

    return 0;
}

