{
  description = "Dev environment for UnopenedChestPage";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";

  outputs =
    { nixpkgs, ... }:
    let
      systems = [
        "x86_64-linux"
        "aarch64-linux"
        "x86_64-darwin"
        "aarch64-darwin"
      ];
      forAllSystems = f: nixpkgs.lib.genAttrs systems (system: f nixpkgs.legacyPackages.${system});
    in
    {
      devShells = forAllSystems (
        pkgs:
        let
          llvm = pkgs.llvmPackages_21;
        in
        {
          default = pkgs.mkShellNoCC {
            packages = [
              llvm.clang-unwrapped # NOT llvm.clang, which is the wrapper that caused the error
              pkgs.gcc-unwrapped
              llvm.lld
              llvm.llvm
              pkgs.cmake # Geode needs 3.29+
              pkgs.ccache
              pkgs.git
            ];

            CC = "${llvm.clang-unwrapped}/bin/clang";
            CXX = "${llvm.clang-unwrapped}/bin/clang++";
          };
        }
      );

      formatter = forAllSystems (pkgs: pkgs.nixfmt);
    };
}
