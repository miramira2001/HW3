#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int l=2, PComparator c = PComparator());
  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap() = default;

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

  void print();
private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> info;
  int v;
  PComparator comp;
  void sortAscending(int);
  void sortDescending(int);
};

// Add implementation of member functions here

template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int l, PComparator c){
  v = l;
  comp = c;
}

// vector cout 
template <typename T, typename PComparator>
void Heap<T,PComparator>::print() {
    int step = 0;
    int largestN = pow(v, step);

    while (step < largestN) {
        for (int i = 0; i < (int)size(); i++) {
            std::cout << info[i] << " ";
        }
        std::cout << "Done \n";
        step++;
        largestN = pow(v, step);
    }
}

//pop 
template <typename T, typename PComparator>
void Heap<T,PComparator>::sortAscending(int yes) {
    int num = yes;
    int i = 1;
    while (i <= v) {
        int kid = yes*v + i;
        if (kid < (int)size() && comp(info[kid], info[num])) {
            num = kid;
        }
        i++;
    }
  
  if(num != yes){
    std::swap(info[yes], info[num]);
    sortAscending(num);
  }

}

//push 
template <typename T, typename PComparator>
void Heap<T, PComparator>::sortDescending(int yes) {
    int kid = yes;
    int adult = (kid - 1) / v;
    while (adult >= 0 && comp(info[kid], info[adult])) {
        std::swap(info[kid], info[adult]);
        kid = adult;
        adult = (kid - 1) / v;
    }
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Empty heap"); 
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return info[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Empty heap");

  }
  std::swap(info[0], info[size()-1]);
  info.pop_back();
  sortAscending(0);

}

//Adds a new element to the heap by putting the element in the last spot of the heap and then sorting down
template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& element){
  info.push_back(element);
  sortDescending((int)size()-1);

}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const{
	return info.size();
}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const {
    return size() == 0;
}


#endif
