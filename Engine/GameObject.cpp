#include "pch.h"
#include "GameObject.h"
#include "TransformComponent.h"


namespace Engine 
{
    // ����� ������������ ������� ��� TransformComponent
    template TransformComponent* GameObject::GetComponent<TransformComponent>();
}