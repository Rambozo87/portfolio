# portfolio

Project content repository for the independent Astro portfolio website.

## Project structure

Each project is a lowercase-hyphen directory under `projects/` with a validated `project.md`:

```text
projects/
  project-slug/
    project.md
    src/       # approved source roots
    include/   # optional approved source root
    examples/  # optional approved source root
    tests/     # optional approved source root
    images/    # Markdown-referenced documentation assets
    docs/      # Markdown-referenced PDF assets
```

The frontmatter requires non-empty `title` and `description`. Optional fields are `tags`, `status`, `year`, `featured`, and `order`.

## Publishing boundaries

The website reads this repository as data at build time and never executes project code or scripts. Documentation publishes only explicitly referenced PNG, JPEG, WebP, GIF, AVIF, and PDF files after path, symlink, size, and basic file-signature validation. The source browser separately publishes only UTF-8 text files with approved extensions from `src/`, `include/`, `examples/`, or `tests/`, up to 256 KiB per file. Unsupported files are skipped; hidden paths, symlinks, traversal, invalid text, invalid JSON, and oversized files are rejected.

To add a project, create the directory and `project.md`, add documentation and approved source files under the allowed roots, then run `npm test` and `npm run build` from `../portfolio-website`. To remove a project, delete only its project directory after checking for unrelated changes; no website route needs manual editing.
