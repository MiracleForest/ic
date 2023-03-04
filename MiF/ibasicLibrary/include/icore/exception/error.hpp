/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：error.hpp
* @创建时间：2022.5.19.13:09
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* 包含i错误类，i错误枚举类型
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once
#pragma warning(disable:4996)
#pragma warning(disable:4819)

#include <source_location>
#include <icore/exception/exception.hpp>
#include <icore/exception/errorcode.hpp>
#include <icore/family/imacrofamily.h>
#include <icore/file/iFilePos.hpp>
#include <icore/type/iLevel.hpp>
#include <map>

#ifndef ___ERROR_MAP
// ErrorCode, icode, description, description2, suggestion, level, canIgnore
#define ___ERROR_MAP(XX) \
    XX(unkError,-1, "未知的错误！", "[unkError]此错误未被记载！是未知的错误！", "仔细检查代码，或向i官方反馈并提交此错误！", -1, false)\
    XX(createErrorFailed, -2, "创建错误失败！", "[createErrorFailed]创建错误失败！在构建错误时发生了严重的错误！此错误不可忽略！", "仔细检查代码中引发此错误的地方，例如确定参数code是有效！", -1, false)\
    XX(loadDynamicLinkLibraryFailed, -1000, "加载动态链接库失败！", "[loadDynamicLinkLibraryFailed]加载动态链接库（dll/so）失败！", "确认动态库路径正确，动态库文件存在，检查动态库文件是否无损！", -1, false)\
    XX(loadDynamicLinkLibraryFailed_theTargetLibraryIsCalledEmpty, -1001, "加载动态链接库失败！目标库名为空！", "[loadDynamicLinkLibraryFailed_theTargetLibraryIsCalledEmpty]加载动态链接库（dll/so）失败！目标库名为空！", "修改目标库名为正确值！", -1, false)\
    XX(theDynamicLinkLibraryHasBeenFreed, -1002, "动态链接库已经被释放！", "[theDynamicLinkLibraryHasBeenFreed]释放动态链接库失败！目标库已经被释放！", "忽略此错误", 0 , true)\
    XX(theIllegalInput,-1100,"非法输入","[theIllegalInput]输入类型与预期读入类型不匹配！","输入类型与预期读入类型应当匹配！",2,true)\
    XX(theIllegalFormatString,-1101,"非法格式字符串","[theIllegalFormatString]非法的格式字符串，‘{’与‘}’字符不匹配","检查格式字符串是否非法，并矫正",-1,false)\
    XX(failedToSetConsoleTitle, -1200, "设置控制台标题失败！", "[failedToSetConsoleTitle]设置控制台标题失败！","重试", 8, true)\
    XX(failedToCreateFile, -1300, "创建文件失败！", "[failedToCreateFile]创建文件失败！", "检查程序是否有创建文件权限！", 1, false)\
    XX(failedToRemoveFile, -1301, "删除文件失败！", "[failedToRemoveFile]删除文件失败！", "检查欲写入的文件是否为只读文件；检查参数filename指针是否超出可存取内存空间；检查核心内存是否不足；检查参数filename是否太长；检查参数filename是否有过多符号连接问题；可能发生存取错误", 1, false)


#endif//!___ERROR_MAP

