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

 
    Point findClosestPair(const std::vector<Point>& points) {
        std::string x_str;
        std::cout << "Choose the x coordinate: ";
        std::cin >> x_str;

        std::string y_str;
        std::cout << "Choose the y coordinate: ";
        std::cin >> y_str;

        Point point = std::make_pair(std::stod(x_str), std::stod(y_str));


        double minDistance = std::numeric_limits<double>::max();
        std::pair<double, double> closestPair = {-1.0, -1.0};

        for (int i = 0; i < points.size(); ++i) {
            double distance = euclideanDistanceSquared(points[i].first, points[i].second, point.first, point.second);
            if (distance < minDistance) {
                minDistance = distance;
                closestPair = points[i];
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
