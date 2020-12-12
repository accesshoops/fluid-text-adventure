#pragma once
#include "Effects/Effect.h"
#include "WorldState.h"
#include "Contexts/BaseContext.h"

using namespace FluidHTN;

enum class AIWorldState
{
	HasBottle,
	BottleIsOpen,
	BottleIsEmpty,
	BottleIsBroken,
	HasWeapon,
	Goal
};
enum class GoalState
{
	None,
	GetBottle,
	DropBottle,
	OpenBottle,
	CloseBottle,
	DrinkBottle,
	BreakBottle,
	SlashBottle,
	ThrowBottle,
	GetSword,
	DropSword,
	SlashAir,
};

class AIWorldStateType : public IWorldState<AIWorldState,uint8_t,AIWorldStateType>
{
protected:
    uint8_t _worldState[(int)(AIWorldState::Goal) + 1] = {0};

public:
    bool HasState(AIWorldState state, uint8_t value) 
    {
        return (_worldState[value] == value);
    }


    uint8_t& GetState(AIWorldState state) 
    {
        return _worldState[(int)state];
    }


    void SetState(AIWorldState state, uint8_t value) 
    {
        _worldState[(int)state] = value;
    }


    int GetMaxPropertyCount() 
    {
        return (int)(AIWorldState::Goal)+1;
    }

};

class AIContext : public BaseContext<AIWorldState,uint8_t,AIWorldStateType>
{
private:
    SharedPtr<class Player> _Player;
    SharedPtr<class GameScreen>  _CurrentScreen;
    SharedPtr<AIWorldStateType> _AIWorldState;
public:
    AIContext() = delete;
    AIContext(const SharedPtr<Player>& p)
    {
        _Player = p;
        _DebugMTR = false;
        _LogDecomposition = true;
        _WorldState = MakeSharedPtr<AIWorldStateType>();
    }
    SharedPtr<Player>& Player() { return _Player; }
    SharedPtr<GameScreen>& CurrentScreen(){ return _CurrentScreen; }

    virtual void Init() override
    {
        BaseContext::Init();
        // Custom init of state
    }

    bool HasGoal(GoalState goal)
    {
        return GetGoal() == goal;
    }

    GoalState GetGoal()
    {
        return (GoalState)BaseContext::GetState(AIWorldState::Goal);
    }

    void SetGoal(GoalState goal, bool setAsDirty = true, EffectType effectType = EffectType::Permanent)
    {
        SetState(AIWorldState::Goal, (uint8_t)goal, setAsDirty, effectType);
    }

    bool HasStateAIWS(AIWorldState state, bool value)
    {
        uint8_t val = (value ? 1 : 0);
        return HasState(state, val);
    }

    bool HasStateAIWS(AIWorldState state)
    {
        return HasStateAIWS(state, 1);
    }

    void SetStateAIWS(AIWorldState state, bool value, EffectType type)
    {
        SetState(state, (uint8_t)(value ? 1 : 0), true, type);
    }

    uint8_t GetState(AIWorldState state) 
    {
        return BaseContext::GetState(state);
    }
};
