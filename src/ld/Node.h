#ifndef NODE_CLASS_INCLUDED
#define NODE_CLASS_INCLUDED

template< class T >
class Node {
  private:
    typedef Node< T > Node_T;
    typedef Node_T* Node_T_Pntr;

  public:
    Node_T_Pntr next;
    T data;
    Node( T data ): data( data ) {
    }
};

#endif // NODE_CLASS_INCLUDED
