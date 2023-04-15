{ pkgs }: {
	deps = [
		pkgs.gitFull
  pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}