#pragma once

#include "args.h++"
#include <vector>

// ---------------------------------------------------------------------------
// Minimal checker satisfying ArgsChecker concept
// ---------------------------------------------------------------------------

struct test_checker {
  nutsloop::args::args_key_value_t_ value;
  test_checker(nutsloop::args::args_key_value_t_ v) : value(std::move(v)) {}
};

// ---------------------------------------------------------------------------
// Minimal helper satisfying ArgsHelper concept
// ---------------------------------------------------------------------------

struct test_helper {
  std::string look_up;
  std::array<int, 3> ver;
  test_helper(std::string s, std::array<int, 3> v) : look_up(std::move(s)), ver(v) {}
};

// ---------------------------------------------------------------------------
// Sequencer aliases
// ---------------------------------------------------------------------------

using seq_t = nutsloop::args::sequencer<test_checker>;
using seq_help_t = nutsloop::args::sequencer<test_checker, test_helper>;

// ---------------------------------------------------------------------------
// Helper: build argc/argv from initializer list
// ---------------------------------------------------------------------------

struct fake_argv {
  std::vector<std::string> storage;
  std::vector<char *> ptrs;

  fake_argv(std::initializer_list<const char *> args) {
    for (auto *a : args) storage.emplace_back(a);
    for (auto &s : storage) ptrs.push_back(s.data());
  }

  int argc() const { return static_cast<int>(ptrs.size()); }
  char **argv() { return ptrs.data(); }
};
