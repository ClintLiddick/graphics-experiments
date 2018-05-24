licenses(["reciprocal"])  # MPL2
exports_files(["COPYING.MPL2"])

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "eigen",
    hdrs = glob(["Eigen/**/*"]),
    strip_include_prefix = "",
    defines = ["EIGEN_MPL2_ONLY"]
)

cc_library(
    name = "eigen_unsupported",
    hdrs = glob(["unsupported/Eigen/**/*"]),
    strip_include_prefix = "unsupported",
    defines = ["EIGEN_MPL2_ONLY"]
)
