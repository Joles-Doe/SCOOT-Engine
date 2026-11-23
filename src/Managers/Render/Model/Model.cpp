#include "Model.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <cstddef>
#include <filesystem>
#include <stdexcept>

Model::Model(const std::string& name) : modelName(name)
{
    const std::filesystem::path modelDirectory = std::filesystem::path("assets/models") / name;
    const char* extensions[] = {
        ".obj", ".fbx", ".gltf", ".glb", ".dae", ".stl", ".ply", ".3ds"
    };

    std::filesystem::path modelPath;
    for (const char* extension : extensions)
    {
        const auto candidate = modelDirectory / (name + extension);
        if (std::filesystem::exists(candidate))
        {
            modelPath = candidate;
            break;
        }
    }

    if (modelPath.empty())
    {
        modelPath = modelDirectory / (name + ".obj");
    }

    LoadModel(modelPath.string());
    SetupMesh();
}

Model::~Model()
{
    if (ebo != 0)
        glDeleteBuffers(1, &ebo);

    if (vbo != 0)
        glDeleteBuffers(1, &vbo);

    if (vao != 0)
        glDeleteVertexArrays(1, &vao);
}

void Model::LoadModel(const std::string& path)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(
        path,
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_GenNormals |
        aiProcess_FlipUVs |
        aiProcess_PreTransformVertices
    );

    if (scene == nullptr ||
        (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) != 0 ||
        scene->mRootNode == nullptr ||
        scene->mNumMeshes == 0)
    {
        throw std::runtime_error(
            "Failed to load model: " + path + "\n" +
            importer.GetErrorString()
        );
    }

    for (unsigned int meshIndex = 0;
         meshIndex < scene->mNumMeshes;
         ++meshIndex)
    {
        const aiMesh* mesh = scene->mMeshes[meshIndex];
        const GLuint baseVertex = static_cast<GLuint>(vertices.size());

        for (unsigned int vertexIndex = 0;
             vertexIndex < mesh->mNumVertices;
             ++vertexIndex)
        {
            const aiVector3D& position = mesh->mVertices[vertexIndex];
            Vertex vertex;
            vertex.position = glm::vec3(position.x, position.y, position.z);

            if (mesh->HasNormals())
            {
                const aiVector3D& normal = mesh->mNormals[vertexIndex];
                vertex.normal = glm::vec3(normal.x, normal.y, normal.z);
            }

            if (mesh->HasTextureCoords(0))
            {
                const aiVector3D& texCoord = mesh->mTextureCoords[0][vertexIndex];
                vertex.texCoord = glm::vec2(texCoord.x, texCoord.y);
            }

            vertices.push_back(vertex);
        }

        for (unsigned int faceIndex = 0;
             faceIndex < mesh->mNumFaces;
             ++faceIndex)
        {
            const aiFace& face = mesh->mFaces[faceIndex];

            for (unsigned int index = 0;
                 index < face.mNumIndices;
                 ++index)
            {
                indices.push_back(baseVertex + face.mIndices[index]);
            }
        }
    }

    if (vertices.empty() || indices.empty())
    {
        throw std::runtime_error(
            "Model contains no valid geometry: " + path
        );
    }
}

void Model::SetupMesh()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex)),
        vertices.data(),
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(indices.size() * sizeof(GLuint)),
        indices.data(),
        GL_STATIC_DRAW
    );

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        reinterpret_cast<void*>(offsetof(Vertex, position))
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        reinterpret_cast<void*>(offsetof(Vertex, texCoord))
    );

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        reinterpret_cast<void*>(offsetof(Vertex, normal))
    );

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

std::size_t Model::GetVertexCount() const
{
    return vertices.size();
}

std::size_t Model::GetIndexCount() const
{
    return indices.size();
}

void Model::Bind() const
{
    glBindVertexArray(vao);
}
