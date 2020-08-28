#ifndef JET_H_
#define JET_H_


#include "Character.h"

#include "Xinput.h"

class JET
{
public:

	JET();

/**
* @fn
* ジェットと
* @brief 
* @param[out] (char_) キャラクターの情報を渡す
* @detail 
*/
	VOID UseJet(CHAR_*);

private:

	Xinput* xinput[2];

};

#endif