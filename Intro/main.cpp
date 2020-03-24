//
// Created by Tal Skverer on 24/03/2020.
//

#include <iostream>
#include <string>

namespace intro {
  int main(){
    // Get number of lines
    int num_lines;
    std::cin >> num_lines;

    std::string line;
    std::string first, second;
    for (int i = 0; i < num_lines; ++i) {
      // Get both numbers. cin splits automatically by spaces.
      std::cin >> first;
      std::cin >> second;
      // Output the necessary relation.
      if (stoi(first) < stoi(second)){
        std::cout << "<" << std::endl;
      }
      else if (stoi(first) == stoi(second)){
        std::cout << "=" << std::endl;
      }
      else {
        std::cout << ">" << std::endl;
      }
    }

    return 0;
  }
}