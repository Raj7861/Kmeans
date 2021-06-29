#include<iostream>
#include <ctime>     
#include <fstream>   
#include <sstream>   
#include <vector>
#include<cmath>
#include<limits>

struct Point
{
    double x,y;
    int cluster;
    double minDistance;

    Point(){
        this -> x = 0.0;
        this -> y = 0.0;
        this -> cluster = -1;
        this->minDistance = std::numeric_limits<float>::infinity();
    }

    Point(double x, double y){
        this->x = x;
        this->y = y;
        this->cluster = -1;
        this->minDistance = std::numeric_limits<float>::infinity();
    }

    double distance(Point p){
        return sqrt(pow((p.x - x),2) + pow((p.x - x),2));
    }
};



int main(){
Point p1 = Point(0.0, 0.0);

std::cout<<p1.x<<std::endl;
return 0;
}
