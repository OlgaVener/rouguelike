#include "pch.h"
#include "TransformComponent.h"
#include "Logger.h"
#include "GameObject.h"

namespace GameEngine
{
    // Конструктор компонента трансформации
    TransformComponent::TransformComponent(GameObject* gameObject)
        : Component(gameObject)  // Инициализация базового класса
    {}

    // Методы Update и Render пустые, так как трансформация 
    // обновляется по требованию через другие методы
    void TransformComponent::Update(float deltaTime) {}
    void TransformComponent::Render() {}

    // === Методы перемещения ===
    void TransformComponent::MoveBy(const Vector2Df& offset)
    {
        MoveBy(offset.x, offset.y);
        isUpdated = false;  // Флаг необходимости обновления матрицы трансформации
    }

    void TransformComponent::MoveBy(float offsetX, float offsetY)
    {
        localPosition.x += offsetX;
        localPosition.y += offsetY;
        isUpdated = false;
    }

    // === Методы установки позиции ===
    void TransformComponent::SetWorldPosition(const Vector2Df& position)
    {
        SetWorldPosition(position.x, position.y);
        isUpdated = false;
    }

    void TransformComponent::SetWorldPosition(float positionX, float positionY)
    {
        Vector2Df newPosition = { positionX, positionY };
        if (parent == nullptr)
        {
            localPosition = newPosition;  // Если нет родителя, локальная = мировая
        }
        else
        {
            // Вычисляем новую локальную трансформацию относительно родителя
            Matrix2D newWorldTransform = createTransform(newPosition, GetWorldRotation(), GetWorldScale());
            localTransform = parent->GetWorldTransform().GetInversed() * newWorldTransform;

            setLocalInfoFrom(localTransform);  // Обновляем локальные параметры
            isUpdated = false;
            updateLocalTransform();  // Обновляем матрицу трансформации
        }
    }

    void TransformComponent::SetLocalPosition(const Vector2Df& position)
    {
        SetLocalPosition(position.x, position.y);
        isUpdated = false;
    }

    void TransformComponent::SetLocalPosition(float positionX, float positionY)
    {
        localPosition.x = positionX;
        localPosition.y = positionY;
        isUpdated = false;
    }

    // === Методы вращения ===
    void TransformComponent::RotateBy(float offset)
    {
        localRotation += offset;
        // Нормализация угла в диапазон [0, 360)
        while (localRotation >= 360) localRotation -= 360;
        while (localRotation < 0) localRotation += 360;
        isUpdated = false;
    }

    void TransformComponent::SetWorldRotation(float angle)
    {
        if (parent == nullptr)
        {
            localRotation = angle;
        }
        else
        {
            // Аналогично позиции - вычисляем относительный поворот
            Matrix2D newWorldTransform = createTransform(GetWorldPosition(), angle, GetWorldScale());
            localTransform = parent->GetWorldTransform().GetInversed() * newWorldTransform;

            setLocalInfoFrom(localTransform);
            isUpdated = false;
            updateLocalTransform();
        }
    }

    void TransformComponent::SetLocalRotation(float angle)
    {
        localRotation = angle;
        // Нормализация угла
        while (localRotation >= 360) localRotation -= 360;
        while (localRotation < 0) localRotation += 360;
        isUpdated = false;
    }

    // === Методы масштабирования ===
    void TransformComponent::ScaleBy(const Vector2Df& scale)
    {
        ScaleBy(scale.x, scale.y);
        isUpdated = false;
    }

    void TransformComponent::ScaleBy(float scaleX, float scaleY)
    {
        localScale.x *= scaleX;
        localScale.y *= scaleY;
        isUpdated = false;
    }

    void TransformComponent::SetWorldScale(const Vector2Df& scale)
    {
        SetWorldScale(scale.x, scale.y);
        isUpdated = false;
    }

