CC=g++

CFLAGS_OMP= -I../mojo/ -std=c++11 -fopenmp -O3 -DMOJO_OPM -DMOJO_AVX -msse4 -mavx
CFLAGS_OMP_DBG=-I../mojo/ -std=c++11 -fopenmp -g -DMOJO_OPM -DMOJO_AVX -msse4 -mavx

all: test train_mnist train_cifar train_caffenet

test: test.cpp 
	$(CC) $(CFLAGS_OMP) test.cpp -o test

train_mnist: train_mnist.cpp
	$(CC) $(CFLAGS_OMP) train_mnist.cpp -o train_mnist

train_cifar: train_cifar.cpp 
	$(CC) $(CFLAGS_OMP) train_cifar.cpp -o train_cifar

train_caffenet: train_caffenet.cpp
	$(CC) $(CFLAGS_OMP_DBG) train_caffenet.cpp -o train_caffenet

clean:
	-rm -f test
	-rm -f train_mnist
	-rm -f train_cifar
	-rm -f train_caffenet
