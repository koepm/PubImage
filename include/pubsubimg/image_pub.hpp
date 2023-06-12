#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include <opencv2/opencv.hpp>
#include <chrono>
//#include <memory>
//#include <functional>

class ImagePublisher : public rclcpp::Node
{
    public:
    ImagePublisher();

    private:
    void timer_callback();

    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    //cv::Mat image_;
    cv::Mat image_;
    cv::VideoCapture cap_;

};
