{
  "targets": [
    {
      "target_name": "libmeasuresuite",
      "type": "static_library",
      "sources": [
        "./src/lib/alloc_helper.c",
        "./src/lib/checker.c",
        "./src/lib/error/description.c",
        "./src/lib/evaluator.c",
        "./src/lib/fisher_yates.c",
        "./src/lib/io/elf_file.c",
        "./src/lib/io/elf_memory.c",
        "./src/lib/io/elf_parser.c",
        "./src/lib/io/file.c",
        "./src/lib/io/shared_object.c",
        "./src/lib/json.c",
        "./src/lib/loader.c",
        "./src/lib/measuresuite.c",
        "./src/lib/printer.c",
        "./src/lib/randomizer.c",
        "./src/lib/struct_helpers.c",
        "./src/lib/timer.c"
      ],
      "include_dirs": [
        "./src/include"
      ],
      "defines": [
        "USE_ASSEMBLYLINE"
      ]
    },
    {
      "target_name": "measureaddon",
      "sources": [
        "./src/binding/binding.c",
        "./src/binding/enable_functions.c",
        "./src/binding/helper.c",
        "./src/binding/load_functions.c",
        "./src/binding/other_functions.c"
      ],
      "dependencies": [
        "libmeasuresuite"
      ],
      "include_dirs": [
        "./src/include",
        "./src/lib"
      ],
      "libraries": [
        "-lassemblyline"
      ]
    }
  ]
}
