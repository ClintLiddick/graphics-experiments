licenses(["notice"])  # zlib/libpng

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "imgui",
    hdrs = [
        "imgui.h",
        "imconfig.h",
    ],
    srcs = [
        "imgui.cpp",
        "imgui_demo.cpp",
        "imgui_draw.cpp",
        "imgui_internal.h",
        "stb_rect_pack.h",
        "stb_textedit.h",
        "stb_truetype.h",
    ],
    strip_include_prefix = "",
)

cc_binary(
    name = "binary_to_compressed_c",
    srcs = ["misc/fonts/binary_to_compressed_c.cpp"],
)

filegroup(
    name = "fonts",
    srcs = glob(["misc/fonts/*.ttf"]),
)
