#include "Component.h"
#include "GameObject.h"

namespace GameEngine 
{
    class ColliderComponent : public Component 
    {
    public:
        ColliderComponent(GameObject* gameObject) : Component(gameObject) {}
    };
}