SPACE(i)
{
    SPACE(core)
    {
        SPACE(iexception)
        {

            class error;

            struct ErrorInfo
            {
                ErrorCode _code = ErrorCode::unkError;
                int _icode = -1;
                std::string _dscription = "";  // 描述
                std::string _dscription2 = ""; // 详细描述
                std::string _suggestion = "";  // 建议
                type::iFilePos _position = {};  // 位置
                type::iLevel _level = type::Level::FALSE;       // 等级
                bool _canBeIgnored = false;       // 是否可以忽略
                std::map<data::text::istring, error> other{ };//其他
            };//struct ErrorInfo



            class error
                :public basic::iBasic<error>
            {
                using istring = data::text::istring;

                iObject(error);
            public:
                //error message type
                ECLASS(EMT) :int
                {
                    errorCode_enum,
                        errorCode_int,
                        dscription,
                        dscription2,
                        suggestion,
                        level
                };
            private:

                error()
                    :_noError(true),
                    _isIString(false),
                    _errorstr("")
                { }

                error(ErrorInfo errorinfo)
                    :_errorinfo(errorinfo),
                    _noError(false),
                    _isIString(false),
                    _errorstr("")
                { }

                error(data::text::istring str)
                    : _noError(false),
                    _isIString(true),
                    _errorstr(str)
                { }

            public:

                ~error()
                { }

            public:

                /****
                * @author Lovelylavender4
                * @since 2022.7.2.9:52
                * @brief 此错误是否可以忽略
                *
                * @retval 此错误是否可以忽略
                *
                * @par Example
                * @code
                * auto e=fun();//IERROR fun();
                * if(!e.isNoError()){
                *     if(e.isCanBeIgnored()){
                *
                *     }
                *     else{
                *
                *     }
                * }
                * @endcode
                *
                *
                * @include -
                * @details
                * 此错误是否可以忽略
                * @enddetails
                ****/
                bool isCanBeIgnored() const
                {
                    return _errorinfo._canBeIgnored;
                }

                /****
                * @author Lovelylavender4
                * @since 2022.7.2.9:55
                * @brief 是否没有错误
                *
                * @retval 是否没有错误
                *
                * @par Example
                * @code
                * auto e=fun();//IERROR fun();
                * if(!e.isNoError()){
                *
                * }
                * @endcode
                *
                * @include -
                * @details
                * 是否没有错误
                * @enddetails
                ****/
                bool isNoError() const
                {
                    return _noError;
                }

                bool isIString() const
                {
                    return _isIString;
                }

            public:

                /****
                * @author Lovelylavender4
                * @since 2022.7.2.9:55
                *
                * @brief 创建一个自定义的错误
                * @param _code 错诶代码
                * @param _dscription = "" 描述
                * @param _suggestion = "" 建议
                * @param _position = {} 位置
                * @param _level = 0 等级
                * @param _canBeIgnored = false 是否可以忽略
                * @retval 错误对象
                * @note 错诶代码
                * @par Example
                * @code
                * IERROR fun(){
                *     return error::make(-123,"...","...","...",{"...",1,1},10,false);
                * }
                * @endcode
                * @include <string>,filepos.hpp,level.hpp
                ****/
                static error make(
                    int _code,
                    std::string _dscription = "",
                    std::string _dscription2 = "",
                    std::string _suggestion = "",
                    type::iFilePos _position = {},
                    type::iLevel _level = type::Level::FALSE,
                    bool _canBeIgnored = false
                )
                {
                    ErrorInfo errorinfo;

                    errorinfo._code = ErrorCode::unkError;
                    errorinfo._icode = _code;
                    errorinfo._dscription = _dscription;
                    errorinfo._dscription2 = _dscription2;
                    errorinfo._suggestion = _suggestion;
                    errorinfo._position = _position;
                    errorinfo._level = _level;
                    errorinfo._canBeIgnored = _canBeIgnored;

                    return errorinfo;
                }

                /****
                * @author Lovelylavender4
                * @since 2022.7.2.10:05
                * @brief 创建一个已有的错误
                *
                * @param _code 错误代码
                * @param _position = {} 错误位置
                * @future 根据参数_code找到此错误的ErrorInfo，并创建error
                * @retval 创建完毕的错误
                *
                * @note
                * _code必须是有效的错误代码
                * @endnote
                * @pre 检测到代码发生了错误
                * @par 示例
                * @code
                * IERROR fun(){
                *     return error::make(ErrorCode::xxx,{"...",1,1});
                * }
                * @endcode
                *
                * @warning 若_code无效，会抛出createErrorFailed异常
                * @include errorcode.hpp,filepos.hpp
                * @details
                * 创建一个已有的错误
                * @enddetails
                ****/
                static error make(
                    ErrorCode code,
                    type::iFilePos position = {},
                    std::string _dscription = "",
                    std::string _dscription2 = ""
                )
                {
                    ErrorInfo errorinfo;
                    try
                    {
                        errorinfo = getErrorInfoFrom(EMT::errorCode_enum, code);
                        errorinfo._position = position;
                        if (_dscription != "")
                        {
                            errorinfo._dscription = _dscription;
                        }
                        if (_dscription2 != "")
                        {
                            errorinfo._dscription2 = _dscription2;
                        }
                    }
                    catch (...)
                    {
                        throw iCreateErrorFailed("错误！参数code是无效的！");
                    }
                    return errorinfo;
                }

                /****
                * @author Lovelylavender4
                * @brief 无错误
                * @retval 错误对象
                *
                * @par 示例
                * @code
                * i::core::iexception::error testFunction(){
                * return i::core::iexception::error::noError();
                * }
                * @endcode
                ****/
                static error noError()
                {
                    return error();
                }

                /**
                * @author Ticks
                * @since 22-7-2 下午1:32
                *
                * @brief 通过错误代码、错误信息描述、错误级别等获取错误信息(ErrorInfo)
                *
                * @param emt EMT枚举类型
                * @param emsg 枚举对应类型
                * @tparam emsg_t 通过emsg_t类型获取
                * @retval ErrorInfo 错误信息结构体
                *
                * @note
                * emsg类型需要与emt枚举中类型对应，否则会发生未定义错误
                * @endnote
                * @pre 示例
                * @code
                * ErrorInfo info = getErrorInfo(EMT::errorCode_int, -1);
                * std::cout << "错误描述: " << info.dscription << std::endl;
                * @endcode
                *
                * @include error.hpp
                * @details
                * 通过错误代码、错误信息描述、错误级别等获取错误信息(ErrorInfo)
                * @enddetails
                *
                **/
                template<class emsg_t>
                static ErrorInfo getErrorInfoFrom(EMT emt, emsg_t emsg)
                {
                    throw - 1;
                }


                template<>
                static ErrorInfo getErrorInfoFrom<ErrorCode>(EMT emt, ErrorCode emsg)
                {
                    if (emt == EMT::errorCode_enum)
                    {
                        if (emsg == ErrorCode::unkError)
                        {
                            return ErrorInfo{ ErrorCode::unkError, -1, "未知的错误",
                                "此错误未被记载！是未知的错误！",
                                "仔细检查代码，或向i官方反馈并提交此错误！",
                                {}, type::Level::φ, false };
                        }
#define XX(error, icode, des, des2, sug, level, ignore) else if (emsg == ErrorCode:: error){ \
            return ErrorInfo{ErrorCode:: error, icode, des, des2, sug, {}, level, ignore};}
                        ___ERROR_MAP(XX)
#undef XX
else
                        {
                            throw - 1;
                        }
                    }
                    else
                    {
                        throw - 1;
                    }
                }

                template<>
                static ErrorInfo getErrorInfoFrom<int>(EMT emt, int emsg)
                {
                    if (emt == EMT::errorCode_int)
                    {
                        if (emsg == static_cast<int>(-1))
                        {
                            return ErrorInfo{ ErrorCode::unkError, -1, "未知的错误",
                                "此错误未被记载！是未知的错误！",
                                "仔细检查代码，或向i官方反馈并提交此错误！",
                                {}, type::Level::φ, false };
                        }
#define XX(error, icode, des, des2, sug, level, ignore) else if (emsg == static_cast<int>(icode)){ \
            return ErrorInfo{ErrorCode:: error, icode, des, des2, sug, {}, level, ignore};}
                        ___ERROR_MAP(XX)
#undef XX
else
                        {
                            throw - 1;
                        }
                    }
                    else if (emt == EMT::level)
                    {
                        if (emsg == -1)
                        {
                            return ErrorInfo{ ErrorCode::unkError, -1, "未知的错误",
                                "此错误未被记载！是未知的错误！",
                                "仔细检查代码，或向i官方反馈并提交此错误！",
                                {}, type::Level::φ, false };
                        }
#define XX(error, icode, des, des2, sug, level, ignore) else if (emsg == level){ \
            return ErrorInfo{ErrorCode:: error, icode, des, des2, sug, {}, level, ignore};}
                        ___ERROR_MAP(XX)
#undef XX
else
                        {
                            throw - 1;
                        }
                    }
                    else
                    {
                        throw - 1;
                    }
                }

                template<>
                static ErrorInfo getErrorInfoFrom<CRef<std::string>>(EMT emt, CRef<std::string> emsg)
                {
                    if (emt == EMT::dscription)
                    {
                        if (emsg == ("未知的错误"))
                        {
                            return ErrorInfo{ ErrorCode::unkError, -1, "未知的错误",
                                "此错误未被记载！是未知的错误！",
                                "仔细检查代码，或向i官方反馈并提交此错误！",
                                {}, type::Level::φ, false };
                        }
#define XX(error, icode, des, des2, sug, level, ignore) else if (emsg == des){ \
            return ErrorInfo{ErrorCode:: error, icode, des, des2, sug, {}, level, ignore};}
                        ___ERROR_MAP(XX)
#undef XX
else
                        {
                            throw - 1;
                        }
                    }
                    else if (emt == EMT::dscription2)
                    {
                        if (emsg == ("此错误未被记载！是未知的错误！"))
                        {
                            return ErrorInfo{ ErrorCode::unkError, -1, "未知的错误",
                                "此错误未被记载！是未知的错误！",
                                "仔细检查代码，或向i官方反馈并提交此错误！",
                                {}, type::Level::φ, false };
                        }
#define XX(error, icode, des, des2, sug, level, ignore) else if (emsg == des2){ \
            return ErrorInfo{ErrorCode:: error, icode, des, des2, sug, {}, level, ignore};}
                        ___ERROR_MAP(XX)
#undef XX
else
                        {
                            throw - 1;
                        }
                    }
                    else if (emt == EMT::suggestion)
                    {
                        if (emsg == ("仔细检查代码，或向i官方反馈并提交此错误！"))
                        {
                            return ErrorInfo{ ErrorCode::unkError, -1, "未知的错误",
                                "此错误未被记载！是未知的错误！",
                                "仔细检查代码，或向i官方反馈并提交此错误！",
                                {}, type::Level::φ, false };
                        }
#define XX(error, icode, des, des2, sug, level, ignore) else if (emsg == sug){ \
            return ErrorInfo{ErrorCode:: error, icode, des, des2, sug, {}, level, ignore};}
                        ___ERROR_MAP(XX)
#undef XX
else
                        {
                            throw - 1;
                        }
                    }
                    else
                    {
                        throw - 1;
                    }
                }

            public:

                /****
                * @author Lovelylavender4
                * @brief 获取错误信息
                * @retval ErrorInfo 错误信息
                * @throws NULL
                * @note NULL
                * @par Example
                * @code
                * NULL
                * @endcode
                * @warning NULL
                * @bug NULL
                * @include NULL
                ****/
                ErrorInfo data()const
                {
                    return _errorinfo;
                }

                ErrorInfo getErrorInfo()const
                {
                    return _errorinfo;
                }

                istring getIString() const
                {
                    return _errorstr;
                }

            private:
                ErrorInfo _errorinfo;
                bool _noError;
                bool _isIString;
                istring _errorstr;
            };//class error

        }//SPACE(iexception)
    }//SPACE(core)
}//SPACE(i)


#undef ___ERROR_MAP

