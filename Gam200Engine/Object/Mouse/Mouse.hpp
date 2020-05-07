/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Mouse.hpp
Author
        sinil.gang -rtd99062@gmail.com
Creation Date: 03.31.2020

    Header file for an AI.
        This object derived from mouse who attacks cheese (Player).
******************************************************************************/

#include <Object/Object.hpp>

class Player;

class Mouse : public Object
{
public:
    struct Patrol_Info
    {
        const vector2 positionA;
        const vector2 positionB;
        bool isGoingTOA;

        Patrol_Info(vector2 positionA, vector2 positionB)
            :positionA(positionA), positionB(positionB), isGoingTOA(true)
        {}
    };

    struct PlayerContainer
    {
        Player* player1;
        Player* player2;

        PlayerContainer(Player* player1, Player* player2)
            : player1(player1), player2(player2)
        {}
    };
public:
    Mouse(vector2 translation, vector2 patrol1, vector2 patrol2, Player* player1, Player* player2, double waitTime = 0.02f);
    ~Mouse();

    void SetMouseName();

    double GetWaitTime() const noexcept;
    void SetWaitTime(double time) noexcept;

    double GetLocalTimer() const noexcept;
    void SetLocalTimer(double time) noexcept;

    Patrol_Info& GetPatrolInfo() noexcept;
    const PlayerContainer& GetPlayers() const noexcept;
private:
    double waitTime;
    double localTimer;
    Patrol_Info patrol_info;

    PlayerContainer players;
};