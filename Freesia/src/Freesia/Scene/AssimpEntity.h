//
// Created by htrap19 on 12/20/21.
//

#ifndef FREESIA_ASSIMPENTITY_H
#define FREESIA_ASSIMPENTITY_H

#include <string>
#include <vector>
#include <assimp/scene.h>

#include "Freesia/Renderer/Renderer.h"
#include "Freesia/Renderer/Texture.h"

namespace Freesia
{
    struct RenderMesh
    {
        std::string Name;
        std::vector<Renderer::ModelVertex> Vertices;
        std::vector<uint32_t> Indices;
        std::vector<Ref<Texture2D>> Textures;

        RenderMesh(const std::string& name, const std::vector<Renderer::ModelVertex>& vertices, const std::vector<uint32_t>& indices, const std::vector<Ref<Texture2D>>& textures = {})
            : Name(name), Vertices(vertices), Indices(indices), Textures(textures)
        {}

        inline bool HasTexture() const { return !Textures.empty(); }
    };

    class AssimpEntity
    {
    public:
        AssimpEntity() = default;
        explicit AssimpEntity(const std::string& filepath);

        inline void PushMesh(const RenderMesh& mesh) { m_Meshes.push_back(mesh); }

        inline const std::vector<RenderMesh>& GetMeshes() const { return m_Meshes; }

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
