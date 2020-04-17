#include "timer.h"

#include <doctest/doctest.h>

#include <ostream>
#include <thread>

#include "logging.h"

using namespace rt;

TEST_CASE("Timer") {
  TimerSummary ts("test");

  auto a = ts.Manual("a");
  usleep(1000);
  a.Stop();
  LOG(INFO) << ts.Report("a");

  for (int i = 0; i < 100; ++i) {
    auto b1 = ts.Manual("b1");
    usleep(1000);
    b1.Stop();
  }
  LOG(INFO) << ts.Report("b1");

  auto b2 = ts.Manual("b2");
  for (int i = 0; i < 100; ++i) {
    b2.Start();
    usleep(1000);
    b2.Stop();
  }
  LOG(INFO) << ts.Report("b2");

  {
    auto c = ts.Scoped("c");
    usleep(1000);
  }
  LOG(INFO) << ts.Report("c");

  for (int i = 0; i < 100; ++i) {
    auto d = ts.Scoped("d");
    usleep(1000);
  }
  LOG(INFO) << ts.Report("d");

  LOG(INFO) << ts.ReportAll();
}