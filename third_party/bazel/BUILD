package(default_visibility = ["//visibility:public"])

licenses(["notice"])  # Apache 2

load("//third_party/protobuf/3.4.1:protobuf.bzl", "py_proto_library")

py_proto_library(
    name = "extra_actions_base_proto",
    srcs = ["proto/extra_actions_base.proto"],
    protoc = "//third_party/protobuf:protoc",
    default_runtime = "//third_party/protobuf:protobuf_python",
)
