/****
*
 * Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
 *
 * @文件名：iElementaryFunction.hpp
 * @创建时间：2023.4.16.9:52
 * @创建者：Minsecrus
 * -----------------------------------------------------------------------------
 * iBasicLibrary 初等函数
 * -----------------------------------------------------------------------------
 * 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
 * 我们一定会努力做得更好的！
 *
 ****/

#pragma once

#include <icore/math/iMath.hpp>
#include <icore/family/imacrofamily.h>
#include <icore/data/text/istring.h>
#include <optional>

SPACE(i)
{
    SPACE(core)
    {
        SPACE(math)
        {
            SPACE(calculus)
            {
                enum class OperationCalculateType
                {
                    ADD,
                    NEGETIVE,
                    MUL,
                    DIV,
                    ROOT,
                    SIN,
                    COS,
                    TAN,
                    COT,
                    SEC,
                    CSC
                };

                inline bool needTwoOperands(OperationCalculateType type)
                {
                    
                    return static_cast<std::underlying_type<OperationCalculateType>::type>(type) < 5 ? false : true;
                }

                class iElementaryFunction : basic::iBasic<iElementaryFunction>
                {
                    iObject(iElementaryFunction)

                public:
                    iElementaryFunction(OperationCalculateType type, iElementaryFunction left,
                                        std::optional<iElementaryFunction> right = std::nullopt) { }

                private:
                    std::unique_ptr<iElementaryFunction> left;
                    std::unique_ptr<iElementaryFunction> right;
                };
            }
        }
    }
}
