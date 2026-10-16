#include "config.h"
#include "csv_converter.h"
#include "random_forest.h"
#include "read_hid.h"
#include "window_frame.h"
#include <chrono>
#include <cstring>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <thread>

namespace {
constexpr int MIN_STATE = 0;
constexpr int MAX_STATE = 3;
constexpr int MIN_SECONDS = 1;

const char *kArgumentError =
    "Use 1 for tracking, 2 for data collection, or 3 for training.";
} // namespace

int prompt_int(const std::string &message, int min, int max) {
  int value;
  while (true) {
    std::cout << message;
    if (std::cin >> value && value >= min && value <= max)
      return value;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

int main(int argc, char **argv) {
  if (argc != 2)
    throw std::runtime_error(kArgumentError);

  const int mode = std::stoi(argv[1]);
  if (mode == 1) {
    window_frame window;
    return window.start() ? 0 : 1;
  }
  if (mode == 2) {
    const int state = prompt_int("State (0-3): ", MIN_STATE, MAX_STATE);
    const int seconds = prompt_int("Sample duration: ", MIN_SECONDS, 3600);
    std::cout << "Collecting state " << state << " for " << seconds
              << " seconds.\n";
    return 0;
  }
  if (mode == 3) {
    train_model("csv/training.csv", "csv/test_data.csv");
    return 0;
  }
  throw std::runtime_error(kArgumentError);
}
