#include<iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>     
#include <fstream>
#include <cstdlib>   
#include <sstream>   
#include <vector>
#include <cmath>
#include <limits>
#include <vector>
#include <algorithm>
#include <string>
#include <mpi.h>



using namespace std;
struct Point
{
    double x,y;
    int cluster;
    double minDistance;

    Point(){
        this -> x = 0.0;
        this -> y = 0.0;
        this -> cluster = -1;
        this->minDistance = numeric_limits<float>::infinity();
    }

    Point(double x, double y){
        this->x = x;
        this->y = y;
        this->cluster = -1;
        this->minDistance = numeric_limits<float>::infinity();
    }

    double distance(Point p){
        return sqrt(pow((p.x - x),2) + pow((p.y - y),2));
    }
};


vector<Point> readcsv() {
    vector<Point> points;
    string line;
    ifstream file("dat.csv");

    while (getline(file, line)) {
        stringstream lineStream(line);
        string bit;
        double x, y;
        getline(lineStream, bit, ',');
        x = stof(bit);
        getline(lineStream, bit, '\n');
        y = stof(bit);

        points.push_back(Point(x, y));
    }
    return points;
}
void kMeansClustering(vector<Point>* points, int epochs, int k) {
    int n = points->size();

    // Randomly initialise centroids
    // The index of the centroid within the centroids vector
    // represents the cluster label.
    vector<Point> centroids;
    srand(time(0));
    for (int i = 0; i < k; ++i) {
        centroids.push_back(points->at(rand() % n));
    }

    for (int i = 0; i < epochs; ++i) {
        // For each centroid, compute distance from centroid to each point
        // and update point's cluster if necessary
        for (vector<Point>::iterator c = begin(centroids); c != end(centroids);
             ++c) {
            int clusterId = c - begin(centroids);
            
            for (vector<Point>::iterator it = points->begin();
                 it != points->end(); ++it) {
                Point p = *it;
                double dist = c->distance(p);
                if (dist < p.minDistance) {
                    p.minDistance = dist;
                    p.cluster = clusterId;
                }
                *it = p;
            }
        }

        // Create vectors to keep track of data needed to compute means
        vector<int> nPoints;
        vector<double> sumX, sumY;
        for (int j = 0; j < k; ++j) {
            nPoints.push_back(0);
            sumX.push_back(0.0);
            sumY.push_back(0.0);
        }
        
        // Iterate over points to append data to centroids
        for (vector<Point>::iterator it = points->begin(); it != points->end();
             ++it) {
                
            int clusterId = it->cluster;
            nPoints[clusterId] += 1;
            sumX[clusterId] += it->x;
            sumY[clusterId] += it->y;

            it->minDistance = numeric_limits<float>::infinity();  // reset distance
        }
        // Compute the new centroids
        for (vector<Point>::iterator c = begin(centroids); c != end(centroids);
             ++c) {
            int clusterId = c - begin(centroids);
            c->x = sumX[clusterId] / nPoints[clusterId];
            c->y = sumY[clusterId] / nPoints[clusterId];
        }
    }

    // Write to .txt
    ofstream myfile; 
    myfile.open("output.txt");
    myfile << "x, y, c" << endl;

    for (vector<Point>::iterator it = points->begin(); it != points->end();
         ++it) {
        myfile << it->x << ", " << it->y << " , " << it->cluster << endl;
    }
    myfile.close();
}


int main(){




vector<Point>points;
srand((unsigned) time(0));
for(int i = 0;i<20;i++){
int r1 = rand()%20;
int r2 = rand()%20;
Point p(r1,r2);
points.push_back(p);
}

for(auto i: points){
cout << i.x << " "<< i.y <<endl;
}
kMeansClustering(&points, 100, 3); 

return 0;
}
