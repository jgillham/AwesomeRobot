#include "WProgram.h"

float getVolts( int IRpin ) {
  return analogRead(IRpin)*0.0048828125;
}
