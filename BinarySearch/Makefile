#******************************************************************************
# INF 610 - Estruturas de Dados e Algoritmos - 2018/2                         *
#                                                                             *
# Lista de exercícios 6                                                       *
#                                                                             *
# Marcelo de Matos Menezes - 75254                                            *
#                                                                             *
#*****************************************************************************/


help:
	@echo type \"make main\" to compile

# Creates build folder case it doesn't exist
create_directories:
	if [ ! -d build ]; then mkdir build; fi

main:
	make create_directories && g++ main.cpp -o build/bs \
	-std=c++11 -O3