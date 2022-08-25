#include <iostream>
#include "Image.h"
#include "RGB.h"
#include<vector>

template<typename PixelType>
using DataType = std::vector<std::vector<PixelType>>;

const double pi = std::acos(-1);

template<typename PixelType>
void imprimir(DataType<PixelType> imagen)
{
    for(unsigned i = 0; i < imagen.size(); ++i)
    {
        for(unsigned j = 0; j < imagen[i].size(); ++j)
        {
            //std::cout<<imagen[i][j]<<" ";
            std::cout<<static_cast<int>(imagen[i][j])<<" ";
        }
        std::cout<<std::endl;
    }
}

template<typename PixelType>
DataType<PixelType> paddingConstantValue(DataType<PixelType>& imagen, unsigned paddingSize, uchar value = 0)
{
    std::size_t Rows = imagen.size();
    std::size_t Columns = imagen[0].size();

    std::size_t paddingRows = imagen.size() + 2*paddingSize;
    std::size_t paddingColumns = imagen[0].size() + 2*paddingSize;

    DataType<PixelType> paddedImage = DataType<PixelType>(paddingRows, std::vector<PixelType>(paddingColumns, PixelType{value}));

    for(unsigned i = 0; i < Rows; ++i)
    {
        for(unsigned j = 0; j < Columns; ++j)
        {
            paddedImage[i+paddingSize][j+paddingSize] = imagen[i][j];
        }
    }
    return paddedImage;
}

template<typename PixelType>
DataType<PixelType> paddingMirror(DataType<PixelType>& imagen, unsigned paddingSize)
{
    std::size_t Rows = imagen.size();
    std::size_t Columns = imagen[0].size();

    std::size_t paddingRows = Rows + 2*paddingSize;
    std::size_t paddingColumns = Columns + 2*paddingSize;

    DataType<PixelType> paddedImage = DataType<PixelType>(paddingRows, std::vector<PixelType>(paddingColumns, PixelType{0}));

    for(unsigned i = 0; i < Rows; ++i)
    {
        for(unsigned j = 0; j < Columns; ++j)
        {
            paddedImage[i+paddingSize][j+paddingSize] = imagen[i][j];
        }
    }

    unsigned distanceMirror = 1;

    //top padding
    distanceMirror = 1;
    for(unsigned i = paddingSize; i > 0; --i)
    {

        for(unsigned j = paddingSize; j < Columns+paddingSize; ++j)
        {
            paddedImage[i-1][j] = paddedImage[i+distanceMirror-1][j];
        }
        distanceMirror+=2;
    }

    //bottom padding
    distanceMirror = 1;
    for(unsigned i = paddingRows-paddingSize; i < paddingRows; ++i)
    {
        for(unsigned j = paddingSize; j < Columns+paddingSize; ++j)
        {
            paddedImage[i][j] = paddedImage[i-distanceMirror][j];
        }
        distanceMirror+=2;
    }

    //left padding
    distanceMirror = 1;
    for(unsigned j = paddingSize; j > 0; --j)
    {
        for(unsigned i = 0; i < paddingRows; ++i)
        {
             //std::cout<<i<<","<<j+distanceMirror-1<<std::endl;
             paddedImage[i][j-1] = paddedImage[i][j+distanceMirror-1];
        }
        distanceMirror+=2;
    }

    // right padding
    distanceMirror = 1;
    for(unsigned j = paddingColumns - paddingSize; j < paddingColumns; ++j)
    {
        for(unsigned i = 0; i < paddingRows; ++i)
        {
             paddedImage[i][j] = paddedImage[i][j-distanceMirror];
        }
        distanceMirror+=2;
    }

    return paddedImage;
}

template<typename PixelType>
DataType<PixelType> paddingExpanded(DataType<PixelType>& imagen, unsigned paddingSize)
{
    std::size_t Rows = imagen.size();
    std::size_t Columns = imagen[0].size();

    std::size_t paddingRows = Rows + 2*paddingSize;
    std::size_t paddingColumns = Columns + 2*paddingSize;

    DataType<PixelType> paddedImage = DataType<PixelType>(paddingRows, std::vector<PixelType>(paddingColumns, PixelType{0}));

    for(unsigned i = 0; i < Rows; ++i)
    {
        for(unsigned j = 0; j < Columns; ++j)
        {
            paddedImage[i+paddingSize][j+paddingSize] = imagen[i][j];
        }
    }

    //top padding
    for(unsigned i = paddingSize; i > 0; --i)
    {

        for(unsigned j = paddingSize; j < Columns+paddingSize; ++j)
        {
            paddedImage[i-1][j] = paddedImage[i][j];
        }
    }

    //bottom padding
    for(unsigned i = paddingRows-paddingSize; i < paddingRows; ++i)
    {
        for(unsigned j = paddingSize; j < Columns+paddingSize; ++j)
        {
            paddedImage[i][j] = paddedImage[i-1][j];
        }
    }

    //left padding
    for(unsigned j = paddingSize; j > 0; --j)
    {
        for(unsigned i = 0; i < paddingRows; ++i)
        {
             paddedImage[i][j-1] = paddedImage[i][j];
        }
    }

    // right padding
    for(unsigned j = paddingColumns - paddingSize; j < paddingColumns; ++j)
    {
        for(unsigned i = 0; i < paddingRows; ++i)
        {
             paddedImage[i][j] = paddedImage[i][j-1];
        }
    }
    return paddedImage;
}

