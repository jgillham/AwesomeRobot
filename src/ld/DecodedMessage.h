#ifndef DECODEDMESSAGE_CLASS_INCLUDED
#define DECODEDMESSAGE_CLASS_INCLUDED
#include "Node.h"
class AutoFree {
  public:
    AutoFree( void* pointer ): pointer( pointer ) {;
    }
    ~AutoFree() {
      free( this->pointer );
    }
  private:
    void* pointer;
};

class DecodedMessage {
  private:
    typedef Node< double > DataNode;
    typedef DataNode* DataNode_Pntr;
    int ID;
    int Number;
    DataNode_Pntr head;
  public:
    static DecodedMessage


};

#endif // DECODEDMESSAGE_CLASS_INCLUDED

