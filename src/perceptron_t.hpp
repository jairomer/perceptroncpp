#ifndef PERCEPTRON_T
#define PERCEPTRON_T

#include <random>
#include <chrono>

class perceptron_t
{
private:
    double get_rand() { return (double) std::rand() / RAND_MAX; }

    uint32_t heaviside(double f) { return (f < 0 ) ? 0 : 1; }

public:
    double*     _weights;
    uint32_t    _inputs;
    double      _bias;
    /**
     * Initializes the perceptron for a given non-negative input count.
     * Sets up seed for the pseudorandom number generator.
     * */
    perceptron_t(uint32_t number_of_inputs)
    {
        /* Initialize seed for random number generator. */
        auto timestamp = std::chrono::system_clock::now().time_since_epoch();
        auto seed = std::chrono::duration_cast<std::chrono::microseconds>(timestamp);
        std::srand(seed.count());

        /* Assign random weights. */
        _inputs = number_of_inputs;
        _weights = new double[number_of_inputs];

        for (int i=0; i<_inputs; i++){
            _weights[i] = get_rand()*2-1;
        }
        _bias = get_rand()*2-1;
    }
    ~perceptron_t() { delete [] _weights; }

    /**
     * Implements the core functionality of the perceptron.
     * It weights the input signals, sums them up, adds the bias,
     * and runs the result through the Heaviside Step function.
     *
     * The size of the input array given should be as large as
     * the number of inputs given during initialization.
     *
     * Given that a perceptron can only clasify into two classes,
     * it will return either 1 or 0 respectively for each class.
    */
    template <typename T>
    uint32_t process( T* input)
    {
        double sum = _bias;
        for (int i=0; i < _inputs; i++)
            sum += (double) input[i] * _weights[i];
        return heaviside(sum);
    }

     /**
     * During the learning phase, the perceptron adjusts the
     * weights and the bias based on how much the perceptrons
     * answer differs from the correct answer.
     *
     * The size of the input array given should be as large as
     * the number of inputs given during initialization.
    */
    template <typename T>
    void adjust(T* input, double delta, double learning_rate)
    {
        for (int i=0; i<_inputs; i++) {
            if (input[i] < 0)
                _weights[i] += ((double) input[i]) * delta * learning_rate;
            else
                _weights[i] -= ((double) input[i]) * delta * learning_rate;
        }
        _bias += delta * learning_rate;
    }
};

#endif