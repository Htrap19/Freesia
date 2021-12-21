//
// Created by htrap19 on 12/20/21.
//

#include "AssimpEntity.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace Freesia
{
    AssimpEntity::AssimpEntity(const std::string& filepath)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

        FS_CORE_ASSERT((scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) != AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode), "[Assimp]: Failed to read file!");

        m_Directory = filepath.substr(0, filepath.find_last_of('/'));
        ProcessNode(scene->mRootNode, scene);
    }

    void AssimpEntity::ProcessNode(aiNode* node, const aiScene* scene)
    {
        for (uint32_t i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            m_Meshes.push_back(ProcessMesh(mesh, scene));
        }

        for (uint32_t i = 0; i < node->mNumChildren; i++)
            ProcessNode(node->mChildren[i], scene);
    }

    RenderMesh AssimpEntity::ProcessMesh(aiMesh* mesh, const aiScene* scene)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        bool hasTexCoord = mesh->mTextureCoords[0] != nullptr;

        glm::vec4 ambient = GetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT);
        glm::vec4 diffuse = GetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE);
        glm::vec4 specular = GetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR);
        glm::vec4 color = ambient + diffuse + specular;
        if (color == glm::vec4(0.0f))
            color = glm::vec4(1.0f);

        // Vertices
        std::vector<Renderer::ModelVertex> vertices;
        for (uint32_t i = 0; i < mesh->mNumVertices; i++)
        {
            Renderer::ModelVertex vertex;

            glm::vec3 pos = { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z };
            glm::vec2 texCoord = { 0.0f, 0.0f };
            // TexCoords
            if (hasTexCoord)
                texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);

            vertex.Position = pos;
            vertex.TexCoord = texCoord;
            vertex.Color = color;

            vertices.push_back(vertex);
        }

        // Indices
        std::vector<uint32_t> indices;
        for (uint32_t i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (uint32_t j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        // Texture
        if (hasTexCoord)
            return { vertices, indices, LoadTexture(material, aiTextureType_DIFFUSE) };

        return { vertices, indices };
    }

    std::vector<Ref<Texture2D>> AssimpEntity::LoadTexture(const aiMaterial* material, aiTextureType type)
    {
        std::vector<Ref<Texture2D>> textures;

        for (uint32_t i = 0; i < material->GetTextureCount(type); i++)
        {
            aiString str;
            material->GetTexture(type, i, &str);

            bool skip = false;
            for (auto& texture : m_Textures)
            {
                if (strcmp(texture->GetPath().c_str(), str.C_Str()) == 0)
                {
                    textures.push_back(texture);
                    skip = true;
                    break;
                }
            }

            if (!skip)
            {
                auto newTexture = Texture2D::Create(m_Directory + "/" + str.C_Str(), false);
                textures.push_back(newTexture);
                m_Textures.push_back(newTexture);
            }
        }

        textures.shrink_to_fit();
        return std::move(textures);
    }

    glm::vec4 AssimpEntity::GetMaterialColor(aiMaterial* material, const char* pkey, uint32_t type, uint32_t idx)
    {
        aiColor4D color;
        if (material->Get(pkey, type, idx, color) == AI_SUCCESS)
            return { color.r, color.g, color.b, color.a };

        return { 0.0f, 0.0f, 0.0f, 0.0f };
    }
}