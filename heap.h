#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>



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
  Heap(int m=2, PComparator c = PComparator()) : m_(m), c_ (c), vec_() {}

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap() {}

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

private:
  /// Add whatever helper functions and data members you need below
  int m_;
  PComparator c_;
  std::vector<T> vec_;


};

// Add implementation of member functions here

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const { 
  return size() == 0;
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const {
  return vec_.size();
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
    throw(std::out_of_range("Out of bounds."));

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return vec_.front();


}

// Parent = (idx - 1) / m
// Left Child = m*idx + 1
// Right Child = m*(idx + 1)

// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Can't pop if empty");
  }
  std::swap(vec_.front(), vec_.back());
  vec_.pop_back();

  //Trickle down
  size_t currIdx = 0; //Parent index
  size_t lIdx = m_*currIdx + 1; //Left index
  size_t rIdx = m_*(currIdx + 1); //Right index

  while(lIdx < size()){ // While there are still children
    size_t numChildren = size() > rIdx ? m_ : m_ - 1 - (rIdx - size());
    size_t tIdx = lIdx + 1; // Temporary Index to iterate, skip first because we look at it outside while
    size_t maxIdx = lIdx;
    T maxPriorityVal = vec_[maxIdx];
     
    //Find child with highest priority
    while(--numChildren > 0){// Pre dec/inc Because we have the first one already
      if(c_(vec_[tIdx], maxPriorityVal)){
        maxPriorityVal = vec_[tIdx];
        maxIdx = tIdx++;
      }
    }
    T& currItem = vec_[currIdx];
    if(c_(maxPriorityVal, currItem)){ //If the child has a higher priority than current, swap
      std::swap(vec_[maxIdx], currItem);
      //Change 
      currIdx = maxIdx;
      lIdx = m_*currIdx + 1;
      rIdx = m_*(currIdx + 1);
    }
    else
      break; //We are at the right spot

  }

}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item) {
   vec_.push_back(item);

   //Trickle up
   size_t currIdx = size() - 1;
   while(currIdx != 0){ //Go until we are the root
    T& currItem = vec_[currIdx];
    T& parent = vec_[(currIdx - 1) / m_];
    if(c_(currItem, parent)){
      std::swap(currItem, parent);
      currIdx = (currIdx - 1) / m_;
    } else
        break; //Unless our parent is better than us
   }
}


#endif

