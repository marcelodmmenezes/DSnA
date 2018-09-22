#******************************************************************************
# INF 610 - Estruturas de Dados e Algoritmos - 2018/2                         *
#                                                                             *
# Lista de exercícios 6                                                       *
#                                                                             *
# Marcelo de Matos Menezes - 75254                                            *
#                                                                             *
#*****************************************************************************/


help:
	@echo type "make sorting" to compile the sorting algorithms test
	@echo type "make partialSorting" to compile the partial \
	sorting algorithms test
	@echo type "make benchmark" to compile the benchmark

# Creates build folder case it doesn't exist
create_directories:
	if [ ! -d build ]; then mkdir build; fi

sorting:
	make create_directories && g++ sorting.cpp -o build/sorting \
	-std=c++11 -O3

paritalSorting:
	make create_directories && g++ partialSorting.cpp -o build/partialSorting \
	-std=c++11 -O3

benchmark:
	make create_directories && g++ benchmark.cpp -o build/benchmark \
	-std=c++11 -O3