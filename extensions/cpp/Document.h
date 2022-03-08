/// file: Document.h
/// date: 2022-02-28


#ifndef __DOCUMENT_H__
#define __DOCUMENT_H__


#include <unordered_map>
#include <map>
#include <vector>
#include <string>

#include "./Token.h"
#include "./Sentence.h"

namespace keytext4py_ext {


class Document {
 public:
  Document() = default;

  void AppendToken(
      const std::string& word, const std::string& pos);

  void AppendSentence();

  Sentence* GetLastSentence();

  void PrintBow();

  std::map<std::string, Token*> BoW();

  std::unordered_map<
      std::string, std::map<std::string, Token*>
  > PosInvertedIndex();

 private:
  std::string token_delimiter_ = " ";
  std::string text_ = "";
  
  std::map<std::string, Token> bow_ = {}; // Bag of Words Dict
  std::vector<Sentence> sentences_ = {};
  std::unordered_map<
      std::string, std::map<std::string, Token*>
  > pos_inverted_idx_ = {};
};


void Document::AppendSentence() {
  this->sentences_.emplace_back(Sentence());
}


Sentence* Document::GetLastSentence() {
  if (this->sentences_.size() == 0) { this->AppendSentence(); }
  return &(this->sentences_[this->sentences_.size() - 1]);
}


void Document::AppendToken(
    const std::string& word, const std::string& pos) {
  this->text_ += (this->token_delimiter_ + word);

  if (this->bow_.find(word) == this->bow_.end()) {
    this->bow_[word] = Token({
      id: this->bow_.size() + 1, 
      text: word, 
      pos: pos, 
      tf: 1
    });
  } else {
    this->bow_[word].tf += 1;
  }

  this->GetLastSentence()->AppendToken(&(this->bow_[word]));
 
  /// Due to `this->bow_` record same word only one time, 
  /// no-matter pos or sth else will change next time, so 
  /// pos bucket name sometime may be different with token's 
  /// pos.
  if (this->pos_inverted_idx_.find(pos) 
      == this->pos_inverted_idx_.end()) {
    this->pos_inverted_idx_[pos] = {};
  }
  if (this->pos_inverted_idx_[pos].find(word) 
      == this->pos_inverted_idx_[pos].end()) {
    this->pos_inverted_idx_[pos][word] = &(this->bow_[word]);
  }
}


void Document::PrintBow() {
  for (auto& item : this->bow_) {
    item.second.Print();
  }
}


std::map<std::string, Token*> Document::BoW() {
  std::map<std::string, Token*> bow;
  for (auto& token : this->bow_) {
    bow[token.first] = &(token.second);
  }
  return bow;
}


std::unordered_map<
    std::string, std::map<std::string, Token*>
> Document::PosInvertedIndex() {
  return this->pos_inverted_idx_;
}


} // namespace keytext4py_ext



#endif
