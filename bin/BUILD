cc_binary(
    name = "circle_v1",
    srcs = ["circle_v1.cc"],
    deps = [
        "//third_party/glad",
        "//third_party/glfw",
        "//third_party/eigen",
    ],
)

cc_binary(
    name = "imgui_demo",
    srcs = ["imgui_demo.cc"],
    deps = [
        "//:imgui_helper",
        "//third_party/glad",
        "//third_party/glfw",
        "//third_party/imgui",
    ],
    data = [
        "//third_party/imgui:fonts",
    ],
)
