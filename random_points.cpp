#include "random_points.h"


void RandomPoints::generateRandomImage(const int maxSize, const int minSize)
{
    m_maxX = randomNumber(maxSize, minSize);
    m_maxY = randomNumber(maxSize, minSize);
    generateBlankImage(m_maxX, m_maxY);
}


void RandomPoints::generateBlankImage(const int maxX, const int maxY)
{
    // From here: http://docs.opencv.org/2.4/doc/tutorials/core/mat_the_basic_image_container/mat_the_basic_image_container.html
    m_img = cv::Mat(maxY, maxX, CV_8UC4, cv::Scalar(0, 0, 0, 255));
}


void RandomPoints::generateRandomDetections(const int number)
{
    for (int i{}; i < number; ++i)
    {
        int x = randomNumber(m_maxX - 100, 100);
        int y = randomNumber(m_maxY - 100, 100);
        generateDetection(x, y);
    }
}


void RandomPoints::generateDetection(const int x, const int y)
{
    AprilTags::TagDetection detection{};
    detection.cxy.first = x;
    detection.cxy.second = y;
    m_randomDetections.push_back(detection);
}


void RandomPoints::writeRandomDetectionsToFile()
{
    m_outFile << m_numberOfPoints << "\n";
    m_outFile << m_maxX << " "  << m_maxY << "\n";
    for (auto point: m_randomDetections)
    {
        m_outFile << point.cxy.first << " " << point.cxy.second << "\n";
    }
    m_outFile.close();
}


void RandomPoints::pullRandomDetectionsFromFile()
{
    m_inFile >> m_numberOfPoints;
    m_inFile >> m_maxX;
    m_inFile >> m_maxY;
    for (int i{}; i < m_numberOfPoints; ++i)
    {
        int x, y;
        m_inFile >> x;
        m_inFile >> y;
        generateDetection(x, y);
    }
}


int RandomPoints::randomNumber(const int vMax, const int vMin)
{
    uint32_t maxVal{-1};
    static const double fraction = 1.0 / static_cast<double>(maxVal);
    return static_cast<int>(m_mersenne() * fraction * (vMax - vMin) + vMin);
}
