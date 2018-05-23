licenses(["notice"])  # zlib/libpng

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "glfw",
    hdrs = [
        "include/GLFW/glfw3.h",
        "include/GLFW/glfw3native.h",
    ],
    srcs = [
        # common
        "src/internal.h",
        "src/context.c",
        "src/init.c",
        "src/input.c",
        "src/monitor.c",
        "src/vulkan.c",
        "src/window.c",
        # X11
        "src/x11_init.c",
        "src/x11_monitor.c",
        "src/x11_platform.h",
        "src/x11_window.c",
        "src/xkb_unicode.c",
        "src/xkb_unicode.h",
        "src/linux_joystick.c",
        "src/linux_joystick.h",
        "src/posix_time.c",
        "src/posix_time.h",
        "src/posix_tls.c",
        "src/posix_tls.h",
        "src/glx_context.c",
        "src/glx_context.h",
        "src/egl_context.c",
        "src/egl_context.h",
    ],
    strip_include_prefix = "include",
    linkopts = [
        "-ldl",
        "-lGL",
        "-lX11",
        "-lXrandr",
        "-lXi",
        "-lXxf86vm",
        "-lXcursor",
        "-lXinerama",
        "-lpthread",
    ],
    copts = ["-fpic"],
    defines = [
        "_GLFW_X11",
    ]
)
