#include "mydeque.h"

#if 0
// begin_ = end_ = 0;
// q leave one empty space when full
MyDeque::MyDeque()
{
  len_ = DEQUE_LEN;
  begin_ = end_ = 0;
}
#endif
bool MyDeque::init()
{
  len_ = DEQUE_LEN;
  begin_ = end_ = 0;
}

bool MyDeque::push_back(int ch)
{
  if (ready() == false) 
    return false;
// copy ch to begin point
// ++begin

  bool ret = true;
  if (can_push())
  {
    *(q_ + begin_) = ch;
    begin_ = ((begin_ + 1) % len_);
  }
  else
    ret = false;
  return ret;
}

bool MyDeque::push_front(int ch)
{
  if (ready() == false) 
    return false;
  bool ret = true;

  // has space to push
  if (can_push())
  {
    end_ = ((end_ + len_ - 1) % len_);
    *(q_ + end_) = ch;
  }
  else
    ret = false;
  return ret;
}

bool MyDeque::pop_front(int &ch)
{
  if (ready() == false) 
    return false;
// return end point value, ++end
  bool ret = true;
  if (can_pop())
  {
    ch = *(q_ + end_);
    end_ = ((end_ + 1) % len_);
  }
  else
  {
    ret = false;
  }
  return ret;
}

bool MyDeque::pop_back(int &ch)
{
  if (ready() == false) 
    return false;

  bool ret = true;
  if (can_pop())
  {
    begin_ = ((begin_ - 1) % len_);
    ch = *(q_ + begin_);
  }
  else
  {
    ret = false;
  }
  return ret;
}
