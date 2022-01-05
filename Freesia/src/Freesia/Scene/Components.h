//
// Created by htrap19 on 12/18/21.
//

#ifndef FREESIA_COMPONENTS_H
#define FREESIA_COMPONENTS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

#include "Freesia/Scene/ScriptableEntity.h"
#include "Freesia/Scene/SceneCamera.h"
#include "Freesia/Scene/AssimpEntity.h"

namespace Freesia
{
    struct TagComponent
    {
        std::string Tag;

        TagComponent() = default;
        TagComponent(const TagComponent&) = default;
        explicit TagComponent(const std::string& tag)
            : Tag(tag)
        {}
    };

    struct TransformComponent
    {
        glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        explicit TransformComponent(glm::vec3 translation)
            : Translation(translation)
        {}

        glm::mat4 GetTransform() const
        {
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), Rotation.x, { 1.0f, 0.0f, 0.0f })
                    * glm::rotate(glm::mat4(1.0f), Rotation.y, { 0.0f, 1.0f, 0.0f })
                    * glm::rotate(glm::mat4(1.0f), Rotation.z, { 0.0f, 0.0f, 1.0f });

            return glm::translate(glm::mat4(1.0f), Translation)
                * rotation
                * glm::scale(glm::mat4(1.0f), Scale);
        }
    };

    struct NativeScriptComponent
    {
        ScriptableEntity* Instance = nullptr;

        ScriptableEntity* (*InstantiateScript)() = nullptr;
        void (*DestroyScript)(NativeScriptComponent*) = nullptr;

        template<typename T>
        void Bind()
        {
            InstantiateScript = []() -> ScriptableEntity* { return static_cast<ScriptableEntity*>(new T()); };
            DestroyScript = [](NativeScriptComponent* ncs) -> void { delete ncs->Instance; ncs->Instance = nullptr; };
        }
    };

    struct CameraComponent
    {
        SceneCamera Camera;

        CameraComponent() = default;
        CameraComponent(const CameraComponent&) = default;
    };

    struct SpriteRendererComponent
    {
        glm::vec4 Color = glm::vec4(1.0f);

        SpriteRendererComponent() = default;
        SpriteRendererComponent(const SpriteRendererComponent&) = default;
        explicit SpriteRendererComponent(const glm::vec4& color)
                : Color(color)
        {}
    };

    struct MeshComponent
    {
        AssimpEntity Mesh;

        MeshComponent(const MeshComponent&) = default;
        explicit MeshComponent(const std::string& filepath)
            : Mesh(filepath)
        {}
    };
}

#endif //FREESIA_COMPONENTS_H
