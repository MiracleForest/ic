/****
*
* Copyright(C) 2022 MiracleForest Studio. All Rights Reserved.
*
* @文件名：iEaseCurve.hpp
* @创建时间：2022.11.17.21:55
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
#include <icore/basic/iBasic.hpp>

SPACE(i)
{
	SPACE(core)
	{

		class iEaseCurve
			: public basic::iBasic<iEaseCurve>
		{
			iObject(iEaseCurve);
		public:

			enum Type
			{
				UnkType = -1,
				Linear = 0,
				InQuad = 1,
				OutQuad = 2,
				InOutQuad = 3,
				InCubic = 4,
				OutCubic = 5,
				InOutCubic = 6,
				InQuart = 7,
				OutQuart = 8,
				InOutQuart = 9,
				InQuint = 10,
				OutQuint = 11,
				InOutQuint = 12,
				InSine = 13,
				OutSine = 14,
				InOutSine = 15,
				InExpo = 16,
				OutExpo = 17,
				InOutExpo = 18,
				InCirc = 19,
				OutCirc = 20,
				InOutCirc = 21,
				InBounce = 22,
				OutBounce = 23,
				InOutBounce = 24,
				InElastic = 25,
				OutElastic = 26,
				InOutElastic = 27,
				InBack = 28,
				OutBack = 29,
				InOutBack = 30
			};

		public:

			iEaseCurve()
				: _easeCurveType(Type::Linear)
			{ }

			iEaseCurve(Type easeCurveType)
				: _easeCurveType(easeCurveType)
			{ }

			~iEaseCurve()
			{ }

		public:

			//根据Type选择曲线，并计算t点(0,1)时曲线的值，若越界返回0或1
			float Evaluate(float t)
			{
				float from = 0;
				float to = 1;
				if (t > 1)
				{
					return 1;
				}
				else if (t < 0)
				{
					return 0;
				}

				switch (_easeCurveType)
				{
				case Type::Linear:
					return linear(from, to, t);
				case Type::InQuad:
					return inQuad(from, to, t);
				case Type::OutQuad:
					return outQuad(from, to, t);
				case Type::InOutQuad:
					return inOutQuad(from, to, t);
				case Type::InCubic:
					return inCubic(from, to, t);
				case Type::OutCubic:
					return outCubic(from, to, t);
				case Type::InOutCubic:
					return inOutCubic(from, to, t);
				case Type::InQuart:
					return inQuart(from, to, t);
				case Type::OutQuart:
					return outQuart(from, to, t);
				case Type::InOutQuart:
					return inOutQuart(from, to, t);
				case Type::InQuint:
					return inQuint(from, to, t);
				case Type::OutQuint:
					return outQuint(from, to, t);
				case Type::InOutQuint:
					return inOutQuint(from, to, t);
				case Type::InSine:
					return inSine(from, to, t);
				case Type::OutSine:
					return outSine(from, to, t);
				case Type::InOutSine:
					return inOutSine(from, to, t);
				case Type::InExpo:
					return inExpo(from, to, t);
				case Type::OutExpo:
					return outExpo(from, to, t);
				case Type::InOutExpo:
					return inOutExpo(from, to, t);
				case Type::InCirc:
					return inCirc(from, to, t);
				case Type::OutCirc:
					return outCirc(from, to, t);
				case Type::InOutCirc:
					return inOutCirc(from, to, t);
				case Type::InBounce:
					return inBounce(from, to, t);
				case Type::OutBounce:
					return outBounce(from, to, t);
				case Type::InOutBounce:
					return inOutBounce(from, to, t);
				case Type::InElastic:
					return inElastic(from, to, t);
				case Type::OutElastic:
					return outElastic(from, to, t);
				case Type::InOutElastic:
					return inOutElastic(from, to, t);
				case Type::InBack:
					return inBack(from, to, t);
				case Type::OutBack:
					return outBack(from, to, t);
				case Type::InOutBack:
					return inOutBack(from, to, t);
				}
				return 0;
			}

			static float Evaluate(Type easeCurveType, float t)
			{
				float from = 0;
				float to = 1;
				if (t > 1)
				{
					return 1;
				}
				else if (t < 0)
				{
					return 0;
				}

				switch (easeCurveType)
				{
				case Type::Linear:
					return linear(from, to, t);
				case Type::InQuad:
					return inQuad(from, to, t);
				case Type::OutQuad:
					return outQuad(from, to, t);
				case Type::InOutQuad:
					return inOutQuad(from, to, t);
				case Type::InCubic:
					return inCubic(from, to, t);
				case Type::OutCubic:
					return outCubic(from, to, t);
				case Type::InOutCubic:
					return inOutCubic(from, to, t);
				case Type::InQuart:
					return inQuart(from, to, t);
				case Type::OutQuart:
					return outQuart(from, to, t);
				case Type::InOutQuart:
					return inOutQuart(from, to, t);
				case Type::InQuint:
					return inQuint(from, to, t);
				case Type::OutQuint:
					return outQuint(from, to, t);
				case Type::InOutQuint:
					return inOutQuint(from, to, t);
				case Type::InSine:
					return inSine(from, to, t);
				case Type::OutSine:
					return outSine(from, to, t);
				case Type::InOutSine:
					return inOutSine(from, to, t);
				case Type::InExpo:
					return inExpo(from, to, t);
				case Type::OutExpo:
					return outExpo(from, to, t);
				case Type::InOutExpo:
					return inOutExpo(from, to, t);
				case Type::InCirc:
					return inCirc(from, to, t);
				case Type::OutCirc:
					return outCirc(from, to, t);
				case Type::InOutCirc:
					return inOutCirc(from, to, t);
				case Type::InBounce:
					return inBounce(from, to, t);
				case Type::OutBounce:
					return outBounce(from, to, t);
				case Type::InOutBounce:
					return inOutBounce(from, to, t);
				case Type::InElastic:
					return inElastic(from, to, t);
				case Type::OutElastic:
					return outElastic(from, to, t);
				case Type::InOutElastic:
					return inOutElastic(from, to, t);
				case Type::InBack:
					return inBack(from, to, t);
				case Type::OutBack:
					return outBack(from, to, t);
				case Type::InOutBack:
					return inOutBack(from, to, t);
				}
				return 0;
			}

		public:

			static float linear(float from, float to, float t)
			{
				float c = to - from;
				t /= 1.0f;
				return c * t / 1.0f + from;
			}

			static float inQuad(float from, float to, float t)
			{
				float c = to - from;
				t /= 1.0f;
				return c * t * t + from;
			}

			static float outQuad(float from, float to, float t)
			{
				float c = to - from;
				t /= 1.0f;
				return -c * t * (t - 2.0f) + from;
			}

			static float inOutQuad(float from, float to, float t)
			{
				float c = to - from;
				t /= 0.5f;
				if (t < 1) return c / 2.0f * t * t + from;
				t--;
				return -c / 2.0f * (t * (t - 2) - 1) + from;
			}

			static float inCubic(float from, float to, float t)
			{
				float c = to - from;
				t /= 1.0f;
				return c * t * t * t + from;
			}

			static float outCubic(float from, float to, float t)
			{
				float c = to - from;
				t /= 1.0f;
				t--;
				return c * (t * t * t + 1) + from;
			}

			static float inOutCubic(float from, float to, float t)
			{
				float c = to - from;
				t /= 0.5f;
				if (t < 1) return c / 2.0f * t * t * t + from;
				t -= 2;
				return c / 2.0f * (t * t * t + 2) + from;
			}

			static float inQuart(float from, float to, float t)
			{
				float c = to - from;
				t /= 1.0f;
				return c * t * t * t * t + from;
			}

			static float outQuart(float from, float to, float t)
			{
				float c = to - from;
				t /= 1.0f;
				t--;
				return -c * (t * t * t * t - 1) + from;
			}

			static float inOutQuart(float from, float to, float t)
			{
				float c = to - from;
				t /= 0.5f;
				if (t < 1) return c / 2.0f * t * t * t * t + from;
				t -= 2;
				return -c / 2.0f * (t * t * t * t - 2) + from;
			}

			static float inQuint(float from, float to, float t)
			{
				float c = to - from;
				t /= 1.0f;
				return c * t * t * t * t * t + from;
			}

			static float outQuint(float from, float to, float t)
			{
				float c = to - from;
				t /= 1.0f;
				t--;
				return c * (t * t * t * t * t + 1) + from;
			}

			static float inOutQuint(float from, float to, float t)
			{
				float c = to - from;
				t /= 0.5f;
				if (t < 1) return c / 2.0f * t * t * t * t * t + from;
				t -= 2;
				return c / 2.0f * (t * t * t * t * t + 2) + from;
			}

			static float inSine(float from, float to, float t)
			{
				float c = to - from;
				return -c * cos(t / 1.0f * (3.1415926535897931 / 2.0f)) + c + from;
			}

			static float outSine(float from, float to, float t)
			{
				float c = to - from;
				return c * sin(t / 1.0f * (3.1415926535897931 / 2.0f)) + from;
			}

			static float inOutSine(float from, float to, float t)
			{
				float c = to - from;
				return -c / 2.0f * (cos(3.1415926535897931 * t / 1.0f) - 1) + from;
			}

			static float inExpo(float from, float to, float t)
			{
				float c = to - from;
				return c * pow(2, 10 * (t / 1.0f - 1)) + from;
			}

			static float outExpo(float from, float to, float t)
			{
				float c = to - from;
				return c * (-pow(2, -10 * t / 1.0f) + 1) + from;
			}

			static float inOutExpo(float from, float to, float t)
			{
				float c = to - from;
				t /= 0.5f;
				if (t < 1.0f) return c / 2.0f * pow(2, 10 * (t - 1)) + from;
				t--;
				return c / 2.0f * (-pow(2, -10 * t) + 2) + from;
			}

			static float inCirc(float from, float to, float t)
			{
				float c = to - from;
				t /= 1.0f;
				return -c * (sqrt(1 - t * t) - 1) + from;
			}

			static float outCirc(float from, float to, float t)
			{
				float c = to - from;
				t /= 1.0f;
				t--;
				return c * sqrt(1 - t * t) + from;
			}

			static float inOutCirc(float from, float to, float t)
			{
				float c = to - from;
				t /= 0.5f;
				if (t < 1) return -c / 2.0f * (sqrt(1 - t * t) - 1) + from;
				t -= 2;
				return c / 2.0f * (sqrt(1 - t * t) + 1) + from;
			}

			static float inBounce(float from, float to, float t)
			{
				float c = to - from;
				return c - outBounce(0.0f, c, 1.0f - t) + from; //does this work?
			}

			static float outBounce(float from, float to, float t)
			{
				float c = to - from;

				if ((t /= 1.0f) < (1 / 2.75f))
				{
					return c * (7.5625f * t * t) + from;
				}
				else if (t < (2 / 2.75f))
				{
					return c * (7.5625f * (t -= (1.5f / 2.75f)) * t + .75f) + from;
				}
				else if (t < (2.5 / 2.75))
				{
					return c * (7.5625f * (t -= (2.25f / 2.75f)) * t + .9375f) + from;
				}
				else
				{
					return c * (7.5625f * (t -= (2.625f / 2.75f)) * t + .984375f) + from;
				}
			}

			static float inOutBounce(float from, float to, float t)
			{
				float c = to - from;
				if (t < 0.5f) return inBounce(0, c, t * 2.0f) * 0.5f + from;
				return outBounce(0, c, t * 2 - 1) * 0.5f + c * 0.5f + from;

			}

			static float inElastic(float from, float to, float t)
			{
				float c = to - from;
				if (t == 0) return from;
				if ((t /= 1.0f) == 1) return from + c;
				float p = 0.3f;
				float s = p / 4.0f;
				return -(c * pow(2, 10 * (t -= 1)) * sin((t - s) * (2 * 3.1415926535897931) / p)) + from;
			}

			static float outElastic(float from, float to, float t)
			{
				float c = to - from;
				if (t == 0) return from;
				if ((t /= 1.0f) == 1) return from + c;
				float p = 0.3f;
				float s = p / 4.0f;
				return (c * pow(2, -10 * t) * sin((t - s) * (2 * 3.1415926535897931) / p) + c + from);
			}

			static float inOutElastic(float from, float to, float t)
			{
				float c = to - from;
				if (t == 0) return from;
				if ((t /= 0.5f) == 2) return from + c;
				float p = 0.3f * 1.5f;
				float s = p / 4.0f;
				if (t < 1) return -0.5f * (c * pow(2, 10 * (t -= 1.0f)) * sin((t - 2) * (2 * 3.1415926535897931) / p)) + from;
				return c * pow(2, -10 * (t -= 1)) * sin((t - s) * (2.0f * 3.1415926535897931) / p) * 0.5f + c + from;
			}

			static float inBack(float from, float to, float t)
			{
				float c = to - from;
				float s = 1.70158f;
				t /= 0.5f;
				return c * t * t * ((s + 1) * t - s) + from;
			}

			static float outBack(float from, float to, float t)
			{
				float c = to - from;
				float s = 1.70158f;
				t = t / 1.0f - 1.0f;
				return c * (t * t * ((s + 1) * t + s) + 1) + from;
			}

			static float inOutBack(float from, float to, float t)
			{
				float c = to - from;
				float s = 1.70158f;
				t /= 0.5f;
				if (t < 1) return c / 2.0f * (t * t * (((s *= (1.525f)) + 1) * t - s)) + from;
				t -= 2;
				return c / 2.0f * (t * t * (((s *= (1.525f)) + 1) * t + s) + 2) + from;
			}


		public:
		protected:
		private:
			Type _easeCurveType;//动画曲线类型
		};//class iEaseCurve

	}//SPACE(core)
}//SPACE(i)


