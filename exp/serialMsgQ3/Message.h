#ifndef MESSAGE_CLASS_INCLUDED
#define MESSAGE_CLASS_INCLUDED

#include "Node.h"

typedef enum  {
  TIME_REQUEST = 't',

} MessageType;
class Interface {
  public:
    virtual bool append( int data ) = 0;
};
#ifndef NDEBUG
#define DEBUG( ARGS... ) ARGS
#else
#define DEBUG( ARGS... )
#endif
class Message: public Interface  {
  private:
    typedef Node< double > dataNode;
  public:
    MessageType type;
    int ID;
    dataNode* head;
    Message( MessageType type, int ID ): type( type ), ID( ID ), head( 0 ) {
    }
    bool append( double data ) {
      dataNode** end = &head;
      while ( *end == 0 ) {
        end = &((*end)->next);
      }
      *end = (dataNode*) malloc( sizeof( dataNode ) );
    }


};

#endif // MESSAGE_CLASS_INCLUDED

