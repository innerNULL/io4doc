/// file: Sentences.h
/// date: 2022-03-09


#ifndef __SENTENCE_H__
#define __SENTENCE_H__


#include <unordered_map>
#include <map>
#include <vector>
#include <string>

#include "./Token.h"


namespace keytext4py_ext {


class Sentence {
 public:
  Sentence() = default;
  ~Sentence() = default;

  void AppendToken(Token* token);

  void Print(bool detail=false);

 private:
  std::string text_ = "";
  std::vector<Token*> tokens_;
};


void Sentence::Print(bool detail) {
  printf("sentence info: \n");
  printf("\ttext='%s'\n", this->text_.c_str());
  if (detail) {
    for (Token* token : this->tokens_) {
      token->Print();
    }
  } else {
    for (Token* token : this->tokens_) {
      if (token == nullptr) { 
        printf("Here's a nullptr token\n");
      }
      printf("%s ", token->text.c_str());
    }
    printf("\n");
  }
}


void Sentence::AppendToken(Token* token) {
  //printf("dbg\n");
  //printf("size: %i\n", (int32_t)tokens_.size());
  //token->Print();
  this->tokens_.push_back(token);
}


} // namespace keytext4py_ext


#endif
