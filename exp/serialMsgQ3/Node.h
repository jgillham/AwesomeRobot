#ifndef NODE_CLASS_INCLUDED
#define NODE_CLASS_INCLUDED

template< class T >
class Node {
  private:
    typedef Node< T > Node_T;

  public:
    Node_T* next;
    T data;
    Node( T data ): data( data ) {
    }
};

#endif // NODE_CLASS_INCLUDED

