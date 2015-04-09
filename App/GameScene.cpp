#include "GameScene.h"


GameScene::GameScene()
	: m_isNextScene(false)
	, m_isFirst(true)
	, m_isNextRyuukyoku(false)
	, m_isNextAgari(false)
	, m_isNextFuuro(false)
{
}

GameScene::~GameScene() throw()
{
}

bool GameScene::IsNextScene() const
{
	return m_isNextScene;
}

bool GameScene::IsFirst()
{
	if (m_isFirst)
	{ 
		m_isFirst = false;
		return true;
	}
	return false;
}

void GameScene::NextScene(bool isNextScene)
{
	m_isNextScene = isNextScene;
}

void GameScene::NextRyuukyoku(bool isNextRyuukyoku)
{
	m_isNextRyuukyoku = isNextRyuukyoku;
}
void GameScene::NextAgari(bool isNextAgari)
{
	m_isNextAgari = isNextAgari;
}
void GameScene::NextFuuro(bool isNextFuuro)
{
	m_isNextFuuro = isNextFuuro;
}
