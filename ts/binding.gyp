{
  "variables": {
    "hasAL": "'<!(pkg-config --exists assemblyline --silence-errors && echo y || echo n)'=='y'"
  },
  "targets": [
    {
      "target_name": "libmeasuresuite",
      "type": "static_library",
      "sources": [
        "../lib/src/alloc_helper.c",
        "../lib/src/checker.c",
        "../lib/src/error/description.c",
        "../lib/src/evaluator.c",
        "../lib/src/fisher_yates.c",
        "../lib/src/io/elf_file.c",
        "../lib/src/io/elf_memory.c",
        "../lib/src/io/elf_parser.c",
        "../lib/src/io/file.c",
        "../lib/src/io/shared_object.c",
        "../lib/src/json.c",
        "../lib/src/loader.c",
        "../lib/src/measuresuite.c",
        "../lib/src/printer.c",
        "../lib/src/randomizer.c",
        "../lib/src/struct_helpers.c",
        "../lib/src/timer.c"
      ],
      "include_dirs": [
        "../lib/src/include"
      ],
      "conditions": [
        [
          "<(hasAL)",
          {
            "defines": [
              "USE_ASSEMBLYLINE"
            ]
          }
        ]
      ]
    },
    {
      "target_name": "measuresuite",
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
        "../lib/src/include",
        "./src/binding"
      ],
      "conditions": [
        [
          "<(hasAL)",
          {
            "libraries": [
              "<!(pkg-config --libs assemblyline)"
            ]
          }
        ]
      ]
    }
  ]
}
