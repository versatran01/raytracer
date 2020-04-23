#include "timer.h"

#include "logging.h"

namespace rt {

std::string ReportFormat(const std::string& name,
                         const TimerSummary::StatsT& stats,
                         int name_width = 8) {
  return fmt::format("\n{:<{}} | {}{:<{}} |",
                     name,
                     name_width,
                     stats.repr(),
                     name,
                     name_width);
}

void TimerSummary::ManualTimer::Stop(bool log) noexcept {
  CHECK(!is_stopped()) << "timer has not started";
  stop();
  if (log) stats.Add(absl::Nanoseconds(elapsed().wall));
}

TimerSummary::ManualTimer TimerSummary::Manual(
    const std::string& name) noexcept {
  CHECK(!name.empty()) << "must provide a name";
  return ManualTimer{stats_dict_[name]};
}

TimerSummary::ScopedTimer TimerSummary::Scoped(
    const std::string& name) noexcept {
  CHECK(!name.empty()) << "must provide a name";
  return ScopedTimer{stats_dict_[name]};
}

std::string TimerSummary::Report(const std::string& name) const {
  const auto it = stats_dict_.find(name);
  if (it == stats_dict_.end()) {
    return fmt::format("[{}] not found in {}.", name, name_);
  }

  return ReportFormat(it->first, it->second);
}

std::string TimerSummary::ReportAll(int name_width) const {
  std::string result = fmt::format("Timer Summary: {}", name_);
  for (const auto& pair : stats_dict_) {
    result += ReportFormat(pair.first, pair.second, name_width);
  }
  return result;
}

TimerSummary::SummaryDict TimerSummary::SummaryAll() const {
  SummaryDict summary;
  for (const auto& kv : stats_dict_) {
    summary[kv.first] = kv.second.Summary();
  }
  return summary;
}

}  // namespace rt