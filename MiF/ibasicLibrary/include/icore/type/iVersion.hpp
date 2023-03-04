/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：version.hpp
* @创建时间：2022.7.14.12:32
* @创建者：Lovelylavender4
* -----------------------------------------------------------------------------
* i版本结构体
* -----------------------------------------------------------------------------
* 如果你发现了bug，你可以去Github或邮箱(MiracleForest@Outlook.com)反馈给我们！
* 我们一定会努力做得更好的！
*
****/
#pragma once

#include <icore/family/imacrofamily.h>
#include <icore/data/text/istring.hpp>


SPACE(i)
{
	SPACE(core)
	{

		struct iVersion
		{

			enum class Status
			{
				Unk,
				Dev,
				Beta,
				Release
			};//enum Status

			int macro = 0;//宏版本
			int major = 0;//主版本
			int minor = 0;//次版本
			int revision = 0;//修订版本
			data::text::istring branch = "master";//分支
			uint64 numberOfBuilds = 0;//构建次数
			Status status = Status::Unk;//状况 
		};//struct iVersion

	}//SPACE(core)
}//SPACE(i)

#ifdef INCLUDE_NLOHMANN_JSON_HPP_

SPACE(nlohmann)
{

	inline void to_json(_ISTD Ref<nlohmann::json> j, _ISTD CRef<_ISTD iVersion> value)
	{
		std::string strbuff = "";
		switch (value.status)
		{
			using enum _ISTD iVersion::Status;
		case Unk:
			strbuff = "Unk";
			break;
		case Dev:
			strbuff = "Dev";
			break;
		case Beta:
			strbuff = "Beta";
			break;
		case Release:
			strbuff = "Release";
			break;
		default:
			strbuff = "Unk";
			break;
		}
		nlohmann::json json = nlohmann::json::array();
		json.push_back(value.macro);
		json.push_back(value.major);
		json.push_back(value.minor);
		json.push_back(value.revision);
		json.push_back(value.branch.data());
		json.push_back(value.numberOfBuilds);
		json.push_back(strbuff);
		j = json;
	}

	inline void from_json(nlohmann::json j, _ISTD Ref<_ISTD iVersion> value)
	{
		value.macro = j[0].get<int>();
		value.major = j[1].get<int>();
		value.minor = j[2].get<int>();
		value.revision = j[3].get<int>();
		value.branch = j[4].get<std::string>();
		value.numberOfBuilds = j[5].get<_ISTD uint64>();
		std::string s = j[6].get<std::string>();
		if (s == "Unk")
		{
			value.status = _ISTD iVersion::Status::Unk;
		}
		else if (s == "Dev")
		{
			value.status = _ISTD iVersion::Status::Dev;
		}
		else if (s == "Beta")
		{
			value.status = _ISTD iVersion::Status::Beta;
		}
		else if (s == "Release")
		{
			value.status = _ISTD iVersion::Status::Release;
		}
		else
		{
			value.status = _ISTD iVersion::Status::Unk;
		}
	}

}

#endif//^^^^INCLUDE_NLOHMANN_JSON_HPP_

