#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>

#include <opencv2/opencv.hpp>

template<typename PixelType>
using DataType = std::vector<std::vector<PixelType>>;

template<typename PixelType> //uchar->intensity, vector<uchar> rgb
class Image
{

    //using DataType = std::vector<std::vector<PixelType>>; //matrix

public:
    Image(){};

    void Read(const std::string& fileName);
    void Show();
    DataType<PixelType>& GetData();
    void SetData(const DataType<PixelType>& otherData);
    std::vector<std::vector<unsigned>> Histogram();
    std::size_t GetNumRows() const;
    std::size_t GetNumColumns() const;

private:

    DataType<PixelType> Data; // matriz de pixels

    std::size_t Rows{};
    std::size_t Columns{};

};

template<typename  PixelType>
void Image<PixelType>::Read(const std::string& fileName)
{

    cv::Mat image = cv::imread(fileName, cv::IMREAD_COLOR);

    if (!image.data)
    {
        std::cerr<<"No image data\n";
        return;
    }

    Rows = image.rows;
    Columns = image.cols;

    Data = DataType<PixelType>(Rows, std::vector<PixelType>(Columns, PixelType{}));

    uchar red, green, blue;
    for (unsigned r=0; r < Rows; ++r)
    {
        cv::Vec3b * row = image.ptr<cv::Vec3b>(r);
        for (unsigned c=0; c < Columns; ++c)
        {
            red =   row[c][2]; //B
            green = row[c][1]; //G
            blue =  row[c][0]; //R

            if constexpr (std::is_fundamental<PixelType>::value) //uchar, short, float (gray)
            {
                //Data[r][c] = static_cast<PixelType>((red + green + blue)/3);
                Data[r][c] = static_cast<PixelType>(0.2126*red + 0.7152*green + 0.0722*blue);
            }
            else //RGB LAB, channels...
            {
                //memoria
                Data[r][c][0] = static_cast<typename PixelType::ValueType>(red);
                Data[r][c][1] = static_cast<typename PixelType::ValueType>(green);
                Data[r][c][2] = static_cast<typename PixelType::ValueType>(blue);
            }


        }
    }

    //std::cout<<image.ptr<cv::Vec3b>(0)[0]<<"\n";
    //std::cout<<+Data[0][0][0]<<","<<+Data[0][0][1]<<","<<+Data[0][0][2]<<"\n";
    /*cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Image", image);
    cv::waitKey(0);*/

}



template<typename  PixelType>
DataType<PixelType>& Image<PixelType>::GetData()
{
    return this->Data;
}

template<typename  PixelType>
void Image<PixelType>::SetData(const DataType<PixelType>& otherData)
{
    Data = otherData;
    Rows = otherData.size();
    Columns = otherData[0].size();

    //std::cout<<"Rows: "<<Rows<<std::endl;
    //std::cout<<"Columns: "<<Columns<<std::endl;
}

template<typename  PixelType>
std::size_t Image<PixelType>::GetNumRows() const
{
    return Rows;
}

template<typename  PixelType>
std::size_t Image<PixelType>::GetNumColumns() const
{
    return Columns;
}

template<typename  PixelType>
void Image<PixelType>::Show()
{
    cv::Mat imageShow;
    if constexpr (std::is_fundamental<PixelType>::value) //uchar, short, float (gray)
    {
        imageShow = cv::Mat(Rows, Columns, CV_8UC1);
        for (unsigned r = 0; r < Rows; ++r)
        {
            PixelType* grayrow = imageShow.ptr<PixelType>(r);
            for (unsigned c = 0; c < Columns; ++c)
            {
                grayrow[c] = Data[r][c];
                //imageShow.at<PixelType>(r, c) = Data[r][c];
            }
        }


    }
    else //RGB LAB, channels...
    {
        imageShow = cv::Mat(Rows, Columns, CV_8UC3);
        for (unsigned r = 0; r < Rows; ++r)
        {
            cv::Vec3b* grayrow = imageShow.ptr<cv::Vec3b>(r);
            for (unsigned c = 0; c < Columns; ++c)
            {
                grayrow[c][2] = Data[r][c][0];
                grayrow[c][1] = Data[r][c][1];
                grayrow[c][0] = Data[r][c][2];
            }

        }
    }

    cv::namedWindow("Imagen Cargada", cv::WINDOW_AUTOSIZE);
    cv::imshow("Imagen Cargada", imageShow);
    cv::waitKey(0);

}

template<typename PixelType>
std::vector<std::vector<unsigned>> Image<PixelType>::Histogram()
{
    std::vector<std::vector<unsigned>> histogramValues;
    if constexpr (std::is_fundamental<PixelType>::value) //uchar, short, float (gray)
    {
        unsigned k = sizeof(PixelType)*8; //bit depth
        histogramValues = std::vector<std::vector<unsigned>>(1, std::vector<unsigned>(std::pow(2,k), 0)); //1 canal
        //std::cout<<std::pow(2,k)<<std::endl;
        for (unsigned r = 0; r < Rows; ++r)
        {
            for (unsigned c = 0; c < Columns; ++c)
            {
                PixelType i = Data[r][c];
                histogramValues[0][i]++; //Se coloca 0 porque solo hay un canal
            }
        }

    }
    else
    {
        unsigned k = 8; //bit depth cambiar para una mayor profundidad o indicar como parametro
        histogramValues = std::vector<std::vector<unsigned>>(3, std::vector<unsigned>(std::pow(2,k), 0)); //3 canales

        for (unsigned r = 0; r < Rows; ++r)
        {
            for (unsigned c = 0; c < Columns; ++c)
            {
                unsigned red = Data[r][c][0];

                unsigned green = Data[r][c][1];

                unsigned blue = Data[r][c][2];

                histogramValues[0][red]++; //Para cada canal
                histogramValues[1][green]++; //Para cada canal
                histogramValues[2][blue]++; //Para cada canal
            }
        }
    }
    return histogramValues;
}






#endif // IMAGE_H
