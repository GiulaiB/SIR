# Programming_Exam: The SIR Project

This project studies the behaviour of an epidemic through the design of a code in C++ language that reproduces the prolification of a virus according to the SIR model.

## Execution

To compile this programm follow the next steps
```shell
g++ -c main.cpp disease.cpp
```
```shell
g++ -o sir main.o disease.o
```
To run this programm follow the next step
```shell
./sir
```
The data file will be in the folder. To take a look at it in the ubuntu terminal please insert
```shell
cat epidemic.txt
```

## Testing

To compile this programm follow the next steps
```shell
g++ -c testing.cpp
```
```shell
g++ -o sirtest testing.o
```
To run this programm follow the next step
```shell
./sirtest
```
