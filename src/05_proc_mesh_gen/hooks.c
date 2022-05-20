#include "chunky/hooks.h"

#include "chunky/display.h"
#include "mesh/model.h"
#include "mesh/scene.h"

static Mesh GenMeshCustom(int triangleCount);
Camera3D camera;
Vector3 cubePosition = {0.0f, 0.0f, 0.0f};

Mesh mesh;
Model model;

void Init() {
  camera = InitCamera3D();
  SetCameraMode(camera, CAMERA_ORBITAL);  // Set a first person camera mode

  model = LoadModelFromMesh(GenMeshCustom(1));
};

void Update() {
  // ?
  UpdateCamera(&camera);
};
void PostUpdate(){};
void Draw() {
  /* SetPixel(32, 32, 0xff0000ff); */
  /* DrawCircleGradient(32, 32, 32, GREEN, SKYBLUE); */

  BeginMode3D(camera);

  /* DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED); */
  /* DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON); */

  DrawModel(model, cubePosition, 1, GREEN);
  DrawGrid(10, 1.0f);

  EndMode3D();
};
void PostDraw(){};
void Close(){};

// Generate a simple triangle mesh from code
static Mesh GenMeshCustom(int triangleCount) {
  Mesh mesh = MeshAlloc(1);

  // Vertex at (0, 0, 0)
  mesh.vertices[0] = 0;
  mesh.vertices[1] = 0;
  mesh.vertices[2] = 0;
  mesh.normals[0] = 0;
  mesh.normals[1] = 1;
  mesh.normals[2] = 0;
  mesh.texcoords[0] = 0;
  mesh.texcoords[1] = 0;

  // Vertex at (1, 0, 2)
  mesh.vertices[3] = 1;
  mesh.vertices[4] = 0;
  mesh.vertices[5] = 2;
  mesh.normals[3] = 0;
  mesh.normals[4] = 1;
  mesh.normals[5] = 0;
  mesh.texcoords[2] = 0.5f;
  mesh.texcoords[3] = 1.0f;

  // Vertex at (2, 0, 0)
  mesh.vertices[6] = 2;
  mesh.vertices[7] = 0;
  mesh.vertices[8] = 0;
  mesh.normals[6] = 0;
  mesh.normals[7] = 1;
  mesh.normals[8] = 0;
  mesh.texcoords[4] = 1;
  mesh.texcoords[5] = 0;

  // Upload mesh data from CPU (RAM) to GPU (VRAM) memory
  UploadMesh(&mesh, false);

  return mesh;
}