    void TransformComponent::SetWorldScale(float scaleX, float scaleY)
    {
        Vector2Df newScale = { scaleX, scaleY };
        if (parent == nullptr)
        {
            localScale = newScale;
        }
        else
        {
            // Вычисляем относительный масштаб
            Matrix2D newWorldTransform = createTransform(GetWorldPosition(), GetWorldRotation(), newScale);
            localTransform = parent->GetWorldTransform().GetInversed() * newWorldTransform;

            setLocalInfoFrom(localTransform);
            isUpdated = false;
            updateLocalTransform();
        }
    }

    void TransformComponent::SetLocalScale(const Vector2Df& scale)
    {
        SetLocalScale(scale.x, scale.y);
        isUpdated = true;
    }

    void TransformComponent::SetLocalScale(float scaleX, float scaleY) {
        if (scaleX == 0 || scaleY == 0) {
            LOG_WARN("Attempt to set zero scale for: " + gameObject->GetName() +
                " X: " + std::to_string(scaleX) +
                " Y: " + std::to_string(scaleY));
            return;
        }

        LOG_INFO("Setting scale for: " + gameObject->GetName() +
            " X: " + std::to_string(scaleX) +
            " Y: " + std::to_string(scaleY));

        localScale.x = scaleX;
        localScale.y = scaleY;
        isUpdated = false;
    }

    // === Методы получения параметров ===
    const Vector2Df& TransformComponent::GetWorldPosition() const
    {
        updateLocalTransform();
        if (parent == nullptr)
        {
            return GetLocalPosition();
        }

        setWorldInfoFrom(parent->GetWorldTransform() * localTransform);
        return position;
    }

    const Vector2Df& TransformComponent::GetLocalPosition() const
    {
        updateLocalTransform();
        return localPosition;
    }

    const float TransformComponent::GetWorldRotation() const
    {
        updateLocalTransform();
        if (parent == nullptr)
        {
            return GetLocalRotation();
        }

        setWorldInfoFrom(parent->GetWorldTransform() * localTransform);
        return rotation;
    }

    const float TransformComponent::GetLocalRotation() const
    {
        updateLocalTransform();
        return localRotation;
    }

    const Vector2Df& TransformComponent::GetWorldScale() const
    {
        updateLocalTransform();
        if (parent == nullptr)
        {
            return GetLocalScale();
        }

        setWorldInfoFrom(parent->GetWorldTransform() * localTransform);
        return scale;
    }

    const Vector2Df& TransformComponent::GetLocalScale() const
    {
        updateLocalTransform();
        return localScale;
    }

    // === Методы работы с иерархией ===
    void TransformComponent::SetParent(TransformComponent* newParent)
    {
        if (parent == newParent) return;

        // Обновляем трансформацию относительно нового родителя
        if (newParent != nullptr)
        {
            Matrix2D newParentInverse = newParent->GetWorldTransform().GetInversed();
            localTransform = newParentInverse * GetWorldTransform();
            setLocalInfoFrom(localTransform);
        }
        else if (parent != nullptr)
        {
            localTransform = parent->GetWorldTransform() * localTransform;
            setLocalInfoFrom(localTransform);
        }

        // Обновляем иерархию GameObject
        if (parent != nullptr)
        {
            parent->gameObject->RemoveChild(gameObject);
        }

        parent = newParent;

        if (parent != nullptr)
        {
            parent->gameObject->AddChild(gameObject);
        }

        isUpdated = false;
    }

    TransformComponent* TransformComponent::GetParent() const
    {
        return parent;
    }

    // Получение мировой матрицы трансформации
    const Matrix2D TransformComponent::GetWorldTransform() const
    {
        updateLocalTransform();

        if (parent == nullptr)
        {
            return localTransform;
        }

        return parent->GetWorldTransform() * localTransform;
    }

