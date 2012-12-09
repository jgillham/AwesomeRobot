#ifndef FIRSTMATE_CLASS_INCLUDED
#define FIRSTMATE_CLASS_INCLUDED

class FirstMate  {
  public:
    virtual void turn( double theta ) = 0;
    virtual void move( double x, double y ) = 0;
    virtual double calculateTheta( double x, double y ) = 0;
};

#endif // FIRSTMATE_CLASS_INCLUDED

