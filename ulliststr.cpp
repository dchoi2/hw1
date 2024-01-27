#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE
void ULListStr::push_back(const std::string& val)
{
  // if there are no objects in the unrolled LL, create a new object and set the value
  if(empty())
  {
    Item* newItem = new Item();
    head_ = tail_ = newItem;

    newItem->last++;
    newItem->val[newItem->first] = val;
  }
  else
  {
    // if the last array is full, the last index is ARRSIZE
    if(tail_->last == ARRSIZE)
    {
      Item* newItem = new Item();
      tail_->next = newItem;

      newItem->prev = tail_;
      newItem->next = NULL;
      tail_ = newItem;

      tail_->last++;
      tail_->val[tail_->first] = val;
    }
    // else, the last array is not full, and have to add to the last index
    else
    {
      tail_->val[tail_->last] = val;
      tail_->last++;
    }
  }
  size_++;
}
  /**
   * Removes a value from the back of the list
   *   - MUST RUN in O(1)
   */
void ULListStr::pop_back()
{
  // if there are no elements in the ULL, do nothing
  if(empty())
  {
    return;
  }
  // if only one item in the tail val array
  tail_->last--;
  size_--;

  if(tail_->last == tail_->first)
  {
    
    if(tail_->prev == NULL)
    {
      delete tail_;
      head_ = tail_ = NULL;
    }
    // if there is an item before the new tail_, set tail_ next item to NULL 
    else
    {
      Item* temp = tail_;
      tail_ = tail_->prev;
      tail_->next = NULL;
      delete temp;
    }
  }
}

/**
  * Adds a new value to the front of the list.
  * If there is room before the 'first' value in
  * the head node add it there, otherwise, 
  * allocate a new head node.
  *   - MUST RUN in O(1)
  */
void ULListStr::push_front(const std::string& val)
{
  if(empty())
  {
    Item* newItem = new Item();
    head_ = tail_ = newItem;

    newItem->val[newItem->first] = val;
    newItem->last++;
  }

  else
  {
    // if the head_ array is full (index 0 is filled), the allocate new node
    if(head_->first == 0)
    {
      Item* newItem = new Item();
      head_->prev = newItem;
      newItem->next = head_;
      head_ = newItem;

      newItem->last = ARRSIZE;
      newItem->first = ARRSIZE - 1;
      newItem->val[newItem->first] = val;
    }
    // else, the head array is not full at the front, and have to add before
    else
    {
      head_->first--;
      head_->val[head_->first] = val;
    }
  }
  size_++;
}
/**
  * Removes a value from the front of the list
  *   - MUST RUN in O(1)
  */


void ULListStr::pop_front()
{
   // if there are no elements in the ULL, do nothing
  if(size_ == 0)
  {
    return;
  }
  // if there is only one value in the val array
  else if(head_->first == (head_->last - 1))
  {
    head_->first++;

    Item* temp = head_;
    head_ = head_->next;
    delete temp;
    // if only one item and now head_ points at NULL, tail_ must be set NULL
    if(head_ == NULL)
    {
      tail_ = NULL;
    }
    // else, there exists more than one item (now head_ points to the second item), set prev to NULL
    else
    {
      head_->prev = NULL;
    }
  }
  // in any other case, increment first
  else
  {
    head_->first++;
  }
  size_--;
}

  /** 
   * Returns a pointer to the item at index, loc,
   *  if loc is valid and NULL otherwise
   *   - MUST RUN in O(n) 
   */
std::string* ULListStr::getValAtLoc(size_t loc) const {
  // if the location is out of bounds, then return NULL
  if (loc >= size_) {
    return NULL;
  }

  Item* temp = head_;
  size_t count = loc; 

  // go through each Item, and count the amount of values within
  // once the location falls within the current Item, then find the index and return
  while(temp != NULL) {
    // subtracting last from first gives # items in the Item
    if(count < (temp->last - temp->first)) {
      // the searched location is within the current Item
      return &temp->val[temp->first + (count)];
    }
    
    count -= (temp->last - temp->first);
    temp = temp->next;
  }

  return NULL;
}



/**
* Returns a const reference to the back element
*   - MUST RUN in O(1)
*/
std::string const & ULListStr::back() const
{
  if(empty())
  {
    return NULL;
  }
  return tail_->val[tail_->last - 1];
}

/**
  * Returns a const reference to the front element
  *   - MUST RUN in O(1)
  */
std::string const & ULListStr::front() const
{
  if(empty())
  {
    return NULL;
  }
  return head_->val[head_->first];
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
