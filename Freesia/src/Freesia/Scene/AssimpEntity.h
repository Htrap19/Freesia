//
// Created by htrap19 on 12/20/21.
//

#ifndef FREESIA_ASSIMPENTITY_H
#define FREESIA_ASSIMPENTITY_H

#include <string>
#include <vector>
#include <assimp/scene.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Freesia/Renderer/Renderer.h"
#include "Freesia/Renderer/Texture.h"

namespace Freesia
{
    struct RenderMesh
    {
        std::vector<Renderer::ModelVertex> Vertices;
        std::vector<uint32_t> Indices;
        std::vector<Ref<Texture2D>> Textures;
        glm::vec4 Color;
        std::string Name;

        RenderMesh(const std::vector<Renderer::ModelVertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<Ref<Texture2D>>& textures = {}, const std::string& name = "", const glm::vec4& color = glm::vec4(1.0f))
            : Vertices(vertices), Indices(indices), Textures(textures), Color(color), Name(name)
        {}

        inline bool HasTexture() const { return !Textures.empty(); }
    };

    class AssimpEntity
    {
    public:
        AssimpEntity() = default;
        explicit AssimpEntity(const std::string& filepath);

        inline const std::vector<RenderMesh>& GetMeshes() const { return m_Meshes; }
        inline std::vector<RenderMesh>& GetMeshes() { return m_Meshes; }

    protected:
        void ProcessNode(aiNode* node, const aiScene* scene);
        std::vector<Ref<Texture2D>> LoadTexture(const aiMaterial* material, aiTextureType type);
        RenderMesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

    private:
        static glm::vec4 GetMaterialColor(aiMaterial* material, const char* pkey, uint32_t type, uint32_t idx);

    private:
        std::string m_Directory;
        std::vector<RenderMesh> m_Meshes;
        std::vector<Ref<Texture2D>> m_Textures;
    };
}

#endif //FREESIA_ASSIMPENTITY_H
