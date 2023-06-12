#include "pubsubimg/image_sub.hpp"
#include "opencv2/highgui/highgui.hpp"

ImageSubscriber::ImageSubscriber()
: Node("image_subscriber")
{
    subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
        "image", 10,
        std::bind(&ImageSubscriber::image_callback, this, std::placeholders::_1)
    );
}

void ImageSubscriber::image_callback(const sensor_msgs::msg::Image::SharedPtr msg)
{
    cv_bridge::CvImagePtr cv_ptr;

    try
    {
        cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
        //cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");

    }
    catch(cv_bridge::Exception &e)
    {
        RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
        return;
    }

    cv::Mat gray_image;
    cv::cvtColor(cv_ptr->image, cv_ptr->image, cv::COLOR_BGR2GRAY);
    cv::imshow("gray", gray_image);
    cv::waitKey(1);
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ImageSubscriber>());
    rclcpp::shutdown();
    return 0;
}