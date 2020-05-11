#include <iostream>
#include <random>
#include <chrono>

#define SLOPE  3
#define OFFSET 2

class perceptron_t
{
public:
    double_t* weights;
    double_t bias;

    double get_random_normalized()
    {
        return (double) std::rand() / RAND_MAX;
    }

    perceptron_t()
    {
        /* Initialize seed for random number generator. */
        auto timestamp = std::chrono::system_clock::now().time_since_epoch();
        auto seed = std::chrono::duration_cast<std::chrono::microseconds>(timestamp);
        std::srand(seed.count());

        /* Assign random weights. */
        weights = new double[2];
        weights[0] = get_random_normalized()*2-1;
        weights[1] = get_random_normalized()*2-1;
        bias = get_random_normalized()*2-1;
    }

    ~perceptron_t() { delete [] weights; }

    int32_t heaviside(double f) { return (f < 0 ) ? 0 : 1; }

    /**
     * Implements the core functionality of the perceptron.
     * It weights the input signals, sums them up, adds the bias,
     * and runs the result through the Heaviside Step function.
    */
    int32_t process(uint32_t x, uint32_t y)
    {
        double sum = bias;
        sum += ((double) x) * weights[0];
        sum += ((double) y) * weights[1];
        return heaviside(sum);
    }

    /**
     * During the learning phase, the perceptron adjusts the
     * weights and the bias based on how much the perceptrons
     * answer differs from the correct answer.
    */
    void adjust(int32_t x, int32_t y, double delta, double learning_rate)
    {
        if (x*weights[0] < 0)
            weights[0] += ((double) x) * delta * learning_rate;
        else
            weights[0] -= ((double) x) * delta * learning_rate;

        if (x*weights[1] < 0)
            weights[1] += ((double) y) * delta * learning_rate;
        else
            weights[1] -= ((double) y) * delta * learning_rate;

        bias += delta * learning_rate;
    }

    /**
     * This is the training function. The perceptron's teacher.
     *
     * The training function delivers the correct or expected outputs
     * for a given input on a supervised training setup.
     *
     * For this case we will use a simple linear function.
    */
    int32_t training_line(int32_t x) { return SLOPE*x + OFFSET; }

    int32_t is_above_line(int32_t x, int32_t y) { return (y > training_line(x)) ? 1 : 0; }

    void train_perceptron(uint32_t iterations, double rate)
    {
        for (int i=0; i < iterations; i++) {
            /* Generate random point. */

            int32_t x = get_random_normalized()*20001 - 10001;
            int32_t y = get_random_normalized()*20001 - 10001;

            // Feed the point to the perceptron and evaluate the
            // result.
            int perceptron_answer = this->process(x, y);
            int expected = is_above_line(x, y);
            double delta = expected - perceptron_answer;
            //std::cout << delta << std::endl;
            this->adjust(x, y, delta, rate);
        }
    }

    double verify (const uint32_t test_count)
    {
        uint32_t correct_answers = 0;
        for (int i=0; i < test_count; i++) {
            uint x = get_random_normalized()*20001 - 10001;
            uint y = get_random_normalized()*20001 - 10001;

            uint32_t p_response = this->process(x, y);
            uint32_t t_response = is_above_line(x, y);

            if ( p_response == t_response ) {
                correct_answers++;
            }
        }
        return  ((double)correct_answers/(double)test_count);
    }
};



int main(int argc, char** argv) {

    /* Test 1: Optimize single perceptron. */
    perceptron_t perc;

    std::cout << perc.verify(1000) << std::endl;
    std::cout << perc.weights[0] << " " << perc.weights[1] << std::endl;

    /* Do not stop training until a consistent 95% success rate is achieved.*/
    while (perc.verify(100) < 0.80)
        perc.train_perceptron(10000, 0.01);

    std::cout << perc.verify(1000) << std::endl;
    std::cout << perc.weights[0] << " " << perc.weights[1] << std::endl;
    std::cout << "--------------" << std::endl;
    /* Test 2_ Try different hyperparameters and observe the results. */

    uint32_t iterations[] =  {1000, 10000, 100000, 1000000};

    double learning_rates[] = {0.5, 0.1, 0.01, 0.001}; // range > 0 and < 1

    perceptron_t ps[16];
    for (int it=0; it<4; it++) {
        for (int lr=0; lr<4; lr++) {
            ps[it + lr*4].train_perceptron(iterations[it], learning_rates[lr]);
            std::cout << "iter: " << iterations[it] << std::endl;
            std::cout << "rate: " << learning_rates[lr] << std::endl;
            std::cout << "success ratio: " << ps[it+lr*4].verify(1000) << std::endl;
            std::cout << "---------------" << std::endl;
        }
    }

    exit(0);
}

