#include "pubsubimg/image_pub.hpp"
#include "cv_bridge/cv_bridge.h"

ImagePublisher::ImagePublisher()
: Node("image_publisher"), cap_(4)
{
    publisher_ = this->create_publisher<sensor_msgs::msg::Image>("image", 10);
    timer_ = this->create_wall_timer(std::chrono::milliseconds(0), std::bind(&ImagePublisher::timer_callback, this));

}

void ImagePublisher::timer_callback()
{
    cap_.read(image_);

    if (!image_.empty())
    {
        std_msgs::msg::Header header;
        header.stamp = this->now();  // 현재 시간으로 설정합니다.
        header.frame_id = "image";  // frame_id를 원하는 값으로 설정합니다.
        auto msg = cv_bridge::CvImage(header, "bgr8", image_).toImageMsg();
        publisher_ ->publish(*msg);
    }
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ImagePublisher>());
    rclcpp::shutdown();
    return 0;
}
