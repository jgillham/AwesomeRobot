#ifndef STATE_CLASS_INCLUDED
#define STATE_CLASS_INCLUDED

class State {
  public:
    virtual void onBegin() = 0;
    virtual void onEnd() = 0;
};

#endif // STATE_CLASS_INCLUDED

