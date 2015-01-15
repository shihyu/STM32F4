#ifndef MYDEQUE_H
#define MYDEQUE_H

const int DEQUE_LEN = 128;

class MyDeque
{
  public:
    //explicit MyDeque();
    bool init();
    bool push_back(int ch);
    bool pop_front(int &ch);
    bool push_front(int ch);
    bool pop_back(int &ch);

    int len() const {return len_;}
    int begin() const {return begin_;}
    int end() const {return end_;}
    bool print()
    {
    #if 0
      cout << "begin: " << begin_ << endl;
      cout << "end: " << end_ << endl;
      if (ready() == false) return false;
      cout << "-- ";
      int e = end();
      for (int i=e ; i != begin() ; )
      {
        cout << *(q_ + i) << " ";
        i = (i + 1) % len_;
      }
      cout << " --" << endl;
      return true;
#endif
    }
    bool ready() const
    {
      //cout << "len_:" << len_ << endl;
      if (len_ > 1)
        return true;
      else
        return false;
    }
    bool full()
    {
      return (!can_push());
    }
    bool empty()
    {
      return (!can_pop());
    }
    bool can_push()
    {
      int next_begin = ((begin() + 1) % len_);
      if (next_begin == end())
        return false;
      else
        return true;
    }
    bool can_pop()
    {
      if (begin() == end())
        return false;
      else
        return true;
    }
  private:
    int q_[DEQUE_LEN];
    int len_;
    int begin_, end_;
    int begin_front_, end_front_;
};

#endif
