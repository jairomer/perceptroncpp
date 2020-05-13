#ifndef PERCEPTRON_T
#define PERCEPTRON_T

#include <random>
#include <chrono>
#include <array>
#include <assert.h>
class perceptron_t
{
private:
    double get_rand() { return (double) std::rand() / RAND_MAX; }

    uint32_t heaviside(double f) { return (f < 0 ) ? 0 : 1; }

public:
    double*     weights_;
    uint32_t    inputs_;
    double      bias_;
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
        inputs_ = number_of_inputs;
        weights_ = new double[number_of_inputs];

        for (int i=0; i<inputs_; i++){
            weights_[i] = get_rand()*2-1;
        }
        bias_ = get_rand()*2-1;
    }
    ~perceptron_t() { delete [] weights_; }

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
    template<class TContainer>
    uint32_t process(TContainer& input)
    {
        assert(input.size() == inputs_);

        double sum = bias_;
        for (int i=0; i < inputs_; i++)
            sum += (double) input[i] * weights_[i];
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
    template <class TContainer>
    void adjust(TContainer& input, double delta, double learning_rate)
    {
        assert(input.size() == inputs_);

        for (int i=0; i<inputs_; i++) {
            weights_[i] -= ((double) std::abs(input[i])) * delta * learning_rate;
        }
        
        bias_ += delta * learning_rate;
    }
};

#endif