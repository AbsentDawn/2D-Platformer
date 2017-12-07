#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

#include<string>
#include <vector>

class GameState
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual bool OnEnter() = 0;
	virtual bool OnExit() = 0;

	virtual std::string GetStateID() const = 0;

	virtual ~GameState() {}

protected:
	std::vector<std::string> _mTextureIdList;
};

#endif