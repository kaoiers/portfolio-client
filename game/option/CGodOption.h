//////////////////////////////////////////////////////////////////////////
// 
// by Hwang Ki-Young, 2011/11/09
//
// File Name : CGodOption.h
// 
// 게임 옵션 설정 클래스
//
//////////////////////////////////////////////////////////////////////////

#ifndef GOD_OPTION_H
#define GOD_OPTION_H

#include "../common/UncopyableUtil.h"

class CGodOption : private UnCopyable
{
	bool	m_bUseSound;				//	사운드
	bool	m_bUseShader;				//	쉐이더
	bool	m_bUseShadow;				//	그림자
	bool	m_bUseVolume;				//	볼륨
	bool    m_bUseFullScreen;			//	풀스크린


	


public :

	CGodOption() : 
		m_bUseSound(false),
		m_bUseShader(false),
		m_bUseShadow(false),
		m_bUseVolume(false),
		m_bUseFullScreen(false)
		
	{
	}

	~CGodOption()
	{};

	void	setUseSound(bool _on) { m_bUseSound = _on; }
	void	setUseShader(bool _on) { m_bUseShader = _on; }
	void	setUseShadow(bool _on) { m_bUseShadow = _on;}
	void	setUseVolume(bool _on) { m_bUseVolume = _on;}
	void    setUseFullScreen(bool _on) { m_bUseFullScreen = _on;}

	const bool	 isSoundOn() const { return m_bUseSound; }
	const bool   isShaderOn() const  { return m_bUseShader; }
	const bool	 isShadowOn() const { return m_bUseShadow; }
	const bool	 isVolumeOn() const { return m_bUseVolume; }
	const bool   isFullScreen() const { return m_bUseFullScreen; }
	

	static	CGodOption*		GetInstance();

};


#endif