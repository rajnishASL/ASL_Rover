#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

float computeheading(vector<float> waypoint, vector<float> current_pos){
    // waypoint = {x,y}, current_pos = {x_curr, y_curr}
    float x = waypoint[0];
    float y = waypoint[1];
    float x_curr = current_pos[0];
    float y_curr = current_pos[1];
    float heading = atan2((y-y_curr), (x-x_curr));
    return heading;
}

float computeVelocity(vector<float> waypoint, vector<float> current_pos, float r_outer_proximity, float Vmax){
    // waypoint = {x,y}, current_pos = {x_curr, y_curr}
    int r = 0;
    r = sqrt(pow(waypoint[0]-current_pos[0],2) + pow(waypoint[1]-current_pos[1],2));
    if (r<=r_outer_proximity){
        return 0.1*r; // if the rover has reached outer Proximity circle, slow down the vehicle
    }
    else{
        return Vmax;
    }
}

bool waypoint_switch(vector<float> waypoint, vector<float> current_pos, float r_inner_proximity){
    // Function to check if the rover has reached the inner Proximity circle. Switch the waypoint if yes.
    int r = 0;
    r = sqrt(pow(waypoint[0]-current_pos[0],2) + pow(waypoint[1]-current_pos[1],2));
    if (r<=r_inner_proximity){
        return true;
    }
    else{
        return false;
    }
}

int main(){
    // Input a 2d-vector of way-points (from User)
    vector<vector<float>> waypoints = {{4.2, 4}, {8,8},  {6, 2.2}};
    
    // Input a 1d-vector of current pose (x,y) (from navigation/encoder module)
    vector<float> current_pos = {4,4};
    
    // Radius of Outer Proximity Circle
    float r_outer_proximity = 2;
    
    // Radius of Inner Proximity Circle
    float r_inner_proximity = 0.5; 
    
    // Maximum forward Velocity of the rover
    float Vmax = 10;
    
    // Output commanded heading and commanded forward velocity
    float theta_com, vel_com;
    
    // Initialize the index of waypoint as 0
    int waypointIndex = 0;
    
    while (waypointIndex<waypoints.size()){
        vector<float> waypoint = waypoints[waypointIndex];
        theta_com = computeheading(waypoint, current_pos);
        vel_com = computeVelocity(waypoint, current_pos, r_outer_proximity, Vmax);
        cout << theta_com << " , " << vel_com << endl;
        if (waypoint_switch(waypoint, current_pos, r_inner_proximity)){
            waypointIndex +=1;
        }
    }

}

