#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>

#define EPSILON 0.000001

glm::vec3 atgv3(const aiVector3D &vec) {
    return {vec.x, vec.y, vec.z};
}

bool rti(const glm::vec3 &rayOrig, const glm::vec3 &rayDir, const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c,
         glm::vec3 *intersect) {
    const auto e1 = b - a;
    const auto e2 = c - a;

    const auto pvec = glm::cross(rayDir, e2);
    const auto det = glm::dot(e1, pvec);

    if (fabs(det) < EPSILON)
        return false;

    const auto invDet = 1.f / det;
    const auto tvec = rayOrig - a;

    const auto u = glm::dot(tvec, pvec) * invDet;
    if (u < 0.f || u > 1.f)
        return false;

    const auto qvec = glm::cross(tvec, e1);
    const auto v = glm::dot(rayDir, qvec) * invDet;
    if (v < 0.f || u + v > 1.f)
        return false;

    const auto t = glm::dot(e2, qvec) * invDet;

    intersect->x = u;
    intersect->y = v;
    intersect->z = t;

    return true;
}

int main() {
    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile("skull.obj", aiProcess_CalcTangentSpace |
                                                          aiProcess_Triangulate |
                                                          aiProcess_JoinIdenticalVertices |
                                                          aiProcess_SortByPType);


    const glm::vec3 a(-1.f, -1.f, 4.f);
    const glm::vec3 b(0.f, 1.f, 4.f);
    const glm::vec3 c(1.f, -1.f, 4.f);

    const glm::vec3 rayOrig(0.f, 0.f, 0.f);
    const glm::vec3 rayDir(0.f, 0.f, 1.f);

    glm::vec3 intersect;
    if (rti(rayOrig, rayDir, a, b, c, &intersect))
        printf("Intersect found at (%f, %f, %f)\n", intersect.x, intersect.y, intersect.z);

    return 0;
}
