#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <iostream>
#include <set>
#include "product.h"

using namespace std;

class Movie: public Product{

  public:
  Movie(const std::string category, const std::string name, double price, int qty, std::string rating, std::string genre);
  virtual std::set<std::string> keywords() const;
  virtual std::string displayString() const;
  void dump(std::ostream& os);

  protected:
  std::set<std::string> keywords_;
  string rating_;
  string genre_;
};
#endif
