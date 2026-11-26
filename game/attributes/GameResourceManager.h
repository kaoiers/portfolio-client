//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/06/27
//
// File Name : GameResourceManager.h
// 
// 구리, 은, 쌀 리소스 자원 관리
// 
//////////////////////////////////////////////////////////////////////////


#define GameResource CGameResourceManager::GetInstance()

class CTextGUI;

struct GlobalResource
{
	unsigned	int		crop;
	unsigned	int		lumber;
	unsigned	int		stone;
};

class CGameResourceManager
{
	GlobalResource*		m_pGameGlobalResource;
	u32					m_uCurrentPlayerLevel;
	u32					m_uCurrentPlayerExp;
	const	u32			m_uInitialExp;
	u32					m_uUnitCounts;
	u32					m_uTotalUnitCounts;
	

	unsigned	int		m_iFlag;
	const	u32			TimeDescendentInterval;
	
	u32					LastUpdatedTime;
	u32					CurrentCrop, CurrentStone, CurrentWood; 

	CTextGUI*			text_gold ;
	CTextGUI*			text_lumber;
	CTextGUI*			text_stone;
	CTextGUI*			text_unit;

	static	CGameResourceManager* m_pInstance;
	
public :

	CGameResourceManager(u32 unitLimits = 10); 

	~CGameResourceManager() 
	{
		SAFE_DELETE(m_pGameGlobalResource);
	}

	void Init();

	static	CGameResourceManager*	GetInstance() {return m_pInstance;};

	void				update(u32 timeMs);
	void				IncreaseStatusCycle();	
	void				DecreaseStatusCycle();
	bool				IsAllResourcesSetting() const;

	
	void				AddPlayerExp(u32 exp);
	void				IncreaseExp( u32 exp);
	const u32			getCurrentLevel() { return m_uCurrentPlayerLevel; }
	
	void				addUnitCounts(); 
	void				SubstractUnitCounts();
	const u32			getUnitCounts() { return m_uUnitCounts; }
	const u32			getTotalUnitCounts() { return m_uTotalUnitCounts; }
	u32					getMaxPlayerExp(u32 level) ;

	inline void AddAllResources(int g, int l, int s)
	{ 
		GlobalResource temp;
		temp.crop = g;
		temp.lumber = l;
		temp.stone = s;	
	}

	
	inline void AddCropResource(unsigned int crop)
	{
		GlobalResource temp;
		temp.crop  = crop;		
		
	}

	inline void AddLumberResource(unsigned int lum)
	{
		GlobalResource temp;
		temp.lumber  = lum;
		
	}

	inline void AddStoneResource(unsigned int stone)
	{
		GlobalResource temp;
		temp.stone  = stone;
		
	}

	bool	isOnMyGame();

public :

	void	OnNetworkSetResources(unsigned int crop,
		unsigned int woods,  unsigned int gold );



};