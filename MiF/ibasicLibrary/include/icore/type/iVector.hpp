/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iVector.hpp
* @创建时间：2022.8.29.21:22
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
*
*
*
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once

#include <icore/family/imacrofamily.h>
#include <icore/math/iMath.hpp>
#include <vector>
#include <iostream>

#undef max
#undef min

SPACE(i)
{
    SPACE(core)
    {
        SPACE(vector)
        {

            template <class T>
            bool isEmpty(std::vector<T> v)
            {
                return (v.size() == 0);
            }


            template <class T>
            bool containsOnlyZeros(std::vector<T> v)
            {
                if (!isEmpty(v))
                {
                    for (int i = 0; i < v.size(); i++)
                    {
                        if (v[i] != 0)
                        {
                            return false;
                        }
                    }

                    return true;
                }
                else
                {
                    throw std::invalid_argument("Received empty vector when checking if vector contains only zeros");
                }
            }


            template <class T>
            bool isAllPositiveOrZero(std::vector<T> v)
            {
                if (!isEmpty(v))
                {
                    for (int i = 0; i < v.size(); i++)
                    {
                        if (v[i] < 0)
                        {
                            return false;
                        }
                    }

                    return true;
                }
                else
                {
                    throw std::invalid_argument("Received empty vector when checking if vector is all positive");
                }
            }


            template <class T>
            bool isAllNegativeOrZero(std::vector<T> v)
            {
                if (!isEmpty(v))
                {
                    for (int i = 0; i < v.size(); i++)
                    {
                        if (v[i] > 0)
                        {
                            return false;
                        }
                    }

                    return true;
                }
                else
                {
                    throw std::invalid_argument("Received empty vector when checking if vector is all negative");
                }
            }


            template <class T>
            bool contains(std::vector<T> v, T element)
            {
                for (int i = 0; i < v.size(); i++)
                {
                    if (v[i] == element)
                    {
                        return true;
                    }
                }

                return false;
            }



            template <class T>
            T max(std::vector<T> v)
            {
                if (!isEmpty(v))
                {
                    T maxVal = v[0];

                    for (int i = 1; i < v.size(); i++)
                    {
                        if (v[i] > maxVal)
                        {
                            maxVal = v[i];
                        }
                    }

                    // return the maxVal
                    return maxVal;
                }
                else
                {
                    throw std::invalid_argument("Received empty vector when calculating max");
                }
            }


            template <class T>
            int maxIndex(std::vector<T> v)
            {
                if (!isEmpty(v))
                {
                    T maxVal = v[0];
                    int maxIndex = 0;

                    for (int i = 1; i < v.size(); i++)
                    {
                        if (v[i] > maxVal)
                        {
                            maxVal = v[i];

                            maxIndex = i;
                        }
                    }

                    return maxIndex;
                }
                else
                {
                    throw std::invalid_argument("Received empty vector when calculating max index");
                }
            }


            template <class T>
            T min(std::vector<T> v)
            {
                if (!isEmpty(v))
                {
                    T minVal = v[0];

                    for (int i = 1; i < v.size(); i++)
                    {
                        if (v[i] < minVal)
                        {
                            minVal = v[i];
                        }
                    }

                    return minVal;
                }
                else
                {
                    throw std::invalid_argument("Received empty vector when calculating min");
                }
            }


            template <class T>
            int minIndex(std::vector<T> v)
            {
                if (!isEmpty(v))
                {
                    T minVal = v[0];
                    int minIndex = 0;

                    for (int i = 1; i < v.size(); i++)
                    {
                        if (v[i] < minVal)
                        {
                            minVal = v[i];

                            minIndex = i;
                        }
                    }

                    return minIndex;
                }
                else
                {
                    throw std::invalid_argument("Received empty vector when calculating minIndex");
                }
            }


            template <class T>
            void printVector(std::vector<T> v)
            {
                for (int i = 0; i < v.size(); i++)
                {
                    std::cout << v[i] << std::endl;
                }
            }


            template <class T>
            T getLastElement(std::vector<T> v)
            {
                if (v.size() > 0)
                {
                    return v[v.size() - 1];
                }
                else
                {
                    throw std::invalid_argument("Attempted to get last element of empty vector");
                }
            }


            template <class T>
            T getFirstElement(std::vector<T> v)
            {
                if (v.size() > 0)
                {
                    return v[0];
                }
                else
                {
                    throw std::invalid_argument("Attempted to get first element of empty vector");
                }
            }


            template <class T>
            std::vector<T> getEvenElements(std::vector<T> v)
            {
                return getEveryNthElementStartingFromK(v, 2, 0);
            }


            template <class T>
            std::vector<T> getOddElements(std::vector<T> v)
            {
                return getEveryNthElementStartingFromK(v, 2, 1);
            }


            template <class T>
            std::vector<T> getEveryNthElementStartingFromK(std::vector<T> v, int n, int k)
            {
                if ((n >= v.size()) || (n >= v.size()))
                {
                    throw std::invalid_argument("Invalid arguments for getEveryNthElementStartingFromK()");
                }
                else
                {
                    std::vector<T> result;

                    int i = k;

                    while (i < v.size())
                    {
                        result.push_back(v[i]);
                        i += n;
                    }

                    return result;
                }
            }


            template <class T>
            void fillVectorWith(Ref<std::vector<T>> v, T element)
            {
                for (int i = 0; i < v.size(); i++)
                {
                    v[i] = element;
                }
            }


            template <class T>
            int countOccurrencesOf(std::vector<T> v, T element)
            {
                int count = 0;

                for (int i = 0; i < v.size(); i++)
                {
                    if (v[i] == element)
                    {
                        count++;
                    }
                }

                return count;
            }


            template <class T>
            T sum(std::vector<T> v)
            {
                T sumVal = 0;

                for (int i = 0; i < v.size(); i++)
                {
                    sumVal += v[i];
                }

                return sumVal;
            }


            template <class T>
            double product(std::vector<T> v)
            {
                if (!isEmpty(v))
                {
                    double prod = (double)v[0];

                    for (int i = 1; i < v.size(); i++)
                    {
                        prod *= ((double)v[i]);
                    }

                    return prod;
                }
                else
                {
                    throw std::invalid_argument("Attempted to calculate the product of an empty vector");
                }
            }


            template <class T>
            double mean(std::vector<T> v)
            {
                if (!isEmpty(v))
                {
                    double L = (double)v.size();

                    double sumVal = (double)sum(v);

                    return sumVal / L;
                }
                else
                {
                    throw std::invalid_argument("Received empty vector when calculating mean");
                }
            }


            template <class T>
            double median(std::vector<T> v)
            {
                if (!isEmpty(v))
                {
                    double median;
                    size_t L = v.size();

                    std::sort(v.begin(), v.end());

                    if (L % 2 == 0)
                    {
                        median = ((double)(v[L / 2 - 1] + v[L / 2])) / 2.0;
                    }
                    else
                    {
                        median = (double)v[(L - 1) / 2];
                    }

                    return median;
                }
                else
                {
                    throw std::invalid_argument("Received empty vector when calculating median");
                }
            }


            template <class T>
            double variance(std::vector<T> v)
            {
                if (!isEmpty(v))
                {
                    double mu = mean(v);

                    double sumVal = 0.0;

                    for (int i = 0; i < v.size(); i++)
                    {
                        double diff = v[i] - mu;
                        sumVal += diff * diff;
                    }

                    return sumVal / ((double)v.size());
                }
                else
                {
                    throw std::invalid_argument("Received empty vector when calculating variance");
                }
            }


            template <class T>
            double standardDeviation(std::vector<T> v)
            {
                if (!isEmpty(v))
                {
                    double var = variance(v);

                    if (var > 0)
                    {
                        return sqrt(var);
                    }
                    else
                    {
                        return 0.0;
                    }
                }
                else
                {
                    throw std::invalid_argument("Received empty vector when calculating standard deviation");
                }
            }


            template <class T>
            double norm1(std::vector<T> v)
            {
                double sumVal = 0.0;

                for (int i = 0; i < v.size(); i++)
                {
                    if (v[i] > 0)
                    {
                        sumVal += (double)v[i];
                    }
                    else
                    {
                        sumVal += (double)(-1 * v[i]);
                    }
                }

                return sumVal;
            }


            template <class T>
            double norm2(std::vector<T> v)
            {
                double sumVal = 0.0;

                for (int i = 0; i < v.size(); i++)
                {
                    sumVal += (double)(v[i] * v[i]);
                }

                return sqrt(sumVal);
            }


            template <class T>
            double magnitude(std::vector<T> v)
            {
                return norm2(v);
            }


            template <class T>
            double normP(std::vector<T> v, double p)
            {
                double sumVal = 0.0;

                for (int i = 0; i < v.size(); i++)
                {
                    double val;

                    if (v[i] > 0)
                    {
                        val = (double)v[i];
                    }
                    else
                    {
                        val = (double)(-1 * v[i]);
                    }

                    sumVal += pow(val, p);
                }

                return pow(sumVal, 1.0 / p);
            }


            template <class T>
            void multiplyInPlace(Ref<std::vector<T>> v, T scalar)
            {
                for (int i = 0; i < v.size(); i++)
                {
                    v[i] *= scalar;
                }
            }


            template <class T>
            void multiplyInPlace(Ref<std::vector<T>> v1, std::vector<T> v2)
            {
                if (v1.size() == v2.size())
                {
                    for (int i = 0; i < v1.size(); i++)
                    {
                        v1[i] *= v2[i];
                    }
                }
                else
                {
                    throw std::invalid_argument("Vector lengths differ in vector multiply");
                }
            }


            template <class T>
            void divideInPlace(Ref<std::vector<T>>v, T scalar)
            {
                if (scalar != 0)
                {
                    for (int i = 0; i < v.size(); i++)
                    {
                        v[i] /= scalar;
                    }
                }
                else
                {
                    throw std::invalid_argument("Attemted to divide a vector by a zero-valued scalar");
                }
            }


            template <class T>
            void divideInPlace(Ref<std::vector<T>>v1, std::vector<T> v2)
            {
                if (v1.size() == v2.size())
                {
                    if (!contains(v2, 0))
                    {
                        for (int i = 0; i < v1.size(); i++)
                        {
                            v1[i] /= v2[i];
                        }
                    }
                    else
                    {
                        throw std::invalid_argument("Attempted to divide by vector containing zeros");
                    }
                }
                else
                {
                    throw std::invalid_argument("Vector lengths differ in vector divide");
                }
            }


            template <class T>
            void addInPlace(Ref<std::vector<T>>v, T value)
            {
                for (int i = 0; i < v.size(); i++)
                {
                    v[i] += value;
                }
            }


            template <class T>
            void addInPlace(Ref<std::vector<T>>v1, std::vector<T> v2)
            {
                if (v1.size() == v2.size())
                {
                    for (int i = 0; i < v1.size(); i++)
                    {
                        v1[i] += v2[i];
                    }
                }
                else
                {
                    throw std::invalid_argument("Vector lengths differ in vector add");
                }
            }


            template <class T>
            void subtractInPlace(Ref<std::vector<T>>v, T value)
            {
                for (int i = 0; i < v.size(); i++)
                {
                    v[i] -= value;
                }
            }


            template <class T>
            void subtractInPlace(Ref<std::vector<T>>v1, std::vector<T> v2)
            {
                if (v1.size() == v2.size())
                {
                    for (int i = 0; i < v1.size(); i++)
                    {
                        v1[i] -= v2[i];
                    }
                }
                else
                {
                    throw std::invalid_argument("Vector lengths differ in vector subtraction");
                }

            }


            template <class T>
            void absInPlace(Ref<std::vector<T>>v)
            {
                for (int i = 0; i < v.size(); i++)
                {
                    if ((v[i] < 0) || (v[i] == -0.0))
                    {
                        v[i] *= -1;
                    }
                }
            }


            template <class T>
            void squareInPlace(Ref<std::vector<T>>v)
            {
                for (int i = 0; i < v.size(); i++)
                {
                    v[i] = v[i] * v[i];
                }
            }


            template <class T>
            void squareRootInPlace(Ref<std::vector<T>>v)
            {
                if (isAllPositiveOrZero(v))
                {
                    for (int i = 0; i < v.size(); i++)
                    {
                        v[i] = (T)sqrt((double)v[i]);
                    }
                }
                else
                {
                    throw std::invalid_argument("Attempted to compute square root of vector containing negative numbers");
                }
            }



            template <class T>
            void sort(Ref<std::vector<T>>v)
            {
                std::sort(v.begin(), v.end());
            }


            template <class T>
            void reverse(Ref<std::vector<T>>v)
            {
                std::reverse(v.begin(), v.end());
            }


            template <class T>
            std::vector<T> multiply(std::vector<T> v, T scalar)
            {
                std::vector<T> result;

                for (int i = 0; i < v.size(); i++)
                {
                    result.push_back(v[i] * scalar);
                }

                return result;
            }


            template <class T>
            std::vector<T> multiply(std::vector<T> v1, std::vector<T> v2)
            {
                if (v1.size() == v2.size())
                {
                    std::vector<T> result;

                    for (int i = 0; i < v1.size(); i++)
                    {
                        result.push_back(v1[i] * v2[i]);
                    }

                    return result;
                }
                else
                {
                    throw std::invalid_argument("Vector lengths differ in vector multiply");
                }
            }


            template <class T>
            std::vector<T> divide(std::vector<T> v, T scalar)
            {
                if (scalar != 0)
                {
                    std::vector<T> result;

                    for (int i = 0; i < v.size(); i++)
                    {
                        result.push_back(v[i] / scalar);
                    }

                    return result;
                }
                else
                {
                    throw std::invalid_argument("Attemted to divide a vector by a zero-valued scalar");
                }
            }


            template <class T>
            std::vector<T> divide(std::vector<T> v1, std::vector<T> v2)
            {
                if (v1.size() == v2.size())
                {
                    if (!contains(v2, 0))
                    {
                        std::vector<T> result;

                        for (int i = 0; i < v1.size(); i++)
                        {
                            result.push_back(v1[i] / v2[i]);
                        }

                        return result;
                    }
                    else
                    {
                        throw std::invalid_argument("Attempted to divide by vector containing zeros");
                    }
                }
                else
                {
                    throw std::invalid_argument("Vector lengths differ in vector divide");
                }
            }


            template <class T>
            std::vector<T> add(std::vector<T> v, T value)
            {
                std::vector<T> result;

                for (int i = 0; i < v.size(); i++)
                {
                    result.push_back(v[i] + value);
                }

                return result;
            }


            template <class T>
            std::vector<T> add(std::vector<T> v1, std::vector<T> v2)
            {
                if (v1.size() == v2.size())
                {
                    std::vector<T> result;

                    for (int i = 0; i < v1.size(); i++)
                    {
                        result.push_back(v1[i] + v2[i]);
                    }

                    return result;
                }
                else
                {
                    throw std::invalid_argument("Vector lengths differ in vector add");
                }
            }


            template <class T>
            std::vector<T> subtract(std::vector<T> v, T value)
            {
                std::vector<T> result;

                for (int i = 0; i < v.size(); i++)
                {
                    result.push_back(v[i] - value);
                }

                return result;
            }


            template <class T>
            std::vector<T> subtract(std::vector<T> v1, std::vector<T> v2)
            {
                if (v1.size() == v2.size())
                {
                    std::vector<T> result;

                    for (int i = 0; i < v1.size(); i++)
                    {
                        result.push_back(v1[i] - v2[i]);
                    }

                    return result;
                }
                else
                {
                    throw std::invalid_argument("Vector lengths differ in vector subtraction");
                }
            }


            template <class T>
            std::vector<T> abs(std::vector<T> v)
            {
                std::vector<T> result;

                for (int i = 0; i < v.size(); i++)
                {
                    if ((v[i] < 0) || (v[i] == -0.0))
                    {
                        result.push_back(-1 * v[i]);
                    }
                    else
                    {
                        result.push_back(v[i]);
                    }
                }

                return result;
            }


            template <class T>
            std::vector<T> square(std::vector<T> v)
            {
                std::vector<T> result;

                for (int i = 0; i < v.size(); i++)
                {
                    result.push_back(v[i] * v[i]);
                }

                return result;
            }



            template <class T>
            std::vector<T> squareRoot(std::vector<T> v)
            {
                if (isAllPositiveOrZero(v))
                {
                    std::vector<T> result;

                    for (int i = 0; i < v.size(); i++)
                    {
                        result.push_back((T)sqrt((double)v[i]));
                    }

                    return result;
                }
                else
                {
                    throw std::invalid_argument("Attempted to compute square root of vector containing negative numbers");
                }
            }


            template <class T>
            std::vector<double> scale(std::vector<T> v, double lowerLimit, double upperLimit)
            {
                std::vector<double> result;

                double minVal = (double)min(v);
                double maxVal = (double)max(v);
                double outputRange = upperLimit - lowerLimit;
                double inputRange = maxVal - minVal;

                for (int i = 0; i < v.size(); i++)
                {
                    double value = (double)v[i];
                    double scaledValue = ((value - minVal) * outputRange) / inputRange + lowerLimit;

                    result.push_back(scaledValue);
                }

                return result;
            }


            template <class T>
            std::vector<T> difference(std::vector<T> v)
            {
                std::vector<T> result;

                for (int i = 1; i < v.size(); i++)
                {
                    result.push_back(v[i] - v[i - 1]);
                }

                return result;
            }


            template <class T>
            std::vector<T> zeros(int N)
            {
                if (N >= 0)
                {
                    std::vector<T> result;

                    for (int i = 0; i < N; i++)
                    {
                        result.push_back(0);
                    }

                    return result;
                }
                else
                {
                    throw std::invalid_argument("Cannot create vector with negative length");
                }
            }


            template <class T>
            std::vector<T> ones(int N)
            {
                if (N >= 0)
                {
                    std::vector<T> result;

                    for (int i = 0; i < N; i++)
                    {
                        result.push_back(1);
                    }

                    return result;
                }
                else
                {
                    throw std::invalid_argument("Cannot create vector with negative length");
                }
            }

            template <class T>
            std::vector<T> range(int limit1, int limit2, int step)
            {
                std::vector<T> result;

                if (step > 0)
                {
                    for (T i = limit1; i < limit2; i += step)
                    {
                        result.push_back(i);
                    }
                }
                else if (step < 0)
                {
                    for (T i = limit1; i > limit2; i += step)
                    {
                        result.push_back(i);
                    }
                }
                else
                {
                    throw std::invalid_argument("Cannot use a step size of 0 when creating a range of values");
                }

                return result;
            }

            template <class T>
            std::vector<T> range(int maxValue)
            {
                return vector::range<T>(0, maxValue, 1);
            }


            template <class T>
            std::vector<T> range(int minValue, int maxValue)
            {
                return vector::range<T>(minValue, maxValue, 1);
            }


            template <class T>
            double dotProduct(std::vector<T> v1, std::vector<T> v2)
            {
                if (v1.size() == v2.size())
                {
                    double sumVal = 0.0;

                    for (int i = 0; i < v1.size(); i++)
                    {
                        sumVal += (v1[i] * v2[i]);
                    }

                    return sumVal;
                }
                else
                {
                    throw std::invalid_argument("Vector lengths differ in vector dot product");
                }
            }


            template <class T>
            double euclideanDistance(std::vector<T> v1, std::vector<T> v2)
            {
                if (v1.size() == v2.size())
                {
                    double sumVal = 0.0;

                    for (int i = 0; i < v1.size(); i++)
                    {
                        double diff = (double)(v1[i] - v2[i]);
                        sumVal += (diff * diff);
                    }

                    if (sumVal > 0)
                    {
                        return sqrt(sumVal);
                    }
                    else
                    {
                        return 0.0;
                    }
                }
                else
                {
                    throw std::invalid_argument("Vector lengths differ in Euclidean distance calculation");
                }
            }


            template <class T>
            double cosineSimilarity(std::vector<T> v1, std::vector<T> v2)
            {
                return dotProduct(v1, v2) / (magnitude(v1) * magnitude(v2));
            }


            template <class T>
            double cosineDistance(std::vector<T> v1, std::vector<T> v2)
            {
                return 1.0 - cosineSimilarity(v1, v2);
            }



        }//SPACE(vector)
    }//SPACE(core)
}//SPACE(i)
