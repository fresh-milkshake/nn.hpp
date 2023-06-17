#ifndef PCB_HPP
#define PCB_HPP

#include <cstdint>

class PCG {
public:
  PCG(uint64_t initState, uint64_t initStream)
      : state(initState), inc((initStream << 1u) | 1u) {}

  double next() {
    uint64_t oldState = state;
    state = oldState * 6364136223846793005ULL + inc;
    uint32_t xorShifted = ((oldState >> 18u) ^ oldState) >> 27u;
    uint32_t rot = oldState >> 59u;
    return static_cast<double>((xorShifted >> rot) |
                               (xorShifted << ((-rot) & 31))) /
           UINT32_MAX;
  }

private:
  uint64_t state, inc;
};

#endif // PCB_HPP
