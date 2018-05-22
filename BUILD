cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":imgui_helper",
        "//third-party/glad",
        "//third-party/glfw",
        "//third-party/imgui",
    ],
    data = [
        "//third-party/imgui:fonts",
    ],
)

cc_library(
    name = "imgui_helper",
    hdrs = ["imgui_helper.hh"],
    srcs = ["imgui_helper.cc"],
    deps = [
        "//third-party/glad",
        "//third-party/glfw",
        "//third-party/imgui",
    ],
)
