#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <csignal>

namespace SignalState {
  extern volatile std::sig_atomic_t serverRunning;
}

#endif
