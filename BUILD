package(default_visibility = ["//visibility:public"])

load("@bazel_tools//tools/build_defs/pkg:pkg.bzl", "pkg_tar")
load("@mxebzl//tools/windows:rules.bzl", "pkg_winzip")

config_setting(
    name = "windows",
    values = {
        "crosstool_top": "@mxebzl//tools/windows:toolchain",
    }
)

cc_binary(
    name = "ld42",
    data = ["//content"],
    linkopts = select({
        ":windows": ["-mwindows", "-lSDL2main" ],
        "//conditions:default": [],
    }) + [
        "-lSDL2",
        "-lSDL2_image",
        "-lSDL2_mixer",
        "-static-libstdc++",
        "-static-libgcc",
    ],
    srcs = ["main.cc"],
    deps = [
        "@libgam//:game",
        ":screens",
    ],
)

pkg_winzip(
    name = "ld42-windows",
    files = [
        ":ld42",
        "//content",
    ]
)

pkg_tar(
    name = "ld42-linux",
    extension = "tar.gz",
    srcs = [
        ":ld42",
        "//content",
    ],
)

cc_library(
    name = "screens",
    srcs = [
        "game_screen.cc",
        "title_screen.cc",
    ],
    hdrs = [
        "game_screen.h",
        "title_screen.h",
    ],
    deps = [
        "@libgam//:backdrop",
        "@libgam//:screen",
        "@libgam//:spritemap",
        "@libgam//:text",
        ":meteor",
        ":platform",
        ":player",
        ":space",
    ],
)

cc_library(
    name = "player",
    srcs = [ "player.cc" ],
    hdrs = [ "player.h" ],
    deps = [
        "@libgam//:audio",
        "@libgam//:graphics",
        "@libgam//:input",
        ":platform",
    ],
)

cc_library(
    name = "space",
    srcs = [ "space.cc" ],
    hdrs = [ "space.h" ],
    deps = [
        "@libgam//:graphics",
        "@libgam//:util",
    ],
)

cc_library(
    name = "platform",
    srcs = [ "platform.cc" ],
    hdrs = [ "platform.h" ],
    deps = [
        "@libgam//:graphics",
    ],
)

cc_library(
    name = "meteor",
    srcs = [ "meteor.cc" ],
    hdrs = [ "meteor.h" ],
    deps = [
        "@libgam//:graphics",
        ":player",
    ],
)
