
#include <iostream>




class State {
    public:
    virtual void receive() {
        std::cout << "Default Receive" << std::endl;
    }
};
extern State* state;

void changeState( State* nState ) {
    state = nState;
}

class Go: public State {
    void receive() {
        std::cout << "Go Receive" << std::endl;
    }
};

class Scan: public State {
    public: void receive() {
        std::cout << "Scan Receive" << std::endl;
        changeState( new Go() );
    }
};

State* state = new Scan();


int main() {

    int i = 0;

    while( i++ < 5 ) {
        state->receive();
    }

    return 0;
}
