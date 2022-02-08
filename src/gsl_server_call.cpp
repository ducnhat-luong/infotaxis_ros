#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <gsl_actionserver/gsl_action_msgAction.h>

int main (int argc, char **argv)
{
    ros::init(argc, argv, "Requesting_GSL");
    ros::NodeHandle private_nh("~");

    std::string method;
    private_nh.param<std::string>("method", method, "infotaxis");
  
    actionlib::SimpleActionClient<gsl_actionserver::gsl_action_msgAction> ac("gsl", true);
    ros::Duration(2).sleep();

    ROS_INFO("Waiting for action server to start.");
    ac.waitForServer(); //will wait for infinite time
    ROS_INFO("Action server started, sending goal.");

    // SIMULATE CALL
    gsl_actionserver::gsl_action_msgGoal goal;
    goal.gsl_method = method;
    ac.sendGoal(goal);

    //wait for the action to return
    bool finished_before_timeout = ac.waitForResult();

    if (finished_before_timeout)
    {
        actionlib::SimpleClientGoalState state = ac.getState();
        ROS_INFO("Action finished: %s",state.toString().c_str());
    }
    else
        ROS_INFO("Action did not finish before the time out.");

   //exit
    return 0;
}
