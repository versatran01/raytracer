#pragma once

#include <fmt/format.h>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/count.hpp>
#include <boost/accumulators/statistics/max.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/sum.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#include <unordered_map>

namespace rt {

namespace bac = boost::accumulators;

/**
 * @brief The Stats class
 * Accumulates statistics of a value
 */
template <typename T = double>
class Stats {
 public:
  using value_type = T;

  void Add(const T& value) noexcept {
    last_ = value;
    acc_(value);
  }
  void Reset() noexcept { acc_ = {}; }

  int Count() const noexcept { return count_(acc_); }
  T Sum() const noexcept { return sum_(acc_); }
  T Mean() const noexcept { return mean_(acc_); }
  T Min() const noexcept { return min_(acc_); }
  T Max() const noexcept { return max_(acc_); }
  const T& Last() const noexcept { return last_; }

  /// A summary of statistics
  using SummaryT = std::unordered_map<std::string, T>;

  SummaryT Summary() const noexcept {
    return {{"mean", Mean()},  // to make it first
            {"last", Last()},
            {"sum", Sum()},
            {"min", Min()},
            {"max", Max()}};
  }

  std::string repr() const {
    std::string result = fmt::format("n: {:<6}| ", Count());
    for (const auto& kv : Summary()) {
      result += fmt::format("{}: {:<14}| ", kv.first, kv.second);
    }
    return result;
  }

 private:
  using stats = bac::stats<bac::tag::count,
                           bac::tag::sum,
                           bac::tag::mean,
                           bac::tag::min,
                           bac::tag::max>;

  bac::accumulator_set<T, stats> acc_;
  bac::extractor<bac::tag::count> count_;
  bac::extractor<bac::tag::sum> sum_;
  bac::extractor<bac::tag::mean> mean_;
  bac::extractor<bac::tag::min> min_;
  bac::extractor<bac::tag::max> max_;
  T last_;
};

}  // namespace rt