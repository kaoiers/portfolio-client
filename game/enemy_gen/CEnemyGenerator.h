//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/10/02
//
// File Name : CEnemyGenerator.h
// 
// 적군 생성기
// 
//////////////////////////////////////////////////////////////////////////



#ifndef ENEMY_GENERATOR_H
#define ENEMY_GENERATOR_H


class CGameMap;
class CGameUnitEnemy;

class CEnemyGenerator
{
	u32					m_uEnemyGeneratePeriod;
	u32					m_uEnemyApperPeriod;
	line3df				m_lEnemyGenerateLine;
	CGameMap*			m_pGameMap;
	u32					m_uNextAppearTime;
	u32					m_uNextGenerateTime;
	bool				m_bGenerateFlag;
	bool				m_bStartFlag;
	

	u32					m_uEnemyMaxCounts;
	u32					m_uCurrentEnemyMaxCounts;
	u32					m_uDeadEnemies;
	CGameUnitEnemy*		m_pEnemy;
	bool				m_bOnWave;
	bool				m_bCompleteWave;

	void				Initialize();
	CGameUnitEnemy*		GenerateEnemy();

public :


	CEnemyGenerator(CGameMap*	pMap, const u32 EnemyGeneratePeriod,
		const  u32	EnemyApperPeriod, const u32   EnemyMaxCounts);
	


	~CEnemyGenerator();

	void	addDeadCount();

	const	line3df&	getEnemyGenerateLine() { return m_lEnemyGenerateLine; }

	void	SetStartWave() {};

	bool	isInGenerate();
};


#endif