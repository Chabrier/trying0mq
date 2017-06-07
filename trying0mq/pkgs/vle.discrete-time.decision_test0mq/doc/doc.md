# trying 0mq
A lightweight documentation to store what has been done to try the 0mq library
# What for
This library is a candidate solution in order to communicate between application for the MIPP project.
# Roadmap

 1. a test with 2 vle launched with on one side a meteo, and the other side a wwdm, one way exchange the meteo emits, a meteo receiver replace the true meteo. a simple protocol could be "rain=0.1|heat=10".
2. On one side a sending meteo receiving crop info...inside a single model. But at a "single moment"

# Done
a first test has been provided between the helloWorldClient and a vle simulator. The "server" has been implemented inside a wwdm model.

 - The package is not well configured the -lzmq is added by hand on the linking command line
 - Work only with a single wwdm
 - This is not a real exchane of data, but more a compilation test with low level functionnal test