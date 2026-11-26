//////////////////////////////////////////////////////////////////////////
//
// by Hwang Ki-Young, 2011/05/07
//
// File Name : Uncopyable.h
//
// 개체 복사 금지용 클래스
//
//////////////////////////////////////////////////////////////////////////

#ifndef UNCOPYABLE_UTIL
#define UNCOPYABLE_UTIL

struct UnCopyable
{
protected:
    UnCopyable() {};
    ~UnCopyable() {};

private:
    UnCopyable(const UnCopyable&);
    UnCopyable& operator= (const UnCopyable&);
};

#endif
