#include "Pch.h"
#include "ConfigUtilities.h"
#include "Camera.h"

Vector2 Camera::WorldToScreen(ViewMatrixStruct view_matrix, Vector3 pos)
{
    int screen_width = Configs.Overlay.OverrideResolution ? Configs.Overlay.Width : GetSystemMetrics(SM_CXSCREEN);
    int screen_height = Configs.Overlay.OverrideResolution ? Configs.Overlay.Height : GetSystemMetrics(SM_CYSCREEN);

    float x, y, z;
    x = pos.x;
    y = pos.y;
    z = pos.z;

    float clip_x = x * view_matrix._0 + y * view_matrix._1 + z * view_matrix._2 + view_matrix._3;
    float clip_y = x * view_matrix._4 + y * view_matrix._5 + z * view_matrix._6 + view_matrix._7;
    float clip_w = x * view_matrix._12 + y * view_matrix._13 + z * view_matrix._14 + view_matrix._15;

    if (clip_w < 0.1)
        return Vector2(0, 0);

    float screen_x = (screen_width / 2) * (clip_x / clip_w) + (screen_width / 2);
    float screen_y = -(screen_height / 2) * (clip_y / clip_w) + (screen_height / 2);

    if (screen_x > screen_width or screen_y > screen_height or screen_x < 0 or screen_y < 0)
        return Vector2(0, 0);

    return Vector2(screen_x, screen_y);
}