#******************************************************************************
# INF 610 - Estruturas de Dados e Algoritmos - 2018/2                         *
#                                                                             *
# Trabalho prático 2                                                          *
#                                                                             *
# Marcelo de Matos Menezes - 75254                                            *
#                                                                             *
#*****************************************************************************/


help:
	@echo type "make ukdt" to compile the umbalanced k-d tree tests

# Creates build folder case it doesn't exist
create_directories:
	if [ ! -d build ]; then mkdir build; fi

ukdt:
	make create_directories && g++ ukdTree.cpp -o build/ukdtree \
	-std=c++11 -O3 -DUKDT_DEBUG