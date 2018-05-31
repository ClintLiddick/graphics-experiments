package(default_visibility = ["//visibility:public"])

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

py_binary(
    name = "completions",
    srcs = ["completions.py"],
    deps = [
        "//third_party/bazel:extra_actions_base_proto",
        "//third_party/protobuf:protobuf_python",
    ], 
)
