#include <iostream>
#include <vector>
#include <cmath>
#include <random>

using namespace std;

// Data point structure
struct Point {
    double x, y;

    Point(double x, double y) : x(x), y(y) {}
};


double distance_squared(const Point& p1, const Point& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return dx * dx + dy * dy;
}

//initialize the cluster centroids 
vector<Point> kMeansPlusPlusInit(const vector<Point>& points, int k) {
    vector<Point> centroids;
    centroids.push_back(points[rand() % points.size()]);

    while (centroids.size() < k) {
        vector<double> minDistances(points.size(), numeric_limits<double>::max());
        double totalDistance = 0.0;

        for (size_t i = 0; i < points.size(); ++i) {
            for (const Point& centroid : centroids) {
                double dist = distance_squared(points[i], centroid);
                minDistances[i] = min(minDistances[i], dist);
            }
            totalDistance += minDistances[i];
        }

        // Choose a new centroid using weighted probability
        double randValue = rand() / (RAND_MAX * 1.0) * totalDistance;
        for (size_t i = 0; i < points.size(); ++i) {
            randValue -= minDistances[i];
            if (randValue <= 0.0) {
                centroids.push_back(points[i]);
                break;
            }
        }
    }

    return centroids;
}

// Function to perform the clustering
vector<int> kMeans(const vector<Point>& points, const vector<Point>& centroids) {
    vector<int> assignments(points.size(), 0);

    for (size_t i = 0; i < points.size(); ++i) {
        double minDistance = numeric_limits<double>::max();
        for (size_t j = 0; j < centroids.size(); ++j) {
            double dist = distance_squared(points[i], centroids[j]);
            if (dist < minDistance) {
                minDistance = dist;
                assignments[i] = j;
            }
        }
    }

    return assignments;
}

int main() {
    // Sample data points
    vector<Point> points = {
        Point(1.0, 2.0),
        Point(2.0, 3.0),
        Point(5.0, 8.0),
        Point(10.0, 12.0),
        Point(13.0, 15.0),
        Point(15.0, 20.0)
    };

    int k = 2; // Number of clusters

    // Initialize centroids 
    vector<Point> centroids = kMeansPlusPlusInit(points, k);

    // Perform clustering
    vector<int> assignments = kMeans(points, centroids);

    // Print the results
    cout << "Data points: " << endl;
    for (const Point& p : points) {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }

    cout << "Cluster centroids: " << endl;
    for (const Point& c : centroids) {
        cout << "(" << c.x << ", " << c.y << ")" << endl;
    }

    cout << "Assignments: " << endl;
    for (int cluster : assignments) {
        cout << cluster << " ";
    }
    cout << endl;

    return 0;
}
