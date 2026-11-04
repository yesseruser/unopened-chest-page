{
  pkgs ? import <nixpkgs> { },
}:

let
  llvm = pkgs.llvmPackages_21;
in
pkgs.mkShellNoCC {
  packages = [
    llvm.clang-unwrapped # NOT llvm.clang, which is the wrapper that caused the error
    llvm.lld
    llvm.llvm
    pkgs.cmake # Geode needs 3.29+
    pkgs.ninja
    pkgs.ccache
    pkgs.git
  ];

  CC = "${llvm.clang-unwrapped}/bin/clang";
  CXX = "${llvm.clang-unwrapped}/bin/clang++";
}
