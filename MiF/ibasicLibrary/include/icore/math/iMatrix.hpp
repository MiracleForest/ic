/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iMatrix.hpp
* @创建时间：2023.1.11.21:15
* @创建者：X
* -----------------------------------------------------------------------------
* iMatrix 简单的矩阵类
*
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/

#pragma once

#include <icore/family/imacrofamily.h>
#include <icore/basic/iBasicDataType.hpp>
#include <icore/exception/exception.hpp>
#include <icore/data/text/istring.hpp>
#include <icore/math/iFraction.hpp>
#include <icore/math/iMath.hpp>

SPACE(i)
{
	SPACE(core)
	{
		SPACE(math)
		{
			class iMatrix
				: public basic::iBasicDataType<iMatrix, Ptr<double>>
			{
				iObject(iMatrix);
			public:
				iMatrix()
					: _data(nullptr), _cols(0), _rows(0), is_square(false)
				{ }

				iMatrix(Ref<iMatrix> mat)
				{
					_data = new double[mat._cols * mat._rows];
					memcpy_s(
						_data,
						mat._cols * mat._rows * sizeof(double),
						mat._data,
						mat._cols * mat._rows * sizeof(double)
					);
					_cols = mat._cols;
					_rows = mat._rows;
					is_square = (_cols == _rows);
				}

				iMatrix(Ptr<double> data, uint rows, uint cols)
				{
					_data = new double[rows * cols];
					memcpy_s(
						_data,
						rows * cols * sizeof(double),
						data,
						rows * cols * sizeof(double)
					);
					_rows = rows;
					_cols = cols;
					is_square = (_cols == _rows);
				}

				iMatrix(uint rows, uint cols)
				{
					_data = new double[rows * cols];
					memset(_data, 0, rows * cols * sizeof(double));
					_rows = rows;
					_cols = cols;
					is_square = (_cols == _rows);
				}

				~iMatrix()
				{
					if (_data != nullptr)
					{
						delete[] _data;
						_data = nullptr;
					}
				}

			public:
				/****
				* @author X
				* @since 2023.1.12 5:52
				* @brief 初始化矩阵
				*
				* @param data 一个一维数组,从左到右从上到下包含了矩阵的值
				* @param rows 行数 cols 列数
				* @retval void
				*
				* @par XXX
				* @code
				* 代码示例
				* double data[] = {1, 2, 3, 4};
				* A.initialMatrix(data, 2, 2);
				* // [[1, 2],
				* //  [3, 4]]
				* @endcode
				*
				****/
				void initialMatrix(Ptr<double> data, uint rows, uint cols)
				{
					if (_data != nullptr) delete[] _data;
					_data = new double[rows * cols * sizeof(double)];
					memcpy_s(
						_data,
						rows * cols * sizeof(double),
						data,
						rows * cols * sizeof(double)
					);
					_rows = rows;
					_cols = cols;
					is_square = (_cols == _rows);
				}

			public: //OPERATORS
				/****
				* @author X
				* @since 2023.1.12 2:34
				* @brief ()号重载, 用来操作矩阵的某一个值
				*
				* @param i 行, j 列
				* @retval 那个值的引用
				* @throws 若越界会抛出 iIndexOutOfBounds
				*
				* @par XXX
				* @code
				* 代码示例
				* double m = A(1, 2);
				* A(3, 4) = 2.6;
				* @endcode
				*
				****/
				Ref<double> operator()(uint i, uint j)
				{
					bool b1 = (i >= _rows);
					bool b2 = (j >= _cols);
					if (b1 && b2)
					{
						throw ::i::core::iexception::iIndexOutOfBounds("cols out of bound");
					}
					else if (b1)
					{
						throw ::i::core::iexception::iIndexOutOfBounds("rows out of bound");
					}
					else if (b2)
					{
						throw ::i::core::iexception::iIndexOutOfBounds("rows and cols out of bound both");
					}
					else return _data[i * _cols + j];
				}

				/****
				* @author X
				* @since 2023.1.12 2:38
				* @brief +号重载, 矩阵相加(广义)
				*
				* @param B 另一个矩阵
				* @retval 结果
				*
				* @par XXX
				* @code
				* 代码示例
				* C = A + B;
				* @endcode
				*
				****/
				iMatrix operator+(iMatrix B)
				{
					iMatrix ret(
						maxi<double>(_rows, B._rows),
						maxi<double>(_cols, B._cols)
					);
					for (uint i = 0; i < ret._rows; i++)
					{
						for (uint j = 0; j < ret._cols; j++)
						{
							if (i < _rows && j < _cols) ret(i, j) += (*this)(i, j);
							if (i < B._rows && j < B._cols) ret(i, j) += B(i, j);
						}
					}
					return ret;
				}

				/****
				* @author X
				* @since 2023.1.12 2:42
				* @brief -号重载, 矩阵相减(广义)
				*
				* @param B 另一个矩阵
				* @retval 结果
				*
				* @par XXX
				* @code
				* 代码示例
				* C = A - B;
				* @endcode
				*
				****/
				iMatrix operator-(iMatrix B)
				{
					iMatrix ret(
						maxi<double>(_rows, B._rows),
						maxi<double>(_cols, B._cols)
					);
					for (uint i = 0; i < ret._rows; i++)
					{
						for (uint j = 0; j < ret._cols; j++)
						{
							if (i < _rows && j < _cols) ret(i, j) += (*this)(i, j);
							if (i < B._rows && j < B._cols) ret(i, j) -= B(i, j);
						}
					}
					return ret;
				}

				/****
				* @author X
				* @since 2023.1.12 2:52
				* @brief *号重载, 矩阵数乘
				*
				* @param c 数字
				* @retval 结果
				*
				* @par XXX
				* @code
				* 代码示例
				* C = A * c;
				* @endcode
				*
				****/
				iMatrix operator*(double c)
				{
					if (c == 0) return iMatrix(_rows, _cols);
					if (c == 1) return *this;
					iMatrix ret = *this;
					for (uint i = 0; i < _rows; i++)
						for (uint j = 0; j < _cols; j++)
							ret(i, j) *= c;
					return ret;
				}

				/****
				* @author X
				* @since 2023.1.12 2:52
				* @brief *号重载, 矩阵相乘(广义)
				*
				* @param B 另一个矩阵
				* @retval 结果
				*
				* @par XXX
				* @code
				* 代码示例
				* C = A * B;
				* @endcode
				*
				****/
				iMatrix operator*(iMatrix B)
				{
					uint n = mini<uint>(_cols, B._rows);
					iMatrix ret(_rows, B._cols);
					for (uint i = 0; i < ret._rows; i++)
					{
						for (uint j = 0; j < ret._cols; j++)
						{
							for (uint k = 0; k < n; k++)
							{
								ret(i, j) += (*this)(i, k) * B(k, j);
							}
						}
					}
					return ret;
				}
			public:
				/****
				* @author X
				* @since 2023.1.12 5:38
				* @brief 矩阵取转置
				*
				* @retval 自己
				*
				* @par XXX
				* @code
				* 代码示例
				* A.transposition();
				* @endcode
				*
				****/
				Ref<iMatrix> transposition()
				{
					iMatrix tmp(_cols, _rows);
					for (uint i = 0; i < _rows; i++)
					{
						for (uint j = 0; j < _cols; j++)
						{
							tmp(j, i) = (*this)(i, j);
						}
					}
					initialMatrix(tmp.data(), _cols, _rows);
					return *this;
				}

				/****
				* @author X
				* @since 2023.1.12 6:24
				* @brief 求矩阵的秩
				*
				* @retval 秩
				*
				* @par XXX
				* @code
				* 代码示例
				* int r = A.rank();
				* @endcode
				*
				****/
				int rank()
				{
					if (_rows == 1)
					{
						for (uint j = 0; j < _cols; j++)
						{
							if ((*this)(0, j) != 0)
								return 1;
						}
						return 0;
					}
					if (_cols == 1)
					{
						for (uint i = 0; i < _rows; i++)
						{
							if ((*this)(i, 0) != 0)
								return 1;
						}
						return 0;
					}
					iMatrix subMat(_rows - 1, _cols - 1);
					for (uint i = 0; i < subMat._rows; i++)
					{
						for (uint j = 0; j < subMat._cols; j++)
						{
							uint I = i + 1;
							uint J = j + 1;
							if ((*this)(I, 0) == 0)
							{
								subMat(i, j) = (*this)(I, J);
							}
							else
							{
								subMat(i, j) = (*this)(I, J) * (*this)(0, 0) / (*this)(I, 0) - (*this)(0, J);
							}
						}
					}
					return 1 + subMat.rank();
				}

				/****
				* @author X
				* @since 2023.1.11 22:29
				* @brief 用于iConsole输出
				*
				* @retval 输出的字符串
				*
				* @par XXX
				* @code
				* 代码示例
				* iConsole::write(A.toStdString())
				* @endcode
				*
				****/
				std::string toStdString()
				{
					std::string s("");
					for (uint i = 0; i < _rows; i++)
					{
						for (uint j = 0; j < _cols; j++)
						{
							s += std::to_string((*this)(i, j)) + " ";
						}
						s += "\n";
					}
					return s;
				}


				virtual Ptr<double> data() const
				{
					return _data;
				}
			private:
				Ptr<double> _data;
				uint _rows; //矩阵行数
				uint _cols;  //矩阵列数
				bool is_square; //是否是方阵
			};
		}
	}
}