    // Вывод информации о трансформации
    void TransformComponent::Print() const
    {
        std::cout << "Transform name: " << gameObject->GetName() << std::endl;

        std::cout << "Position" << std::endl;
        std::cout << "World: (" << GetWorldPosition().x << ", " << GetWorldPosition().y << ")" << std::endl;
        std::cout << "Local: (" << GetLocalPosition().x << ", " << GetLocalPosition().y << ")" << std::endl;

        std::cout << "Rotation" << std::endl;
        std::cout << "World: " << GetWorldRotation() << std::endl;
        std::cout << "Local: " << GetLocalRotation() << std::endl;

        std::cout << "Scale" << std::endl;
        std::cout << "World: (" << GetWorldScale().x << ", " << GetWorldScale().y << ")" << std::endl;
        std::cout << "Local: (" << GetLocalScale().x << ", " << GetLocalScale().y << ")" << std::endl;
    }

    // === Вспомогательные методы ===
    void TransformComponent::setWorldInfoFrom(const Matrix2D& transform) const
    {
        // Извлечение позиции из матрицы
        position.x = transform.GetMatrix()[0][2];
        position.y = transform.GetMatrix()[1][2];

        // Вычисление масштаба
        scale.x = std::sqrt(transform.GetMatrix()[0][0] * transform.GetMatrix()[0][0] +
            transform.GetMatrix()[1][0] * transform.GetMatrix()[1][0]);
        scale.y = std::sqrt(transform.GetMatrix()[0][1] * transform.GetMatrix()[0][1] +
            transform.GetMatrix()[1][1] * transform.GetMatrix()[1][1]);

        // Вычисление угла поворота
        rotation = std::atan2(transform.GetMatrix()[0][1], transform.GetMatrix()[0][0]) * 180 / 3.14159265;
    }

    void TransformComponent::setLocalInfoFrom(const Matrix2D& transform) const
    {
        // Аналогично setWorldInfoFrom, но для локальных координат
        localPosition.x = transform.GetMatrix()[0][2];
        localPosition.y = transform.GetMatrix()[1][2];

        localScale.x = std::sqrt(transform.GetMatrix()[0][0] * transform.GetMatrix()[0][0] +
            transform.GetMatrix()[1][0] * transform.GetMatrix()[1][0]);
        localScale.y = std::sqrt(transform.GetMatrix()[0][1] * transform.GetMatrix()[0][1] +
            transform.GetMatrix()[1][1] * transform.GetMatrix()[1][1]);

        localRotation = std::atan2(transform.GetMatrix()[0][1], transform.GetMatrix()[0][0]) * 180 / 3.14159265;
    }

    void TransformComponent::updateLocalTransform() const
    {
        if (!isUpdated)
        {
            localTransform = createTransform(localPosition, localRotation, localScale);
            isUpdated = true;
        }
    }

    void TransformComponent::updateLocalTransform(const Vector2Df& position, float rotation, const Vector2Df& scale) const
    {
        localPosition = position;
        localRotation = rotation;
        localScale = scale;
        localTransform = createTransform(position, rotation, scale);
        isUpdated = true;
    }

    // Создание матрицы трансформации
    Matrix2D TransformComponent::createTransform(const Vector2Df& position, float rotation, const Vector2Df& scale) const
    {
        Matrix2D transform;
        float rad = rotation * 3.14159265f / 180.0f;  // Перевод градусов в радианы
        float cosRot = cos(rad);
        float sinRot = sin(rad);

        auto& matrix = transform.GetMatrix();

        // Заполнение матрицы 3x3:
        matrix[0][0] = scale.x * cosRot;    // Масштаб X и поворот
        matrix[0][1] = scale.x * -sinRot;    // Поворот с инверсией
        matrix[1][0] = scale.y * sinRot;     // Поворот
        matrix[1][1] = scale.y * cosRot;     // Масштаб Y и поворот
        matrix[0][2] = position.x;           // Позиция X
        matrix[1][2] = position.y;           // Позиция Y
        matrix[2][0] = 0.0f;                 // Не используется в 2D
        matrix[2][1] = 0.0f;                 // Не используется в 2D
        matrix[2][2] = 1.0f;                 // Однородная координата

        return transform;
    }
}