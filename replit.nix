{ pkgs }: {
	deps = [
		pkgs.netatalk
  pkgs.gh
  pkgs.gitFull
  pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}