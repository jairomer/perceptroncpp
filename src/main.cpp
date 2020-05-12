#include <iostream>
#include <random>
#include <chrono>
#include "perceptron_t.hpp"


#define SLOPE  3
#define OFFSET 2
/**
 * Once a seed has been initialized, it returns a random
 * double value between 0 and 1.
*/
double get_rand() { return (double) std::rand() / RAND_MAX; }

double training_line(double x, double slope, double offset) { return slope*x + offset; }

int32_t is_above_line(double x, double y) { return (y > training_line(x, SLOPE, OFFSET)) ? 1 : 0; }

/**
 * This is the training function. The perceptron's teacher so to speak.
 *
 * The training function delivers the correct or expected outputs
 * for a given input on a supervised training setup.
 *
 * For this case we will use a simple linear function.
*/
void train_perceptron(perceptron_t& p, uint32_t iterations, double rate)
{
     /* Initialize seed for random number generator. */
    auto timestamp = std::chrono::system_clock::now().time_since_epoch();
    auto seed = std::chrono::duration_cast<std::chrono::microseconds>(timestamp);
    std::srand(seed.count());

    /* Start training loop. */
    double point[2];
    for (int i=0; i < iterations; i++) {
        /* Generate random point. */
        point[0] = get_rand()*201 - 101;
        point[1] = get_rand()*201 - 101;
        // Feed the point to the perceptron and evaluate the
        // result.
        int perceptron_answer = p.process(point);

        int expected = is_above_line(point[0], point[1]);
        double delta = expected - perceptron_answer;
        //std::cout << delta << std::endl;
        p.adjust(point, delta, rate);
    }
}

double verify (perceptron_t& p, const uint32_t test_count)
{
    uint32_t correct_answers = 0;
    double point[2];
    for (int i=0; i < test_count; i++) {
        /* Generate random point. */
        point[0] = get_rand()*201 - 101;
        point[1] = get_rand()*201 - 101;

        uint32_t p_response = p.process(point);
        uint32_t t_response = is_above_line(point[0], point[1]);

        if ( p_response == t_response ) {
            correct_answers++;
        }
    }
    return  ((double)correct_answers/(double)test_count);
}

int main(int argc, char** argv) {

    /* Test 1: Optimize single perceptron. */
    perceptron_t perc(2);

    std::cout << verify(perc, 1000) << std::endl;
    /* Do not stop training until a consistent 95% success rate is achieved.*/
    while (verify(perc, 100) < 1)
        train_perceptron(perc, 10000, 0.001);

    std::cout << verify(perc, 1000) << std::endl;
    std::cout << "--------------" << std::endl;
    /* Test 2_ Try different hyperparameters and observe the results. */

    uint32_t iterations[] =  {1000, 10000, 100000, 1000000};

    double learning_rates[] = {0.5, 0.1, 0.01, 0.001}; // range > 0 and < 1

    perceptron_t* ps[16];
    for (int it=0; it<4; it++) {
        for (int lr=0; lr<4; lr++) {
            ps[it + lr*4] = new perceptron_t(2);
            train_perceptron(*ps[it+lr*4], iterations[it], learning_rates[lr]);
            std::cout << "iter: " << iterations[it] << std::endl;
            std::cout << "rate: " << learning_rates[lr] << std::endl;
            std::cout << "success ratio: " << verify(*ps[it+lr*4], 1000) << std::endl;
            std::cout << "---------------" << std::endl;
            delete ps[it + lr*4];
        }
    }

    exit(0);
}

