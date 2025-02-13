#include <gtest/gtest.h>
#include <Eigen/Dense>
#include <sophus/se3.hpp>

// Mock settings class to simulate getMinCos()
struct Settings {
    float min_cos;

    float getMinCos() const { return min_cos; }
};

// Global settings instance
Settings settings_;

// Mock function to compute cosine of ray parallax
float cosRayParallax(const Eigen::Vector3f& ray1, const Eigen::Vector3f& ray2) {
    return ray1.dot(ray2);
}

// Function to be tested
bool isValidParallax(const Eigen::Vector3f& xn1, const Eigen::Vector3f& xn2, 
                        const Sophus::SE3f& T1w, const Sophus::SE3f& T2w, 
                        const Eigen::Vector3f& x3D_1, const Eigen::Vector3f& x3D_2) {
    auto x_1 = T1w * x3D_1;
    auto x_2 = T2w * x3D_2;

    if (x_1[2] < 0.0 || x_2[2] < 0.0) return false;

    auto ray1 = (T1w.inverse().rotationMatrix() * xn1).normalized();
    auto ray2 = (T2w.inverse().rotationMatrix() * xn2).normalized();
    auto parallax = cosRayParallax(ray1, ray2);

    return parallax <= settings_.getMinCos();
}

// Unit tests
TEST(IsValidParallaxTest, NominalCase) {
    settings_.min_cos = 0.9f;

    Sophus::SE3f T1w(Eigen::Matrix3f::Identity(), Eigen::Vector3f(0, 0, 0));
    Sophus::SE3f T2w(Eigen::Matrix3f::Identity(), Eigen::Vector3f(1, 0, 0));

    Eigen::Vector3f xn1(1, 0, 1); xn1.normalize();
    Eigen::Vector3f xn2(0, 1, 1); xn2.normalize();
    Eigen::Vector3f x3D_1(0, 0, 1);
    Eigen::Vector3f x3D_2(1, 1, 1);

    EXPECT_TRUE(isValidParallax(xn1, xn2, T1w, T2w, x3D_1, x3D_2));
}

TEST(IsValidParallaxTest, NegativeZComponent) {
    settings_.min_cos = 0.9f;

    Sophus::SE3f T1w(Eigen::Matrix3f::Identity(), Eigen::Vector3f(0, 0, 0));
    Sophus::SE3f T2w(Eigen::Matrix3f::Identity(), Eigen::Vector3f(1, 0, 0));

    Eigen::Vector3f xn1(1, 0, 1); xn1.normalize();
    Eigen::Vector3f xn2(0, 1, 1); xn2.normalize();
    Eigen::Vector3f x3D_1(0, 0, -1);
    Eigen::Vector3f x3D_2(1, 1, -1);

    EXPECT_FALSE(isValidParallax(xn1, xn2, T1w, T2w, x3D_1, x3D_2));
}

TEST(IsValidParallaxTest, ParallaxTooSmall) {
    settings_.min_cos = 0.9f;

    Sophus::SE3f T1w(Eigen::Matrix3f::Identity(), Eigen::Vector3f(0, 0, 0));
    Sophus::SE3f T2w(Eigen::Matrix3f::Identity(), Eigen::Vector3f(0, 0, 0.001));

    Eigen::Vector3f xn1(1, 0, 1); xn1.normalize();
    Eigen::Vector3f xn2(1, 0, 1); xn2.normalize(); // Same direction
    Eigen::Vector3f x3D_1(0, 0, 1);
    Eigen::Vector3f x3D_2(1, 1, 1);

    EXPECT_FALSE(isValidParallax(xn1, xn2, T1w, T2w, x3D_1, x3D_2));
}

TEST(IsValidParallaxTest, DegenerateCase) {
    settings_.min_cos = 0.9f;

    Sophus::SE3f T1w(Eigen::Matrix3f::Identity(), Eigen::Vector3f(0, 0, 0));
    Sophus::SE3f T2w(Eigen::Matrix3f::Zero(), Eigen::Vector3f(0, 0, 0));

    Eigen::Vector3f xn1(1, 0, 1); xn1.normalize();
    Eigen::Vector3f xn2(0, 1, 1); xn2.normalize();
    Eigen::Vector3f x3D_1(0, 0, 1);
    Eigen::Vector3f x3D_2(1, 1, 1);

    EXPECT_FALSE(isValidParallax(xn1, xn2, T1w, T2w, x3D_1, x3D_2));
}

// Main entry point for tests
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}