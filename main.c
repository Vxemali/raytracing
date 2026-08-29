#include "raylib.h"
#include <math.h>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 300

typedef struct { float x, y, z; } Vector3f;

typedef struct { Vector3f origin, direction; } Ray3f;

typedef struct {
    bool hit;
    float t;
    Vector3f point;
    Vector3f normal;
    Color color;
} HitResult;

Vector3f Add(Vector3f a, Vector3f b) { return (Vector3f){a.x + b.x, a.y + b.y, a.z + b.z}; }
Vector3f Sub(Vector3f a, Vector3f b) { return (Vector3f){a.x - b.x, a.y - b.y, a.z - b.z}; }
Vector3f Scale(Vector3f a, float b) { return (Vector3f){a.x * b, a.y * b, a.z * b}; }
float Dot(Vector3f a, Vector3f b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
Vector3f Normalize(Vector3f v) {
    float len = sqrtf(Dot(v, v));
    return len == 0 ? v : (Vector3f){v.x / len, v.y / len, v.z / len};
}

HitResult IntersectSphere(Ray3f ray, Vector3f center, float radius, Color col) {
    HitResult res = {0};
    Vector3f oc = Sub(ray.origin, center);
    float a = Dot(ray.direction, ray.direction);
    float b = 2.0f * Dot(oc, ray.direction);
    float c = Dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        float t = (-b - sqrtf(discriminant)) / (2.0f * a);
        if (t > 0.001f) {
            res.hit = true;
            res.t = t;
            res.point = Add(ray.origin, Scale(ray.direction, t));
            res.normal = Normalize(Sub(res.point, center));
            res.color = col;
        }
    }
    return res;
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Minimal Raytracer - Raylib");
    SetTargetFPS(60);

    Image canvas = GenImageColor(SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
    Texture2D texture = LoadTextureFromImage(canvas);

    Vector3f sphereCenter = {0.0f, 0.0f, 3.0f};
    float sphereRadius = 1.0f;
    Vector3f lightDir = Normalize((Vector3f){-1.0f, 1.0f, -1.0f});

    while (!WindowShouldClose()) {
        sphereCenter.x = sinf((float)GetTime()) * 0.75f;

        ImageDrawRectangle(&canvas, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            for (int x = 0; x < SCREEN_WIDTH; x++) {
                float u = (2.0f * x / SCREEN_WIDTH) - 1.0f;
                float v = (1.0f - (2.0f * y / SCREEN_HEIGHT)) * ((float)SCREEN_HEIGHT / SCREEN_WIDTH);

                Ray3f ray = { {0.0f, 0.0f, 0.0f}, Normalize((Vector3f){u, v, 1.0f}) };

                HitResult hit = IntersectSphere(ray, sphereCenter, sphereRadius, RED);

                if (hit.hit) {
                    float diff = fmaxf(0.0f, Dot(hit.normal, lightDir));
                    float ambient = 0.2f;
                    float light = fminf(1.0f, diff + ambient);

                    Color finalColor = {
                        (unsigned char)(hit.color.r * light),
                        (unsigned char)(hit.color.g * light),
                        (unsigned char)(hit.color.b * light),
                        255
                    };
                    ImageDrawPixel(&canvas, x, y, finalColor);
                }
            }
        }

        UpdateTexture(texture, canvas.data);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(texture, 0, 0, WHITE);
        DrawText("Minimal CPU Raytracer", 10, 10, 10, DARKGRAY);
        EndDrawing();
    }

    UnloadTexture(texture);
    UnloadImage(canvas);
    CloseWindow();

    return 0;
}