#include "pch.h"
#include "GameObject.h"
#include "TransformComponent.h"


namespace Engine 
{
    // явна€ инстанциаци€ шаблона дл€ TransformComponent
    template TransformComponent* GameObject::GetComponent<TransformComponent>();
}