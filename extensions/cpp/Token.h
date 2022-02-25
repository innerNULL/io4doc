/// file: Token.h
/// date: 2022-02-27


#ifndef __TOKEN_H__
#define __TOKEN_H__


#include <string>


namespace keytext4py_ext {

    
class Token {
 public:
  void print();

 public:
  uint64_t id = 0;
  std::string text = "";
  std::string pos = "";
  int32_t tf = 0; /// Term Frequency
  float weight = 0.0;
};


void Token::print() {
  printf("token info: \n");
  printf("\tid=%ld\n", this->id);
  printf("\ttext='%s'\n", this->text.c_str());
  printf("\tpos='%s'\n", this->pos.c_str()); 
  printf("\ttf=%i\n", this->tf);
  printf("\tweight=%f\n", this->weight);
}


} // namespace keytext4py_ext



#endif
