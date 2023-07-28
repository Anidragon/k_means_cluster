#include <ctime>
#include <vector>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <limits>

using namespace std;
float FLT_MAX = numeric_limits<float>::max();
struct Point {
  float x;
  float y;
  int cluster;
  float dist;

  Point() :
    x(0.0),
    y(0.0),
    cluster(-1),
    dist(FLT_MAX){}

  Point(float X, float Y) :
      x(X),
      y(Y),
      cluster(-1),
      dist(FLT_MAX){}

  float distCalc(Point n){
    return pow(n.x - x, 2) + pow(n.y - y, 2);

  }
};

vector<Point> allPoints;
float clusteredData[200] = {
    1.2, 1.5, 1.1, 1.3, 1.4, 1.2, 1.3, 1.1, 1.5, 1.4,
    8.5, 8.3, 7.9, 8.2, 7.8, 8.6, 8.1, 8.0, 8.4, 7.7,
    22.1, 4.9, 21.5, 5.3, 22.0, 5.0, 21.8, 5.1, 21.9, 5.2,
    14.8, 14.9, 14.4, 15.2, 15.1, 14.7, 14.5, 14.6, 14.3, 14.9,
    26.5, 5.9, 25.9, 5.8, 26.1, 5.7, 26.3, 5.6, 26.0, 5.5,
    14.3, 15.7, 14.6, 15.3, 14.5, 15.6, 14.4, 15.8, 14.7, 15.4,
    4.1, 5.6, 4.0, 5.5, 3.9, 5.7, 4.3, 5.4, 4.2, 5.6,
    24.9, 5.1, 25.1, 5.3, 24.8, 5.2, 25.0, 5.4, 25.2, 5.0,
    4.0, 4.0, 4.2, 3.9, 3.9, 4.2, 3.8, 4.1, 4.1, 4.3,
    14.9, 14.3, 15.0, 14.5, 14.8, 14.7, 14.6, 14.4, 14.5, 14.6,
    8.3, 7.9, 8.1, 8.5, 8.0, 7.8, 8.2, 8.6, 7.7, 8.4,
    25.5, 5.5, 25.2, 5.6, 25.3, 5.8, 25.4, 5.7, 25.1, 5.9,
    1.6, 1.8, 1.3, 1.7, 1.5, 1.6, 1.2, 1.9, 1.4, 1.7,
    5.5, 4.0, 5.2, 4.1, 5.4, 4.3, 5.3, 4.2, 5.1, 4.0,
    14.6, 15.2, 14.7, 15.3, 15.1, 15.4, 14.9, 15.0, 14.8, 15.5,
    21.7, 4.9, 22.1, 5.2, 21.9, 5.0, 21.8, 4.8, 21.5, 5.1,
    14.3, 15.5, 14.6, 15.7, 14.5, 15.6, 14.7, 15.3, 14.4, 15.8,
    4.1, 5.5, 4.2, 5.4, 4.0, 5.6, 3.9, 5.7, 4.3, 5.3,
    21.5, 5.1, 21.9, 4.8, 22.1, 5.3, 21.7, 4.9, 21.8, 5.0,
    14.6, 15.4, 14.5, 15.6, 14.4, 15.5, 14.3, 15.7, 14.7, 15.3,
};
inline void init_Points(int n, int Xmax, int Ymax)
{
  for(int i = 0; i < n; i++){
   //allPoints.push_back(Point((float)(rand()%Xmax),(float)(rand()%Ymax)));
    allPoints.push_back(Point(clusteredData[i*2],clusteredData[(i*2)+1]));
  }

}

vector<Point> centroids;
//pass points, num times to iterate algorithm, and number of clusters "k"
void kCluster(vector<Point>* points, int k, int steps)
{
  //set random centroids to start clustering
  for(int i = 0; i < k; i++){
    centroids.push_back(points->at(rand() % (allPoints.size())));
  }

  //cluster based on starting centroids
  for(vector<Point>::iterator i = begin(centroids);
      i != end(centroids); i++){

    int group = i - begin(centroids);
   for(vector<Point>::iterator j = points->begin();
        j != points->end(); j++){

      Point p = *j;
      float distance = i->distCalc(p);
      if(distance < p.dist){
        p.dist = distance;
        p.cluster = group;

      }
      *j = p;

    }

  }
  //points in each cluster
  vector<int> nPoints;
  //sum of position coordinates
  vector<float> sumX, sumY;
  for (int i = 0; i < k; i++) {
    nPoints.push_back(0);
    sumX.push_back(0.0);
    sumY.push_back(0.0);
  }
  for(int x = 0; x < steps; x++){
  // Iterate over points and update
  for (vector<Point>::iterator i = points->begin();
       i != points->end(); i++) {
    int clusterId = i->cluster;
    nPoints[clusterId] += 1;
    sumX[clusterId] += i->x;
    sumY[clusterId] += i->y;

    i->dist = FLT_MAX;  // reset distance
  }

  // Compute the new centroids
  for (vector<Point>::iterator c = begin(centroids);
       c != end(centroids); ++c) {
    int group = c - begin(centroids);
    c->x = sumX[group] / nPoints[group];
    c->y = sumY[group] / nPoints[group];
  }
 }

}

int main()
{
  srand(time(0));
  init_Points(100, 50, 50);
  std::cout <<"Before:"<<"\n";
  for(int i = 0; i < allPoints.size(); i++)
  {
    std::cout << "Point #" << i << ", (" << allPoints[i].x <<" , "<< allPoints[i].y << ")" << "\n";

  }
  kCluster(&allPoints, 8, 10000);
    std::cout <<"After:"<<"\n";
    for(int i = 0; i < allPoints.size(); i++)
      {
        std::cout << allPoints[i].x <<","<< allPoints[i].y << "," << allPoints[i].cluster<<"\n";
      }
    std::cout <<"Centroids:"<<"\n";
    for(int i = 0; i < centroids.size(); i++)
      {
        std::cout << " (" << centroids[i].x <<" , "<< centroids[i].y << ")" <<"Cluster: "<< centroids[i].cluster <<"\n";

      }


}
