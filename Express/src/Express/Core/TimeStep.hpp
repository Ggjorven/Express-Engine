#pragma once

namespace Express 
{

	class TimeStep
	{
	public:
		TimeStep(float timeInSeconds = 0.0f)
			: m_Time(timeInSeconds)
		{
		}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};

}