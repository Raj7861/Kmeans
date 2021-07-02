#include<iostream>
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
};

double distance(double x1, double y1, double x2, double y2){
  return abs(x1 - x2) + abs(y1 - y2);
}

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
    //srand(time(0));
    centroids.push_back(points->at(0));
    centroids.push_back(points->at(3));
    centroids.push_back(points->at(6));
    int nc = centroids.size();

    for (int i = 0; i < k; ++i) {
        //centroids.push_back(points->at(rand() % 10));
        cout<<"Checking -> "<<centroids[i].x<<" "<<centroids[i].y<<endl;
    }


    for (int ii = 0; ii < epochs; ++ii) {
        // For each centroid, compute distance from centroid to each point
        // and update point's cluster if necessary
        for (int i = 0; i < n; ++i) {
             
            for (int it = 0; it<nc ; ++it) {
                  
                 double dist = distance(centroids[it].x,centroids[it].y,points->at(i).x ,points->at(i).y); 
                if (dist < points->at(i).minDistance) {
                       
                     points->at(i).minDistance = dist;
                     points->at(i).cluster = it;
                    
                }
         
            }
    
           
        }
     
        vector<int> nPoints; 
        vector<double> new_cX, new_cY;

        for (int j = 0; j < k; ++j) {
            nPoints.push_back(0);
            new_cX.push_back(0.0);
            new_cY.push_back(0.0);
        }
        for (int i = 0; i < n; ++i) {
        
            int c_id = points->at(i).cluster;
            nPoints[c_id] += 1;
            new_cX[c_id] += points->at(i).x;
            new_cY[c_id] += points->at(i).y; 
            points->at(i).minDistance = numeric_limits<float>::infinity();  // reset distance
        }
        
        // Compute the new centroids
        for (int i = 0; i < nc;++i) {
            centroids[i].x = new_cX[i] / nPoints[i];
            centroids[i].y = new_cY[i] / nPoints[i];
        }
    }

   // Write to .txt
    ofstream myfile; 
    myfile.open("output555.txt");
    myfile << "x, y, i" << endl;

    for (int it = 0; it < n ;++it) {
        myfile << points->at(it).x << ", " << points->at(it).y << " , " << points->at(it).cluster<< endl;
    }

    myfile.close();
}


int main(){

vector<Point>points;
// //srand((unsigned) time(0));
// for(int i = 0;i<10;i++){
// int r1 = rand()%10;
// int r2 = rand()%10;
// Point p(r1,r2);
// points.push_back(p);
// }
points.push_back(Point(2,10));
points.push_back(Point(2,5));
points.push_back(Point(8,4));
points.push_back(Point(5,8));
points.push_back(Point(7,5));
points.push_back(Point(6,4));
points.push_back(Point(1,2));
points.push_back(Point(4,9));

for(auto i: points){
cout << i.x << " "<< i.y <<endl;
}
kMeansClustering(&points, 1, 3); 

return 0;
}
