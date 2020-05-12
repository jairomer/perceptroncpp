#ifndef HYPERVECTOR_TRAINER_H
#define HYPERVECTOR_TRAINER_H

#include <random>

namespace hypervector_training {

    /**
     * Once a seed has been initialized, it returns a random
     * double value between 0 and 1.
    */
    double get_rand() { return (double) std::rand() / RAND_MAX; }

    /**
     * Return the value of a vector multiplication.
     *
     * If both vectors are not compatible, meaning that they are not
     * the same size -1 will be returned and 0 otherwise.
    */
    template<typename T>
    int vector_dot_product(std::vector<T> &m1, std::vector<T> &m2, T* result)
    {
        if (m1.size() != m2.size()) {return -1;}

        T accum = 0;
        for (auto it1 = m1.begin(); it1 != m1.end(); it1++) {
            for (auto it2 = m2.begin(); it2 != m2.end(); it2++) {
                accum =+ (*it1) * (*it2);
            }
        }

        *result = accum;

        return 0;
    }


};

#endif