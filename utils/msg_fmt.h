#ifndef MSG_FMT
#define MSG_FMT

#include <string>

namespace msg {

void Fatal(std::string msg, std::string test_id);
void Error(std::string msg, std::string test_id);
void Ok(std::string test_id);

} // namespace msg

#endif
