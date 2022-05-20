#include "model.h"

Mesh MeshAlloc(int triangleCount) {
  Mesh mesh = {0};
  mesh.triangleCount = triangleCount;
  mesh.vertexCount = mesh.triangleCount * 3;
  mesh.vertices = (float *)MemAlloc(mesh.vertexCount * 3 *
                                    sizeof(float));  // 3 vertices, 3 coordinates each (x, y, z)
  mesh.texcoords = (float *)MemAlloc(mesh.vertexCount * 2 *
                                     sizeof(float));  // 3 vertices, 2 coordinates each (x, y)
  mesh.normals = (float *)MemAlloc(mesh.vertexCount * 3 *
                                   sizeof(float));  // 3 vertices, 3 coordinates each (x, y, z)

  return mesh;
}
