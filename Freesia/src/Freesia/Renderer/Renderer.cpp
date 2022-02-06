//
// Created by Htrap19 on 12/6/21.
//

#include "Renderer.h"

#include "Freesia/Renderer/RenderCommand.h"
#include "Freesia/Renderer/Shader.h"
#include "Freesia/Renderer/Texture.h"

#include "Freesia/Scene/AssimpEntity.h"

namespace Freesia
{
    struct RendererData
    {
        static const uint32_t MaxVertices = UINT32_MAX / 16;
        static const uint32_t MaxIndices = (UINT32_MAX / 16) / sizeof(uint32_t);
        static const uint32_t MaxTextureSlots = 32;

        Ref<VertexArray> ModelVertexArray;
        Ref<VertexBuffer> ModelVertexBuffer;
        Ref<IndexBuffer> ModelIndexBuffer;
        Ref<Shader> ModelShader;
        Ref<Texture2D> WhiteTexture;

        std::array<Ref<Texture2D>, RendererData::MaxTextureSlots> TexturesSlots;
        uint32_t TextureSlotsIndex = 1; // 0 - White Texture
        uint32_t IndexOffset = 0;
        uint32_t IndexCount = 0;

        Renderer::Statistics stats;
    };

    static RendererData s_Data;

    void Renderer::Init()
    {
        RenderCommand::Init();

        // Model Init
        int32_t samplers[RendererData::MaxTextureSlots];
        for (int32_t i = 0; i < RendererData::MaxTextureSlots; i++)
            samplers[i] = i;
        s_Data.ModelShader = Shader::Create("assets/shaders/Model3D.glsl");
        s_Data.ModelShader->Bind();
        s_Data.ModelShader->SetIntArray("u_Textures", samplers, RendererData::MaxTextureSlots);

        s_Data.ModelVertexArray = VertexArray::Create();
        s_Data.ModelVertexBuffer = VertexBuffer::Create(RendererData::MaxVertices);
        s_Data.ModelVertexBuffer->SetLayout({
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Mat4, "a_Model" },
            { ShaderDataType::Float2, "a_TexCoord" },
            { ShaderDataType::Float4, "a_Color" },
            { ShaderDataType::Float, "a_TexIndex" }
        });

        s_Data.ModelIndexBuffer = IndexBuffer::Create(RendererData::MaxIndices);

        s_Data.ModelVertexArray->AddVertexBuffer(s_Data.ModelVertexBuffer);
        s_Data.ModelVertexArray->SetIndexBuffer(s_Data.ModelIndexBuffer);

        s_Data.WhiteTexture = Texture2D::Create(1, 1);
        uint32_t whiteData = 0xffffffff;
        s_Data.WhiteTexture->SetData(&whiteData, sizeof(uint32_t));

        s_Data.TexturesSlots[0] = s_Data.WhiteTexture;
    }

    void Renderer::Shutdown()
    {
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    void Renderer::BeginScene(const Camera& camera, const glm::mat4& view)
    {
        ResetStats();

        s_Data.ModelShader->Bind();
        s_Data.ModelShader->SetMat4("u_Projection", camera.GetProjection());
        s_Data.ModelShader->SetMat4("u_View", view);

        StartBatch();
    }

    void Renderer::EndScene()
    {
        Flush();
    }

    void Renderer::Flush()
    {
        if (s_Data.IndexCount == 0)
            return; // Nothing to draw

        // Bind textures
        for (uint32_t i = 0; i < s_Data.TextureSlotsIndex; i++)
            s_Data.TexturesSlots[i]->Bind(i);

        s_Data.ModelShader->Bind();
        RenderCommand::DrawIndexed(s_Data.ModelVertexArray, s_Data.IndexCount);

        s_Data.stats.DrawCalls++;
    }

    void Renderer::DrawMesh(const glm::mat4& model, const RenderMesh& mesh, const glm::vec4& color)
    {
        uint32_t numVertices = mesh.Vertices.size();
        uint32_t numIndices = mesh.Indices.size();

        if (s_Data.IndexCount >= RendererData::MaxIndices)
            NextBatch();

        float textureIndex = 0.0f;
        for (uint32_t i = 0; i < s_Data.TextureSlotsIndex; i++)
        {
            for (const auto& texture : mesh.Textures)
            {
                if (*texture == *s_Data.TexturesSlots[i])
                {
                    textureIndex = (float)i;
                    break;
                }
            }
        }

        if (textureIndex == 0.0f && mesh.HasTexture())
        {
            textureIndex = (float)s_Data.TextureSlotsIndex;
            s_Data.TexturesSlots[s_Data.TextureSlotsIndex++] = mesh.Textures[0];
        }

        auto tmpMesh = mesh;
        for (auto& vertex : tmpMesh.Vertices)
            vertex.Model = model, vertex.TexIndex = textureIndex, vertex.Color = color;

        for (auto& idx : tmpMesh.Indices)
            idx = s_Data.IndexOffset + idx;

        s_Data.ModelVertexBuffer->SetData(tmpMesh.Vertices.data(), numVertices * sizeof(Renderer::ModelVertex), s_Data.IndexOffset * sizeof(Renderer::ModelVertex));
        s_Data.ModelIndexBuffer->SetData(tmpMesh.Indices.data(), numIndices, s_Data.IndexCount);

        s_Data.IndexOffset += numVertices;
        s_Data.IndexCount += numIndices;

        s_Data.stats.MeshCount++;
        s_Data.stats.TotalVertices += numVertices;
        s_Data.stats.TotalIndices += numIndices;
    }

    void Renderer::ResetStats()
    {
        memset(&s_Data.stats, 0, sizeof(Renderer::Statistics));
    }

    Renderer::Statistics Renderer::GetStats()
    {
        return s_Data.stats;
    }

    void Renderer::StartBatch()
    {
        s_Data.TextureSlotsIndex = 1;
        s_Data.IndexCount = 0;
        s_Data.IndexOffset = 0;
    }

    void Renderer::NextBatch()
    {
        Flush();
        StartBatch();
    }
}