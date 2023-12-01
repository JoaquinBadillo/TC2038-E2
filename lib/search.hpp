// search.hpp
#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <vector>
#include <limits>

namespace p3 {

    typedef std::pair<double, double> Point; 

 
    double euclideanDistanceSquared(double x1, double y1, double x2, double y2) {
        return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
    }

 
    std::pair<int, int> findClosestPair(const std::vector<Point>& points) {
        double minDistance = std::numeric_limits<double>::max();
        std::pair<int, int> closestPair = {-1, -1};

        for (int i = 0; i < points.size(); ++i) {
            for (int j = i + 1; j < points.size(); ++j) {
                double distance = euclideanDistanceSquared(points[i].first, points[i].second, points[j].first, points[j].second);
                if (distance < minDistance) {
                    minDistance = distance;
                    closestPair = {i, j};
                }
            }
        }

        return closestPair;
    }

    
    void findAndPrintClosestPair(int numberOfNodes) {
        std::vector<Point> points(numberOfNodes);


        for (int i = 0; i < numberOfNodes; ++i) {
            std::cout << "Enter coordinates for node " << i << " (format: x y): ";
            std::cin >> points[i].first >> points[i].second;
        }

        
        std::pair<int, int> closestPair = findClosestPair(points);

        
        std::cout << "Closest pair of points: Node " << closestPair.first 
                  << " (" << points[closestPair.first].first << ", " << points[closestPair.first].second << ") and Node " 
                  << closestPair.second << " (" << points[closestPair.second].first << ", " << points[closestPair.second].second << ")" << std::endl;
    }
}

#endif
