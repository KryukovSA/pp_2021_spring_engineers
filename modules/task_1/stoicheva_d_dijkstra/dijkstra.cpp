// Copyright 2021 Stoicheva Darya
#include "../../../modules/task_1/stoicheva_d_dijkstra/dijkstra.h"

int find_unprocessed_point_with_min_distance(const std::vector<int>& graph,
    const std::vector<int>& distances, const std::vector<bool>& processed) {
    int found_point = -1;
    int found_min_distance = std::numeric_limits<int>::max();
    for (size_t point = 0;  point < processed.size(); point++) {
        if (!processed[point] && distances[point] < found_min_distance) {
            found_min_distance = distances[point];
            found_point = point;
        }
    }
    return found_point;
}

int process_unprocessed_point(const std::vector<int>& graph,
    std::vector<int>* distances,
    std::vector<bool>* processed, int current_point) {

    int min_distance = std::numeric_limits<int>::max();
    int min_distance_point = -1;
    for (size_t point = 0; point < processed->size(); point++) {
        int start_row_index = current_point * processed->size();
        int distance = graph[start_row_index + point];
        if (!(*processed)[current_point] && distance > 0) {
            int *dp = distances->data() + point;
            int *dcp = distances->data() + current_point;
            *dp = std::min(*dp, *dcp + distance);
            if (min_distance > *dp) {
                min_distance = *dp;
                min_distance_point = point;
            }
        }
    }
    (*processed)[current_point] = true;
    return min_distance_point;
}

std::vector<int> dijkstra(const std::vector<int>& graph, int start) {
    if (graph.size() == 0)
        throw "Error: empty graph";

    int points_count = static_cast<int>(sqrt(graph.size()));
    if (points_count * points_count != graph.size())
        throw "Error: incorrect graph";

    if (points_count == 1) {
        return std::vector<int>({ 0 });
    }

    int max_int = std::numeric_limits<int>::max();
    std::vector<int> distances = std::vector<int>(points_count, max_int);
    std::vector<bool> processed = std::vector<bool>(points_count, false);

    distances[start] = 0;

    int next_unprocessed_point = start;
    while (next_unprocessed_point >= 0) {
        next_unprocessed_point = process_unprocessed_point(graph,
                   &distances, &processed, next_unprocessed_point);
        if (next_unprocessed_point < 0) {
            next_unprocessed_point =
                find_unprocessed_point_with_min_distance(graph, distances,
                                                         processed);
        }
    }

    return distances;
}
