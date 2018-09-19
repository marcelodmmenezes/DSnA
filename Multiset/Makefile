#******************************************************************************
# INF 610 - Estruturas de Dados e Algoritmos - 2018/2                         *
#                                                                             *
# Lista de exercícios 3                                                       *
#                                                                             *
# Marcelo de Matos Menezes - 75254                                            *
#                                                                             *
#*****************************************************************************/


# Creates build folder case it doesn't exist
create_directories:
	if [ ! -d build ]; then mkdir build; fi

debug:
	make create_directories && g++ debug.cpp -o build/debug \
	-std=c++11 -DODA_DEBUG -DRBT_DEBUG

benchmark:
	make create_directories && g++ benchmark.cpp -o build/benchmark \
	-std=c++11 -O3 -DWRITE_TO_FILE
