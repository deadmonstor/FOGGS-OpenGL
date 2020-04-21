#include "highScores.h"
#include <stddef.h>

highScores* highScores::m_Instance = NULL;

highScores* highScores::Instance()
{
	if (!m_Instance)
		m_Instance = new highScores;

	return m_Instance;
}

void highScores::incrementScore(int i)
{
	if (curScore == 0 && i < 0) return;

	curScore += i;
}

int highScores::getScore()
{
	return curScore;
}