template<typename PixelType>
DataType<PixelType> paddingPeriodicRepetitions(DataType<PixelType>& imagen, unsigned paddingSize)
{
    std::size_t Rows = imagen.size();
    std::size_t Columns = imagen[0].size();

    std::size_t paddingRows = Rows + 2*paddingSize;
    std::size_t paddingColumns = Columns + 2*paddingSize;

    DataType<PixelType> paddedImage = DataType<PixelType>(paddingRows, std::vector<PixelType>(paddingColumns, PixelType{0}));

    for(unsigned i = 0; i < Rows; ++i)
    {
        for(unsigned j = 0; j < Columns; ++j)
        {
            paddedImage[i+paddingSize][j+paddingSize] = imagen[i][j];
        }
    }

    //top padding
    for(unsigned i = 0; i < paddingSize; ++i)
    {
        for(unsigned j = paddingSize; j < Columns+paddingSize; ++j)
        {
            paddedImage[i][j] = paddedImage[i+Rows][j];
        }
    }

    //bottom padding
    for(unsigned i = paddingRows-paddingSize; i < paddingRows; ++i)
    {
        for(unsigned j = paddingSize; j < Columns+paddingSize; ++j)
        {
            paddedImage[i][j] = paddedImage[i-Rows][j];
        }
    }

    //left padding
    for(unsigned j = 0; j < paddingSize; ++j)
    {
        for(unsigned i = 0; i < paddingRows; ++i)
        {
             paddedImage[i][j] = paddedImage[i][j+Columns];
        }
    }

    // right padding
    for(unsigned j = paddingColumns - paddingSize; j < paddingColumns; ++j)
    {
        for(unsigned i = 0; i < paddingRows; ++i)
        {
             paddedImage[i][j] = paddedImage[i][j-Columns];
        }
    }

    return paddedImage;
}

// Padding, Kernel K, Factor de scala S, padding, valor de padding(solo caso1)
template<typename PixelType>
DataType<PixelType> convolution(DataType<PixelType>& imagen, DataType<float> kernel, int scale, std::string padding, unsigned valuePadding = 0)
{
    std::size_t Rows = imagen.size();
    std::size_t Columns = imagen[0].size();

    DataType<PixelType> imagePadding;
    DataType<PixelType> result = DataType<PixelType>(Rows, std::vector<PixelType>(Columns, PixelType{0}));

    //Tamanio del padding
    unsigned paddingSize = kernel.size()/2;

    //Padding selection
    // Padding: constant, expanded, mirror, repetition
    imagePadding = paddingMirror(imagen, paddingSize);
    if(padding == "constant")
    {imagePadding = paddingConstantValue(imagen, paddingSize, valuePadding);}
    else if(padding == "expanded")
    {imagePadding = paddingExpanded(imagen, paddingSize);}
    else if(padding == "mirror")
    {imagePadding = paddingMirror(imagen, paddingSize);}
    else if(padding == "repetition")
    {imagePadding = paddingPeriodicRepetitions(imagen, paddingSize);}

    for(unsigned i = 0; i < Rows; ++i)
    {
        for(unsigned j = 0; j < Columns; ++j)
        {
            PixelType m{0};
            //for para el kernel
            for(unsigned h = 0; h < kernel.size(); ++h)
            {
                for(unsigned k = 0; k < kernel[h].size(); ++k)
                {
                    m = m + (imagePadding[h+i][k+j] * kernel[h][k]/scale);
                }

            }
            result[i][j] = m;
        }
    }

    return result;
}

// Solo para escala de grises
std::vector<uchar> LocalBinaryPattern(DataType<uchar>& imagen, float radio, int numNeightbors)
{
    std::size_t Rows = imagen.size();
    std::size_t Columns = imagen[0].size();

    DataType<uchar> imagePadding;
    DataType<uchar> result = DataType<uchar>(Rows, std::vector<uchar>(Columns, 0));

    float x = 1;
    float y = 1;
    float step = 360 / numNeightbors;
    float angle = 0;
    uchar min = 0;
    uchar max = 0;

    //Se hace un padding para las esquinas
    unsigned paddingSize = std::ceil(radio); //En caso de tener un radio float
    imagePadding = paddingConstantValue(imagen, paddingSize, 0);

    for(unsigned i = 0; i < Rows; ++i)
    {
        for(unsigned j = 0; j < Columns; ++j)
        {
            uchar sum = 0.0f;
            angle = 0;
            for(unsigned h = 0; h < numNeightbors; ++h)
            {
                // cos y sin, necesitan radianes, se le aumenta el radio para evitar posiciones negativas
                x = i + std::round(radio * std::cos(angle * pi / 180) + radio);
                y = j + std::round(radio * std::sin(angle * pi / 180) + radio);

                sum += ((imagePadding[x][y] - imagen[i][j]) >= 0 ? 1.0f : 0.0f) * std::pow(2, h);
                angle = angle + step;
            }
            result[i][j] = sum;
            //Hallar el minimo y el maximo
            min = std::min(sum, min);
            max = std::max(sum, max);
        }
    }

    std::vector<uchar> histogram = std::vector<uchar>(max-min, 0);

    for(unsigned i = 0; i < Rows; ++i)
    {
        for(unsigned j = 0; j < Columns; ++j)
        {
            histogram[result[i][j] - min]++;
        }
    }

    Image<uchar> image2;
    image2.SetData(result);
    image2.Show();

    return histogram;
}

int main()
{

    Image<uchar> image;
    image.Read("/home/marco/ProyectosQt/OpenCV_Example/image.jpg");
    image.Show();

    // LocalBinaryPattern(imagen, radio, vecinos);
    std::vector<uchar> histogram = LocalBinaryPattern(image.GetData(), 1, 8);

    for(unsigned i = 0; i < histogram.size(); ++i)
    {
        std::cout<<(unsigned)histogram[i]<<" ";
    }
    std::cout<<std::endl;

    return 0;
}
