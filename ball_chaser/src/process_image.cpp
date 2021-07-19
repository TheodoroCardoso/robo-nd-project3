#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    // Call the safe_move service and pass the requested joint angles
    if (!client.call(srv))
        ROS_ERROR("Failed to call service command_robot");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;
    bool found_ball = false;
    double ball_center_x;
    int i, j;
    static int section = 0;

    // DONE: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera
    for (i = 0; i < img.height * img.step; i+=3) 
    {
        if (img.data[i] == white_pixel && img.data[i+1] == white_pixel && img.data[i+2] == white_pixel) 
        {
            j = i+3;
            while (img.data[j] == white_pixel && img.data[j+1] == white_pixel && img.data[j+2] == white_pixel
            && (j-i) < (img.step - (i % img.height))) // This second line ensures single row centroid search under any conditions
            {
                j+=3;
            }
            found_ball = true;
            break;
        }
    }
    if (found_ball)
    {
        // Average i and j to get the center pixel. Get the remainder to ignore the height since only the horizontal distance matters.    
        ball_center_x = (((i+j)/2) % img.step);
        //ROS_INFO_STREAM("i = " + std::to_string(i) + " j = " + std::to_string(j) + " h = " + std::to_string(img.height) + " bc_x= " + std::to_string(ball_center_x));
        
        // Get the center distance in absolute values.
        ball_center_x = (ball_center_x / img.step);
        //ROS_INFO_STREAM("step = " + std::to_string(img.step) + " bc_x= " + std::to_string(ball_center_x));

        if (ball_center_x < 0.33 && section != 1) // ball in the left
        {
            drive_robot(0.2,0.5);
            section = 1;
        } 
        else if (ball_center_x > 0.66 && section != 3) // ball in the right
        {
            drive_robot(0.2,-0.5);
            section = 3;
        }
        else if (ball_center_x >= 0.33 && ball_center_x <= 0.66 && section != 2)
        {
            drive_robot(0.2,0); // ball in the middle
            section = 2;
        }        
    }
    else if (section != 0)
    {
        drive_robot(0,0);
        section = 0;
    }    
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
