cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":imgui_helper",
        "//third_party/glad",
        "//third_party/glfw",
        "//third_party/imgui",
        "//third_party/eigen",
    ],
    data = [
        "//third_party/imgui:fonts",
    ],
)

cc_library(
    name = "imgui_helper",
    hdrs = ["imgui_helper.hh"],
    srcs = ["imgui_helper.cc"],
    deps = [
        "//third_party/glad",
        "//third_party/glfw",
        "//third_party/imgui",
    ],
)
