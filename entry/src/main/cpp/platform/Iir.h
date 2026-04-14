#ifndef IIR_H_STUB
#define IIR_H_STUB

#include <cstddef>

namespace Iir {

namespace RBJ {
class LowShelf {
public:
    void setup(double sample_rate, double cutoff_freq, double gain_db, double slope = 1.0) {}
    inline double filter(double sample) { return sample; }
};

class HighShelf {
public:
    void setup(double sample_rate, double cutoff_freq, double gain_db, double slope = 1.0) {}
    inline double filter(double sample) { return sample; }
};

class AllPass {
public:
    void setup(double sample_rate, double cutoff_freq, double q_factor = 0.707) {}
    inline double filter(double sample) { return sample; }
};
}

namespace Butterworth {

template <int order>
class HighPass {
public:
    void setup(double sample_rate, double cutoff_freq) {}
    void setup(int order_arg, double sample_rate, double cutoff_freq) {}
    inline double filter(double sample) { return sample; }
    void reset() {}
};

template <int order>
class LowPass {
public:
    void setup(double sample_rate, double cutoff_freq) {}
    void setup(int order_arg, double sample_rate, double cutoff_freq) {}
    inline double filter(double sample) { return sample; }
    void reset() {}
};

}

}

#endif
