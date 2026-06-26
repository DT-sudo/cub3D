# cub3D

*This project has been created as part of the 42 curriculum by olcherno and dtereshc.*

## Description

cub3D is a simplified [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D)-style
raycasting engine written in C using [MiniLibX](https://github.com/42Paris/minilibx-linux).

The program parses a `.cub` scene description file, validates the map
(walls form a closed perimeter, exactly one player spawn), loads the wall
textures, and renders a real-time first-person 3D view of the map. Each
wall is textured according to its orientation (north/south/east/west) and
the ceiling/floor are filled with the colors defined in the scene file.

## Scene file format (`.cub`)

```
NO ./images/wall_no.xpm
SO ./images/wall_so.xpm
WE ./images/wall_we.xpm
EA ./images/wall_ea.xpm

F 220,100,0
C 25,25,112

1111111111111111111
1000000000000000001
1000000000000000001
1000000S00000000001
1000000000000000001
1111111111111111111
```

- `NO`, `SO`, `WE`, `EA`: paths to the north/south/west/east wall textures
  (XPM images).
- `F`: floor color as `R,G,B`.
- `C`: ceiling color as `R,G,B`.
- The map grid is made of `0` (floor), `1` (wall) and exactly one of
  `N`, `S`, `E`, `W` marking the player's starting position and facing
  direction. The playable area must be fully enclosed by walls.

## Controls

| Key             | Action                |
| --------------- | --------------------- |
| `W` / `A` / `S` / `D` | Move forward / left / back / right |
| `←` / `→`       | Rotate the camera      |
| `ESC` or window close button | Quit the program |

## Build & run

```sh
make
./cub3D maps/mandatory.cub
```

Other useful targets: `make clean`, `make fclean`, `make re`.

## Project structure

- `src/parser*.c` — `.cub` file parsing, header/map validation and the
  flood-fill check that the map is closed.
- `src/textures.c` — loading the wall textures via MiniLibX.
- `src/player*.c` — player state, movement, rotation and collision.
- `src/raycast*.c` — the DDA raycasting loop and column rendering.
- `src/window*.c`, `src/hooks.c` — MiniLibX window setup, the render
  loop and keyboard/close event handling.

## Reading `git status`

`git status -s` (or the "Status" line shown by some tools) prefixes each
file with one or two letters describing its state compared to the last
commit:

- **`M`** (Modified) — the file is tracked by git and its contents have
  changed since the last commit.
- **`A`** (Added) — a new file has been staged (added to the index) but
  not committed yet.
- **`D`** (Deleted) — a tracked file has been removed.
- **`U`** (Unmerged) — the file has a merge conflict that needs to be
  resolved manually (appears during a conflicted merge/rebase).
- **`??`** — the file is untracked (git doesn't know about it yet, e.g.
  build artifacts or new files not yet `git add`ed).

A status with two columns (e.g. `MM`, ` M`, `A `) shows the staged state
(first column) and the working-tree state (second column) separately.

## AI usage disclosure

Parts of this project (code structure, the raycasting/DDA implementation,
parsing logic and the 42-Norm refactor) were written with the assistance
of an AI coding assistant (Claude), based on the algorithms and
requirements described in the subject. All code was reviewed, adapted and
tested by the author.

## Resources

- [Lode's Computer Graphics Tutorial — Raycasting](https://lodev.org/cgtutor/raycasting.html)
- [MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)

## Acknowledgments

- **42 School** — for the project subject and curriculum.
- **libft** — my own C standard-library reimplementation, reused here.
- **MiniLibX** — the lightweight graphics library provided by 42 for window
  management, event handling and image rendering.
