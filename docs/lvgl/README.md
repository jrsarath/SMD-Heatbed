# LVGL Pro XML Documentation & Developer Reference

This directory contains the official **LVGL Pro XML syntax and architecture documentation** for UI development in `src/lvgl_ui/`.

---

## 📚 Core Syntax & Reference Index

| Topic / Document | File Path | Description |
| :--- | :--- | :--- |
| **Main Syntax Index** | [`syntax.mdx`](syntax.mdx) | High-level index of LVGL XML syntax and building blocks |
| **Introduction** | [`syntax/introduction.mdx`](syntax/introduction.mdx) | Fundamentals of LVGL XML format and UI definition system |
| **Overview & Types** | [`syntax/overview.mdx`](syntax/overview.mdx) | Syntax rules, naming conventions, attributes, property types |
| **Project File** | [`syntax/project.mdx`](syntax/project.mdx) | `project.xml` configuration, targets, and display preview settings |
| **Components** | [`syntax/components.mdx`](syntax/components.mdx) | Reusable UI components with properties, parameters, and slots |
| **Widgets** | [`syntax/widgets.mdx`](syntax/widgets.mdx) | Reference guide for custom and built-in widget tags |
| **Built-in Widgets** | [`built_in_widgets.mdx`](built_in_widgets.mdx) | Built-in LVGL widget schemas and style properties |
| **Screens** | [`syntax/screens.mdx`](syntax/screens.mdx) | Screen definition, navigation, permanent screens, lifecycles |
| **View** | [`syntax/view.mdx`](syntax/view.mdx) | Visual structure, hierarchy, and `<view extends="...">` |
| **Styles** | [`syntax/styles.mdx`](syntax/styles.mdx) | Style sheets, local styles, state selectors, theme bindings |
| **Constants** | [`syntax/constants.mdx`](syntax/constants.mdx) | Global & local constants (`#color_primary`, `#space_md`) |
| **Animations** | [`syntax/animations.mdx`](syntax/animations.mdx) | Timelines, keyframes, transitions, and multi-step animations |
| **Images** | [`syntax/images.mdx`](syntax/images.mdx) | SVG conversion, image assets, external resources |
| **Fonts** | [`syntax/fonts.mdx`](syntax/fonts.mdx) | Font registration, font engines, typography |
| **API Definitions** | [`syntax/api.mdx`](syntax/api.mdx) | Custom component APIs: properties, parameters, enums, elements |
| **Events** | [`syntax/events.mdx`](syntax/events.mdx) | Interaction handling, screen navigation, subject mutation |
| **Data Binding** | [`syntax/data-binding.mdx`](syntax/data-binding.mdx) | Subject binding (`bind_text`, `bind_value`, `bind_style`) |
| **Translations** | [`syntax/translations.mdx`](syntax/translations.mdx) | Multi-language translation string support |
| **Multiple Targets** | [`syntax/targets.mdx`](syntax/targets.mdx) | Display resolution variants and asset pack overrides |
| **Testing** | [`syntax/testing.mdx`](syntax/testing.mdx) | Headless XML test definitions and assertions |
| **Preview** | [`syntax/preview.mdx`](syntax/preview.mdx) | Preview settings and contexts for UI editor |
| **AI Integration** | [`ai.mdx`](ai.mdx) | Guidelines for AI agents generating and validating LVGL XML |
| **CLI Reference** | [`cli.mdx`](cli.mdx) | Command-line tools for validation, generation, and testing |

---

## 🤖 Instructions for AI Agents Working on LVGL XML

When developing, refactoring, or generating XML files in `src/lvgl_ui/`:

1. **Always Consult Local Docs First:** Refer to the corresponding `.mdx` file above before guessing XML tags, attributes, or property names.
2. **Follow Naming Conventions:**
   - Attribute names: lowercase with underscore separation (`bg_color`, `border_width`, `pad_top`).
   - Constant references: prefix with `#` (e.g., `pad="#space_md"`, `color="#color_primary"`).
   - Component property references: prefix with `$` (e.g., `text="$title"`, `value="$current_val"`).
   - Expressions: `{}` syntax without `$` or `#` (e.g., `width="{width - 20}"`).
3. **Use Design Tokens & Components:**
   - Check `src/lvgl_ui/globals.xml` for existing styles, colors, and subject variables.
   - Reuse existing primitives in `src/lvgl_ui/components/` (`container`, `panel`, `row`, `column`, `button`, `text`, `h1`-`h5`, `navigation_bar`, etc.) instead of hardcoding raw styles.
4. **Data Binding Best Practices:**
   - Bind dynamic state to subjects (`bind_text`, `bind_value`, `bind_style`) defined in `globals.xml`.
