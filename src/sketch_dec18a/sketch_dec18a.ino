#include "my-class.h"



Test *t = 0;

void setup() {
  // put your setup code here, to run once:
//  unique_ptr<Test> song2();
  
  t = new Test();
}

void loop() {
  // put your main code here, to run repeatedly:
  t->write("abc");
}
