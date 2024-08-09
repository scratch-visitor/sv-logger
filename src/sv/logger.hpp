#pragma once

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif // _WIN32

#include <boost/asio.hpp>
#include <fmt/format.h>
#include <thread>
#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <memory>
#include <chrono>
#include <iomanip>
#include <sstream>

#define trace log(__func__)
#define scope_trace(x) sv::scope_log __##x(#x)

namespace sv
{
namespace detail
{

template<class StringT>
struct console_out
{
  StringT msg_;
  std::chrono::system_clock::time_point timestamp_;
  void operator()();
};

template<class StringT>
struct file_out
{
  StringT msg_;
  std::chrono::system_clock::time_point timestamp_;
  void operator()();
};

template<class Executor, class StringT>
struct network_out
{
  Executor& ex_;
  StringT msg_;
  std::chrono::system_clock::time_point timestamp_;
  void operator()();
};

} // namespace sv::detail

template<class StringT>
struct basic_logger
{
  using string_type = StringT;
  using self = basic_logger<StringT>;

  static void push(string_type const& s)
  {
    std::call_once(once_,
    [&]
    {
      instance_ = std::unique_ptr<self>(new self());
    });

    instance_->do_push(s);
  }
  static void release()
  {
    instance_.reset();
  }

private:
  basic_logger()
    : ioc_()
    , workguard_(ioc_.get_executor())
    , worker_([&]
             {
               ioc_.run();
             })
  {
  }
public:
  ~basic_logger()
  {
    workguard_.reset();
    if (worker_.joinable())
    {
      worker_.join();
    }
  }
private:
  void do_push(StringT const& s)
  {
    auto now = std::chrono::system_clock::now();
    boost::asio::post(ioc_, detail::console_out<StringT>{ s, now });
    boost::asio::post(ioc_, detail::file_out<StringT>{ s, now });
    boost::asio::post(ioc_, detail::network_out<boost::asio::io_context, StringT>{ ioc_, s, now });
  }

private:
  boost::asio::io_context ioc_;
  boost::asio::executor_work_guard<boost::asio::executor> workguard_;
  std::thread worker_;

private:
  static std::once_flag once_;
  static std::unique_ptr<basic_logger<StringT>> instance_;
};

template<class StringT>
std::once_flag basic_logger<StringT>::once_;

template<class StringT>
std::unique_ptr<basic_logger<StringT>> basic_logger<StringT>::instance_;

using logger = basic_logger<std::string>;

} // namespace sv

template<class StringT>
void log(StringT&& s)
{
  sv::logger::push(std::forward<StringT>(s));
}

template<class...T>
void log(fmt::format_string<T...> fmt, T&&...v)
{
  log(fmt::vformat(fmt.get(), fmt::make_format_args(v...)));
}

template<class StringT>
void on_error(boost::system::error_code const& ec, StringT&& tag)
{
  log("[error][{}][{}] {}", tag, ec.value(), ec.message());
}

namespace sv
{

template<class StringT>
struct basic_scope_log
{
  basic_scope_log(StringT&& tag)
    : tag_(tag)
  {
    log("{} begin", tag_);
  }
  ~basic_scope_log()
  {
    log("{} end", tag_);
  }

private:
  StringT tag_;
};

using scope_log = basic_scope_log<std::string>;

} // namespace sv

////////////////////////////////////////////////////////////////////////////////////////////////////
// implementations
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sv
{
namespace detail
{

template<class TimePoint>
std::string to_string(TimePoint const& tp)
{
  time_t epoch = std::chrono::system_clock::to_time_t(tp);
  tm tick;
  ::localtime_s(&tick, &epoch);

  std::stringstream ss;
  ss << std::put_time(&tick, "%F %T");

  return ss.str();
}

template<class StringT>
void console_out<StringT>::operator()()
{
  std::cout << fmt::format("[{}] {}\n", to_string(timestamp_), msg_) << std::flush;
}

template<class StringT>
void file_out<StringT>::operator()()
{
  std::fstream logfile("app.log", std::ios::app);

  logfile << fmt::format("[{}] {}\n", to_string(timestamp_), msg_) << std::flush;
}

template<class Executor, class StringT>
void network_out<Executor, StringT>::operator()()
{
  namespace asio = boost::asio;
  using udp = asio::ip::udp;

  udp::endpoint ep(asio::ip::make_address("127.0.0.1"), 12531);

  udp::socket sock(ex_);
  asio::streambuf buffer;
  std::ostream os(&buffer);

  os << fmt::format("[{}] {}\n", to_string(timestamp_), msg_);

  sock.async_send_to(buffer.data(), ep, [](auto ec, auto sz) { /*no matter*/ });
}

} // namespace sv::detail
} // namespace sv