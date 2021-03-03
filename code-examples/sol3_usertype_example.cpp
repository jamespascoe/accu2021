#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

#include "date.h"

#include <string>
#include <utility>
#include <vector>
#include <chrono>
#include <iostream>

class timestamped_messages {

  using ts_msg = std::pair<std::string, std::string>;
  using ts_msg_vec = std::vector<ts_msg>;
  ts_msg_vec ts_msgs;

public:

  using value_type = ts_msg_vec::value_type;
  using iterator = ts_msg_vec::iterator;
  using size_type = ts_msg_vec::size_type;

  iterator begin() { return iterator(ts_msgs.begin()); }
  iterator end() { return iterator(ts_msgs.end()); }
  size_type size() const noexcept { return ts_msgs.size(); }
  bool empty() const noexcept { return ts_msgs.empty(); }

  void add_msg(std::string const& msg) {

    using namespace std::chrono;

    auto now = system_clock::now();
    time_t now_t = system_clock::to_time_t(now);
    tm *date = std::localtime(&now_t);
    date->tm_hour = 0;
    date->tm_min = 0;
    date->tm_sec = 0;
    auto midnight = system_clock::from_time_t(std::mktime(date));

    std::ostringstream oss;
    oss << date::hh_mm_ss(now-midnight);

    ts_msgs.push_back({ oss.str(), msg });
  }
};

int main() {
  sol::state lua;
  lua.open_libraries(sol::lib::base);

  lua.new_usertype<timestamped_messages>(
    "timestamped_messages",
    "add_msg", &timestamped_messages::add_msg
  );

  lua.script(R"(
    ts_msgs = timestamped_messages.new()
    ts_msgs:add_msg("msg 1")
    ts_msgs:add_msg("msg 2")
    ts_msgs:add_msg("msg 3")

    for _, ts, msg in pairs(ts_msgs)
    do
      print(tostring(ts) .. " " .. tostring(msg))
    end
  )");

  timestamped_messages& ts_msgs = lua["ts_msgs"];
  for (auto [ts, msg] : ts_msgs)
    std::cout << ts << " " << msg << std::endl;
}
