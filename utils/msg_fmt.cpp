#include "msg_fmt.h"

#include <iostream>

namespace msg {

void Fatal(std::string msg, std::string test_id) {
  std::cerr << "FAIL\t" << test_id << " - " << msg << std::endl;
};

void Error(std::string msg, std::string test_id) {
  std::cerr << "ERROR\t" << test_id << " - " << msg << std::endl;
};

void Ok(std::string test_id) { std::cerr << "ok\t" << test_id << std::endl; };

} // namespace msg
