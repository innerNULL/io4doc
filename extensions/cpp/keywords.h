/// file: utils.h
/// date: 2022-02-26


#ifndef __KEYWORDS_H__
#define __KEYWORDS_H__


#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <unordered_map>
#include <set>

#include "./utils.h"
#include "./Token.h"
#include "./Document.h"


namespace keytext4py_ext {


std::vector<Token*> keywords_cand_gen(
    std::map<std::string, Token*>& tokens, 
    int32_t top_k=-1,
    int32_t min_word_len=1, 
    int32_t min_tf=3) {
  std::vector<Token*> keywords_cand;
  std::vector<Token*> sorter(tokens.size(), nullptr);

  int32_t count = 0;
  for (
    std::map<std::string, Token*>::iterator iter = tokens.begin(); 
    iter != tokens.end(); ++iter) {
    sorter[count++] = iter->second;
  }

  std::sort(sorter.begin(), sorter.end(), 
      [](const Token* a, const Token* b) {
          return a->tf > b->tf; }
  );
  for (auto x : sorter) {
    if (keywords_cand.size() > top_k && top_k > 0) { break; }
    if (x == nullptr) { continue; }
    if (x->tf < min_tf) { break; }
    if (x->text.size() < min_word_len) { continue; }
    keywords_cand.emplace_back(x);
  }
  return keywords_cand;
}


std::vector<Token*> keywords_cand_gen(
    std::map<std::string, Token>& tokens, 
    int32_t top_k=-1,
    int32_t min_word_len=1, 
    int32_t min_tf=3) {
  std::map<std::string, Token*> tokens_ptr;
  for (auto& token : tokens) {
    tokens_ptr[token.first] = &(token.second);
  }
  return keywords_cand_gen(
    tokens_ptr, top_k, min_word_len, min_tf);
}


void cands_quota(
    std::vector<int32_t>& dest, 
    std::vector<std::vector<Token*> >& cands, 
    int32_t top_k=-1) {
  dest.clear();
  if (top_k <= 0) {
    for (auto& cand_group : cands) {
      dest.emplace_back((int32_t)cand_group.size());
    }
  } else {
    std::sort(cands.begin(), cands.end(), 
        [](std::vector<Token*>& a, std::vector<Token*>& b) {
          return a.size() < b.size(); }
    );
    top_k = top_k / cands.size() + 1;
    int32_t count = 1;
    for (auto& cand_group : cands) {
      int32_t quota = 
          (int32_t)cand_group.size() > top_k ? 
            top_k : (int32_t)cand_group.size();
      dest.emplace_back(quota);

      if (count != (int32_t)cands.size()) {
        //printf("dbg: %i, %i, %i, %i\n", 
        //  top_k, top_k - quota, count, cands.size() - count);
        top_k = top_k + 
            (top_k - quota) / (cands.size() - count);
      }
      ++count;
    }
  }
}


void cands_weight(
    std::vector<Token*>& dest, 
    float weight_scale=100.0) {
  int32_t tf_sum = 0;
  for (auto& x : dest) { tf_sum += x->tf; }
  if (tf_sum == 0) { return; }
  for (auto& x : dest) { 
    x->weight = weight_scale * x->tf / tf_sum; 
  }
  std::sort(dest.begin(), dest.end(), 
      [](const Token* a, const Token* b) {
        return a->weight > b->weight; 
  });
}


void cands_selector(
    std::vector<Token*>& dest, 
    std::vector<std::vector<Token*> >& cands, 
    int32_t top_k=-1) {
  dest.clear();
  std::vector<int32_t> quota;

  cands_quota(quota, cands, top_k);
  for (int32_t i = 0; i < quota.size(); ++i) {
    for (int32_t j = 0; 
        j < cands[i].size() && j < quota[i]; ++j) {
      dest.emplace_back(cands[i][j]);    
    }
  }
  cands_weight(dest);
}


void cands_selector(
    std::vector<std::tuple<std::string, float> >& dest, 
    std::vector<std::vector<Token*> >& cands, 
    int32_t top_k=-1) {
  dest.clear();
  std::vector<Token*> dest_;

  cands_selector(dest_, cands, top_k);
  for (auto x : dest_) {
    dest.emplace_back(
      std::tuple<std::string, float>({x->text, x->weight}));
  }
}


/**
 * @brief
 * This is a fast keywords extractor based on some manually 
 * strategies, includes:
 *     1. Filting tokens according their PoS
 *     2. (Bucketing tokens according their PoS)
 *     3. Ranking tokens according their TF in current document.
 *     4. Merging each bucket's ranking result with a quota algo.
 *
 * @note:
 * `weight_scale` is not used for now
 */
std::vector<std::tuple<std::string, float> > 
fast_keywords(
    std::vector<
        std::tuple<std::string, std::string> >& tokens, 
    int32_t top_k=-1, 
    std::set<std::string> target_pos={"NR", "NN"}, 
    int32_t min_word_len=1, bool weight_norm=true, 
    float weight_scale=100.0, bool pos_bucketing=false) {
  std::vector<std::tuple<std::string, float> > keywords;
  Document doc;
  std::vector<std::vector<Token*> > keywords_cands;

  for (auto& item : tokens) {
    doc.AppendToken(std::get<0>(item), std::get<1>(item));
  }
  //doc.print_bow();

  if (pos_bucketing) {
    for (auto& bucket : doc.PosInvertedIndex()) {
      if (target_pos.find(bucket.first) == target_pos.end()) {
        continue;
      }
      //printf("%s, %i\n", bucket.first.c_str(), bucket.second.size());
      keywords_cands.emplace_back(keywords_cand_gen(bucket.second));
    }
  } else {
    std::map<std::string, Token*> bow = doc.BoW();
    keywords_cands.emplace_back(keywords_cand_gen(bow));
  }

  cands_selector(keywords, keywords_cands, top_k);
  return keywords;
}


} // namespace keytext4py_ext


#endif
