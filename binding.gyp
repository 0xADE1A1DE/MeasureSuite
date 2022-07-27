{
  "targets": [
    {
      "target_name": "libmeasuresuite",
      "type": "static_library",
      "sources": [
        "./src/lib/checker.c",
        "./src/lib/evaluator.c",
        "./src/lib/measure_helper.c",
        "./src/lib/measuresuite.c",
        "./src/lib/ms_error_description.c",
        "./src/lib/printer.c",
        "./src/lib/randomizer.c",
        "./src/lib/timer.c"
      ],
      "include_dirs": [
        "./src/include"
      ]
    },
    {
      "target_name": "measureaddon",
      "sources": [
        "./src/binding/measuresuite_binding.c"
      ],
      "dependencies": [
        "libmeasuresuite"
      ],
      "include_dirs": [
        "./src/include",
        "./src/lib",
        "<(module_root_dir)/../../../bins/node/include"
      ],
      "libraries": [
        "-lassemblyline"
      ]
    }
  ]
}
