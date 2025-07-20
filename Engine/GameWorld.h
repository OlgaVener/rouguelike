#pragma once
#include <vector>
#include "GameObject.h"

namespace GameEngine
{
    class GameWorld
    {
    public:
        static GameWorld* Instance();

        void Update(float deltaTime);
        void Render();
        void LateUpdate();


        GameObject* CreateGameObject();
        void DestroyGameObject(GameObject* gameObject);
        void Clear();

    private:
        std::vector<GameObject*> gameObjects;
        std::vector<GameObject*> markedToDestroyGameObjects;

        void DestroyGameObjectImmediate(GameObject* gameObject);

        GameWorld() = default;
        ~GameWorld() = default;
    };
}