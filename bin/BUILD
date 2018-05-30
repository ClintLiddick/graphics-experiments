cc_binary(
    name = "empty",
    srcs = ["empty.cc"],
    deps = [
        "//third_party/glog",
    ],
)

cc_binary(
    name = "circle_v1",
    srcs = ["circle_v1.cc"],
    deps = [
        "//gl:includes",
        "//third_party/eigen",
    ],
)

cc_binary(
    name = "imgui_demo",
    srcs = ["imgui_demo.cc"],
    deps = [
        "//:imgui_helper",
        "//gl:includes",
        "//third_party/imgui",
    ],
    data = [
        "//third_party/imgui:fonts",
    ],
)
