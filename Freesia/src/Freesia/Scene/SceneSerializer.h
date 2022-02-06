//
// Created by htrap19 on 1/30/22.
//

#ifndef FREESIA_SCENESERIALIZER_H
#define FREESIA_SCENESERIALIZER_H

#include "Freesia/Core/Core.h"

#include "Freesia/Scene/Scene.h"

namespace Freesia
{
    class SceneSerializer
    {
    public:
        explicit SceneSerializer(const Ref<Scene>& scene);

        void Serialize(const std::string& filepath);
        void SerializeRuntime(const std::string& filepath);

        bool Deserialize(const std::string& filepath);
        bool DeserializeRuntime(const std::string& filepath);

    private:
        Ref<Scene> m_Scene;
    };
}

#endif //FREESIA_SCENESERIALIZER_H
