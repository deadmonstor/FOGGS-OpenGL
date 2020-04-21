#pragma once

class highScores
{
	public:
		void incrementScore(int i);
		static highScores* Instance();
		int getScore();

	private:
		int curScore = 0;
		static highScores* m_Instance;


};

