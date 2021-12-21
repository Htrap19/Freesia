//
// Created by Htrap19 on 12/6/21.
//

#ifndef FREESIA_RENDERER_H
#define FREESIA_RENDERER_H

#include "Freesia/Renderer/Camera.h"
#include "Freesia/Renderer/RendererAPI.h"

namespace Freesia
{
    struct RenderMesh;

    class Renderer
    {
    public:
        struct ModelVertex
        {
            glm::vec3 Position;
            glm::mat4 Model = glm::mat4(1.0f);
            glm::vec2 TexCoord;
            glm::vec4 Color = glm::vec4(1.0f);
            float TexIndex;
        };

        struct Statistics
        {
            uint32_t DrawCalls = 0;
            uint32_t MeshCount = 0;
            uint32_t TotalVertices = 0;
            uint32_t TotalIndices = 0;
        };

    public:
        static void Init();
        static void Shutdown();
        static void OnWindowResize(uint32_t width, uint32_t height);

        static inline RendererAPI::Api GetApi() { return RendererAPI::GetApi(); }

        static void BeginScene(Camera& camera, const glm::mat4& view);
        static void EndScene();
        static void Flush();

        static void DrawMesh(const glm::mat4& model, const RenderMesh& mesh);

        static void ResetStats();
        static Statistics GetStats();

    private:
        static void StartBatch();
        static void NextBatch();
    };
}

#endif //FREESIA_RENDERER_H
