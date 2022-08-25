#ifndef RGB_H
#define RGB_H

#include <vector>
#include <iostream>
#include <cmath>

template<typename Type=unsigned char> //deep
class RGB //Pixel//Color
{
public:
    RGB();
    RGB(Type value);
    RGB(Type r, Type g, Type b);

    const Type& operator[](unsigned index) const {return Channels[index];}
    Type& operator[](unsigned index) {return Channels[index];}

    using ValueType = Type;

    //Sobrecarga de operadores
    RGB<Type> operator+ (const Type& a)
    {
        float depth = sizeof(Type)*8;
        float values = std::pow(2, depth);
        //std::cout<<values<<std::endl;

        RGB<Type> result;

        //Restriccion cuando se pasa de los valores permitidos
        for(unsigned i = 0; i < result.Channels.size(); ++i)
        {
            float temp = Channels[i] + a;
            result.Channels[i] = (temp < values) ? temp : values-1;
                //std::cout<<"Hola"<<std::endl;
        }
        return result;
    }

    RGB<Type> operator- (const Type& a)
    {

        RGB<Type> result;

        //Restriccion cuando se pasa de los valores permitidos
        for(unsigned i = 0; i < result.Channels.size(); ++i)
        {
            float temp = Channels[i] - a;
            result.Channels[i] = (temp > 0) ? temp : 0;
        }
        return result;
    }

    RGB<Type> operator* (const Type& a)
    {
        float depth = sizeof(Type)*8;
        float values = std::pow(2, depth);
        //std::cout<<values<<std::endl;

        RGB<Type> result;

        //Restriccion cuando se pasa de los valores permitidos
        for(unsigned i = 0; i < result.Channels.size(); ++i)
        {
            float temp = Channels[i] * a;
            result.Channels[i] = (temp < values) ? temp : values-1;
                //std::cout<<"Hola"<<std::endl;
        }
        return result;
    }

    RGB<Type> operator/ (const Type& a)
    {
        RGB<Type> result;
        for(unsigned i = 0; i < result.Channels.size(); ++i)
        {
            float temp = (a == 0) ? Channels[i] : Channels[i]/a;
            result.Channels[i] = temp;
        }
        return result;
    }

    //Sobrecarga de operadores pixel wise
    RGB<Type> operator+ (const RGB<Type>& other)
    {
        float depth = sizeof(Type)*8;
        float values = std::pow(2, depth);
        //std::cout<<values<<std::endl;

        RGB<Type> result;

        //Restriccion cuando se pasa de los valores permitidos
        for(unsigned i = 0; i < result.Channels.size(); ++i)
        {
            float temp = Channels[i] + other.Channels[i];
            result.Channels[i] = (temp < values) ? temp : values-1;
                //std::cout<<"Hola"<<std::endl;
        }
        return result;
    }

    RGB<Type> operator- (const RGB<Type>& other)
    {

        RGB<Type> result;

        //Restriccion cuando se pasa de los valores permitidos
        for(unsigned i = 0; i < result.Channels.size(); ++i)
        {
            float temp = Channels[i] - other.Channels[i];
            result.Channels[i] = (temp > 0) ? temp : 0;
        }
        return result;
    }

    RGB<Type> operator* (const RGB<Type>& other)
    {
        float depth = sizeof(Type)*8;
        float values = std::pow(2, depth);
        //std::cout<<values<<std::endl;

        RGB<Type> result;

        //Restriccion cuando se pasa de los valores permitidos
        for(unsigned i = 0; i < result.Channels.size(); ++i)
        {
            float temp = Channels[i] * other.Channels[i];
            result.Channels[i] = (temp < values) ? temp : values-1;
                //std::cout<<"Hola"<<std::endl;
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream&  output, const RGB<Type>& rgb)
    {
        output<<"("<<static_cast<int>(rgb.Channels[0])<<", "<<static_cast<int>(rgb.Channels[1])<<", "<<static_cast<int>(rgb.Channels[2])<<")";
        return output;
    }

private:

    std::vector<Type> Channels{}; //vector size 3

};

template<typename Type>
RGB<Type>::RGB(): Channels{std::vector<Type>(3, {})}
{

}

template<typename Type>
RGB<Type>::RGB(Type value): Channels{std::vector<Type>(3, value)}
{

}

template<typename Type>
RGB<Type>::RGB(Type r, Type g, Type b): Channels{r, g, b}
{

}

#endif // RGB_H
