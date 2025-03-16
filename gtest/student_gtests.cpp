#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

TEST(Dijkstra, small){
  Graph G;
  std::ifstream infile("../src/small.txt");
  ASSERT_TRUE(infile.is_open()) << "Failed to open small.txt";
  
  infile >> G;
  infile.close();
  
  EXPECT_EQ(G.numVertices, 4);  // Verify correct number of vertices

  vector<int> previous;
  vector<int> distances = dijkstra_shortest_path(G, 0, previous);

  // Expected distances from node 0
  vector<int> expected_distances = {0, 3, 6, 1}; 
  EXPECT_EQ(distances, expected_distances);

  // Verify the shortest path to node 2
  vector<int> path = extract_shortest_path(distances, previous, 2);
  vector<int> expected_path = {0, 3, 1, 2};
  EXPECT_EQ(path, expected_path);
}

TEST(DijkstraTest, SmallGraph) {
    Graph new_graph;

    // Load the graph from file
    std::ifstream infile("../src/medium.txt");  // Ensmere this path is correct
    infile >> new_graph;
    infile.close();

    // Run Dijkstra’s algorithm from node 0
    vector<int> previous(new_graph.numVertices, -1);
    vector<int> distances = dijkstra_shortest_path(new_graph, 0, previous);

    // Expected shortest distances
    vector<int> expected_distances = {0, 5, 3, 12, 10, 2};

    // Expected paths
    vector<int> expected_path_to_2 = {0, 5, 2};  // Shortest path to node 2
    vector<int> expected_path_to_3 = {0, 5, 2, 3};  // Shortest path to node 3
    vector<int> expected_path_to_4 = {0, 5, 4};  // Shortest path to node 4

    // Assertions
    EXPECT_EQ(distances, expected_distances);

    EXPECT_EQ(extract_shortest_path(distances, previous, 2), expected_path_to_2);
    EXPECT_EQ(extract_shortest_path(distances, previous, 3), expected_path_to_3);
    EXPECT_EQ(extract_shortest_path(distances, previous, 4), expected_path_to_4);
}

TEST(Dijkstra, print){
  Graph G;
  std::ifstream infile("../src/medium.txt");
  infile >> G;
  infile.close();
  int destination = 3;
  vector<int> previous;
  vector<int> distances = dijkstra_shortest_path(G, 0, previous);
  vector<int> path = extract_shortest_path(distances, previous, destination);
  int total_cost = (distances[destination] == INF) ? -1 : distances[destination];
  testing::internal::CaptureStdout();
  print_path(path, total_cost);
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, "0 5 2 3\nTotal cost: 12\n");
}