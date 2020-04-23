#pragma once

#include <absl/time/time.h>

#include <boost/timer/timer.hpp>
#include <limits>
#include <map>

#include "stats.h"

/// Specialize numeric_limits for absl::Duration
namespace std {
template <>
struct numeric_limits<absl::Duration> {
  static constexpr bool is_specialized = true;

  static constexpr absl::Duration min() noexcept {
    return absl::Nanoseconds(0);
  }

  static constexpr absl::Duration max() noexcept {
    return absl::InfiniteDuration();
  }
};

}  // namespace std

/// Specialize fdiv for absl::Duration
/// https://www.boost.org/doc/libs/1_72_0/doc/html/accumulators/user_s_guide.html
/// See Specializing Numeric Operators
namespace boost::numeric::functional {

struct AbslDurationTag {};

template <>
struct tag<absl::Duration> {
  using type = AbslDurationTag;
};

template <typename Left, typename Right>
struct fdiv<Left, Right, AbslDurationTag, void> {
  // Define the type of the result
  using result_type = absl::Duration;

  result_type operator()(Left& left, Right& right) const {
    return left / right;
  }
};

}  // namespace boost::numeric::functional

namespace rt {

using AutoTimer = boost::timer::auto_cpu_timer;
using CpuTimer = boost::timer::cpu_timer;

inline absl::Duration Cpu2AbslDuration(
    const boost::timer::cpu_times& cpu_time) noexcept {
  return absl::Nanoseconds(cpu_time.wall);
}

/**
 * @brief The TimerSummary class
 * This is similar to Ceres-Solver's ExecutionSummary class, where we record
 * execution statistics (mainly time). Instead of simply record the time, we
 * store a bunch of other statistics using boost accumulator.
 */
class TimerSummary {
 public:
  using StatsT = Stats<absl::Duration>;
  using StatsDict = std::map<std::string, StatsT>;
  using SummaryDict = std::map<std::string, StatsT::SummaryT>;

  /// A manual timer where user needs to call stop explicitly
  struct ManualTimer : private CpuTimer {
    explicit ManualTimer(StatsT& stats) noexcept : stats{stats} {}

    /// Start the timer
    void Start() noexcept { start(); }

    /// Stop the timer and log to statistics
    void Stop(bool log = true) noexcept;

    StatsT& stats;
  };

  /// A scoped timer that will call stop on destruction
  struct ScopedTimer : public ManualTimer {
    explicit ScopedTimer(StatsT& stats) : ManualTimer{stats} {}
    ~ScopedTimer() { Stop(true); }
  };

  /// Constructor
  explicit TimerSummary(const std::string& name = "summary") noexcept
      : name_{name} {}

  const std::string& name() const noexcept { return name_; }
  int size() const noexcept { return stats_dict_.size(); }

  /// Start a ManualTimer (already started )by name, need to manually stop the
  /// returned timer. After stop one can just call timer.Start() to restart
  ManualTimer Manual(const std::string& name) noexcept;

  /// Returns a ScopedTimer (already started) and will stop when out of scope
  ScopedTimer Scoped(const std::string& name) noexcept;

  /// Return a string of timer statistics
  std::string ReportAll(int name_width = 32) const;
  std::string Report(const std::string& name) const;

  /// Return a summary of all stats as <name, <stat, value>>
  /// This is primarily used for serialization to json
  SummaryDict SummaryAll() const;

 private:
  std::string name_;
  StatsDict stats_dict_;
};

}  // namespace rt