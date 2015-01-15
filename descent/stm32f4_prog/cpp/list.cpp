// template linked list test in os kernel
#include <cstdio>

using namespace std;

#include "stm32.h"

template <typename type>
class List
{
  public:
    List(type *item)
    {
      set_item(item);
      prev_ = next_ = 0;
    }
    void add_next(List *n)
    {
      next_ = n;
    }
    type *item(){return item_;}
    void set_item(type *item)
    {
      item_ = item;
    }
    List *next(){return next_;}
  private:
    type *item_;
    List *prev_;
    List *next_;
};

struct page 
{
 unsigned int vaddr;
 unsigned int flags;
 int order;
};


void mymain()
{
  page p1, p2;
  List<page> node1(&p1), node2(&p2);
  List<page> *head;

#if 0
  printf("%p\n", &p1);
  printf("%p\n", &p2);
#endif

  //node1.set_item(p1);
  //node2.set_item(p2);

  node1.add_next(&node2);
  head = &node1;
  page *cur_page = 0;
  for (List<page> *cur=head ; cur ; cur=cur->next())
  {
    cur_page =  cur->item();
    //printf("%p\n", cur->item());
  }
  while(1);

#if 0

  p1.list.next = p2.list.prev;
  struct list_head *lh = &amp;p1.list;
  //struct list_head *lh = &amp;p1.list;

  struct page *p3=0;
  ((struct page *)0)-&gt;list ;
  printf("%p\n", &amp;((struct page *)0)-&gt;list);
  printf("%p\n", (char *)lh);
  printf("%p\n", ( (char *)lh - ((unsigned int) &amp;((struct page *)0)-&gt;list) ) );
  printf("%p\n", &amp;p1);
        
  //list_entry(lh,struct page,list);
  return 0;
#endif
}

#if 0
  ({ const typeof( ((struct page *)0)-&gt;list ) *__mptr = (lh); 
  (struct page *)( (char *)__mptr - ((unsigned int) &amp;((struct page *)0)-&gt;list) );});
  return 0;
#endif
