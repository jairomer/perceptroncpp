# Perceptroncpp

A small experiment during my adventures trying to learn about machine learning
algorithms.

This is a very simple perceptron implementation that receives a 2D point and
determines if it is over a specific line or not.

The line is defined by two macros SLOPE and OFFSET.

`y = SLOPE*x + OFFSET`

You can expect around a ~70% of consistent success rate from this algorithm
no matter how much you train it. This is probably due to the fact that you
can only achieve certain level of convergence with the current weights, see
sources for more information.


### Challenges
- Understading why it works and why it does not.
- Getting trully random values.

### What I learned
- The most basic kind of neural network.
- Random numbers in C++11.
- The quality of these algorithms depend fully on the quality and quantity of data.

### Future Work?
- Obtain the best hyperparameters in a more systematic way via a search or genetic algorithm.
- Use it against multidimensional linear data.
- Try same problem with deeper neural networks and observe if the success rate gets any better.

### Sources
- https://towardsdatascience.com/perceptron-learning-algorithm-d5db0deab975
- https://appliedgo.net/perceptron/
