.PHONY: clean

all: shortest_path_unweighted_graph_test shortest_path_weighted_graph_1_test shortest_path_weighted_graph_2_test

shortest_path_unweighted_graph_test: shortest_path_unweighted_graph_test.o shortest_path_unweighted_graph.o graph.o
	gcc -o shortest_path_unweighted_graph_test shortest_path_unweighted_graph_test.o shortest_path_unweighted_graph.o graph.o

shortest_path_unweighted_graph_test.o: shortest_path_unweighted_graph_test.c
	gcc -c shortest_path_unweighted_graph_test.c

shortest_path_unweighted_graph.o:
	gcc -c shortest_path_unweighted_graph.c

shortest_path_weighted_graph_1_test: shortest_path_weighted_graph_test.o shortest_path_weighted_graph_1.o graph.o
	gcc -o shortest_path_weighted_graph_1_test shortest_path_weighted_graph_test.o shortest_path_weighted_graph_1.o graph.o

shortest_path_weighted_graph_2_test: shortest_path_weighted_graph_test.o shortest_path_weighted_graph_2.o graph.o
	gcc -o shortest_path_weighted_graph_2_test shortest_path_weighted_graph_test.o shortest_path_weighted_graph_2.o graph.o

shortest_path_weighted_graph_test.o: shortest_path_weighted_graph_test.c
	gcc -c shortest_path_weighted_graph_test.c

shortest_path_weighted_graph_1.o:
	gcc -c shortest_path_weighted_graph_1.c

shortest_path_weighted_graph_2.o:
	gcc -c shortest_path_weighted_graph_2.c

graph.o: ../graph/graph.c
	gcc -c ../graph/graph.c

clean:
	rm *.o shortest_path_unweighted_graph_test shortest_path_weighted_graph_1_test shortest_path_weighted_graph_2_test
