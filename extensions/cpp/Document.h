/// file: Document.h
/// date: 2022-02-28


#ifndef __DOCUMENT_H__
#define __DOCUMENT_H__


#include <unordered_map>
#include <map>
#include <vector>
#include <string>

#include "./Token.h"


namespace keytext4py_ext {


class Document {
 public:
  Document() = default;

  void append_token(
      const std::string& word, const std::string& pos);

  void print_bow();

  std::map<std::string, Token*> bow();

  std::unordered_map<
      std::string, std::map<std::string, Token*>
  > pos_inverted_idx();

 private:
  std::string _token_delimiter = " ";
  std::string _text = "";
  
  std::map<std::string, Token> _bow = {}; // Bag of Words Dict
  std::vector<Token*> _tokens = {};
  std::unordered_map<
      std::string, std::map<std::string, Token*>
  > _pos_inverted_idx = {};
};


void Document::append_token(
    const std::string& word, const std::string& pos) {
  this->_text += (this->_token_delimiter + word);

  if (this->_bow.find(word) == this->_bow.end()) {
    this->_bow[word] = Token({
      id: this->_bow.size() + 1, 
      text: word, 
      pos: pos, 
      tf: 1
    });
  } else {
    this->_bow[word].tf += 1;
  }

  this->_tokens.emplace_back(&(this->_bow[word]));
 
  /// Due to `this->_bow` record same word only one time, 
  /// no-matter pos or sth else will change next time, so 
  /// pos bucket name sometime may be different with token's 
  /// pos.
  if (this->_pos_inverted_idx.find(pos) 
      == this->_pos_inverted_idx.end()) {
    this->_pos_inverted_idx[pos] = {};
  }
  if (this->_pos_inverted_idx[pos].find(word) 
      == this->_pos_inverted_idx[pos].end()) {
    this->_pos_inverted_idx[pos][word] = &(this->_bow[word]);
  }
}


void Document::print_bow() {
  for (auto& item : this->_bow) {
    item.second.print();
  }
}


std::map<std::string, Token*> Document::bow() {
  std::map<std::string, Token*> bow;
  for (auto& token : this->_bow) {
    bow[token.first] = &(token.second);
  }
  return bow;
}


std::unordered_map<
    std::string, std::map<std::string, Token*>
> Document::pos_inverted_idx() {
  return this->_pos_inverted_idx;
}


} // namespace keytext4py_ext



#endif
