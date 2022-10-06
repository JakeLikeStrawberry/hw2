#include <iostream>
#include "movie.h"
#include "util.h"
using namespace std;


Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string rating, std::string genre) :
Product(category, name, price, qty){
  rating_ = rating;
  genre_ = genre;
  //keywords_ = NULL; //might need to call keywords function here, not sure
}

  std::set<std::string> Movie::keywords() const{

   set<string> result;        
   set<string> name_search;
   set<string> temp;

   temp = parseStringToWords(genre_);         //parses variables
   name_search = parseStringToWords(name_);
  result = setUnion(name_search, temp);
  
//  set<string>::iterator itr;
//   for (itr = result.begin(); itr != result.end(); ++itr){
//     cout << *itr << endl;
//   }
  
  return result;

  }

  std::string Movie::displayString() const{
    string priceString = std::to_string(price_);
    string qtyString = std::to_string(qty_);
    string result = name_ + "\nGenre: " + genre_ + " Rating: " + rating_ + "\n" + priceString + " " + qtyString + " left.";
    return result;
  }


  void Movie::dump(std::ostream& os) {
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << endl;
  }


