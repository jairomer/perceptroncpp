# Perceptroncpp

A small experiment during my adventures trying to learn about machine learning
algorithms.

This is a very simple perceptron implementation that receives a 2D point and
determines if it is over a specific line or not.

The perceptron itself is implemented using generic programming and may be 
reused in other projects. However, an already classified dataset is needed 
beforehand and the data must be linearly representable. Linear regression can 
be a better alternative to this kind of system. 

The line is defined by two macros SLOPE and OFFSET.

`y = SLOPE*x + OFFSET`

### Challenges
- Understading why it works and why it does not.
- Getting trully random values.

### What I learned
- How a perceptron works and what it is useful for. 
- Random numbers in C++11.
- Generic Programming in C++. 
- The quality of these algorithms depend fully on the quality and quantity of data.

### Future Work?
- Obtain the best hyperparameters in a more systematic way via a search or genetic algorithm.
- Use it against multidimensional linear data.
- Use it in a real project.

### Sources
- https://towardsdatascience.com/perceptron-learning-algorithm-d5db0deab975
- https://appliedgo.net/perceptron/
